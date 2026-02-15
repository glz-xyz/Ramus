#version 460 core

layout(location = 0) in vec2 vTexCoord;
layout(binding = 0) uniform sampler2D uTexture;
layout(location = 0) out vec4 fragColor;

void main() 
{
    vec4 color = texture(uTexture, vTexCoord);
    
    if(color.a < 0.1) 
    {
        discard;
    }
    
    fragColor = color;
}