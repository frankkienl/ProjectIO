#version 150

uniform sampler2D inTexture;

out vec4 outFragment;
in vec2 outTexCoord;
in vec4 outColour;

void main() {
	outFragment = mix(outColour, texture(inTexture, outTexCoord.st), 1.0);
}
