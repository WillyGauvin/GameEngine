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


	m_pLight = new fw::GameObject(this);
	m_pLight->AddComponent(new fw::TransformComponent(m_pLight, vec3(0.0f, 30.0f, 20.0f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 5.0f, 5.0f)));
	m_pLight->AddComponent(new fw::RenderComponent(m_pLight, getMesh("Cube"), getMaterial("Blue")));
	m_pLight->AddComponent(new fw::LightComponent(m_pLight, 100.0f, 0.1f, 1.0f, 5.0f));
	m_Objects.push_back(m_pLight);
	m_Lights.push_back(m_pLight);




	m_cameraAt = vec3(0.0f, -15.0f, 0.0f);
	m_cameraEye = vec3(0.0f, 55.0f, -35.0f);
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
	m_pComponentManager->Update(deltaTime);
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

	ImGui::Begin("LightColor");

	fw::color4f fcolor = m_pLight->GetRenderComponent()->m_pMaterial->GetColor();
	static float color[] = { fcolor.r, fcolor.g, fcolor.b, fcolor.a };
	ImGui::ColorEdit4("edit", color);
	ImGui::ColorPicker4("picker", color);
	m_pLight->GetRenderComponent()->m_pMaterial->SetColor(fw::color4f(color[0], color[1], color[2], color[3]));

	ImGui::End();

	ImGui::Begin("Light Properties");

	vec3 position = m_pLight->GetTransformComponent()->m_position;
	ImGui::Text("Position\n x: %f, y: %f, z: %f", position.x, position.y, position.z);
	ImGui::SliderFloat("Range", &m_pLight->GetLightComponent()->m_LightRange, 0.0f, 200.0f);
	ImGui::SliderFloat("Ambient Percentage", &m_pLight->GetLightComponent()->m_AmbientPerc, 0.0f, 3.0f);
	ImGui::SliderFloat("Falloff Exponent", &m_pLight->GetLightComponent()->m_FalloffExp, 0.0f, 5.0f);
	ImGui::SliderFloat("Specular Exponent", &m_pLight->GetLightComponent()->m_SpecularExp, 0.0f, 10.0f);

	ImGui::End();

}
