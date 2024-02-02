#include "TestScene.h"
#include "Game.h"

TestScene::TestScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
    Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, "Box1", vec3(10,0,0), getMesh("Square"), getMaterial("Red")));
    m_Objects.push_back(new fw::GameObject(this, "Box2", vec3(10,10,0), getMesh("Square"), getMaterial("Blue")));

    for (fw::GameObject* gameObject : m_Objects)
    {
        gameObject->AddComponent(new fw::TransformComponent(gameObject, gameObject->GetPosition(), gameObject->GetRotation(), gameObject->GetScale()));
        gameObject->AddComponent(new fw::RenderComponent(gameObject, gameObject->GetMesh(), gameObject->GetMaterial()));
    }
}

TestScene::~TestScene()
{
}

void TestScene::ExecuteEvent(fw::Event* pEvent)
{
}

void TestScene::StartFrame(float deltaTime)
{
	m_pEventManager->ProcessEvents();
}

void TestScene::Update(float deltaTime)
{
	m_pCamera->Update(deltaTime);
    m_pComponentManager->UpdateTransforms();
}

void TestScene::Draw()
{
    int viewID = 0;
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    m_pComponentManager->RenderMeshes();
}
