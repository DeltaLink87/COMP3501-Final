#version 400
#define M_PI 3.1415926535897932384626433832795

// Vertex buffer
in vec3 vertex;
in vec3 normal;
in vec3 color; //Actually contains a number between 0 and 1 in the R variable

// Uniform (global) buffer
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform float timer;
uniform float progress;
uniform int phase;

// Attributes forwarded to the geometry shader
out vec3 vertex_color;
out float timestep;

// Simulation parameters (constants)
float speed = 3.0; // Allows to control the speed at which 


void main()
{
    float offset = color.r; //Number between 0 and 1 that indicates when a particle starts
    float t = mod(progress + offset, 1.0); // Our time parameter
    
    // Let's first work in model space (apply only world matrix)
    vec4 position = world_mat * vec4(vertex, 1.0);
    vec4 norm = normal_mat * vec4(normal, 1.0);

    position.x += norm.x*sin(t * 2 * M_PI)*speed / 5.0;
    position.y += t*speed;
    position.z += norm.z*cos(t * 2 * M_PI)*speed / 5.0;
    
    // Now apply view transformation
    gl_Position = view_mat * position;
        
    // Define outputs
    // Define color of vertex
    vertex_color = color.rgb; // Color defined during the construction of the particles
	vertex_color.r = offset;

    // Forward time step to geometry shader
    timestep = t;
}
