uniform vec4 u_color1;
uniform vec4 u_color2;
uniform float u_time;

out vec4 PixelColor;

void main()
{
    PixelColor = mix(u_color1,u_color2, (sin(u_time) + 1.0) / 2.0);
}


