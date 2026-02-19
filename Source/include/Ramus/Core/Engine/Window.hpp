#pragma once

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

        void* GetNativeHandle() const { return m_nativeHandle; }
        int GetWidth() const { return m_settings.width; }
        int GetHeight() const { return m_settings.height; }
        float GetAspectRatio() const;

    private:
        WindowSettings m_settings;
        void* m_nativeHandle;
    };

}