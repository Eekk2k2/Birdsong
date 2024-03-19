#version 430 core
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
//    vec3 WorldPos;
    vec3 Normal;
    vec3 FragPos;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D albedoMap;
uniform sampler2D shadowMaps[1];

uniform vec3 eyePos;

uniform vec3 lightPositions[1];
uniform vec3 lightColors[1];

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMaps[0], projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    vec3 lightDir = normalize(lightPositions[0] - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);
//    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;  
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMaps[0], 0);
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            float pcfDepth = texture(shadowMaps[0], projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}  

void main() {
    vec3 color = texture(albedoMap, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(1.0);
    // ambient
    vec3 ambient = 0.15 * lightColor;
    
    // diffuse
    vec3 lightDir = normalize(lightPositions[0] - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    vec3 viewDir = normalize(eyePos - fs_in.FragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
//FragColor = vec4(diffuse, 1.0);

//    FragColor = texture(shadowMaps[0], fs_in.TexCoords).rgba;
}

//#version 430 core
//
//out vec4 FragColor;
//
//in vec2 TexCoords;
//in vec3 WorldPos;
//in vec3 Normal;
//
//uniform vec3 eyePos;
//
//uniform sampler2D albedoMap;
//uniform sampler2D normalMap;
//uniform sampler2D metallicMap;
//uniform sampler2D roughnessMap; 
//uniform sampler2D aoMap; 
//
//uniform vec3 lightPositions[1];
//uniform vec3 lightColors[1];
//
//const float PI = 3.14159265359;
//
//vec3 getNormalFromMap()
//{
//    vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0;
//
//    vec3 Q1  = dFdx(WorldPos);
//    vec3 Q2  = dFdy(WorldPos);
//    vec2 st1 = dFdx(TexCoords);
//    vec2 st2 = dFdy(TexCoords);
//
//    vec3 N   = normalize(Normal);
//    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
//    vec3 B  = -normalize(cross(N, T));
//    mat3 TBN = mat3(T, B, N);
//
//    return normalize(TBN * tangentNormal);
//}
//
//vec3 fresnelSchlick(float cosTheta, vec3 F0) {
//	return F0 + (1.0f - F0) * pow(clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
//}
//
//float DistributionGGX(vec3 N, vec3 H, float roughness)
//{
//    float a = roughness*roughness;
//    float a2 = a*a;
//    float NdotH = max(dot(N, H), 0.0);
//    float NdotH2 = NdotH*NdotH;
//
//    float nom   = a2;
//    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
//    denom = PI * denom * denom;
//
//    return nom / denom;
//}
//
//float GeometrySchlickGGX(float NdotV, float roughness)
//{
//    float r = (roughness + 1.0);
//    float k = (r*r) / 8.0;
//
//    float nom   = NdotV;
//    float denom = NdotV * (1.0 - k) + k;
//
//    return nom / denom;
//}
//
//float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
//{
//    float NdotV = max(dot(N, V), 0.0);
//    float NdotL = max(dot(N, L), 0.0);
//    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
//    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
//
//    return ggx1 * ggx2;
//}
//
//void main() {
//    vec3 albedoRaw = texture(albedoMap, TexCoords).rgb;
//    vec3 albedo     = vec3(pow(albedoRaw.x, 2.2), pow(albedoRaw.y, 2.2), pow(albedoRaw.z, 2.2));
//    vec3 normal     = getNormalFromMap();
//    float metallic  = texture(metallicMap, TexCoords).r;
//    float roughness = texture(roughnessMap, TexCoords).r;
//    float ao        = texture(aoMap, TexCoords).r;
//
//	vec3 N = normalize(Normal);
//	vec3 V = normalize(eyePos - WorldPos);
//
//	vec3 F0 = vec3(0.04f);
//	F0		= mix(F0, albedo, metallic);
//
//	vec3 Lo = vec3(0.0f);
//	for (int i = 0; i < 1; i++) { // We currently only have one light
//        vec3 L = normalize(lightPositions[i] - WorldPos);
//        vec3 H = normalize(V + L);
//        float m_distance = length(lightPositions[i] - WorldPos);
//        float attenuation = 1.0 / (m_distance * m_distance);
//        vec3 radiance = lightColors[i] * attenuation;
//
//        float NDF = DistributionGGX(N, H, roughness);   
//        float G   = GeometrySmith(N, V, L, roughness);      
//        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
//
//        vec3 numerator = NDF * G * F;
//        float denominator = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.0001;
//        vec3 specular = numerator / denominator;
//
//        vec3 kS = F;
//        vec3 kD = vec3(1.0f) - kS;
//
//        kD *= 1.0 - metallic;
//
//        float NdotL = max(dot(N, L), 0.0f);
//        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
//	}
//
//    vec3 ambient = vec3(0.03) * albedo * ao;
//    vec3 color = ambient + Lo;
//
//    // HDR tonemapping
//    color = color / (color + vec3(1.0));
//    // gamma correct
//    color = pow(color, vec3(1.0/2.2));
//
//    FragColor = vec4(color, 1.0f);
//}