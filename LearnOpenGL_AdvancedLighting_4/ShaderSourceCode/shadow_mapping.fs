#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // (-1, 1)
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // (-1, 1) -> (0, 1)
    projCoords = projCoords * 0.5 + 0.5;

    // 若物体比远平面还远，直接返回不在阴影中
    if(projCoords.z > 1.0)
    {
        //shadow = 0.0;
        return 0.0;
    }

    // 这个 r 到底是啥？？？
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    float currentDpeth = projCoords.z;

    //float bias = 0.005;
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); // 用于阴影偏移
    
    float shadow = 0.0;
    //float shadow = (currentDpeth - bias) > closestDepth ? 1.0 : 0.0;
    // 对周围像素采样，减少阴影边缘的锯齿
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += (currentDpeth - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    

    return shadow;
}

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.4);
    // ambient
    vec3 ambient = 0.2 * lightColor;
    // diffues
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular 这里用的是 blinn-phone 模型
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    //vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir); // 半角向量
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;

    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir);
    shadow = min(shadow, 0.75);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0f);
}