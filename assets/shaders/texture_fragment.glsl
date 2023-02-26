#version 300 es
precision mediump float;

out vec4 oFragColor;

in vec2 oTexCoords;

uniform sampler2D uTexture;

void main()
{
    oFragColor = texture(uTexture, oTexCoords);
}
