#pragma once

#include "Ramus/Core/Scene/Scene.hpp"
#include <entt/entt.hpp>

namespace ramus
{
    class Scene;
    class Entity 
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene)
            : m_handle(handle), m_scene(scene) {}

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            return m_scene->m_Registry.emplace<T>(m_handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            return m_scene->m_Registry.get<T>(m_handle);
        }

        template<typename T>
        bool HasComponent() {
            return m_scene->m_Registry.any_of<T>(m_handle);
        }

        operator bool() const { return m_handle != entt::null; }
        operator entt::entity() const { return m_handle; }
        operator uint32_t() const { return (uint32_t)m_handle; }

        bool operator==(const Entity& other) const { 
            return m_handle == other.m_handle && m_scene == other.m_scene; 
        }

    private:
        entt::entity m_handle{ entt::null };
        Scene* m_scene = nullptr; 
    };
}