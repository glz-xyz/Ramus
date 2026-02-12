#pragma once

#include "Ramus/Graphics/RHI/GraphicsContext.hpp"

namespace ramus 
{

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(void* nativeWindow);
        ~OpenGLContext();

        void Init() override;
        void SwapBuffers() override;
        void SetVSync(const bool enabled) override;;

    private:
        void* m_nativeWindow;
    };

}