#pragma once

namespace ramus
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnImGuiRender() = 0; 
        //virtual void OnEvent(Event& event) = 0;

    private:
        
    };
}