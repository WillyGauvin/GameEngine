#include "Framework.h"

#include "DynamicLightScene.h"
#include "Game.h"
#include "Objects/VirtualController.h"
#include "Objects/OrbitCamera.h"
#include "Objects/Player.h"

DynamicLightScene::DynamicLightScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{

	m_pController = new VirtualController(m_pEventManager);

	m_pPlayer = new Player(this);
	m_pPlayer->SetController(m_pController);

	m_pOrbitCamera = new OrbitCamera(this, vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 1.0f, 0.0f), m_pPlayer->GetTransformComponent()->m_position, m_pController, m_pPlayer);

	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	m_pPlane = new fw::GameObject(this);
	m_pPlane->AddComponent(new fw::RenderComponent(m_pPlane, getMesh("Plane"), getMaterial("Water")));
	m_pPlane->AddComponent(new fw::TransformComponent(m_pPlane, vec3(-200, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(m_pPlane);

	m_pIsland = new fw::GameObject(this);
	m_pIsland->AddComponent(new fw::RenderComponent(m_pIsland, getMesh("HeightTest"), getMaterial("Rock")));
	m_pIsland->AddComponent(new fw::TransformComponent(m_pIsland, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(m_pIsland);


	m_pLight = new fw::GameObject(this);
	m_pLight->AddComponent(new fw::TransformComponent(m_pLight, vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 5.0f, 5.0f)));
	m_pLight->AddComponent(new fw::RenderComponent(m_pLight, getMesh("Cube"), getMaterial("Blue")));
	m_pLight->AddComponent(new fw::LightComponent(m_pLight, 100.0f, 0.1f, 1.0f, 5.0f));
	m_Objects.push_back(m_pLight);
	m_Lights.push_back(m_pLight);

	PlaceTrees();
	
	
}

DynamicLightScene::~DynamicLightScene()
{
}

void DynamicLightScene::ExecuteEvent(fw::Event* pEvent)
{

}

void DynamicLightScene::StartFrame(float deltaTime)
{
	Super::StartFrame(deltaTime);
}

void DynamicLightScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
	m_pPlayer->Update(deltaTime);
	m_pOrbitCamera->Update(deltaTime);
	m_pController->StartFrame();

}

void DynamicLightScene::Draw()
{
	Super::Draw();
	int viewID = EditorView_Game;

	m_pOrbitCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);


	vec3 position = m_pLight->GetTransformComponent()->m_position;

	ImGui::Begin("Light Position");
	ImGui::SliderFloat("X", &position.x, -50.0f, 150.0f);
	ImGui::SliderFloat("Y", &position.y, -50.0f, 150.0f);
	ImGui::SliderFloat("Z", &position.z, -50.0f, 150.0f);
	ImGui::End();

	m_pLight->GetTransformComponent()->m_position = position;

	ImGui::Begin("LightColor");

	fw::color4f fcolor = m_pLight->GetRenderComponent()->m_pMaterial->GetColor();
	static float color[] = { fcolor.r, fcolor.g, fcolor.b, fcolor.a };
	ImGui::ColorEdit4("edit", color);
	ImGui::ColorPicker4("picker", color);
	m_pLight->GetRenderComponent()->m_pMaterial->SetColor(fw::color4f(color[0], color[1], color[2], color[3]));

	ImGui::End();


	ImGui::Begin("Light Properties");

	//vec3 position = m_pLight->GetTransformComponent()->m_position;
	//ImGui::Text("Position\n x: %f, y: %f, z: %f", position.x, position.y, position.z);
	ImGui::SliderFloat("Range", &m_pLight->GetLightComponent()->m_LightRange, 0.0f, 200.0f);
	ImGui::SliderFloat("Ambient Percentage", &m_pLight->GetLightComponent()->m_AmbientPerc, 0.0f, 3.0f);
	ImGui::SliderFloat("Falloff Exponent", &m_pLight->GetLightComponent()->m_FalloffExp, 0.0f, 5.0f);
	ImGui::SliderFloat("Specular Exponent", &m_pLight->GetLightComponent()->m_SpecularExp, 0.0f, 10.0f);

	ImGui::End();
}

void DynamicLightScene::PlaceTrees()
{
	Game* game = static_cast<Game*>(m_pGameCore);
	#define getMesh game->GetResourceManager()->Get<fw::Mesh>
	#define getMaterial game->GetResourceManager()->Get<fw::Material>

	std::vector<vec3> vertexs = m_pIsland->GetRenderComponent()->m_pMesh->GetVertex();
	
	std::vector<vec3> PossiblePositions;

	for (int i = 0; i < vertexs.size() - 1; i++)
	{
		if (vertexs[i].y >= 2.0f)
		{
			PossiblePositions.push_back(vertexs[i]);	
		}
	}

	for (int i = 0; i < 30; i++)
	{
		int randomIndex = rand() % PossiblePositions.size();
		

		m_Objects.push_back(new fw::GameObject(this));
		fw::GameObject* tree = m_Objects[m_Objects.size() - 1];

		float LO = 0.0f;
		float HI = 360.0f;
		float randRotation = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));


		LO = 0.8f;
		HI = 1.2f;
		float randScale = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

		tree->AddComponent(new fw::RenderComponent(tree, getMesh("Tree"), getMaterial("LightedTree")));
		tree->AddComponent(new fw::TransformComponent(tree, PossiblePositions[randomIndex], vec3(0, randRotation, 0), vec3(randScale, randScale, randScale)));
	}
	
}

