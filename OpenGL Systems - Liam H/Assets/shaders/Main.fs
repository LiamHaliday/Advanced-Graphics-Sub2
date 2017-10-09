#version 430 core 
in vec3 outColor; 
in vec2 TexCoord;

//vec3 norm = normalize(Normal);
//vec3 lightDir = normalize(lightPos - FragPos); 
//float diff = max(dot(norm, lightDir), 0.0); 
//vec3 diffuse = diff * lightColor;


out vec4 color;

uniform sampler2D Texture;
uniform float currentTime;

void main(){

    color = texture(Texture, TexCoord) * vec4(outColor, 1.0f) * abs(1);

}