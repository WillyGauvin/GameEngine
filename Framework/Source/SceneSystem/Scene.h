#pragma once

namespace fw 
{
	class GameCore;
	class ComponentManager;
	class Scene
	{
	public:
		Scene(GameCore* pGameCore);
		virtual ~Scene();
		GameCore* GetGameCore() { return m_pGameCore; }
		ComponentManager* GetComponentManager() { return m_pComponentManager; }

	protected:
		GameCore* m_pGameCore;
		ComponentManager* m_pComponentManager;
	};
}
