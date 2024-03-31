#include "RenderComponent.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "SceneSystem/Scene.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"
#include "Objects/GameObject.h"
#include "Component/TransformComponent.h"
#include "Component/LightComponent.h"
#include "Objects/Camera.h"
namespace fw
{

	RenderComponent::RenderComponent(GameObject* pGameObject, Mesh* pMesh, Material* pMaterial)
		: Component(pGameObject),
		m_pMesh(pMesh),
		m_pMaterial(pMaterial)
	{

	}

	RenderComponent::~RenderComponent()
	{

	}

	void RenderComponent::Render(int viewID)
	{
		Uniforms* pUniforms = m_pGameObject->GetScene()->GetGameCore()->GetUniforms();
		bgfx::setUniform(pUniforms->GetUniform("u_MatWorld"), &m_pGameObject->GetTransformComponent()->m_transform);

		mat4 rotation;
		rotation.CreateRotation(m_pGameObject->GetTransformComponent()->m_rotation);
		bgfx::setUniform(pUniforms->GetUniform("u_MatWorldRotation"), &rotation);

		// Camera Position
		vec4 cameraPos = vec4(m_pGameObject->GetScene()->GetCamera()->GetEye(),1);
		bgfx::setUniform(pUniforms->GetUniform("u_CameraPosition"), &cameraPos);


		//Set Lights
		if (fw::GameObject* light = m_pGameObject->GetScene()->GetClosetLight(m_pGameObject->GetTransformComponent()->m_position))
		{
			bgfx::setUniform(pUniforms->GetUniform("u_LightPosition"), &light->GetTransformComponent()->m_position);
			
			color4f color = light->GetRenderComponent()->m_pMaterial->GetColor();
			vec4 vec4Color = vec4(color.r, color.g, color.b, color.a);
			bgfx::setUniform(pUniforms->GetUniform("u_LightColor"), &vec4Color);

			LightComponent* component = light->GetLightComponent();

			float range = component->m_LightRange;
			float amb = component->m_AmbientPerc;
			float fall = component->m_FalloffExp;
			float spec = component->m_SpecularExp;

			bgfx::setUniform(pUniforms->GetUniform("u_LightRange"), &range);
			bgfx::setUniform(pUniforms->GetUniform("u_AmbientPercentage"), &amb);
			bgfx::setUniform(pUniforms->GetUniform("u_FalloffExponent"), &fall);
			bgfx::setUniform(pUniforms->GetUniform("u_SpecularExponent"), &spec);

		}


		m_pMesh->Draw(viewID, m_pGameObject->GetScene()->GetGameCore()->GetUniforms(), m_pMaterial);
	}

}
//m_pUniforms->CreateUniform("u_LightPosition", bgfx::UniformType::Vec4);
////light color vec4
//m_pUniforms->CreateUniform("u_LightColor", bgfx::UniformType::Vec4);
//
////light range float
////ambient percentage float
////falloff exponent float
////specular exponent float
////Vec4 all together.
//m_pUniforms->CreateUniform("u_RangeAmbFallSpec", bgfx::UniformType::Vec4);