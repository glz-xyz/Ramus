#pragma once

namespace ramus
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        virtual void SetVSync(bool enabled) = 0;
    };
}