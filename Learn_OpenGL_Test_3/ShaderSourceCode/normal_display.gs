/*#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT
{
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.4;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    for(int i = 0; i < 3; i++)
    {
        GenerateLine(i);
    }
}*/

#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];


uniform float time;

const float MAGNITUDE = 0.4;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    vec3 normal = GetNormal();

    vec4 tmp_position;

    for(int i = 0; i < 3; i++)
    {
        tmp_position = explode(gl_in[i].gl_Position, normal);
        gl_Position = tmp_position;
        EmitVertex();
        gl_Position = tmp_position + vec4(gs_in[i].normal, 0.0) * MAGNITUDE;
        EmitVertex();

        EndPrimitive();
    }


    
}