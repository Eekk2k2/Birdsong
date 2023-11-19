#version 330 core
out vec4 FragColor;
 
uniform vec3 ambientColor;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    float m_distance = length(lightPosition - FragPos);
    float attenuation = 1.0f / m_distance * m_distance;

    // Diffuse Shading
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(lightDir, normalize(Normal)), 0.0f);
    vec3 diffuse = diff * lightColor * attenuation;
    
    vec4 fragColor = vec4(diffuse, 1.0f) * texture(texture1, TexCoord);
    FragColor.rgb = pow(fragColor.rgb, vec3(1.0f/2.2f)); // Gamma correction
}