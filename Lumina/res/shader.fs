#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
    FragColor = mixValue* texture(texture2, TexCoord) + (1 - mixValue) * texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y));
}