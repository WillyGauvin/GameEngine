#include "OBJScene.h"
#include "Game.h"

OBJScene::OBJScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_pPlane = new fw::GameObject(this);
	m_pPlane->AddComponent(new fw::RenderComponent(m_pPlane, getMesh("Plane"), getMaterial("Water")));
	m_pPlane->AddComponent(new fw::TransformComponent(m_pPlane, vec3(-50, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(m_pPlane);

	m_pCamera->SetEye(vec3(0.0f, 10.0f, -10.0f));
	m_pCamera->SetAt(vec3(0.0f, 0.0f, 0.0f));
}

OBJScene::~OBJScene()
{
}

void OBJScene::ExecuteEvent(fw::Event* pEvent)
{

}

void OBJScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void OBJScene::Update(float deltaTime)
{
	m_pComponentManager->UpdateTransforms();
	m_pCamera->Update(deltaTime);

}

void OBJScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);
}
