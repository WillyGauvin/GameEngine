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


		m_pMesh->Draw(viewID, m_pGameObject->GetScene()->GetGameCore()->GetUniforms(), m_pMaterial);
	}

	vec4 RenderComponent::GetColor()
	{
		color4f color = m_pMaterial->GetColor();
		vec4 vec4Color = vec4(color.r, color.g, color.b, color.a);
		return vec4Color;
	}

}