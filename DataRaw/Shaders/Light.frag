$input v_worldspaceposition, v_texcoord0, v_normal

#include <bgfx_shader.sh>

uniform vec4 u_LightColor[10];
uniform vec4 u_LightPosition[10];
uniform vec4 u_LightRange[10];
uniform vec4 u_AmbientPercentage[10];
uniform vec4 u_FalloffExponent[10];
uniform vec4 u_SpecularExponent[10];


uniform vec4 u_CameraPosition;
SAMPLER2D( u_TextureColor, 0 );


void main()
{
    vec4 finalColor = vec4(0,0,0,1);
    vec4 surfaceColor = texture2D( u_TextureColor, v_texcoord0 );
    vec3 normal = v_normal;
    normal = normalize(normal);
    vec3 surfacePos = v_worldspaceposition;
    vec3 cameraPosition = u_CameraPosition.xyz;

    vec3 dirToCamera = normalize(cameraPosition - surfacePos);


    for (int i = 0; i < 10; i++)
    {
        vec4 lightColor = u_LightColor[i];
        vec3 lightPos = u_LightPosition[i].xyz;
        float lightRange = u_LightRange[i].x;
        float ambientPercentage = u_AmbientPercentage[i].x;
        float falloffExponent = u_FalloffExponent[i].x;
        float specularExponent = u_SpecularExponent[i].x;


        vec3 dirToLight = normalize(lightPos - surfacePos);
        vec3 halfVector = normalize(dirToCamera + dirToLight);
       

        float specularPerc = max(0, dot(halfVector, v_normal));
        specularPerc = pow (specularPerc, specularExponent);

        float diffusePerc = max(0, dot(dirToLight, normal));

        float distanceFromLight = length( lightPos - surfacePos);

        float falloff = 0;
        if (lightRange > 0.0f)
        {
            falloff = max(0, 1 - distanceFromLight/lightRange);
            falloff = pow(falloff, falloffExponent);
        }

        vec4 ambient = surfaceColor * ambientPercentage;
        vec4 diffuse = surfaceColor * diffusePerc;
        vec4 specular = lightColor * specularPerc;

        finalColor += ambient + ((diffuse + specular) * falloff);
    }


    gl_FragColor = finalColor;

}

