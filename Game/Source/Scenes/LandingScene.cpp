#include "LandingScene.h"
#include "Game.h"
#include "Objects/VirtualController.h"
#include "Events/GameEvents.h"

struct Packet
{
	char command;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int playerNum;
	vec3 pos;
	vec3 rot;
};

LandingScene::LandingScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	InitNetwork();

	m_pBox2DWorld->SetGravity(b2Vec2(0.0f, -1.62f));
	m_pController = new VirtualController(m_pEventManager);

	Game* game = static_cast<Game*>(m_pGameCore);
	m_pCamera->SetEye(vec3(0, 50, -100));
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_Objects.push_back(new fw::GameObject(this));
	fw::GameObject* moon = m_Objects[0];
	moon->AddComponent(new fw::TransformComponent(moon, vec3(0, -20, 0), vec3(0, 0, 0), vec3(700, 50, 1)));
	moon->AddComponent(new fw::RenderComponent(moon, getMesh("Square"), getMaterial("White")));
	moon->AddComponent(new fw::PhysicsComponent(moon, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));
	moon->GetPhysicsComponent()->SetBox();


	m_pOff = getMaterial("ShipOff");
	m_pLeft = getMaterial("ShipLeft");
	m_pRight = getMaterial("ShipRight");
	m_pBoth = getMaterial("ShipBoth");
	m_pCrash = getMaterial("ShipCrash");
	m_pLanded = getMaterial("ShipLanded");

	m_pPlayer = new fw::GameObject(this);
	m_Objects.push_back(m_pPlayer);
	m_pPlayer->AddComponent(new fw::TransformComponent(m_pPlayer, vec3(0, 50, 0), vec3(0, 0, 0), vec3(10, 10, 1)));
	m_pPlayer->AddComponent(new fw::RenderComponent(m_pPlayer, getMesh("Sprite"), m_pOff));
	m_pPlayer->AddComponent(new fw::PhysicsComponent(m_pPlayer, m_pWorld, true, LunarCollisionProfile::Ship, LunarCollisionProfile::maskCollideAll));
	m_pPlayer->GetPhysicsComponent()->SetBox(vec2(5, 7.5));

	//m_Objects.push_back(new fw::GameObject(this));
	//fw::GameObject* mainbody = m_Objects[m_Objects.size()-1];
	//mainbody->AddComponent(new fw::TransformComponent(mainbody, vec3(0, 50, 0), vec3(0, 0, 0), vec3(5, 7.5, 1)));
	//mainbody->AddComponent(new fw::RenderComponent(mainbody, getMesh("Square"), getMaterial("Red")));
	//mainbody->AddComponent(new fw::PhysicsComponent(mainbody, m_pWorld, false));
	//mainbody->GetPhysicsComponent()->SetBox();

	m_pLeftEngine = new fw::GameObject(this);
	m_Objects.push_back(m_pLeftEngine);
	m_pLeftEngine->AddComponent(new fw::TransformComponent(m_pLeftEngine, vec3(-2.85f, 49.7f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.75f, 2.5f, 1.0f)));
//	m_pLeftEngine->AddComponent(new fw::RenderComponent(m_pLeftEngine, getMesh("Square"), getMaterial("Blue")));
	m_pLeftEngine->AddComponent(new fw::PhysicsComponent(m_pLeftEngine, m_pWorld, true, LunarCollisionProfile::Ship, LunarCollisionProfile::maskCollideAll));
	m_pLeftEngine->GetPhysicsComponent()->SetBox();
	
	m_pRightEngine = new fw::GameObject(this);
	m_Objects.push_back(m_pRightEngine);
	m_pRightEngine->AddComponent(new fw::TransformComponent(m_pRightEngine, vec3(2.85f, 49.7f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.75f, 2.5f, 1.0f)));
//	m_pRightEngine->AddComponent(new fw::RenderComponent(m_pRightEngine, getMesh("Square"), getMaterial("Blue")));
	m_pRightEngine->AddComponent(new fw::PhysicsComponent(m_pRightEngine, m_pWorld, true, LunarCollisionProfile::Ship, LunarCollisionProfile::maskCollideAll));
	m_pRightEngine->GetPhysicsComponent()->SetBox();

	m_pPlayer->GetPhysicsComponent()->CreateWeldJoint(m_pLeftEngine, vec2(-2.5f, 0.0f), vec2(0.375f, 0.3f));
	m_pPlayer->GetPhysicsComponent()->CreateWeldJoint(m_pRightEngine, vec2(2.5f, 0.0f), vec2(-0.375f, 0.3f));



	CreateObstacles();


	m_pEventManager->RegisterListener("InputEvent", this);
	m_pEventManager->RegisterListener("CollisionEvent", this);

	Reset();
}

