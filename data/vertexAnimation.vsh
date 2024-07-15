uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;

uniform float u_time;

in vec4 a_position;

void main()
{
    vec4 pos = a_position;
    pos.y *= abs(sin(u_time + pos.x / 100.0));
    gl_Position = projection * view * world * pos;
}

