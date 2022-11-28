#version 330 core
in vec2 tex_coords;
out vec4 colour;

uniform sampler2D image;
uniform vec3 sprite_colour;

void main()
{
    colour = vec4(sprite_colour, 1.0) * texture(image, tex_coords);
}