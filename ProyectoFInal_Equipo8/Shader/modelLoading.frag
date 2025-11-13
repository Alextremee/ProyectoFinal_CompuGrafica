#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1; // textura principal
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int transparency; // 1 = activar transparencia, 0 = ignorar

void main()
{
    // Normal e iluminación básica
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Color de la textura
    vec4 texColor = texture(texture_diffuse1, TexCoords);

    // Aplicamos luz básica al color
    vec3 result = diffuse * texColor.rgb;
    FragColor = vec4(result, texColor.a);

    // Descartar píxeles transparentes
    if (FragColor.a < 0.1 && transparency == 1)
        discard;
}
