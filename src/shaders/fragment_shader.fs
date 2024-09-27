#version 330 core
out vec4 FragColor;

in vec3 vertexColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	FragColor  = texture(texture1,TexCoord) * vec4(1.0,0.3,0.8,1.0);
}
