#include "Ramus/Core/Scene/Scene.hpp"
#include "Ramus/Core/Scene/Entity.hpp"
#include "Ramus/Core/Scene/Components.hpp"

namespace ramus
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();
        entity.AddComponent<TagComponent>(name.empty() ? "Entity" : name);
        return entity;
    }
}