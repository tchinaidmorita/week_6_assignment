
out vec4 PixelColor;

in vec2 v_clipSpacePos;

void main()
{
    PixelColor = vec4(v_clipSpacePos.x,v_clipSpacePos.y,0.0,1.0);
}

