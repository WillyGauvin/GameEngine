$input v_worldspaceposition, v_texcoord0, v_normal

#include <bgfx_shader.sh>

uniform vec4 u_LightColor;
uniform vec4 u_LightPosition;
uniform vec4 u_LightRange;
uniform vec4 u_AmbientPercentage;
uniform vec4 u_FalloffExponent;
uniform vec4 u_SpecularExponent;

uniform vec4 u_CameraPosition;
SAMPLER2D( u_TextureColor, 0 );


void main()
{
    vec4 surfaceColor = texture2D( u_TextureColor, v_texcoord0 );

    vec4 lightColor = u_LightColor;
    vec3 lightPos = u_LightPosition.xyz;
    float lightRange = u_LightRange.x;
    float ambientPercentage = u_AmbientPercentage.x;
    float falloffExponent = u_FalloffExponent.x;
    float specularExponent = u_SpecularExponent.x;

    vec3 surfacePos = v_worldspaceposition;
    vec3 cameraPosition = u_CameraPosition.xyz;


    vec3 dirToLight = normalize(lightPos - surfacePos);
    vec3 dirToCamera = normalize(cameraPosition - surfacePos);
    vec3 halfVector = normalize(dirToCamera + dirToLight);
    
    vec3 normal = v_normal;
    normal = normalize(normal);

    float specularPerc = max(0, dot(halfVector, v_normal));
    specularPerc = pow (specularPerc, specularExponent);

    float diffusePerc = max(0, dot(dirToLight, normal));

    float distanceFromLight = length( lightPos - surfacePos);
    float falloff = max(0, 1 - distanceFromLight/lightRange);
    falloff = pow(falloff, falloffExponent);

    vec4 ambient = surfaceColor * ambientPercentage;
    vec4 diffuse = surfaceColor * diffusePerc;
    vec4 specular = lightColor * specularPerc;

    vec4 finalColour = ambient + (diffuse + specular) * falloff;


    gl_FragColor = finalColour;

}

