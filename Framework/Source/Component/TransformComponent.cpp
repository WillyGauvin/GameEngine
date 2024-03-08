#include "TransformComponent.h"

#include "SceneSystem/Scene.h"
#include "GameCore.h"
#include "Component/PhysicsComponent.h"
namespace fw
{

	TransformComponent::TransformComponent(GameObject* pGameObject, vec3 position, vec3 rotation, vec3 scale) : Component(pGameObject)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;

		m_originalPosition = m_position;
		m_originalRotation = m_rotation;
		m_originalScale = m_scale;
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::UpdateSRT()
	{
		m_transform.CreateSRT(m_scale, m_rotation, m_position);
	}

	void TransformComponent::Reset()
	{
		m_position = m_originalPosition;
		m_rotation = m_originalRotation;
		m_scale = m_originalScale;
		UpdateSRT();
	}

}
