#version 450

// vulkan NDC:	x: -1(left), 1(right)
//				y: -1(top), 1(bottom)

vec2 positions[4] = vec2[](
    vec2(-0.5,  0.5), // 0: Sol Alt
    vec2( 0.5,  0.5), // 1: Sað Alt
    vec2(-0.5, -0.5), // 2: Sol Üst
    vec2( 0.5, -0.5)  // 3: Sað Üst
);

vec3 colors[4] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 0.5, 0.0),
	vec3(0.0, 0.0, 1.0),
	vec3(0.5, 0.5, 0.0)
);

layout(location = 0) out vec3 fragColor;

void main() {
	gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
	fragColor = colors[gl_VertexIndex];
}