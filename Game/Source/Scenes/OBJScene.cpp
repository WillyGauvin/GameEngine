#include "OBJScene.h"
#include "Game.h"

OBJScene::OBJScene(fw::GameCore* pGameCore) : Scene(pGameCore)
{
	Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

	//m_pPlane = new fw::GameObject(this);
	//m_pPlane->AddComponent(new fw::RenderComponent(m_pPlane, getMesh("Plane"), getMaterial("Water")));
	//m_pPlane->AddComponent(new fw::TransformComponent(m_pPlane, vec3(-200, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1)));
	//m_Objects.push_back(m_pPlane);

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

	m_pCamera->SetEye(vec3(0, 30, -15));
	m_pCamera->SetAt(vec3(0, -15, 0));

	
	
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
