#include "LandingScene.h"
#include "Game.h"
#include "Objects/VirtualController.h"
#include "Events/GameEvents.h"

LandingScene::LandingScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	m_pController = new VirtualController(m_pEventManager);

	Game* game = static_cast<Game*>(m_pGameCore);
	m_pCamera->SetEye(vec3(0, 50, -100));
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_Objects.push_back(new fw::GameObject(this));
	fw::GameObject* moon = m_Objects[0];
	moon->AddComponent(new fw::TransformComponent(moon, vec3(0, 0, 0), vec3(0, 0, 0), vec3(100, 1, 1)));
	moon->AddComponent(new fw::RenderComponent(moon, getMesh("Square"), getMaterial("Blue")));
	moon->AddComponent(new fw::PhysicsComponent(moon, m_pWorld, false));
	moon->GetPhysicsComponent()->SetBox();

	//m_pArrow = new fw::GameObject(this);
	//m_Objects.push_back(m_pArrow);
	//m_pArrow->AddComponent(new fw::TransformComponent(m_pArrow, vec3(10,10, 0), vec3(0, 0, 90), vec3(10, 0.5, 1)));
	//m_pArrow->AddComponent(new fw::RenderComponent(m_pArrow, getMesh("Square"), getMaterial("Blue")));


	m_pOff = getMaterial("ShipOff");
	m_pLeft = getMaterial("ShipLeft");
	m_pRight = getMaterial("ShipRight");
	m_pBoth = getMaterial("ShipBoth");
	m_pCrash = getMaterial("ShipCrash");

	m_pPlayer = new fw::GameObject(this);
	m_Objects.push_back(m_pPlayer);
	m_pPlayer->AddComponent(new fw::TransformComponent(m_pPlayer, vec3(0, 50, 0), vec3(0, 0, 0), vec3(10, 10, 1)));
	m_pPlayer->AddComponent(new fw::RenderComponent(m_pPlayer, getMesh("Sprite"), m_pOff));
	m_pPlayer->AddComponent(new fw::PhysicsComponent(m_pPlayer, m_pWorld, true));
	m_pPlayer->GetPhysicsComponent()->SetBox(vec2(5, 7.5));

	//m_Objects.push_back(new fw::GameObject(this));
	//fw::GameObject* mainbody = m_Objects[3];
	//mainbody->AddComponent(new fw::TransformComponent(mainbody, vec3(0, 10, 0), vec3(0, 0, 0), vec3(5, 7.5, 1)));
	//mainbody->AddComponent(new fw::RenderComponent(mainbody, getMesh("Square"), getMaterial("Red")));
	//mainbody->AddComponent(new fw::PhysicsComponent(mainbody, m_pWorld, false));
	//mainbody->GetPhysicsComponent()->SetBox();

	m_pLeftEngine = new fw::GameObject(this);
	m_Objects.push_back(m_pLeftEngine);
	m_pLeftEngine->AddComponent(new fw::TransformComponent(m_pLeftEngine, vec3(-2.85, 49.7, 0), vec3(0, 0, 0), vec3(0.75, 2.5, 1)));
//	m_pLeftEngine->AddComponent(new fw::RenderComponent(m_pLeftEngine, getMesh("Square"), getMaterial("Blue")));
	m_pLeftEngine->AddComponent(new fw::PhysicsComponent(m_pLeftEngine, m_pWorld, true));
	m_pLeftEngine->GetPhysicsComponent()->SetBox();
	
	m_pRightEngine = new fw::GameObject(this);
	m_Objects.push_back(m_pRightEngine);
	m_pRightEngine->AddComponent(new fw::TransformComponent(m_pRightEngine, vec3(2.85, 49.7, 0), vec3(0, 0, 0), vec3(0.75, 2.5, 1)));
