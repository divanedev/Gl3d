#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 Color;
uniform mat4 u_MVP;
out vec4 v_Color;

void main() {
    gl_Position = u_MVP * position;
    v_Color = Color;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
in vec2 v_TexCoord;
in vec4 v_Color;

void main() {
    color = v_Color;
};