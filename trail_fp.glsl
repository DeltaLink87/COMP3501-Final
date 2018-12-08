#version 400

// Attributes passed from the geometry shader
in vec4 frag_color;
in vec2 tex_coord;

uniform float progress;
uniform int phase;

// Uniform (global) buffer
uniform sampler2D tex_samp;

void main (void)
{
		// Get pixel from texture
	float offset = frag_color.r;
	float t = mod(progress + offset, 1.0);
    vec4 outval = texture(tex_samp, tex_coord);
	outval.a = 0.3;

	if (t > 0.7) {
		outval.a -= t - 0.7;
	}
	if (phase == 1) {
		if (t > progress) {
			outval.a = 0;
		}
	} else if (phase==3) {
		if (t < progress || progress >= 1.0) {
			outval.a = 0;
		}
	}

    // Set output fragment color
    gl_FragColor = outval;
}
