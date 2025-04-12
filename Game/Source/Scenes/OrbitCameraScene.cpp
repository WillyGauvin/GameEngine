#include "OrbitCameraScene.h"
#include "Game.h"

OrbitCameraScene::OrbitCameraScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>


	m_pPlayer = new fw::GameObject(this);
	m_pPlayer->AddComponent(new fw::RenderComponent(m_pPlayer, getMesh("Tree"), getMaterial("LightTest")));
	m_pPlayer->AddComponent(new fw::TransformComponent(m_pPlayer, vec3(0.0f,0.0f,0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(10.0f, 10.0f, 10.0f)));
	m_Objects.push_back(m_pPlayer);
}

OrbitCameraScene::~OrbitCameraScene()
{
}

void OrbitCameraScene::ExecuteEvent(fw::Event* pEvent)
{
}

void OrbitCameraScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void OrbitCameraScene::Update(float deltaTime)
{
	m_pComponentManager->Update(deltaTime);
	m_pCamera->Update(deltaTime);
}

void OrbitCameraScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);
}
