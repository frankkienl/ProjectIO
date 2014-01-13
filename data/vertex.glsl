#version 150

uniform mat4x4 inViewMatrix;
uniform mat4x4 inModelMatrix;
uniform mat4x4 inProjectionMatrix;

in vec4 inVertex;
in vec2 inTexCoord;
in vec4 inColour;
smooth out vec2 outTexCoord;
out vec4 outColour;

void main() {
    gl_Position = inVertex * inModelMatrix * inViewMatrix * inProjectionMatrix;
    outColour = inColour;
    outTexCoord = inTexCoord;
}
