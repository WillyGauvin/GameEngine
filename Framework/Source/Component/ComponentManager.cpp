#include "ComponentManager.h"

#include "Component/TransformComponent.h"
#include "Component/RenderComponent.h"
#include "Component/PhysicsComponent.h"

#include "Physics/Jolt/JoltContactListener.h"
#include "Physics/Box2D/MyContactListener.h"	

namespace fw
{
	ComponentManager::ComponentManager(EventManager* pEventManager, PhysicsLibrary physicsType)
	{
		if (physicsType == PhysicsLibrary::Box2D)
		{
			m_pBox2DWorld = new b2World(b2Vec2(0.f, -9.8f));
			m_pBox2DContactListener = new MyContactListener(pEventManager);
			m_pBox2DWorld->SetContactListener(m_pBox2DContactListener);
		}
		else if (physicsType == PhysicsLibrary::Jolt)
		{
			m_pJoltContactListener = new JoltContactListener(pEventManager);
			m_pJoltWorld = fw::CreateJoltWorld(pEventManager, m_pJoltContactListener);
		}
	}

	ComponentManager::~ComponentManager()
	{
		delete m_pBox2DWorld;
		delete m_pBox2DContactListener;
		delete m_pJoltContactListener;
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

	void ComponentManager::Update(float deltaTime)
	{
		UpdatePhysics(deltaTime);
		UpdateTransforms();
	}

	void ComponentManager::RenderMeshes(int viewID)
	{
		std::vector<Component*>& ComponentList = m_Components["RenderComponent"];

		for (int i = 0; i < ComponentList.size(); i++)
		{
			static_cast<RenderComponent*>(ComponentList[i])->Render(viewID);
		}
	}

	void ComponentManager::UpdatePhysics(float deltaTime)
	{
		if (m_pBox2DWorld)
		{
			m_pBox2DWorld->Step(deltaTime, 8, 3);
		}
		if (m_pJoltWorld)
		{
			UpdateJoltWorld(m_pJoltWorld, deltaTime);
		}

		std::vector<Component*>& ComponentList = m_Components["PhysicsComponent"];
		for (int i = 0; i < ComponentList.size(); i++)
		{
			static_cast<PhysicsComponent*>(ComponentList[i])->UpdateBody();
		}
	}

	void ComponentManager::UpdateTransforms()
	{
		std::vector<Component*>& ComponentList = m_Components["TransformComponent"];

		for (int i = 0; i < ComponentList.size(); i++)
		{
			static_cast<TransformComponent*>(ComponentList[i])->UpdateSRT();
		}
	}
}