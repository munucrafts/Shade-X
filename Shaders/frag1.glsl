#version 330 core

uniform vec2 iResolution;
uniform float iTime;

out vec4 FragColor;
in vec2 vUV;  

float RandFloat(float x) 
{
    return fract(sin(x * 127.1) * 43758.5453123);
}

vec3 RandColor(float x)
{
    float r = RandFloat(x);
    float g = RandFloat(x + r);
    float b = RandFloat(x + r + g);
    
    if (r == 0.0 && g == 0.0 && b == 0.0) r = g = b = 0.8;
    
    return vec3(r, g, b);
}


void main()
{  
    vec2 fragCoord = vUV * iResolution;
    vec2 uv = 40.0 * (fragCoord - 0.5 * iResolution.xy) / iResolution.y;
    
    vec2 id = floor(uv);
    vec2 gv = fract(uv) - 0.5;

    float speed = RandFloat(id.x + 2.0) * 5.0 + 1.0;     
    float barHeight = sin(iTime * speed * 2.0) * 8.0;

    vec3 col;

    if (id.y < barHeight) col = RandColor(id.x * RandFloat(id.x));

    if (gv.x > 0.45 || gv.y > 0.45) col = vec3(0, 0, 0);

    FragColor = vec4(col, 1.0);
}
