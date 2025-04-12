#pragma once

#include "CoreHeaders.h"
#include "Component/Component.h"

#include "Physics/Jolt/JoltHelpers.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

namespace fw
{
	class MyContactListener;
	class JoltContactListener;
	class EventManager;

	class ComponentManager
	{
	public:
		ComponentManager(EventManager* pEventManager);
		virtual ~ComponentManager();

		void AddComponent(Component* pComponent);
		void RemoveComponent(Component* pComponent);
		std::vector<Component*>& GetComponentOfType(ComponentType type);

		void Update(float deltaTime);
		void RenderMeshes(int viewID);

		b2World* GetBox2DWorld() { return m_pBox2DWorld; }
		JoltWorldBundle* GetJoltWorld() { return m_pJoltWorld; }

	private:
		void UpdatePhysics(float deltaTime);

		void UpdateTransforms();

	public:
		std::map<ComponentType, std::vector<Component*>> m_Components;

	private:

#pragma region Physics

		//Box2D
		b2World* m_pBox2DWorld = nullptr;
		MyContactListener* m_pBox2DContactListener = nullptr;

		//Jolt
		JoltWorldBundle* m_pJoltWorld = nullptr;
		JoltContactListener* m_pJoltContactListener = nullptr;

#pragma endregion Physics
	};
}