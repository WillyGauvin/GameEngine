#include "LightScene.h"
#include "Game.h"

LightScene::LightScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>


	m_pCube = new fw::GameObject(this);
	m_pCube->AddComponent(new fw::RenderComponent(m_pCube, getMesh("Tree"), getMaterial("LightTest")));
	m_pCube->AddComponent(new fw::TransformComponent(m_pCube, vec3(0.0f,0.0f,0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(10.0f, 10.0f, 10.0f)));
	m_Objects.push_back(m_pCube);

	m_cameraAt = vec3(0.0f, -15.0f, 0.0f);
	m_cameraEye = vec3(0.0f, 75.0f, -100.0f);
	m_pCamera->SetEye(m_cameraEye);
	m_pCamera->SetAt(m_cameraAt);
}

LightScene::~LightScene()
{
}

void LightScene::ExecuteEvent(fw::Event* pEvent)
{
}

void LightScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void LightScene::Update(float deltaTime)
{
	m_pComponentManager->UpdateTransforms();
	m_pCamera->SetEye(m_cameraEye);
	m_pCamera->SetAt(m_cameraAt);
	m_pCamera->Update(deltaTime);
}

void LightScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);

	ImGui::Begin("CameraEye");
	ImGui::SliderFloat("X", &m_cameraEye.x, -100.0f, 100.0f);
	ImGui::SliderFloat("Y", &m_cameraEye.y, -100.0f, 100.0f);
	ImGui::SliderFloat("Z", &m_cameraEye.z, -100.0f, 100.0f);
	ImGui::End();

	ImGui::Begin("CameraAt");
	ImGui::SliderFloat("X", &m_cameraAt.x, -100.0f, 100.0f);
	ImGui::SliderFloat("Y", &m_cameraAt.y, -100.0f, 100.0f);
	ImGui::SliderFloat("Z", &m_cameraAt.z, -100.0f, 100.0f);
	ImGui::End();

}
