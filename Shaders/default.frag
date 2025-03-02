#version 330 core

uniform vec2 iResolution;
uniform float iTime;

out vec4 FragColor;
in vec2 vUV;  // Updated: this is UV passed from vertex shader

float RandFloat(vec2 p) 
{
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

vec2 RandVec2(vec2 p) 
{ 
    return fract(sin(p * mat2(127.1, 311.7, 269.5, 183.3)) * 43758.5453123);
}

float LineSegment(vec2 p, vec2 a, vec2 b) 
{
    vec2 pa = p - a;
    vec2 ba = b - a;
    float t = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    return length(pa - ba * t);
}

float Line(vec2 p, vec2 a, vec2 b) 
{
    float d = LineSegment(p, a, b);
    float w = 10.0 / iResolution.y;
    float m = smoothstep(w, -w, d - 0.02);
    m *= smoothstep(2.0, 1.0, length(a - b));
    return m;
}

vec2 GetPointPosition(vec2 id, vec2 offset) 
{
    vec2 v = RandVec2(id + offset);
    return offset + sin(v * 6.2831 + iTime) * 0.4;
}

void main()
{  
    vec2 fragCoord = vUV * iResolution;  // Correctly compute fragCoord in pixels
    vec2 uv = 20.0 * (fragCoord - 0.5 * iResolution.xy) / iResolution.y;

    vec2 id = floor(uv);
    vec2 gv = fract(uv) - 0.5;

    float m = 0.0;
    vec2 p[9];

    int i = 0;
    for (float y = -1.0; y <= 1.0; y++) 
    {
        for (float x = -1.0; x <= 1.0; x++) 
        {
            p[i++] = GetPointPosition(id, vec2(x, y));
        }
    }

    for (int i = 0; i < 9; i++) 
    {
        m += Line(gv, p[4], p[i]);
    }

    m += Line(gv, p[1], p[3]);
    m += Line(gv, p[1], p[5]);
    m += Line(gv, p[5], p[7]);
    m += Line(gv, p[7], p[3]);
    
    float randR = clamp(sin(iTime), 0.0, 0.3);
   
    vec3 col = vec3(m) * vec3(randR, 0.3, 1.0) * 1.5;

    FragColor = vec4(col, 1.0);
}
