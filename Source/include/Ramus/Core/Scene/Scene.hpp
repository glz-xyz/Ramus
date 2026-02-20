#pragma once

#include <entt/entt.hpp>
#include <string>

namespace ramus
{
    class Entity;
    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());

        void OnUpdateEditor(float deltaTime);
        void OnRender();

    private:
        entt::registry m_Registry;

        friend class Entity;
    };
}