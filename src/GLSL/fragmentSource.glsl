#version 330 core
in vec2 TexCoords;
out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    colour = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}