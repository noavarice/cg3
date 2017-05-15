#version 330
in vec3 vertexNormal;
in vec3 fragPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
out vec3 color;

void main(void)
{
    vec3 norm = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    vec3 diffuse = max(dot(norm, lightPosition), 0.5f) * lightColor;
    color = diffuse * objectColor;
}
