#version 330
 
// get values from fragment shader
in vec3 color;
 
layout(location = 0) out vec4 out_color;
 
void main()
{
    out_color = vec4(0.5, 0.5, 1, 1);

}