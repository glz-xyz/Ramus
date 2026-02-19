#pragma once

namespace ramus
{
    class ImGuiLayer final
    {
    public:
        ImGuiLayer() = default;

        void OnAttach(void* nativeWindow);
        void OnDetach();
        
        void BeginFrame();
        void EndFrame();
        
        void OnImGuiRender(); 

    private:
        void* m_nativeWindow = nullptr;
    };
}