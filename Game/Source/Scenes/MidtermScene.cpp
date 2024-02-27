#include "MidtermScene.h"
#include "Game.h"

MidtermScene::MidtermScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
	//m_pCamera->SetEye(vec3(5, 5, -15));
	//m_pCamera->SetAt(vec3(0, -5, 0));
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_pLeftBox = new fw::GameObject(this);
	m_Objects.push_back(m_pLeftBox);
	m_pLeftBox->AddComponent(new fw::TransformComponent(m_pLeftBox, vec3(-5, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_pLeftBox->AddComponent(new fw::RenderComponent(m_pLeftBox, getMesh("Square"), getMaterial("Blue")));
	m_pLeftBox->AddComponent(new fw::PhysicsComponent(m_pLeftBox, m_pWorld, false));
	m_pLeftBox->GetPhysicsComponent()->SetBox();

	m_pRightBox = new fw::GameObject(this);
	m_Objects.push_back(m_pRightBox);
	m_pRightBox->AddComponent(new fw::TransformComponent(m_pRightBox, vec3(5, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_pRightBox->AddComponent(new fw::RenderComponent(m_pRightBox, getMesh("Square"), getMaterial("Blue")));
	m_pRightBox->AddComponent(new fw::PhysicsComponent(m_pRightBox, m_pWorld, false));
	m_pRightBox->GetPhysicsComponent()->SetBox();

	m_pPlayer = new fw::GameObject(this);
	m_Objects.push_back(m_pPlayer);
	m_pPlayer->AddComponent(new fw::TransformComponent(m_pPlayer, vec3(-10, 2, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_pPlayer->AddComponent(new fw::RenderComponent(m_pPlayer, getMesh("Square"), getMaterial("Blue")));
	m_pPlayer->AddComponent(new fw::PhysicsComponent(m_pPlayer, m_pWorld, true, MidtermCollisionProfile::Box, MidtermCollisionProfile::BoxProfile));
	m_pPlayer->GetPhysicsComponent()->SetBox();

	m_pPlayer->GetPhysicsComponent()->CreateRevolutionJoint(m_pLeftBox, vec2(4, 4), vec2(0, 0));



	m_pLeftSensor = new fw::GameObject(this);
	m_Objects.push_back(m_pLeftSensor);
	m_pLeftSensor->AddComponent(new fw::TransformComponent(m_pLeftSensor, vec3(-5, 0, 0), vec3(0, 0, 0), vec3(0.5, 20, 1)));
	m_pLeftSensor->AddComponent(new fw::RenderComponent(m_pLeftSensor, getMesh("Square"), getMaterial("Red")));
	m_pLeftSensor->AddComponent(new fw::PhysicsComponent(m_pLeftSensor, m_pWorld, false, MidtermCollisionProfile::LeftSensor, MidtermCollisionProfile::LeftSensorProfile));
	m_pLeftSensor->GetPhysicsComponent()->SetLineCensor();

	m_pRightSensor = new fw::GameObject(this);
	m_Objects.push_back(m_pRightSensor);
	m_pRightSensor->AddComponent(new fw::TransformComponent(m_pRightSensor, vec3(5, 0, 0), vec3(0, 0, 0), vec3(0.5, 20, 1)));
	m_pRightSensor->AddComponent(new fw::RenderComponent(m_pRightSensor, getMesh("Square"), getMaterial("Red")));
	m_pRightSensor->AddComponent(new fw::PhysicsComponent(m_pRightSensor, m_pWorld, false, MidtermCollisionProfile::RightSensor, MidtermCollisionProfile::RightSensorProfile));
	m_pRightSensor->GetPhysicsComponent()->SetLineCensor();











	m_pEventManager->RegisterListener("InputEvent", this);
	m_pEventManager->RegisterListener("CollisionEvent", this);




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
	if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
	{
		fw::InputEvent* event = static_cast<fw::InputEvent*>(pEvent);

		if (event->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
		{
			if (event->GetKeyCode() == 'E')
			{
				m_pPlayer->GetPhysicsComponent()->DestoryJoint();
			}
		}
	}

	if (pEvent->GetType() == fw::CollisionEvent::GetStaticEventType())
	{
		fw::CollisionEvent* event = static_cast<fw::CollisionEvent*>(pEvent);
		if (event->GetObjectB()->GetPhysicsComponent()->m_fixtureDef.filter.categoryBits == MidtermCollisionProfile::LeftSensor && side != CurrentSide::LeftSide)
		{
			//Attach
			side = CurrentSide::LeftSide;
			m_pPlayer->GetPhysicsComponent()->CreateRevolutionJoint(m_pLeftBox);


		}
		else if (event->GetObjectB()->GetPhysicsComponent()->m_fixtureDef.filter.categoryBits == MidtermCollisionProfile::RightSensor && side != CurrentSide::RightSide)
		{
			//Attach
			side = CurrentSide::RightSide;
			m_pPlayer->GetPhysicsComponent()->CreateRevolutionJoint(m_pRightBox);

		}
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
