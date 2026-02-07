#pragma once

#include "ramus/Resources/IResourceService.hpp"

namespace ramus
{

    class ServiceLocator
    {
    public:
        static IResourceService* GetResources() { return m_resourceService; }
        static void Provide(IResourceService* resourceService) { m_resourceService = resourceService; }

    private:
        static inline IResourceService* m_resourceService;
    };

}