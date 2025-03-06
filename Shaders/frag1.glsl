#version 330 core

uniform vec2 iResolution;
uniform float iTime;

out vec4 FragColor;
in vec2 vUV;  

void main()
{  
    vec2 fragCoord = vUV * iResolution;
    vec2 uv = 2.0 * (fragCoord - 0.5 * iResolution.xy) / iResolution.y;

    uv.x *= iResolution.x / iResolution.y;

    float radius = 0.8;

    float wave = 0.05 * sin(uv.y * 10.0+ iTime * 3.0) 
                + 0.05 * cos(uv.x * 8.0 + iTime * 7.0);

    radius += wave;
    
    float dist = length(uv);
    float black = smoothstep(radius, radius + 0.001, dist);
    float white = smoothstep(radius - 0.075, radius + 0.001 - 0.075, dist);

    vec3 color = mix(vec3(0.0), vec3(1.0), black);
    color = mix(color, vec3(1.0), white);
    color = mix(color, vec3(1.0, 0.0, 0.25), black);
    
    FragColor = vec4(color, 1.0);
}
