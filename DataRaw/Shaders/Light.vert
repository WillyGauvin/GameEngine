$input a_position
$output v_worldspaceposition

//$output v_MaterialColour, v_LightColour

#include <bgfx_shader.sh>

uniform mat4 u_MatWorld;
uniform mat4 u_MatView;
uniform mat4 u_MatProj;

void main()
{
	vec4 objectSpacePosition = vec4( a_position, 1 );  
	vec4 worldSpacePosition = mul( u_MatWorld, objectSpacePosition );
	vec4 viewSpacePosition = mul( u_MatView, worldSpacePosition);
	vec4 clipSpacePosition = mul( u_MatProj, viewSpacePosition);

	v_worldspaceposition = worldSpacePosition.xyz;
	gl_Position = clipSpacePosition;


}

