#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_modelViewProj;

/*
[TODO] UBO
layout (std140, binding = 0) uniform CameraBlock 
{
    mat4 u_ViewProjection;
};
*/

layout(location = 0) out vec2 v_texCoord;

void main() 
{
    v_texCoord = a_texCoord;
    gl_Position = u_modelViewProj * vec4(a_position, 1.0);
}