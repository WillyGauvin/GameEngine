#include "PhysicsScene.h"
#include "Events/GameEvents.h"
#include "Game.h"
#include "EventSystem/Events.h"
#include "Component/PhysicsComponent.h"

PhysicsScene::PhysicsScene(fw::GameCore* pGameCore) : fw::Scene(pGameCore)
{

    Game* game = static_cast<Game*>(m_pGameCore);
    m_pCamera->SetEye(vec3(0, 5, -70));
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

     /*
  ---------
  BALLS
  ---------
   */

    fw::GameObject* ball1 = new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Ball);
    ball1->AddComponent(new fw::RenderComponent(ball1, getMesh("Circle"), getMaterial("Green")));
    ball1->AddComponent(new fw::TransformComponent(ball1, vec3(-8, 8, 0), vec3(0, 0, 0), vec3(0.15,0.15,0)));
    ball1->AddComponent(new fw::PhysicsComponent(ball1, m_pWorld, true));
    ball1->GetPhysicsComponent()->SetCircle();
    m_Objects.push_back(ball1);
    m_balls.push_back(ball1);

    /*
   ---------
   WALLS
   ---------
    */
    
    //Left
    CreateWall(vec2(-15, 15), 90, vec2(50, 0.5));

    //Right
    CreateWall(vec2(15, 15), 90, vec2(50, 0.5));

    //Roof
    CreateWall(vec2(0, 40), 0, vec2(30, 0.5));

    //BottomLeft
    CreateWall(vec2(-10.5, -14.5), 45, vec2(13, 0.5));

    //BottomRight
    CreateWall(vec2(10.5, -14.5), -45, vec2(13, 0.5));



    //PADDLES

    CreatePaddle(vec2(-6.5, -18.5), vec2(5.5, 0.5), 70.0f, -45.0f, -1);
    
    CreatePaddle(vec2(6.5, -18.5), vec2(5.5, 0.5), 45.0f, -70.0f, 1);


    //BUMPERS

    CreateBumper(vec2(-10.0f, 20.0f), vec2(0.5f,0.5f));

    CreateBumper(vec2(10.0f, 20.0f), vec2(0.5f, 0.5f));
    CreateBumper(vec2(7.0f, 14.0f), vec2(0.5f, 0.5f));
    CreateBumper(vec2(4.0f, 20.0f), vec2(0.5f, 0.5f));


    m_pEventManager->RegisterListener("CollisionEvent", this);
    m_pEventManager->RegisterListener("InputEvent", this);


