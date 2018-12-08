#version 400

// Attributes passed from the geometry shader
in vec4 frag_color;
in vec2 tex_coord;
in float time;

uniform float progress;

// Uniform (global) buffer
uniform sampler2D tex_samp;

void main (void)
{
		// Get pixel from texture
    vec4 outval = texture(tex_samp, tex_coord);

	if (outval.a ==0) {
		discard;
	}

	if (time >= 0.5) {
		outval.a = 0;
	} else {
		outval.a = 0.5;
	}

    // Set output fragment color
    gl_FragColor = outval;
}
