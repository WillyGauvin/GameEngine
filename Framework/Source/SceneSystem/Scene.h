#pragma once
#include "EventSystem/EventListener.h"
namespace fw 
{
	class GameCore;
	class ComponentManager;
	class Event;
	class ImGuiManager;

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


	protected:
		GameCore* m_pGameCore = nullptr;
		ComponentManager* m_pComponentManager = nullptr;
		fw::EventManager* m_pEventManager = nullptr;

		// Editor Interface.
		ImGuiManager* m_pImGuiManager = nullptr;

	};
}
