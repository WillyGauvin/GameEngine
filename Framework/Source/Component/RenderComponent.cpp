#include "RenderComponent.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"

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

}
