#pragma once

#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Core/Engine/Layer.hpp"
#include "Ramus/UI/Panels/SceneHierarchyPanel.hpp"
#include "Ramus/UI/Panels/InspectorPanel.hpp"
#include "Ramus/Core/Scene/Scene.hpp"

namespace ramus
{
    class AssetManager;
    class EditorLayer final : public Layer
    {
    public:
        EditorLayer(AssetManager* assetManager);
        ~EditorLayer() = default;

        void OnAttach(void* nativeWindow);
        void OnDetach();
        
        void BeginFrame();
        void EndFrame();
        
        void OnUpdate(float deltaTime) override {}
        void OnImGuiRender() override;

        void DrawAssetBrowser();

    private:
        std::shared_ptr<Scene> m_scene;
        SceneHierarchyPanel m_sceneHierarchyPanel;
        InspectorPanel m_inspectorPanel;

        AssetManager* m_assetManager;
        void* m_nativeWindow = nullptr;
    };
}