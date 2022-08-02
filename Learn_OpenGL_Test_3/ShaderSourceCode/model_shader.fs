#version 330 core
out vec4 FragColor;

struct Material
{
	// 一般情况下，ambient和diffuse相等，直接用diffuse即可
	//vec3 ambient;
	sampler2D diffuse1;
	sampler2D specular1;
	float shininess;
};

// 定向光
struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform Material material;
uniform DirLight light;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{    
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    // 反射
    //vec3 R = reflect(I, normalize(Normal));
    // 折射
    vec3 R = refract(I, normalize(Normal), ratio);

    // 模型原有的贴图
    FragColor = texture(material.diffuse1, TexCoords);
    // 反射或折射天空盒
    //FragColor = vec4(texture(skybox, R).rgb, 1.0);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(cameraPos - Position);
    vec3 result = CalcDirLight(light, norm, viewDir);

    vec3 col = texture(skybox, R).rgb * vec3(texture(material.specular1, TexCoords));
    //FragColor = vec4(col + result, 1.0);

    //FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    // 漫反射
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
    // 合并
    return (ambient + diffuse + specular);
}