#include "MidtermScene.h"
#include "Game.h"

MidtermScene::MidtermScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
	//m_pCamera->SetEye(vec3(5, 5, -15));
	//m_pCamera->SetAt(vec3(0, -5, 0));
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_Objects.push_back(new fw::GameObject(this));
	fw::GameObject* testObject = m_Objects[0];
	testObject->AddComponent(new fw::TransformComponent(testObject, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	testObject->AddComponent(new fw::RenderComponent(testObject, getMesh("Square"), getMaterial("Blue")));
	testObject->AddComponent(new fw::PhysicsComponent(testObject, m_pWorld, true));
	testObject->GetPhysicsComponent()->SetBox();
}

MidtermScene::~MidtermScene()
{
}

void MidtermScene::ExecuteEvent(fw::Event* pEvent)
{
	if (pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType())
	{
		int width = GetGameCore()->GetFramework()->GetWindowClientWidth();
		int height = GetGameCore()->GetFramework()->GetWindowClientHeight();

		m_pCamera->SetAspectRatio((float)width / height);

	}
}

void MidtermScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void MidtermScene::Update(float deltaTime)
{
	m_pComponentManager->UpdateTransforms();

	m_pComponentManager->UpdateBodies(m_pWorld, deltaTime);

	m_pCamera->Update(deltaTime);
}

void MidtermScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);
}
