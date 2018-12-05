#version 130

// Attributes passed from the vertex shader

uniform int lightNum;
uniform float reflectivity;
uniform float roughness;

in vec4 color_interp;
in vec2 uv_interp;
in vec3 position_interp;
in vec3 normal_interp;
in vec3 light1_pos;
in vec3 light2_pos;
in vec3 light3_pos;
in vec3 light4_pos;
in vec3 light5_pos;

uniform float light1Range;
uniform float light2Range;
uniform float light3Range;
uniform float light4Range;
uniform float light5Range;

uniform vec3 light1Specular;
uniform vec3 light2Specular;
uniform vec3 light3Specular;
uniform vec3 light4Specular;
uniform vec3 light5Specular;

void illumination(in vec3 position, in vec3 normal, in vec3 lightPosition, in float range, in vec3 ambientColor, in vec3 diffuseColor, in vec3 specularColor, in float roughness, in float intensity, out vec3 illumination);

// General constants
float pi = 3.1415926535897932;

// Material attributes (constants)

// Blue metal
// Needs environment illumination (ambient term)
vec3 diffuse_color = vec3(0.1, 0.1, 0.1);
vec3 specular_color = vec3(0.2, 0.2, 0.95);
vec3 ambient_color = specular_color*0.3;

// Copper
//vec3 diffuse_color = vec3(0.0, 0.0, 0.0);
//vec3 specular_color = vec3(0.95, 0.64, 0.54);
//vec3 ambient_color = specular_color*0.3;

float light_intensity = 0.5*pi;

uniform sampler2D texture_map;
uniform samplerCube env_map;

void illumination(in vec3 position, in vec3 normal, in vec3 lightPosition, in float range, in vec3 ambientColor, in vec3 diffuseColor, in vec3 specularColor, in float roughness, in float intensity, out vec3 illumination) 
{
	vec3 N, // Interpolated normal for fragment
         L, // Light-source direction
         V, // View direction
         H; // Half-way vector

    // Initialize input quantities
    N = normalize(normal);

    L = (lightPosition - position);
    L = normalize(L);

    // V = (eye_position - position_interp);
    V = - position; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

    //H = 0.5*(V + L); // Halfway vector
    H = (V + L); // Halfway vector
    H = normalize(H);

    // Compute useful quantities
    float NH = max(dot(N, H), 0.0);
    float LH = max(dot(L, H), 0.0);
    float NL = max(dot(N, L), 0.0);

    // Compute shading model
    // Diffuse term (subsurface scattering)
    vec3 diffuse = diffuseColor / pi;

	vec3 vectorBetween = lightPosition - position;

	float distance = length(vectorBetween);

	float rangeFalloffFactor;

	if (distance <= range) {
		rangeFalloffFactor = 1.0;
	} else if (distance - range >= range) {
		rangeFalloffFactor = 0.0;
	} else {
		rangeFalloffFactor = min(1.0, (range * 2 - distance) / range);
	}

    // Microfacet geometry
    // Fresnel term
    vec3 fresnel = specularColor + (vec3(1.0, 1.0, 1.0) - specularColor)*pow(1 - LH, 5.0);
    // GGX distribution function
    float denom = NH*NH*(roughness*roughness - 1.0) + 1.0;
    float ndist = roughness / (pi*denom*denom);
    // Microfacet term: assume implicit geometry function
    vec3 mfacet = fresnel * (ndist / 4.0);

    // Full illumination
    illumination = ambientColor + (diffuse + mfacet)*intensity*NL*rangeFalloffFactor;

	// Compute indirect lighting
	// Reflection vector
	vec3 Lr = 2.0 * NL * N - L;
	// Query environment map
	vec4 il = texture(env_map, Lr);
	// Add pixel value to the illumination
	// Modulate influence of environment light by reflective surface value between 0 and 1
	float reflectValue = max(0.0, min(1.0, reflectivity));
	illumination += reflectValue*il.xyz;
}

void main() 
{
	gl_FragColor = color_interp;

	vec4 pixel = texture(texture_map, uv_interp);
	gl_FragColor = pixel;
	//gl_FragColor = vec4(0.6, 0.6, 0.6, 1.0);

	if (lightNum == 0) {
		gl_FragColor = pixel;
	} else {
		diffuse_color.r = pixel.r;
		diffuse_color.g = pixel.g;
		diffuse_color.b = pixel.b;

		ambient_color.r = pixel.r * 0.1;
		ambient_color.g = pixel.g * 0.1;
		ambient_color.b = pixel.b * 0.1;

		vec3 illum1 = vec3(0.0, 0.0, 0.0);
		vec3 illum2 = vec3(0.0, 0.0, 0.0);
		vec3 illum3 = vec3(0.0, 0.0, 0.0);
		vec3 illum4 = vec3(0.0, 0.0, 0.0);
		vec3 illum5 = vec3(0.0, 0.0, 0.0);

		illumination(position_interp, normal_interp, light1_pos, light1Range, ambient_color, diffuse_color, light1Specular, roughness, light_intensity, illum1);
		if (lightNum > 1) {
			illumination(position_interp, normal_interp, light2_pos, light2Range, ambient_color, diffuse_color, light2Specular, roughness, light_intensity, illum2);
		}

		if (lightNum > 2) {
			illumination(position_interp, normal_interp, light3_pos, light3Range, ambient_color, diffuse_color, light3Specular, roughness, light_intensity, illum3);
		}

		if (lightNum > 3) {
			illumination(position_interp, normal_interp, light4_pos, light4Range, ambient_color, diffuse_color, light4Specular, roughness, light_intensity, illum4);
		}

		if (lightNum > 4) {
			illumination(position_interp, normal_interp, light5_pos, light5Range, ambient_color, diffuse_color, light5Specular, roughness, light_intensity, illum5);
		}

		vec3 illum = illum1 + illum2 + illum3 + illum4 + illum5;

		// Assign illumination to the fragment
		gl_FragColor = vec4(illum, 1.0);
	}

}
