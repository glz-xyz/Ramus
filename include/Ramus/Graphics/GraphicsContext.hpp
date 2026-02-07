#pragma once

struct GLFWwindow;

namespace ramus 
{

    class GraphicsContext
    {
    public:
        GraphicsContext(struct GLFWwindow* nativeHandle);

        void MakeCurrent();
        void SwapBuffers();

        void SetVSync(const bool enabled);

    private:
        GLFWwindow* m_nativeWindow;
    };

}