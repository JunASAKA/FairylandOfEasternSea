#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 tex_scale;
uniform mat4 tex_trans;

void main()
{
    tex_coords = (tex_trans*tex_scale*vec4(vertex.zw,0.0,1.0)).xy;
    //tex_coords = vertex.zw;
    //tex_coords = (id*vec4(vertex.zw,1.0,0.0)).xy;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}