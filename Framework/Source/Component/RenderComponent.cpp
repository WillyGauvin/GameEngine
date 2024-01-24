#include "RenderComponent.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "SceneSystem/Scene.h"
#include "GameCore.h"
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

	void RenderComponent::Render()
	{
		m_pMesh->Draw(0, m_pGameObject->GetScene()->GetGameCore()->GetUniforms(), m_pMaterial);
	}

}
