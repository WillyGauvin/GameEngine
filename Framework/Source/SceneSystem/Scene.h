#pragma once

namespace fw 
{
	class GameCore;
	class Scene
	{
	public:
		Scene(GameCore* pGameCore);
		virtual ~Scene();
		GameCore* GetGameCore() { return m_pGameCore; }

	protected:
		GameCore* m_pGameCore;
	};
}
