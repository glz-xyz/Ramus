#include "Ramus/Graphics/Device/OpenGL/OpenGLBuffer.hpp"
#include "Ramus/Core/Services/Logger.hpp"

namespace ramus
{
   OpenGLBuffer::OpenGLBuffer(size_t size, const void* data, BufferFlags flags)
   {
      uint32_t handle;
      glCreateBuffers(1, &handle);

      uint32_t f = static_cast<uint32_t>(flags);
      GLbitfield glFlags = 0;
      if (f & static_cast<uint32_t>(BufferFlags::MapRead))  glFlags |= GL_MAP_READ_BIT;
      if (f & static_cast<uint32_t>(BufferFlags::MapWrite)) glFlags |= GL_MAP_WRITE_BIT;
      if (f & static_cast<uint32_t>(BufferFlags::Dynamic))  glFlags |= GL_DYNAMIC_STORAGE_BIT;
      if (f & static_cast<uint32_t>(BufferFlags::Client))   glFlags |= GL_CLIENT_STORAGE_BIT;

      glNamedBufferStorage(handle, static_cast<GLsizeiptr>(size), data, glFlags);

      GLint allocatedSize = 0;
      glGetNamedBufferParameteriv(handle, GL_BUFFER_SIZE, &allocatedSize);
      if (allocatedSize == 0) 
      {
          Logger::GetDeviceLogger()->error("Failed to allocate memory for Buffer {}", handle);
      }

      m_handle = OpenGLHandle<BufferDeleter>(handle);
   }

   OpenGLBuffer::~OpenGLBuffer()
   {

   }

}