#version 440

layout(location = 0) in vec2 texCoords_FS_in;

out vec4 color_FS_out;

uniform sampler2D tex;

void main(void)
{
	color_FS_out = vec4(0, 1, 0, 1);//texture(tex, texCoords_FS_in);
}