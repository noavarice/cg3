#version 330
in vec3 vertexNormal;
in vec3 fragPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPosition1;
uniform vec3 lightColor1;
out vec3 color;

void main(void)
{
    vec3 norm = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    vec3 diffuse = max(dot(norm, lightPosition), 0.1f) * lightColor;
    vec3 lightDirection1 = normalize(lightPosition1 - fragPosition);
    vec3 diffuse1 = max(dot(norm, lightPosition1), 0.1f) * lightColor1;
    color = (diffuse + diffuse1) * objectColor;
}
