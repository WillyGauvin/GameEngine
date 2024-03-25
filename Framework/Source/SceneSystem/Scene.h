#pragma once
#include "EventSystem/EventListener.h"
#include "Math/Vector.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"


namespace fw 
{
	class GameCore;
	class ComponentManager;
	class Event;
	class Camera;
	class GameObject;
	class MyContactListener;

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
		fw::Camera* GetCamera() { return m_pCamera; }


		void CreateRevoluteJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos);

		void CreatePrismaticJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos, vec2 axis);


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
		MyContactListener* m_pContactListener = nullptr;

	};
}
