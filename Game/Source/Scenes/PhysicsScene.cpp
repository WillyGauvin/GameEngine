#include "PhysicsScene.h"
#include "Events/GameEvents.h"

#define B2_USER_SETTINGS

PhysicsScene::PhysicsScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{
    m_pWorld = new b2World( b2Vec2(0,-10));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    m_groundBody = m_pWorld->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = 5.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    m_groundBody->CreateFixture(&fixtureDef);



   /* while (true)
    {
        m_pWorld->Step(1 / 60.0f, 8, 3);

        b2Vec2 pos = m_groundBody->GetPosition();

        fw::OutputMessage("Positon: %0.2f, %0.2f", pos.x, pos.y);
    }*/
}

PhysicsScene::~PhysicsScene()
{
    delete m_pWorld;
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
}
