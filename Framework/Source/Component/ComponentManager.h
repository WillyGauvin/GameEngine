#pragma once

#include "CoreHeaders.h"
#include "Component/Component.h"

namespace fw
{

	class ComponentManager
	{
	public:
		ComponentManager();
		virtual ~ComponentManager();

		void AddComponent(Component* pComponent);
		void RemoveComponent(Component* pComponent);
		std::vector<Component*>& GetComponentOfType(ComponentType type);

		void UpdateTransforms();
		void RenderMeshes();

	public:
		std::map<ComponentType, std::vector<Component*>> m_Components;
	};
}