$input v_worldspaceposition, v_texcoord0, v_normal

#include <bgfx_shader.sh>

//uniform vec3 u_MaterialColour;
//uniform vec3 u_LightColour;
uniform vec4 u_CameraPosition;
SAMPLER2D( u_TextureColor, 0 );


void main()
{
//Make sure normal being passed in is normalized

    vec4 surfaceColor = texture2D( u_TextureColor, v_texcoord0 );

    vec3 lightPos = vec3(0.0,25.0,0.0);
    vec3 surfacePos = v_worldspaceposition;
    vec3 cameraPosition = u_CameraPosition.xyz;

    float ambientPerc = 0.1;

    vec3 dirToLight = normalize(lightPos - surfacePos);
    vec3 dirToCamera = normalize(cameraPosition - surfacePos);
    vec3 halfVector = normalize(dirToCamera + dirToLight);
    
    vec3 normal = v_normal;
    float specularPerc = max(0.0, dot(halfVector, normal));

    float shininess = 5.0;
    specularPerc = pow (specularPerc, shininess);

    float diffusePerc = max(dot(dirToLight, normal), 0.0);

    //Create a light range uniform
    float lightRange = 50.0;

    float fallOffExponent = 1.0;
    float distanceFromLight = length( lightPos - surfacePos);
    float falloff = max(0.0, 1.0 - distanceFromLight/lightRange);
    falloff = pow(falloff, fallOffExponent);

    vec4 u_LightColour = vec4(1.0,1.0,1.0,1.0);


    vec4 ambient = surfaceColor * ambientPerc;
    vec4 diffuse = surfaceColor * diffusePerc;
    vec4 specular = u_LightColour * specularPerc;

    vec4 finalColour = vec4 (ambient + (diffuse + specular) * falloff);


    gl_FragColor = finalColour;

}

