#version 330

layout(location = 0) in vec3 v_position;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float Time;

// Output value to fragment shader
out vec3 color;

void main()
{
	color = object_color;
	float pi = 3.14159;
	float dist = length(v_position);
	float dx = cos(2 * pi * dist + Time);
	float dy = 0.3f * sin(23 * pi * dist + 2 * Time);
	float dz = sin(2 * pi * dist + Time);
	vec3 pos = vec3(v_position.x * 2, v_position.y * 1.5, v_position.z * 3);
	gl_Position = Projection * View * Model * vec4(pos, 1.0);
}