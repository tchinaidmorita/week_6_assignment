uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
uniform float u_time;

in vec4 a_position;
in vec4 a_color;

out vec4 v_color;

void main()
{
    vec4 pos = a_position;
    
    // Wave displacement based on radial distance and dynamic time
    float dist = length(pos.xz);
    pos.y = sin(dist * 8.0 - u_time * 4.0) * 0.15;

    gl_Position = projection * view * world * pos;
    v_color = a_color;
}