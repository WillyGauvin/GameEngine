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


		b2World* GetBox2DWorld() { return m_pBox2DWorld; }
		JoltWorldBundle* GetJoltWorld() { return m_pJoltWorld; }

		virtual fw::Camera* GetCamera() { return m_pCamera; }


		std::vector<GameObject*> GetLights() { return m_Lights; }
		GameObject* GetClosestLight(vec3 position);

		void CreateRevoluteJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos);

		void CreatePrismaticJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos, vec2 axis);

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

#pragma region Physics

		//Box2D
		b2World* m_pBox2DWorld = nullptr;
		MyContactListener* m_pBox2DContactListener = nullptr;

		//Jolt
		JoltWorldBundle* m_pJoltWorld = nullptr;
		JoltContactListener* m_pJoltContactListener = nullptr;

#pragma endregion Physics

		vec4 m_LightPos[10];
		vec4 m_LightColor[10];
		vec4 m_LightRange[10];
		vec4 m_AmbPerc[10];
		vec4 m_FalloffExp[10];
		vec4 m_SpecExp[10];

	};
}
