#version 400

// Attributes passed from the geometry shader
in vec4 frag_color;
in vec2 tex_coord;

uniform float progress;

// Uniform (global) buffer
uniform sampler2D tex_samp;

void main (void)
{
		// Get pixel from texture
    vec4 outval = texture(tex_samp, tex_coord);


	if (progress > 0.5) {
		float darkening = progress - 0.5;
		outval.x -= darkening;
		outval.y -= darkening;
		outval.z -= darkening;
		outval.a -= darkening * 2;
	}

    // Set output fragment color
    gl_FragColor = outval;
}
