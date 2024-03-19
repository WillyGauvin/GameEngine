#include "OBJScene.h"
#include "Game.h"

OBJScene::OBJScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
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


	//fw::GameObject* m_pTree = new fw::GameObject(this);
	//m_pTree->AddComponent(new fw::RenderComponent(m_pTree, getMesh("Tree"), getMaterial("Tree")));
	//m_pTree->AddComponent(new fw::TransformComponent(m_pTree, vec3(10, 0, 10), vec3(0, 0, 0), vec3(1, 1, 1)));
	//m_Objects.push_back(m_pTree);

	fw::GameObject* cube1 = new fw::GameObject(this);
	cube1->AddComponent(new fw::RenderComponent(cube1, getMesh("Cube"), getMaterial("Green")));
	cube1->AddComponent(new fw::TransformComponent(cube1, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(cube1);

	fw::GameObject* cube2 = new fw::GameObject(this);
	cube2->AddComponent(new fw::RenderComponent(cube2, getMesh("Cube"), getMaterial("Green")));
	cube2->AddComponent(new fw::TransformComponent(cube2, vec3(10, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(cube2);

	fw::GameObject* cube3 = new fw::GameObject(this);
	cube3->AddComponent(new fw::RenderComponent(cube3, getMesh("Cube"), getMaterial("Green")));
	cube3->AddComponent(new fw::TransformComponent(cube3, vec3(0, 0, 10), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(cube3);

	fw::GameObject* cube4 = new fw::GameObject(this);
	cube4->AddComponent(new fw::RenderComponent(cube4, getMesh("Cube"), getMaterial("Green")));
	cube4->AddComponent(new fw::TransformComponent(cube4, vec3(10, 0, 10), vec3(0, 0, 0), vec3(1, 1, 1)));
	m_Objects.push_back(cube4);

	//m_pTestDice = new fw::GameObject(this);
	//m_pTestDice->AddComponent(new fw::RenderComponent(m_pTestDice, getMesh("ObjTest"), getMaterial("Blue")));
	//m_pTestDice->AddComponent(new fw::TransformComponent(m_pTestDice, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1)));
	//m_Objects.push_back(m_pTestDice);

	m_pCamera->SetEye(vec3(5, 15, 0));
	m_pCamera->SetAt(vec3(0, -10, 0));

	PlaceTrees();
	
	
}

OBJScene::~OBJScene()
{
}

void OBJScene::ExecuteEvent(fw::Event* pEvent)
{

}

void OBJScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void OBJScene::Update(float deltaTime)
{
	m_pComponentManager->UpdateTransforms();
	m_pCamera->Update(deltaTime);

}

void OBJScene::Draw()
{
	int viewID = EditorView_Game;

	m_pCamera->Enable(viewID);

	m_pComponentManager->RenderMeshes(viewID);
}

void OBJScene::PlaceTrees()
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

		tree->AddComponent(new fw::RenderComponent(tree, getMesh("Tree"), getMaterial("Tree")));
		tree->AddComponent(new fw::TransformComponent(tree, PossiblePositions[randomIndex], vec3(0, randRotation, 0), vec3(randScale, randScale, randScale)));
	}
	
}

