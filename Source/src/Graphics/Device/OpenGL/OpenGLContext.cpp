#include "Ramus/Graphics/Device/OpenGL/OpenGLContext.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLTexture.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLIndexBuffer.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexBuffer.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <glad/gl.h>

namespace ramus
{

    OpenGLContext::OpenGLContext()
    {
        
    }

    OpenGLContext::~OpenGLContext()
    {
        Logger::GetRendererLogger()->info("OpenGL context destroyed.");
    }

    void OpenGLContext::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    void OpenGLContext::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLContext::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void OpenGLContext::SetTexture(uint32_t slot, TextureBase* texture)
    {
        assert(texture);

        auto* glTex = static_cast<OpenGLTexture*>(texture);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, glTex->GetHandle());
    }

    void OpenGLContext::SetVertexBuffer(VertexBufferBase* vbo)
    {

    }

    void OpenGLContext::SetIndexBuffer(IndexBufferBase* ibo)
    {

    }

    void OpenGLContext::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) 
    {

    }

    void OpenGLContext::BindGeometry(DeviceResource* resource)
    {
        if (resource)
        {
            auto* glMesh = static_cast<OpenGLMesh*>(resource);
            glMesh->Bind();
        }
        else
        {
            assert(false && "Attempting to bind a null geometry resource!");
            return;
        }
    }

    void OpenGLContext::UnbindGeometry()
    {
        glBindVertexArray(0);
    }

    void OpenGLContext::DrawIndexed(uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
}