;}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::ExecuteEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == "InputEvent")
    {
        fw::InputEvent* inputEvent = static_cast<fw::InputEvent*>(pEvent);

        //Start the motor
        if (inputEvent->GetKeyCode() == 'A' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
        {
            for (fw::GameObject* gameObject : m_CounterClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(true);
            }
        }

        if (inputEvent->GetKeyCode() == 'D' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
        {
            for (fw::GameObject* gameObject : m_ClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(true);
            }
        }

        //End the motor
        if (inputEvent->GetKeyCode() == 'A' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
        {
            for (fw::GameObject* gameObject : m_CounterClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(false);
            }
        }

        if (inputEvent->GetKeyCode() == 'D' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
        {
            for (fw::GameObject* gameObject : m_ClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(false);
            }
        }

    }
    else if (pEvent->GetType() == "CollisionEvent")
    {
        fw::CollisionEvent* collisionEvent = static_cast<fw::CollisionEvent*>(pEvent);
        
        //ObjectA Info
        fw::GameObject* ObjectA = collisionEvent->GetObjectA();
        fw::PhysicsCategories CategoryA = ObjectA->GetCollisionCategory();
        vec2 normalA = collisionEvent->GetCollisionNormalA();
        float speedA = collisionEvent->GetSpeedA();

        //ObjectB Info
        fw::GameObject* ObjectB = collisionEvent->GetObjectB();
        fw::PhysicsCategories CategoryB = ObjectB->GetCollisionCategory();
        vec2 normalB = collisionEvent->GetCollisionNormalB();
        float speedB = collisionEvent->GetSpeedB();


        if (CategoryB == fw::PhysicsCategories::PhysicsCategory_Ball)
        {
            switch (CategoryA)
            {
            case fw::PhysicsCategories::PhysicsCategory_Wall:
            {
                ObjectB->GetPhysicsComponent()->AddLinearImpulse(normalA * m_WallImpulse);
                break;
            }
            case fw::PhysicsCategories::PhysicsCategory_Bumper:
            {
                ObjectB->GetPhysicsComponent()->AddLinearImpulse(normalA * m_BumperImpulse);
                break;
            }
            case fw::PhysicsCategories::PhysicsCategory_Paddle:
            {
                ObjectB->GetPhysicsComponent()->AddLinearImpulse(normalA);
                break;
            }
            }
        }
        else if (CategoryA == fw::PhysicsCategories::PhysicsCategory_Ball)
        {
            switch (CategoryB)
            {
            case fw::PhysicsCategories::PhysicsCategory_Wall:
            {
                ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB * m_WallImpulse);
                break;
            }
            case fw::PhysicsCategories::PhysicsCategory_Bumper:
            {
                ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB * m_BumperImpulse);
                break;
            }
            case fw::PhysicsCategories::PhysicsCategory_Paddle:
            {
                ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB);
                break;
            }
            }
        }

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
    
    //Adding extra gravity to balls and paddles. 
    for (fw::GameObject* ball : m_balls)
    {
        ball->GetPhysicsComponent()->AddForce(m_ballExtraGravity);
    }
    for (fw::GameObject* paddle : m_CounterClockWisePaddles)
    {
        if (paddle->GetPhysicsComponent()->isEnabled() == false)
        {
            paddle->GetPhysicsComponent()->AddForce(m_paddleExtraGravity);
        }
    }
    for (fw::GameObject* paddle : m_ClockWisePaddles)
    {
        if (paddle->GetPhysicsComponent()->isEnabled() == false)
        {
            paddle->GetPhysicsComponent()->AddForce(m_paddleExtraGravity);
        }
    }

}

void PhysicsScene::Draw()
{
    int viewID = 0;
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(viewID);

    m_pComponentManager->RenderMeshes();
}

void PhysicsScene::CreateBumper(vec2 position, vec2 scale)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Bumper));

    fw::GameObject* object = m_Objects[m_Objects.size()-1];

    object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Green")));
    object->AddComponent(new fw::TransformComponent(object, vec3(position.x, position.y, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, false));
    object->GetPhysicsComponent()->SetCircle();
}

void PhysicsScene::CreateWall(vec2 position, float rotation, vec2 scale)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Wall));

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];

    object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Blue")));
    object->AddComponent(new fw::TransformComponent(object, vec3(position.x, position.y, 0.0f), vec3(0, 0, rotation), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, false));
    object->GetPhysicsComponent()->SetBox();
  
}

//direction = -1 = rotating counterclockwise
//direction = 1 = rotating clockwise
void PhysicsScene::CreatePaddle(vec2 position, vec2 scale, float upperLimit, float LowerLimit, int direction)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Paddle));

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];

    object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Red")));
    object->AddComponent(new fw::TransformComponent(object, vec3(0, 0, 0), vec3(0, 0, 0), vec3(scale.x,scale.y,0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, true));
    object->GetPhysicsComponent()->SetBox();



    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Default));
    fw::GameObject* joint = m_Objects[m_Objects.size() - 1];

    joint->AddComponent(new fw::TransformComponent(joint, vec3(position.x, position.y, 0), vec3(0, 0, 0), vec3(1, 1, 0)));
    joint->AddComponent(new fw::PhysicsComponent(joint, m_pWorld, false));
    joint->GetPhysicsComponent()->SetBox();

    object->GetPhysicsComponent()->CreateRevolutionJoint(joint, vec2((scale.x/2)*(float)direction, 0.25), vec2(-0.5 * (float)direction, -0.5), upperLimit * PI/180, LowerLimit * PI/180, 1000.0f * (float)direction, 3000.0f);

    if (direction == -1)
    {
        m_CounterClockWisePaddles.push_back(object);
    }
    else if (direction == 1)
    {
        m_ClockWisePaddles.push_back(object);
    }
    else
    {
        assert(true);
    }
}
