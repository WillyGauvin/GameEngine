#include "Scene.h"
#include "Component/ComponentManager.h"
#include "EventSystem/EventManager.h"
#include "Objects/Camera.h"
#include "Objects/GameObject.h"

namespace fw
{
	Scene::Scene(GameCore* pGameCore) :
		m_pGameCore(pGameCore)
	{
		m_pComponentManager = new ComponentManager();
		m_pEventManager = new EventManager(m_pGameCore);
		m_pCamera = new Camera(this, vec3(0, 0, 0));
	}

	Scene::~Scene()
	{
		delete m_pComponentManager;
		delete m_pEventManager;
		delete m_pCamera;

		for (fw::GameObject* pObject : m_Objects)
		{
			delete pObject;
		}
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
