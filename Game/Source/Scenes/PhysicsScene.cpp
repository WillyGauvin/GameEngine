#include "PhysicsScene.h"
#include "Events/GameEvents.h"
#include "Game.h"
#include "EventSystem/Events.h"

PhysicsScene::PhysicsScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{

    Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    fw::GameObject* G1 = new fw::GameObject(this, "Ball");
    G1->AddComponent(new fw::RenderComponent(G1, getMesh("Circle"), getMaterial("Green")));
    G1->AddComponent(new fw::TransformComponent(G1, vec3(0, 10, 0), vec3(0, 0, 0), vec3(0.15,0.15,0)));
    fw::PhysicsComponent* G1physics = new fw::PhysicsComponent(G1, m_pWorld, true, fw::PhysicsCategories::PhysicsCategory_Ball);
    G1physics->SetCircle();
    G1->AddComponent(G1physics);
    
    m_Objects.push_back(G1);


    fw::GameObject* LeftWall = new fw::GameObject(this, "Wall");
    LeftWall->AddComponent(new fw::RenderComponent(LeftWall, getMesh("Square"), getMaterial("Blue")));
    LeftWall->AddComponent(new fw::TransformComponent(LeftWall, vec3(0, -10, 0), vec3(0, 0, 0), vec3(10, 2, 0)));
    fw::PhysicsComponent* WallPhysics = new fw::PhysicsComponent(LeftWall, m_pWorld, false, fw::PhysicsCategories::PhysicsCategory_Wall);
    WallPhysics->SetBox();
    LeftWall->AddComponent(WallPhysics);
    m_Objects.push_back(LeftWall);


    m_pEventManager->RegisterListener("CollisionEvent", this);






;}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::ExecuteEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == "CollisionEvent")
    {
        fw::CollisionEvent* collisionEvent = static_cast<fw::CollisionEvent*>(pEvent);
        if (collisionEvent->GetBody1());
    }
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
