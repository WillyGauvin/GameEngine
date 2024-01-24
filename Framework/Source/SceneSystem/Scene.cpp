#include "Scene.h"
#include "Component/ComponentManager.h"

namespace fw
{
	Scene::Scene(GameCore* pGameCore) :
		m_pGameCore(pGameCore)
	{
		m_pComponentManager = new ComponentManager();
	}

	Scene::~Scene()
	{
		delete m_pComponentManager;
	}

	void Scene::ExecuteEvent(fw::Event* pEvent)
	{
	}

	void Scene::StartFrame(float deltaTime)
	{
	}

	void Scene::Update(float deltaTime)
	{
	}

	void Scene::Draw()
	{
	}

}
