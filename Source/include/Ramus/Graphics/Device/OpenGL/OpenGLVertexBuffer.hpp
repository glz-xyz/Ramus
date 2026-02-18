#pragma once
#include "Ramus/Graphics/Device/OpenGL/OpenGLBuffer.hpp"
#include "Ramus/Graphics/GraphicsDefines.hpp"

#include <string>
#include <vector>

namespace ramus
{

    // [TODO] Should inherit from VertexBufferBase (and that from OpenGLBuffer)
    class OpenGLVertexBuffer : public OpenGLBuffer
    {
    public:
        struct Element 
        {
            std::string name;
            ShaderDataType type;
            uint32_t size;
            size_t offset;
            bool normalized;

            Element(ShaderDataType type, const std::string& name, bool normalized = false) :
                name(name), 
                type(type), 
                size(ShaderDataTypeSize(type)), 
                offset(0), 
                normalized(normalized) {}

            uint32_t GetComponentCount() const 
            { 
                return GetShaderDataTypeComponentCount(type);
            }
        };

        class Layout 
        {
        public:
            Layout() = default;
            Layout(const std::initializer_list<Element>& elements) : m_elements(elements) 
            {
                CalculateOffsetsAndStride();
            }

            uint32_t GetStride() const { return m_stride; }
            const std::vector<Element>& GetElements() const { return m_elements; }

            std::vector<Element>::iterator begin() { return m_elements.begin(); }
            std::vector<Element>::iterator end() { return m_elements.end(); }

            std::vector<Element>::const_iterator begin() const { return m_elements.begin(); }
            std::vector<Element>::const_iterator end() const { return m_elements.end(); }

        private:
            void CalculateOffsetsAndStride() 
            {
                size_t currentOffset = 0;
                m_stride = 0;
                for (auto& element : m_elements) 
                {
                    element.offset = currentOffset;
                    currentOffset += element.size;
                    m_stride += element.size;
                }
            }

            std::vector<Element> m_elements;
            uint32_t m_stride = 0;
        };

    public:
        OpenGLVertexBuffer(size_t size, const void* data, BufferFlags flags = BufferFlags::None)
            : OpenGLBuffer(size, data, flags) 
        {
        }

        void SetLayout(const Layout& layout) { m_layout = layout; }
        const Layout& GetLayout() const { return m_layout; }

    private:
        Layout m_layout;
    };

}