LandingScene::~LandingScene()
{
	delete m_pController;
	/*delete m_pPlayer;
	delete m_pLeftEngine;
	delete m_pRightEngine;
	*/
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
		if (event->GetProfileA() == LunarCollisionProfile::Ship && event->GetProfileB() == LunarCollisionProfile::Landing)
		{
			m_hasTouchedDown = true;
		}
		if (event->GetProfileA() == LunarCollisionProfile::Ship && event->GetProfileB() == LunarCollisionProfile::Obstacle)
		{
			m_hasTouchedDown = true;
			m_hasCrashed = true;

			int i = rand() % 3 + 1;
			switch (i)
			{
			case 1:
				m_ReasonForCrash = "Can't Land there!";
				break;
			case 2:
				m_ReasonForCrash = "That wasn't a landing zone!";
				break;
			case 3:
				m_ReasonForCrash = "Not a landing spot!";
				break;

			}
			
		}
	}
}

void LandingScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void LandingScene::Update(float deltaTime)
{
	UpdateNetwork();

	m_pComponentManager->UpdateTransforms();

	m_pComponentManager->UpdateBodies(m_pWorld, deltaTime);

	vec2 shipPosition = vec2(m_pPlayer->GetTransformComponent()->m_position.x, m_pPlayer->GetTransformComponent()->m_position.y);
	float CameraZPos = ( - 1.0f / 50.0f) * powf(shipPosition.y, 2) - 45.0f;
	fw::MyClamp<float>(CameraZPos, -200, -20);
	m_pCamera->SetEye(vec3(shipPosition.x, shipPosition.y, CameraZPos));

	m_pCamera->Update(deltaTime);

	// Inputs
	if (m_hasCrashed == false && m_hasSafeLanded == false)
	{
		if (m_pController->isActionHeld(VirtualController::Left) && m_pController->isActionHeld(VirtualController::Right))
		{
			m_pPlayer->GetRenderComponent()->SetMaterial(m_pBoth);
			m_pPlayer->GetPhysicsComponent()->AddUpForce(500.0f);
			m_hasTouchedDown = false;

		}
		else if (m_pController->isActionHeld(VirtualController::Right))
		{
			m_pPlayer->GetRenderComponent()->SetMaterial(m_pRight);
			m_pRightEngine->GetPhysicsComponent()->AddUpForce(250.0f);

			m_hasTouchedDown = false;
		}
		else if (m_pController->isActionHeld(VirtualController::Left))
		{
			m_pPlayer->GetRenderComponent()->SetMaterial(m_pLeft);
			m_pLeftEngine->GetPhysicsComponent()->AddUpForce(250.0f);

			m_hasTouchedDown = false;
		}
		else
		{
			m_pPlayer->GetRenderComponent()->SetMaterial(m_pOff);
		}
	}

	if (m_hasTouchedDown == true && m_hasCrashed == true)
	{
		m_pPlayer->GetRenderComponent()->SetMaterial(m_pCrash);
	}

	else if (m_hasTouchedDown == true && m_hasCrashed == false && m_hasSafeLanded == false)
	{
		if (m_ShipSpeed > 10)
		{
			m_hasCrashed = true;
			m_ReasonForCrash = "You landed too fast!!";
		}
		if (fw::fequal(m_ShipSpeed, 0.0f))
		{
			m_hasSafeLanded = true;
			m_pPlayer->GetRenderComponent()->SetMaterial(m_pLanded);
		}
		else if (m_ShipAngle < -15.0f || m_ShipAngle > 15)
		{
			m_hasCrashed = true;
			m_ReasonForCrash = "Bad angle!";
		}
	}
	if (m_pController->WasActionPressed(VirtualController::Reset))
	{
		Reset();
	}

	//Update Ship Values
	m_ShipSpeed = vec2(m_pPlayer->GetPhysicsComponent()->m_pBody->GetLinearVelocity().x, m_pPlayer->GetPhysicsComponent()->m_pBody->GetLinearVelocity().y).Length();
	m_ShipAngle = fw::radsToDegrees(m_pPlayer->GetPhysicsComponent()->m_pBody->GetAngle());


	m_pController->StartFrame();
}

void LandingScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);

	if (ImGui::Begin("Debug"))
	{
		ImGui::Text("Angle: %f", fw::radsToDegrees(m_pPlayer->GetPhysicsComponent()->m_pBody->GetAngle()));
		ImGui::Text("Speed: %f", m_ShipSpeed);
		//ImGui::Text()
	}
	ImGui::End();

	if (ImGui::Begin("Lander Angle"))
	{
		int angle = (int)m_ShipAngle;
		ImGui::Text("Angle %d", angle);
		if (angle < -15 || angle > 15)
		{
			ImGui::Text("BAD ANGLE!");
		}
		else
		{
			ImGui::Text("Good Angle!");
		}
	}
	ImGui::End();

	if (ImGui::Begin("Lander Speed"))
	{
		int speed = (int)m_ShipSpeed;
		ImGui::Text("Speed %d", speed);
		if (speed > 10)
		{
			ImGui::Text("TOO FAST!");
		}
		else
		{
			ImGui::Text("Good Speed!");
		}
	}
	ImGui::End();
	if (ImGui::Begin("Landing Status"))
	{
		if (m_hasTouchedDown == false)
		{
			ImGui::Text("Landing...");
		}  
		else if (m_hasTouchedDown == true && m_hasCrashed == false && m_hasSafeLanded == false)
		{
			ImGui::Text("Touched Down...");
		}
		else if (m_hasTouchedDown == true && m_hasCrashed == true)
		{
			ImGui::Text("CRASHED!");
			const char* CrashReason = m_ReasonForCrash.c_str();
			ImGui::Text("Reason For Crash");
			ImGui::Text(CrashReason);
		}
		else if (m_hasTouchedDown == true && m_hasSafeLanded == true)
		{
			ImGui::Text("Safely Landed!");
		}
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

	m_hasTouchedDown = false;
	m_hasCrashed = false;
	m_hasSafeLanded = false;
	m_pCamera->SetEye(vec3(0, 50, -100));

}

