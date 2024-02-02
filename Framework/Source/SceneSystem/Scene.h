#pragma once
#include "EventSystem/EventListener.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"


namespace fw 
{
	class GameCore;
	class ComponentManager;
	class Event;
	class Camera;
	class GameObject;

	class Scene : public EventListener
	{
	public:
		Scene(GameCore* pGameCore);
		virtual ~Scene();

		virtual void ExecuteEvent(fw::Event* pEvent) override;
		virtual void StartFrame(float deltaTime);
		virtual void Update(float deltaTime);
		virtual void Draw();

		GameCore* GetGameCore() { return m_pGameCore; }
		ComponentManager* GetComponentManager() { return m_pComponentManager; }
		fw::EventManager* GetEventManager() { return m_pEventManager; }
		b2World* GetWorld() { return m_pWorld; }


	protected:
		GameCore* m_pGameCore = nullptr;

		//Managers
		ComponentManager* m_pComponentManager = nullptr;
		fw::EventManager* m_pEventManager = nullptr;

		//Objects
		std::vector<GameObject*> m_Objects;
		fw::Camera* m_pCamera = nullptr;

		//B2Box
		b2World* m_pWorld = nullptr;

	};
}
