#include "TransformComponent.h"

#include "SceneSystem/Scene.h"
#include "GameCore.h"

namespace fw
{

	TransformComponent::TransformComponent(GameObject* pGameObject, vec3 position, vec3 rotation, vec3 scale) : Component(pGameObject)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::UpdateSRT()
	{
		m_transform.CreateSRT(m_scale, m_rotation, m_position);
	}

}
