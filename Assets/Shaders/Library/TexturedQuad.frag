#version 460 core

layout(location = 0) in vec2 v_texCoord;

layout(binding = 0) uniform sampler2D u_diffuse;

layout(location = 0) out vec4 f_color;


void main() 
{
    vec4 color = texture(u_diffuse, v_texCoord);
    
    if(color.a < 0.1) 
    {
        discard;
    }
    
    f_color = color;
}