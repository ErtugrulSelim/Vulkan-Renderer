#version 450

vec2 positions[4] = vec2[](
    vec2(-0.05,  0.05), // 0: Sol Alt
    vec2( 0.05,  0.05), // 1: Sað Alt
    vec2(-0.05, -0.05), // 2: Sol Üst
    vec2( 0.05, -0.05)  // 3: Sað Üst
);

vec3 colors[4] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 0.5, 0.0),
	vec3(0.0, 0.0, 1.0),
	vec3(0.5, 0.5, 0.0)
);

layout (push_constant) uniform constants {
	mat4 model;
}ObjectData;

layout(location = 0) out vec3 fragColor;

void main() {
	gl_Position = ObjectData.model * vec4(positions[gl_VertexIndex], 0.0, 1.0);
	fragColor = colors[gl_VertexIndex];
}	