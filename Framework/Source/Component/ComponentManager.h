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

		void UpdateBodies(b2World* world, float deltaTime);
		void UpdateTransforms();
		void RenderMeshes(int viewID);

	public:
		std::map<ComponentType, std::vector<Component*>> m_Components;
	};
}