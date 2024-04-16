#include "Framework.h"

#include "MiniPuttScene.h"
#include "Game.h"
#include "Objects/VirtualController.h"
#include "Objects/OrbitCamera.h"
#include "Objects/Player.h"
#include "Meshes/HeightMapMesh.h"
#include "Events/GameEvents.h"
#include "Objects/GolfBall.h"

#include "Jolt/Jolt.h"
#include "Jolt/Physics/Body/Body.h"
#include "Jolt/Renderer/DebugRenderer.h"

MiniPuttScene::MiniPuttScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_pJoltContactListener = new fw::JoltContactListener(m_pEventManager);
	m_pWorldBundle = fw::CreateJoltWorld(m_pEventManager, m_pJoltContactListener);

	m_pPlane = new fw::GameObject(this);
	m_pPlane->AddComponent(new fw::RenderComponent(m_pPlane, getMesh("Plane"), getMaterial("Water")));
	m_pPlane->AddComponent(new fw::TransformComponent(m_pPlane, vec3(-200, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(m_pPlane);

	m_pLight = new fw::GameObject(this);
	m_pLight->AddComponent(new fw::TransformComponent(m_pLight, vec3(0.0f, 50.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_pLight->AddComponent(new fw::RenderComponent(m_pLight, getMesh("Cube"), getMaterial("White")));
	m_pLight->AddComponent(new fw::LightComponent(m_pLight, 100.0f, 0.1f, 5.0f, 10.0f));
	m_Objects.push_back(m_pLight);
	m_Lights.push_back(m_pLight);


	m_pRedLight = new fw::GameObject(this);
	m_pRedLight->AddComponent(new fw::TransformComponent(m_pRedLight, vec3(4.0f, 2.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_pRedLight->AddComponent(new fw::RenderComponent(m_pRedLight, getMesh("Cube"), getMaterial("Red")));
	m_pRedLight->AddComponent(new fw::LightComponent(m_pRedLight, 100.0f, 0.0f, 5.0f, 2.0f));
	m_Objects.push_back(m_pRedLight);
	m_Lights.push_back(m_pRedLight);

	m_pBlueLight = new fw::GameObject(this);
	m_pBlueLight->AddComponent(new fw::TransformComponent(m_pBlueLight, vec3(-1.0f, 2.0f, 4.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_pBlueLight->AddComponent(new fw::RenderComponent(m_pBlueLight, getMesh("Cube"), getMaterial("Blue")));
	m_pBlueLight->AddComponent(new fw::LightComponent(m_pBlueLight, 100.0f, 0.0f, 5.0f, 2.0f));
	m_Objects.push_back(m_pBlueLight);
	m_Lights.push_back(m_pBlueLight);








	m_pCourse = new fw::GameObject(this);
	m_pCourse->AddComponent(new fw::RenderComponent(m_pCourse, getMesh("MiniPuttCourse"), getMaterial("MiniPuttCourse")));
	m_pCourse->AddComponent(new fw::TransformComponent(m_pCourse, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_Objects.push_back(m_pCourse);
	
	m_pHole = new fw::GameObject(this);
	m_pHole->AddComponent(new fw::RenderComponent(m_pHole, getMesh("Cube"), getMaterial("Blue")));
	m_pHole->AddComponent(new fw::TransformComponent(m_pHole, vec3(4.5f, -0.2f, 4.9f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_Objects.push_back(m_pHole);

	m_pController = new VirtualController(m_pEventManager);

	m_pGolfBall = new GolfBall(this);
	m_pGolfBall->SetController(m_pController);
	m_pGolfBall->GetTransformComponent()->m_position = m_golfballStartingPos;

	m_pOrbitCamera = new OrbitCamera(this, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), m_pGolfBall->GetTransformComponent()->m_position, m_pController, m_pGolfBall);

	m_pOrbitCamera->SetStartingDistance(1.0f);
	m_pCourseBody = fw::CreateMeshJoltBody(m_pWorldBundle->m_pWorld, m_pCourse->GetTransformComponent()->m_position, m_pCourse->GetTransformComponent()->m_rotation, m_pCourse->GetTransformComponent()->m_scale, false, 1.0f, m_pCourse);

	m_pBallBody = fw::CreateSphereJoltBody(m_pWorldBundle->m_pWorld, m_pGolfBall->GetTransformComponent()->m_position, 0.025f, true, 0.01f, m_pGolfBall);

	m_pHoleBody = fw::CreateJoltBody(m_pWorldBundle->m_pWorld, m_pHole->GetTransformComponent()->m_position, m_pHole->GetTransformComponent()->m_rotation, m_pHole->GetTransformComponent()->m_scale, false, 1.0f, m_pHole);
	m_pEventManager->RegisterListener(SwingClubEvent::GetStaticEventType(), this);
	m_pEventManager->RegisterListener(fw::CollisionEvent::GetStaticEventType(), this);
	m_pEventManager->RegisterListener(ResetGameEvent::GetStaticEventType(), this);


}

MiniPuttScene::~MiniPuttScene()
{
	fw::DestroyJoltBody(m_pWorldBundle->m_pWorld, m_pCourseBody);
	fw::DestroyJoltBody(m_pWorldBundle->m_pWorld, m_pBallBody);

	fw::DestroyJoltWorld(m_pWorldBundle);
	delete m_pWorldBundle;
}

void MiniPuttScene::ExecuteEvent(fw::Event* pEvent)
{
	if (pEvent->GetType() == SwingClubEvent::GetStaticEventType())
	{
		SwingClubEvent* event = static_cast<SwingClubEvent*>(pEvent);
		vec3 force = event->GetForce();
		JPH::Vec3Arg newForce = JPH::Vec3Arg(force.x, force.y, force.z);
 		m_pBallBody->AddImpulse(newForce);
		m_StrokeCount++;
	}
	else if (pEvent->GetType() == fw::CollisionEvent::GetStaticEventType())
	{
		fw::CollisionEvent* CollisionEvent = static_cast<fw::CollisionEvent*>(pEvent);
		uint32 profileA = CollisionEvent->GetProfileA();
		uint32 profileB = CollisionEvent->GetProfileB();
		if (profileA == 2 || profileB == 2)
		{
			m_hasWon = true;
		}
	}
	else if (pEvent->GetType() == ResetGameEvent::GetStaticEventType())
	{
		ResetGame();
	}

}

void MiniPuttScene::StartFrame(float deltaTime)
{
	Super::StartFrame(deltaTime);
}

void MiniPuttScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	fw::UpdateJoltWorld(m_pWorldBundle, deltaTime);

	vec3 pos = vec3(m_pBallBody->GetPosition().GetX(), m_pBallBody->GetPosition().GetY(), m_pBallBody->GetPosition().GetZ());
	m_pGolfBall->GetTransformComponent()->m_position = pos;

	vec3 rotation = vec3(m_pBallBody->GetRotation().GetX(), m_pBallBody->GetRotation().GetY(), m_pBallBody->GetRotation().GetZ());

	rotation *= 360;
	
	m_pGolfBall->GetTransformComponent()->m_rotation = rotation;

	m_pGolfBall->Update(deltaTime);
	m_pOrbitCamera->Update(deltaTime);
	vec3 lightPos = m_pLight->GetTransformComponent()->m_position;
	vec3 playerPos = m_pGolfBall->GetTransformComponent()->m_position;
	m_pLight->GetTransformComponent()->m_position = vec3(playerPos.x, playerPos.y + 5.0f, playerPos.z);
	m_pController->StartFrame();

}

void MiniPuttScene::Draw()
{
	Super::Draw();
	int viewID = EditorView_Game;

	m_pOrbitCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);

	if (m_pGolfBall->IsSwinging())
	{
		ImGui::Begin("Power");

		float power = m_pGolfBall->GetPower();
		float maxPower = m_pGolfBall->GetMaxPower();
		float fraction = power / maxPower;
		ImGui::ProgressBar(fraction);
		ImGui::End();
	}

	if (m_hasWon)
	{
		ImGui::Begin("Win Screen");
		ImGui::Text("You WIN\n Number of stroke: %d", m_StrokeCount);
		ImGui::Text("Press r to restart");
		ImGui::End();
	}
}

fw::Camera* MiniPuttScene::GetCamera()
{
	return m_pOrbitCamera;
}

void MiniPuttScene::ResetGame()
{
	m_hasWon = false;
	m_StrokeCount = 0;

	m_pGolfBall->GetTransformComponent()->m_position = m_golfballStartingPos;
	m_pGolfBall->GetTransformComponent()->m_rotation = vec3(0.0f, 0.0f, 0.0f);

	fw::DestroyJoltBody(m_pWorldBundle->m_pWorld, m_pBallBody);
	m_pBallBody = fw::CreateSphereJoltBody(m_pWorldBundle->m_pWorld, m_pGolfBall->GetTransformComponent()->m_position, 0.025f, true, 0.01f, m_pGolfBall);

}

