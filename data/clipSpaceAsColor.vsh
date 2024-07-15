uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;

in vec4 a_position;

out vec2 v_clipSpacePos;

void main()
{
    gl_Position = projection * view * world * a_position;
    v_clipSpacePos = (gl_Position.xy + 1.0) / 2.0;
}

