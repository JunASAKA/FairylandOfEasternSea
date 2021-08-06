#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 texScale;
uniform mat4 texTrans;

void main()
{
    TexCoords = (texTrans*texScale*vec4(vertex.zw,0.0,1.0)).xy;
    //TexCoords = vertex.zw;
    //TexCoords = (id*vec4(vertex.zw,1.0,0.0)).xy;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}