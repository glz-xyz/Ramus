#pragma once
#include <string>

struct GLFWwindow;

namespace ramus
{

    class AppWindow
    {
    public:
        AppWindow(const std::string& title, int width, int height);
        ~AppWindow();

        void HandleEvents();
        bool ShouldClose() const;
        void SwapBuffers();

    private:
        std::string m_title;
        GLFWwindow* m_nativeWindow;
    };

}