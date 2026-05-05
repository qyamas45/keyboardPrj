#version 330 core
out vec4 FragColor;
uniform vec3 keyColor;
uniform bool useKeyColor;
 
in vec3 ourColor;
// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//between [0, 1]
	vec3 color = useKeyColor ? keyColor : ourColor;
    FragColor = vec4(color, 1.0);

}