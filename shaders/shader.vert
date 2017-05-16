#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
out vec3 vertexNormal;
out vec3 fragPosition;
out vec2 textureCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
    textureCoords = texCoords;
    vec4 posv4 = vec4(position, 1.0);
    gl_Position = projection * view * model * posv4;
    fragPosition = vec3(model * posv4);
    vertexNormal = normal;
}
