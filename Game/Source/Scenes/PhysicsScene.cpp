#include "PhysicsScene.h"
#include "Events/GameEvents.h"
#include "Game.h"

PhysicsScene::PhysicsScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{

    Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    fw::GameObject* G1 = new fw::GameObject(this, "Box1");
    G1->AddComponent(new fw::RenderComponent(G1, getMesh("Square"), getMaterial("Green")));
    G1->AddComponent(new fw::TransformComponent(G1, vec3(10, 0, 0), vec3(0, 0, 0), vec3(1, 1, 0)));
    fw::PhysicsComponent* G1physics = new fw::PhysicsComponent(G1, m_pWorld, true);
    G1physics->SetBox(vec2(1, 1));
    G1->AddComponent(G1physics);
    

}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::ExecuteEvent(fw::Event* pEvent)
{
}

void PhysicsScene::StartFrame(float deltaTime)
{
    m_pEventManager->ProcessEvents();
}

void PhysicsScene::Update(float deltaTime)
{
    m_pComponentManager->UpdateBodies(m_pWorld, deltaTime);

    m_pComponentManager->UpdateTransforms();

    m_pCamera->Update(deltaTime);
    
}

void PhysicsScene::Draw()
{
    int viewID = 0;
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    m_pComponentManager->RenderMeshes();
}