//	m_pRightEngine->AddComponent(new fw::RenderComponent(m_pRightEngine, getMesh("Square"), getMaterial("Blue")));
	m_pRightEngine->AddComponent(new fw::PhysicsComponent(m_pRightEngine, m_pWorld, true));
	m_pRightEngine->GetPhysicsComponent()->SetBox();

	m_pPlayer->GetPhysicsComponent()->CreateWeldJoint(m_pLeftEngine, vec2(-2.5, 0), vec2(0.375, 0.3));
	m_pPlayer->GetPhysicsComponent()->CreateWeldJoint(m_pRightEngine, vec2(2.5, 0), vec2(-0.375, 0.3));






	m_pEventManager->RegisterListener("InputEvent", this);
	m_pEventManager->RegisterListener("CollisionEvent", this);
	m_pEventManager->RegisterListener("ThrusterActivateEvent", this);
	m_pEventManager->RegisterListener("ResetEvent", this);

}

LandingScene::~LandingScene()
{
}

void LandingScene::ExecuteEvent(fw::Event* pEvent)
{
	if (pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType())
	{
		int width = GetGameCore()->GetFramework()->GetWindowClientWidth();
		int height = GetGameCore()->GetFramework()->GetWindowClientHeight();

		m_pCamera->SetAspectRatio((float)width / height);

	}

	if (pEvent->GetType() == fw::CollisionEvent::GetStaticEventType())
	{
		fw::CollisionEvent* event = static_cast<fw::CollisionEvent*>(pEvent);

	}
}

void LandingScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
	m_pController->StartFrame();
}

void LandingScene::Update(float deltaTime)
{
	m_pComponentManager->UpdateTransforms();

	m_pComponentManager->UpdateBodies(m_pWorld, deltaTime);

	vec2 shipPosition = vec2(m_pPlayer->GetTransformComponent()->m_position.x, m_pPlayer->GetTransformComponent()->m_position.y);
	float CameraZPos = ( - 1.0f / 50.0f) * powf(shipPosition.y, 2) - 45.0f;
	fw::MyClamp<float>(CameraZPos, -200, -20);
	m_pCamera->SetEye(vec3(shipPosition.x, shipPosition.y, CameraZPos));

	//m_pCamera->SetEye(vec3())
	m_pCamera->Update(deltaTime);

	if (m_pController->isActionHeld(VirtualController::Left) && m_pController->isActionHeld(VirtualController::Right))
	{
		m_pPlayer->GetRenderComponent()->SetMaterial(m_pBoth);
		m_pPlayer->GetPhysicsComponent()->AddUpForce(1000.0f);
		
	}
	else if (m_pController->isActionHeld(VirtualController::Right))
	{
		m_pPlayer->GetRenderComponent()->SetMaterial(m_pRight);
		m_pRightEngine->GetPhysicsComponent()->AddUpForce(500.0f);


	}
	else if (m_pController->isActionHeld(VirtualController::Left))
	{
		m_pPlayer->GetRenderComponent()->SetMaterial(m_pLeft);
		m_pLeftEngine->GetPhysicsComponent()->AddUpForce(500.0f);


	}
	else
	{
		m_pPlayer->GetRenderComponent()->SetMaterial(m_pOff);
	}
	if (m_pController->isActionHeld(VirtualController::Reset))
	{
		Reset();
	}
	//m_pArrow->GetTransformComponent()->m_rotation = vec3(0, 0, fw::radsToDegrees(m_pPlayer->GetPhysicsComponent()->m_pBody->GetAngle()) * -1 + 90);
}

void LandingScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);

	if (ImGui::Begin("Debug"))
	{
		ImGui::Text("UpVector: %f, %f", m_pPlayer->GetPhysicsComponent()->UpVector.x, m_pPlayer->GetPhysicsComponent()->UpVector.y);
		ImGui::Text("Angle: %f", fw::radsToDegrees(m_pPlayer->GetPhysicsComponent()->m_pBody->GetAngle()));
		
	}
	ImGui::End();
}

void LandingScene::Reset()
{
	m_pPlayer->GetTransformComponent()->Reset();
	m_pPlayer->GetPhysicsComponent()->Reset();

	m_pLeftEngine->GetTransformComponent()->Reset();
	m_pLeftEngine->GetPhysicsComponent()->Reset();

	m_pRightEngine->GetTransformComponent()->Reset();
	m_pRightEngine->GetPhysicsComponent()->Reset();
}
