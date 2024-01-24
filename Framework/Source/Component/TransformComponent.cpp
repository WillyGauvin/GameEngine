#include "TransformComponent.h"

namespace fw
{

	TransformComponent::TransformComponent(GameObject* pGameObject)
		: Component(pGameObject)
	{

	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::UpdateSRT()
	{
		m_transform.CreateSRT(m_scale, m_rotation, m_position);
	}

}
