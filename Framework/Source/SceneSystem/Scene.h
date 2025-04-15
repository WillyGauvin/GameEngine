#pragma once
#include "CoreHeaders.h"
#include "EventSystem/EventListener.h"
#include "Math/Vector.h"
#include "Component/PhysicsComponent.h"
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
	class JoltWorldBundle;

	class Scene : public EventListener
	{
	public:
		Scene(GameCore* pGameCore, PhysicsLibrary usingPhysicsEngine = PhysicsLibrary::None);
		virtual ~Scene();

		virtual void ExecuteEvent(fw::Event* pEvent) override;
		virtual void StartFrame(float deltaTime);
		virtual void Update(float deltaTime);
		virtual void Draw();

		GameCore* GetGameCore() { return m_pGameCore; }
		ComponentManager* GetComponentManager() { return m_pComponentManager; }
		fw::EventManager* GetEventManager() { return m_pEventManager; }

		virtual fw::Camera* GetCamera() { return m_pCamera; }


		std::vector<GameObject*> GetLights() { return m_Lights; }
		GameObject* GetClosestLight(vec3 position);

		void PopulateAllLightArrays();

	protected:
		GameCore* m_pGameCore = nullptr;

		//Managers
		ComponentManager* m_pComponentManager = nullptr;
		fw::EventManager* m_pEventManager = nullptr;

		//Objects
		std::vector<GameObject*> m_Objects;
		fw::Camera* m_pCamera = nullptr;

		std::vector<GameObject*> m_Lights;

		vec4 m_LightPos[10];
		vec4 m_LightColor[10];
		vec4 m_LightRange[10];
		vec4 m_AmbPerc[10];
		vec4 m_FalloffExp[10];
		vec4 m_SpecExp[10];

	};
}
