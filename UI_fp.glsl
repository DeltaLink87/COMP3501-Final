#version 130

// Passed from the vertex shader
in vec2 uv0;

// Passed from outside
uniform float timer;
uniform sampler2D texture_map;

// Attributes passed from the vertex shader
in vec3 position_interp;
in vec3 normal_interp;
in vec4 color_interp;
in vec2 uv_interp;
in vec3 light_pos;


void main() 
{
    // wavering
    vec2 pos = uv0;
    pos.x = pos.x + 0.05*(sin(timer*0.0+0.0*pos.y));

    vec4 pixel = texture(texture_map, pos);

	// Retrieve texture value
    vec4 tex = texture(texture_map, uv_interp);

    
    gl_FragColor = pixel;
}
