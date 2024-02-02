#include "ComponentManager.h"
#include "Component/TransformComponent.h"
#include "Component/RenderComponent.h"

namespace fw
{
	ComponentManager::ComponentManager()
	{
	}
	ComponentManager::~ComponentManager()
	{
	}


	void ComponentManager::AddComponent(Component* pComponent)
	{
		m_Components[pComponent->GetType()].push_back(pComponent);
	}

	void ComponentManager::RemoveComponent(Component* pComponent)
	{
		std::vector<Component*>& ComponentList = m_Components[pComponent->GetType()];

		std::vector<Component*>::iterator position = std::find(ComponentList.begin(), ComponentList.end(), pComponent);

		if (position != ComponentList.end())
		{
			ComponentList.erase(position);
		}

		//There was multiple pComponent in the list.
		assert(std::find(ComponentList.begin(), ComponentList.end(), pComponent) == ComponentList.end());

	}


	std::vector<Component*>& ComponentManager::GetComponentOfType(ComponentType type)
	{
		return m_Components[type];
	}

	void ComponentManager::UpdateTransforms()
	{
		std::vector<Component*>& ComponentList = m_Components["TransformComponent"];

		for (int i = 0; i < ComponentList.size(); i++)
		{
			static_cast<TransformComponent*>(ComponentList[i])->UpdateSRT();
		}
	}

	void ComponentManager::RenderMeshes()
	{
		std::vector<Component*>& ComponentList = m_Components["RenderComponent"];

		for (int i = 0; i < ComponentList.size(); i++)
		{
			static_cast<RenderComponent*>(ComponentList[i])->Render();
		}
	}
}