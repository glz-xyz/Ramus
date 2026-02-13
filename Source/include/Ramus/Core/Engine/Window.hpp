#pragma once

#include <string>
#include <memory>

namespace ramus
{
    struct WindowSettings
    {
        std::string title = "Ramus Engine";
        int width = 800;
        int height = 600;
    };
    
    class Window
    {
    public:
        Window(const WindowSettings& settings);
        ~Window();

        void HandleEvents();
        bool IsOpen() const;
        void Display();

        void* GetNativeHandle();

    private:
        std::string m_title;
        void* m_nativeHandle;
    };

}