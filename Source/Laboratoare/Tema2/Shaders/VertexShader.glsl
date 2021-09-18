#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 color;

// TODO: output values to fragment shader
out vec3 frag_color;

void main()
{
	// TODO: send output to fragment shader
	frag_color = color;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
