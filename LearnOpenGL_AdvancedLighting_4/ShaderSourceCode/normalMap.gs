#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec3 lightPos;
uniform vec3 viewPos;

out VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} gs_in[];

out GS_OUT
{
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} gs_out;

void main()
{
    vec3 nm = (0.0, 0.0, 1.0);

    vec3 tangent1;
    vec3 bitangent1;

    vec3 edge1 = gl_in[1] - gl_in[0];
    vec3 edge2 = gl_in[2] - gl_in[0];

    vec2 deltaUV1 = gs_in[1].TexCoords - gs_in[0].TexCoords;
    vec2 deltaUV2 = gs_in[2].TexCoords - gs_in[0].TexCoords;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = normalize(bitangent1);


}