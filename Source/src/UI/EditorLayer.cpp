#include "Ramus/UI/EditorLayer.hpp"
#include "Ramus/Assets/AssetManager.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <filesystem>
namespace fs = std::filesystem;
#include <ranges>
namespace rv = std::ranges::views;

namespace ramus
{

    EditorLayer::EditorLayer(AssetManager* assetManager) :
        m_assetManager(assetManager)
    {
        
    }

    void EditorLayer::OnAttach(void* nativeWindow)
    {
        m_nativeWindow = nativeWindow;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(m_nativeWindow), true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void EditorLayer::BeginFrame() 
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EditorLayer::EndFrame() 
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_nativeWindow);
        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = winWidth;
        io.DisplaySize.y = winHeight;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
        {
            GLFWwindow* contextBackup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(contextBackup);
        }
    }

    void EditorLayer::OnDetach() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorLayer::OnImGuiRender() 
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(300, viewport->Size.y));
        
        // INSPECTOR
        ImGui::Begin("Inspector");
            ImGuiID dock_id = ImGui::GetID("InspectorDockSpace");
            ImGui::DockSpace(dock_id, ImVec2(0, 0));
        ImGui::End();

        // TRANSFORM
        static glm::vec3 translation, rotation, scale;
        ImGui::Begin("Transform");
        if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::DragFloat3("Position", &translation.x, 0.1f);
            ImGui::DragFloat3("Rotation", &rotation.x, 0.5f);
            ImGui::DragFloat3("Scale", &scale.x, 0.1f);
        
            if (ImGui::Button("Reset Transform")) 
            {
                translation = glm::vec3(0.0f);
                rotation = glm::vec3(0.0f);
                scale = glm::vec3(1.0f);
            }
        }
        ImGui::End();

        DrawAssetBrowser();

        //if (m_assetManager->IsLoading()) {
        //    // Center the window
        //    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        //    
        //    ImGui::Begin("Loading...", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        //    
        //    float progress = m_AssetManager->GetLoadingProgress();
        //    // (Fraction 0.0-1.0, size (-1 is full width), overlay text)
        //    ImGui::ProgressBar(progress, ImVec2(300, 0.0f), "Extracting Geometry...");
        //    
        //    ImGui::End();
        //}
    }

    void EditorLayer::DrawAssetBrowser()
    {
        ImGui::Begin("Asset Browser");

        static fs::path currentDisplayPath = Engine::GetAssetsPath();
        static const std::vector<std::string> supported = { ".gltf", ".glb", ".png", ".jpg" };

        // "Back" button to escape folders
        if (currentDisplayPath != Engine::GetAssetsPath()) {
            if (ImGui::Button(".. Up")) {
                currentDisplayPath = currentDisplayPath.parent_path();
            }
            ImGui::Separator();
        }

        try {
            // C++20 Filter Pipeline
            auto asset_view = fs::directory_iterator(currentDisplayPath) 
                | rv::filter([&](const fs::directory_entry& entry) {
                    try {
                        if (entry.is_directory()) return true;

                        // Safe extension check
                        auto ext = entry.path().extension().string();
                        std::ranges::transform(ext, ext.begin(), [](unsigned char c){ return std::tolower(c); });
                        return std::ranges::any_of(supported, [&](const std::string& s) { 
                            return s == ext; 
                        });
                    } catch (...) { return false; }
                });

            for (const auto& entry : asset_view) {
                const auto& path = entry.path();
                std::string filename = path.filename().string();

                if (entry.is_directory()) {
                    if (ImGui::Selectable(("[DIR] " + filename).c_str())) {
                        currentDisplayPath /= path.filename();
                    }
                } else {
                    if (ImGui::Selectable(filename.c_str())) {
                        // Use generic_string to ensure forward slashes and bypass ANSI issues
                        m_assetManager->LoadModel(path.generic_string());
                    }
                }
            }
        } catch (const std::exception& e) {
            // This catches the "No mapping for Unicode" if it happens during iteration
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Folder contains incompatible characters.");
            if (ImGui::Button("Return to Root")) currentDisplayPath = Engine::GetAssetsPath();
        }

        ImGui::End();
    }
}