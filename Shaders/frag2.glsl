#version 330 core

uniform vec2 iResolution;
uniform float iTime;

out vec4 FragColor;
in vec2 vUV;  

float sdfCircle( vec2 p, float r )
{
    return length(p) - r;
}

void main()
{  
    vec2 fragCoord = vUV * iResolution;
    vec2 uv = 8.0 * (fragCoord - 0.5 * iResolution.xy) / iResolution.y;
    
    vec3 colA = vec3(0.0, 0.45, 1.0);
    vec3 colB = vec3(0.0, 1.0, 0.0);
    
    float rad = 2.0;
    vec2 center = vec2(0.0, 0.0);
    float dist = sdfCircle(uv - center, rad);

    vec3 col = dist >= 0.0 ? colA : colB;
    col *= 1.0 - exp(-2.0 * abs(dist));
    col *= 0.75 + col * 0.5 * sin(60.0 * dist - 20.0 * iTime);
    col = mix(vec3(1.0), col, smoothstep(0.08, 0.09, abs(dist)));
    col = mix(col, vec3(1.0, 0.0, 0.0), smoothstep(0.05, 0.049, abs(dist)));
    
    FragColor = vec4(col ,1.0);
}
