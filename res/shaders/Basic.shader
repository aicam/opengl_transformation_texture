#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 ourColor;
uniform mat4 MVP;
void main()
{
  ourColor = aColor;
  gl_Position = MVP * vec4(position, 1.0);
  v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;
in vec3 ourColor;
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

void main()
{
  vec4 texColor = texture(u_Texture, v_TexCoord)*vec4(ourColor, 1.0);
  color = texColor;
}