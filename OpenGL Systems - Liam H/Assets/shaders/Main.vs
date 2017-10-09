#version 430 core
 layout (location = 0) in vec3 position; 
 layout (location = 1) in vec3 color; 
 layout (location = 2) in vec2 texCoord;


 //FragPos = vec3(model* vec4(position, 1.0f));
 //Normal = mat3(transpose(inverse(model))) * normal;

out vec3 outColor; 
out vec2 TexCoord;

uniform mat4 transform; 

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 world;
uniform mat4 scale;


void main(void)
{ 
	gl_Position = world * projection * view * model * vec4(position, 1.0);
	//  (transform * projection * view * model * vec4(position, 1.0));
	outColor = color;
	TexCoord = texCoord;

 }    