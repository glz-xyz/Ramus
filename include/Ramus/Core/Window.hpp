#pragma once

#include "Ramus/Graphics/GraphicsContext.hpp"

#include <string>
#include <memory>

struct GLFWwindow;

namespace ramus
{

    class Window
    {
    public:
        Window(const std::string& title, int width, int height);
        ~Window();

        void HandleEvents();
        bool IsOpen() const;
        void Display();

    private:
        std::string m_title;
        GLFWwindow* m_nativeWindow;
        std::unique_ptr<GraphicsContext> m_graphicsContext;
    };

}