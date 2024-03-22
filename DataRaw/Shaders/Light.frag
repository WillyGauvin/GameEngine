$input v_worldspaceposition

#include <bgfx_shader.sh>

//uniform vec3 u_MaterialColour;
//uniform vec3 u_LightColour;

uniform vec4 u_DiffuseColor;


void main()
{
    vec3 LightPos = vec3(0,2,0);
    vec3 WorldSpacePos = v_worldspaceposition;

    vec3 normalDir = normalize(LightPos - WorldSpacePos);

    vec3 Normal = vec3(0.0,1.0,0.0);

    float diffusePercent = max(dot(normalDir, Normal), 0);

    float distance = length(LightPos - WorldSpacePos);

    float LightRange = 5;

    float Attenuation = max(1 - pow(distance/LightRange,2), 0);

    vec3 u_MaterialColour = vec3(0.5,1.0,0.2);
    vec3 u_LightColour = vec3(1.0,1.0,1.0);

    vec4 finalColour = vec4 (u_MaterialColour * u_LightColour * diffusePercent * Attenuation, 1);

    gl_FragColor = finalColour;

}
