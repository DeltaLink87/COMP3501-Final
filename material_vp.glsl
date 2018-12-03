#version 130

// Vertex buffer
in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec3 color;

// Uniform (global) buffer
uniform vec3 position;
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;
uniform mat4 normal_mat;
uniform vec3 light1Pos;
uniform vec3 light2Pos;
uniform vec3 light3Pos;
uniform vec3 light4Pos;
uniform vec3 light5Pos;

// Attributes forwarded to the fragment shader
out vec4 color_interp;
out vec2 uv_interp;
out vec3 normal_interp;
out vec3 position_interp;
out vec3 light1_pos;
out vec3 light2_pos;
out vec3 light3_pos;
out vec3 light4_pos;
out vec3 light5_pos;

vec3 light_position = vec3(-0.5, -0.5, 1.5);

void main()
{
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);

    color_interp = vec4(color, 1.0);

	uv_interp = uv;

	position_interp = vec3(view_mat * world_mat * vec4(vertex, 1.0));

	// Transform normal
    normal_interp = vec3(normal_mat * vec4(normal, 0.0));

    // Transform light position to align with view
    light1_pos = vec3(view_mat * vec4(light1Pos, 1.0));
	light2_pos = vec3(view_mat * vec4(light2Pos, 1.0));
	light3_pos = vec3(view_mat * vec4(light3Pos, 1.0));
	light4_pos = vec3(view_mat * vec4(light4Pos, 1.0));
	light5_pos = vec3(view_mat * vec4(light5Pos, 1.0));
}