void LandingScene::CreateObstacles()
{

	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	fw::Mesh* pTriangle = getMesh("Triangle");
	fw::Mesh* pSquare = getMesh("Square");
	fw::Mesh* pCircle = getMesh("Circle");

	fw::GameObject* moonRock = nullptr;

	float xSpacing = 3;
	for (int i = -100; i < 100; i++)
	{
		int num = (rand() % 19) + 1;
		float randRotation = (float)(rand() % 359) + 1;
		float randHeight = (float)(rand() % 4) + 3;
		float randScale = (float)(rand() % 7) + 4;
		switch (num)
		{
		//White Triangle
		case 1:
		case 2:
		case 3:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale, randScale, 5)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pTriangle, getMaterial("White")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetTriangle();
			break;
		//White Square
		case 4:
		case 5:
		case 6:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale, randScale, 5)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pSquare, getMaterial("White")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetBox();
			break;
		//White Circle
		case 7:
		case 8:
		case 9:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale / 4, randScale / 4, 1.25)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pCircle, getMaterial("White")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetCircle(false);
			break;
		//Grey Triangle
		case 10:
		case 11:
		case 12:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale, randScale, 5)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pTriangle, getMaterial("Grey")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetTriangle();
			break;
		//Grey Square
		case 13:
		case 14:
		case 15:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale, randScale, 5)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pSquare, getMaterial("Grey")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetBox();
			break;
		//Grey Circle
		case 16:
		case 17:
		case 18:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, randHeight, 0), vec3(0, 0, randRotation), vec3(randScale / 4, randScale / 4, 1.25)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, pCircle, getMaterial("Grey")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Obstacle, LunarCollisionProfile::maskCollideAll));

			moonRock->GetPhysicsComponent()->SetCircle(false);
			break;
		case 19:
			m_Obstacles.push_back(new fw::GameObject(this));
			moonRock = m_Obstacles[m_Obstacles.size() - 1];
			moonRock->AddComponent(new fw::TransformComponent(moonRock, vec3(i * xSpacing, 7, 0), vec3(0, 0, 0), vec3(8, 8, 5)));
			moonRock->AddComponent(new fw::RenderComponent(moonRock, getMesh("Square"), getMaterial("Red")));
			moonRock->AddComponent(new fw::PhysicsComponent(moonRock, m_pWorld, false, LunarCollisionProfile::Landing, LunarCollisionProfile::maskCollideAll));
			moonRock->GetPhysicsComponent()->SetBox();
			break;
		}
	}
	for (fw::GameObject* object : m_Obstacles)
	{
		m_Objects.push_back(object);
	}
}

void LandingScene::InitNetwork()
{

	m_SocketHandle = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = INADDR_ANY;

	localaddr.sin_port = htons(10000);

	bind(m_SocketHandle, (const sockaddr*)&localaddr, sizeof(sockaddr_in));

	DWORD value = 1;
	ioctlsocket(m_SocketHandle, FIONBIO, &value);

	hostent* host = gethostbyname("10.50.35.181");
	in_addr serverInAddr = *(in_addr*)host->h_addr_list[0];

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_addr = serverInAddr;
	m_serverAddr.sin_port = htons(12345);
}

void LandingScene::UpdateNetwork()
{
	Packet packet; 

	packet.command = 'z';
	packet.r = 0;
	packet.g = 255;
	packet.b = 0;
	packet.playerNum = 13;
	//packet.pos = vec3(-5, 5, 0);
	packet.pos = m_pPlayer->GetTransformComponent()->m_position;
	packet.pos.y -= 40;
	packet.rot = m_pPlayer->GetTransformComponent()->m_rotation;


	int flags = 0;
	sendto(m_SocketHandle, (const char*)&packet, sizeof(Packet),
		flags, (sockaddr*)&m_serverAddr, sizeof(sockaddr_in));


	char buffer[1000];
	int bufferSize = 1000;
	sockaddr_in address;
	int addrLength = sizeof(sockaddr_in);

	int bytes = -500;
	while (bytes != -1)
	{
		int flags = 0;
		bytes = (int)recvfrom(m_SocketHandle, buffer, bufferSize,
			flags, (sockaddr*)&address, &addrLength);

		if (bytes != -1)
		{
			Packet* pPacket = reinterpret_cast<Packet*>(buffer);
		}
	}
}
