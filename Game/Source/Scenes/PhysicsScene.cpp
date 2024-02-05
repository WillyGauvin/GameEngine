#include "PhysicsScene.h"
#include "Events/GameEvents.h"
#include "Game.h"

PhysicsScene::PhysicsScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
    m_pCamera->SetPosition(vec3(0, 0, 0));

    Game* game = static_cast<Game*>(m_pGameCore);
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, "Box1", vec3(5.0f, 10.0f, 0.0f), getMesh("Square"), getMaterial("Blue")));
   // m_Objects.push_back(new fw::GameObject(this, "Box2", vec3(5.0f, 0.0f, 0.0f), getMesh("Square"), getMaterial("Blue")));
    m_Objects.push_back(new fw::GameObject(this, "RevoluteJoint", vec3(0.0f, 0.0f, 0.0f), getMesh("Square"), getMaterial("Green")));
    m_Objects.push_back(new fw::GameObject(this, "Florr", vec3(0.0f, -10.0f, 0.0f), getMesh("Square"), getMaterial("Green")));


    m_Objects[0]->CreateBody(true);
    m_Objects[1]->CreateBody(true);

    CreatePrismaticJoint(m_Objects[1]->GetBody(), m_Objects[0]->GetBody(), vec2(0,0), vec2(1,0));


    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position = b2Vec2(m_Objects[2]->GetPosition().x, m_Objects[2]->GetPosition().y);
    b2Body* body = m_pWorld->CreateBody(&bodyDef);

    b2PolygonShape poly;
    poly.SetAsBox(1000.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);
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
    m_pWorld->Step(deltaTime, 8, 3);

    for (fw::GameObject* object : m_Objects)
    {
        object->Update(deltaTime);
    }

    m_pCamera->Update(deltaTime);
}

void PhysicsScene::Draw()
{
    int viewID = 0;

    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform(m_pGameCore->GetUniforms()->GetUniform("u_Time"), &time);


    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    for (fw::GameObject* object : m_Objects)
    {
        object->Draw(m_pCamera);
    }
}
