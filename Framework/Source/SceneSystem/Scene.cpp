#include "Scene.h"
#include "Component/ComponentManager.h"

fw::Scene::Scene(GameCore* pGameCore) :
	m_pGameCore(pGameCore)
{
	m_pComponentManager = new ComponentManager();
}

fw::Scene::~Scene()
{
	delete m_pComponentManager;
}
