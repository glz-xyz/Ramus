#pragma once

#include "Ramus/Core/Scene/Scene.hpp"
#include "Ramus/Core/Scene/Entity.hpp"
#include <memory>

namespace ramus 
{

    class SceneHierarchyPanel 
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const std::shared_ptr<Scene>& context);

        void SetContext(const std::shared_ptr<Scene>& context);
        void OnImGuiRender();

        Entity GetSelectedEntity() const { return m_selectedEntity; }
        void SetSelectedEntity(Entity entity) { m_selectedEntity = entity; }

    private:
        void DrawEntityNode(Entity entity);

    private:
        std::shared_ptr<Scene> m_scene;
        Entity m_selectedEntity;
    };

}