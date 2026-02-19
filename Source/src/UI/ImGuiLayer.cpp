#include "Ramus/UI/ImGuiLayer.hpp"

#include <glfw/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace ramus
{

    void ImGuiLayer::OnAttach(void* nativeWindow)
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
        ImGui_ImplOpenGL3_Init("#version 410"); // Match your shader version
    }

    void ImGuiLayer::BeginFrame() 
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::EndFrame() 
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

    void ImGuiLayer::OnDetach() 
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnImGuiRender() 
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(300, viewport->Size.y));
        
        ImGui::Begin("Inspector");
            ImGuiID dock_id = ImGui::GetID("InspectorDockSpace");
            ImGui::DockSpace(dock_id, ImVec2(0, 0));
        ImGui::End();

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
    }
}