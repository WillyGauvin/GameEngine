#include "JoltScene.h"
#include "Game.h"
#include "Jolt/Jolt.h"
#include "Jolt/Physics/Body/Body.h"


JoltScene::JoltScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
	m_pCamera->SetEye(vec3(5, 5, -15));
	m_pCamera->SetAt(vec3(0, -5, 0));
	#define getMesh game->GetResourceManager()->Get<fw::Mesh>
	#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_pWorldBundle = fw::CreateJoltWorld(m_pEventManager);

	m_Objects.push_back(new fw::GameObject(this));

	fw::GameObject* testObject = m_Objects[0];

	testObject->AddComponent(new fw::TransformComponent(testObject, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	testObject->AddComponent(new fw::RenderComponent(testObject, getMesh("Cube"), getMaterial("Dice")));

	m_pBody = fw::CreateJoltBody(m_pWorldBundle->m_pWorld, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), true, 1.0f, testObject);
}
JoltScene::~JoltScene()
{
	fw::DestroyJoltBody(m_pWorldBundle->m_pWorld, m_pBody);
	fw::DestroyJoltWorld(m_pWorldBundle);
}

void JoltScene::ExecuteEvent(fw::Event* pEvent)
{
	if (pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType())
	{
		int width = GetGameCore()->GetFramework()->GetWindowClientWidth();
		int height = GetGameCore()->GetFramework()->GetWindowClientHeight();

		m_pCamera->SetAspectRatio((float)width / height);

	}
}

void JoltScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void JoltScene::Update(float deltaTime)
{
	fw::UpdateJoltWorld(m_pWorldBundle, deltaTime);
	
	fw::GameObject* object = m_Objects[0];

	object->GetTransformComponent()->m_position = vec3(m_pBody->GetPosition().GetX(), m_pBody->GetPosition().GetY(), m_pBody->GetPosition().GetZ());
	object->GetTransformComponent()->m_rotation = vec3(m_pBody->GetRotation().GetX(), m_pBody->GetRotation().GetY(), m_pBody->GetRotation().GetZ());

	m_pComponentManager->UpdateBodies(m_pWorld, deltaTime);

	m_pComponentManager->UpdateTransforms();

	m_pCamera->Update(deltaTime);

}

void JoltScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);
}
