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

	m_pWorldBundle = fw::CreateJoltWorld(m_pEventManager);

	m_pPlane = new fw::GameObject(this);
	m_pPlane->AddComponent(new fw::RenderComponent(m_pPlane, getMesh("Plane"), getMaterial("Water")));
	m_pPlane->AddComponent(new fw::TransformComponent(m_pPlane, vec3(-200, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(m_pPlane);

	//m_pIsland = new fw::GameObject(this);
	//m_pIsland->AddComponent(new fw::RenderComponent(m_pIsland, getMesh("HeightTest"), getMaterial("Rock")));
	//m_pIsland->AddComponent(new fw::TransformComponent(m_pIsland, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	//m_Objects.push_back(m_pIsland);

	m_pLight = new fw::GameObject(this);
	m_pLight->AddComponent(new fw::TransformComponent(m_pLight, vec3(0.0f, 50.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_pLight->AddComponent(new fw::RenderComponent(m_pLight, getMesh("Cube"), getMaterial("White")));
	m_pLight->AddComponent(new fw::LightComponent(m_pLight, 100.0f, 0.1f, 5.0f, 10.0f));
	m_Objects.push_back(m_pLight);
	m_Lights.push_back(m_pLight);

	m_pCourse = new fw::GameObject(this);
	m_pCourse->AddComponent(new fw::RenderComponent(m_pCourse, getMesh("MiniPuttCourse"), getMaterial("MiniPuttCourse")));
	m_pCourse->AddComponent(new fw::TransformComponent(m_pCourse, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	m_Objects.push_back(m_pCourse);
	//PlaceTrees();

	m_pController = new VirtualController(m_pEventManager);

	m_pGolfBall = new GolfBall(this);
	m_pGolfBall->SetController(m_pController);
	m_pGolfBall->GetTransformComponent()->m_position = vec3(0.5f, 2.0f, 4.0f);

	m_pOrbitCamera = new OrbitCamera(this, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), m_pGolfBall->GetTransformComponent()->m_position, m_pController, m_pGolfBall);

	m_pOrbitCamera->SetStartingDistance(1.0f);
	m_pCourseBody = fw::CreateMeshJoltBody(m_pWorldBundle->m_pWorld, m_pCourse->GetTransformComponent()->m_position, m_pCourse->GetTransformComponent()->m_rotation, m_pCourse->GetTransformComponent()->m_scale, false, 1.0f, m_pCourse);

	m_pBallBody = fw::CreateSphereJoltBody(m_pWorldBundle->m_pWorld, m_pGolfBall->GetTransformComponent()->m_position, 0.025f, true, 1.0f, m_pGolfBall);

	m_pEventManager->RegisterListener(SwingClubEvent::GetStaticEventType(), this);
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
	/*vec3 position = m_pLight->GetTransformComponent()->m_position;

	ImGui::Begin("Light Position");
	ImGui::Text("X: %f\nY: %f\nZ %f", position.x, position.y, position.z);
	ImGui::End();

	m_pLight->GetTransformComponent()->m_position = position;

	ImGui::Begin("LightColor");

	fw::color4f fcolor = m_pLight->GetRenderComponent()->m_pMaterial->GetColor();
	static float color[] = { fcolor.r, fcolor.g, fcolor.b, fcolor.a };
	ImGui::ColorEdit4("edit", color);
	ImGui::ColorPicker4("picker", color);
	m_pLight->GetRenderComponent()->m_pMaterial->SetColor(fw::color4f(color[0], color[1], color[2], color[3]));

	ImGui::End();*/


	//ImGui::Begin("Light Properties");

	////vec3 position = m_pLight->GetTransformComponent()->m_position;
	////ImGui::Text("Position\n x: %f, y: %f, z: %f", position.x, position.y, position.z);
	//ImGui::SliderFloat("Range", &m_pLight->GetLightComponent()->m_LightRange, 0.0f, 200.0f);
	//ImGui::SliderFloat("Ambient Percentage", &m_pLight->GetLightComponent()->m_AmbientPerc, 0.0f, 3.0f);
	//ImGui::SliderFloat("Falloff Exponent", &m_pLight->GetLightComponent()->m_FalloffExp, 0.0f, 5.0f);
	//ImGui::SliderFloat("Specular Exponent", &m_pLight->GetLightComponent()->m_SpecularExp, 0.0f, 10.0f);

	//ImGui::End();
}

fw::Camera* MiniPuttScene::GetCamera()
{
	return m_pOrbitCamera;
}

