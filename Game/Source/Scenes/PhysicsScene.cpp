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

    CreateBall(fw::PhysicsCategories::PhysicsCategory_RedBall, vec2(10, 30));
    CreateBall(fw::PhysicsCategories::PhysicsCategory_RedBall, vec2(5, 30));
    CreateBall(fw::PhysicsCategories::PhysicsCategory_RedBall, vec2(-10, 30));


    CreateBall(fw::PhysicsCategories::PhysicsCategory_BlueBall, vec2(-3, 30));
    CreateBall(fw::PhysicsCategories::PhysicsCategory_BlueBall, vec2(13, 30));

    CreateBall(fw::PhysicsCategories::PhysicsCategory_GreenBall, vec2(15, 30));
    CreateBall(fw::PhysicsCategories::PhysicsCategory_GreenBall, vec2(5, 30));
    CreateBall(fw::PhysicsCategories::PhysicsCategory_GreenBall, vec2(-13, 30));

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

    //LockedBumperArea
    CreateWall(vec2(-9, 10), 90, vec2(22, 0.25));
    CreateWall(vec2(-10.5, 22.5), 45, vec2(5, 0.25));
    CreateWall(vec2(-10.5, -2.5), -45, vec2(5, 0.25));

    //Corners
    CreateWall(vec2(-14, 39), -45, vec2(3, 0.25));
    CreateWall(vec2(14, 39), 45, vec2(3, 0.25));

    //BottomRight
    CreateWall(vec2(10, -10), -45, vec2(5, 0.25));

    CreateWall(vec2(8, -4), 45, vec2(5, 0.25));

    CreateWall(vec2(-8.5, -12.5), 45, vec2(10, 0.25));

    CreateWall(vec2(-5, -10), -15, vec2(5, 0.25));

    CreateWall(vec2(12, 10), -20, vec2(5, 0.25));

    CreateWall(vec2(-11, 30), -20, vec2(5, 0.25));

    CreateWall(vec2(5, 35), -50, vec2(6, 0.25));
    CreateWall(vec2(1, 35), 50, vec2(6, 0.25));


    //PADDLES
    CreatePaddle(vec2(-6.5, -18.5), vec2(5.5, 0.5), 70.0f, -45.0f, -1);
    CreatePaddle(vec2(6.5, -18.5), vec2(5.5, 0.5), 45.0f, -70.0f, 1);
    CreatePaddle(vec2(13, 25), vec2(5.5, 0.5), 45.0f, -70.0f, 1);


    //BlueObstacles

    CreateGears(vec2(-7.0f, 15.0f), vec2(-4.0f, 16.0f), vec2(4.0f, 0.25f), vec2(2.0f, 0.25f), 60.0f, 80.0f, 0.5f, fw::PhysicsCategories::PhysicsCategory_BlueObstacle);
    CreateGears(vec2(7.0f, 5.0f), vec2(4.0f, 8.0f), vec2(5.0f, 0.25f), vec2(4.0f, 0.25f), 50.0f, 120.0f, 0.5f, fw::PhysicsCategories::PhysicsCategory_BlueObstacle);
    //CreateObstacle(vec2(0, 0), 0, vec2(0, 0),fw::PhysicsCategories::PhysicsCategory_BlueObstacle);


    //RedObstacles

    CreateGears(vec2(-7.0f, 10.0f), vec2(-5.0f, 12.0f), vec2(3.0f, 0.25f), vec2(3.0f, 0.25f), 20.0f, -70.0f, 0.5f, fw::PhysicsCategories::PhysicsCategory_RedObstacle);

    //CreateObstacle(vec2(0,0), 0, vec2(0,0), fw::PhysicsCategories::PhysicsCategory_RedObstacle);
    CreateObstacle(vec2(12, -8), -5, vec2(5, 0.25), fw::PhysicsCategories::PhysicsCategory_RedObstacle);



    //GreenObstacles

    CreateGears(vec2(-7.0f, 5.0f), vec2(-4.0f, 8.0f), vec2(3.0f, 0.25f), vec2(2.0f, 0.25f), 50.0f, 120.0f, 0.5f, fw::PhysicsCategories::PhysicsCategory_GreenObstacle);

    CreateObstacle(vec2(12, -7), -5, vec2(5, 0.25), fw::PhysicsCategories::PhysicsCategory_GreenObstacle);
    //CreateObstacle(vec2(0,0), 0, vec2(0, 0.25), fw::PhysicsCategories::PhysicsCategory_GreenObstacle);

    //BUMPERS

    CreateBumper(vec2(-13.5f, 2.5f), vec2(0.25f,0.25f));
    CreateBumper(vec2(-11.0f, 2.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-12.25f, 0.0f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-9.75f, 0.0f), vec2(0.25f, 0.25f));

    CreateBumper(vec2(-13.5f, 7.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-11.0f, 7.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-12.25f, 5.0f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-10.0f, 5.0f), vec2(0.25f, 0.25f));

    CreateBumper(vec2(-13.5f, 12.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-11.0f, 12.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-12.25f, 10.0f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-10.0f, 10.0f), vec2(0.25f, 0.25f));

    CreateBumper(vec2(-11.0f, 17.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-12.25f, 15.0f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(-10.0f, 15.0f), vec2(0.25f, 0.25f));



    CreateBumper(vec2(11.0f, 35.5f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(12.25f, 33.0f), vec2(0.25f, 0.25f));
    CreateBumper(vec2(10.0f, 33.0f), vec2(0.25f, 0.25f));

    CreateBumper(vec2(-9.0f, -9.0f), vec2(0.25f, 0.25f));


    //Moveable Obstacles

  
    CreateGate(vec2(-11.5,24), vec2(4,0.25), 45.0f, true);
    CreateGate(vec2(-11.25, -3.75), vec2(3, 0.25), -45.0f, false);

    //Sensor

    CreateSensor(vec2(11, -11), vec2(0.5, 0.5));






 















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
        if (inputEvent->GetKeyCode() == 'Q' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
        {
            for (fw::GameObject* gameObject : m_CounterClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(true);
            }
        }

        if (inputEvent->GetKeyCode() == 'E' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
        {
            for (fw::GameObject* gameObject : m_ClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(true);
            }
        }

        //End the motor
        if (inputEvent->GetKeyCode() == 'Q' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
        {
            for (fw::GameObject* gameObject : m_CounterClockWisePaddles)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2RevoluteJoint>(false);
            }
        }

        if (inputEvent->GetKeyCode() == 'E' && inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released)
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

        if (CategoryA == fw::PhysicsCategories::PhysicsCategory_Sensor || CategoryB == fw::PhysicsCategories::PhysicsCategory_Sensor)
        {
            for (fw::GameObject* gameObject : m_gates)
            {
                gameObject->GetPhysicsComponent()->EnableMotor<b2PrismaticJoint>(true);
            }
        }
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
        case fw::PhysicsCategories::PhysicsCategory_RedObstacle:
        {
            ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB * m_ObstacleImpulse);
            break;
        }
        case fw::PhysicsCategories::PhysicsCategory_BlueObstacle:
        {
            ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB * m_ObstacleImpulse);
            break;
        }
        case fw::PhysicsCategories::PhysicsCategory_GreenObstacle:
        {
            ObjectA->GetPhysicsComponent()->AddLinearImpulse(normalB * m_ObstacleImpulse);
            break;
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

    object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Yellow")));
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

    object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Orange")));
    object->AddComponent(new fw::TransformComponent(object, vec3(position.x, position.y, 0.0f), vec3(0, 0, rotation), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, false));
    object->GetPhysicsComponent()->SetBox();
  
}

void PhysicsScene::CreatePaddle(vec2 position, vec2 scale, float upperLimit, float LowerLimit, int direction)
{
    //direction = -1 = rotating counterclockwise
    //direction = 1 = rotating clockwise
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

void PhysicsScene::CreateGate(vec2 position, vec2 scale, float angle, bool isMotorEnabled)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Wall));
    fw::GameObject* object = m_Objects[m_Objects.size() - 1];
    object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Orange")));
    object->AddComponent(new fw::TransformComponent(object, vec3(0, 0, 0.0f), vec3(0, 0, angle), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, true));
    object->GetPhysicsComponent()->SetBox();

    m_gates.push_back(object);


    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Default));

    fw::GameObject* object1 = m_Objects[m_Objects.size() - 1];

    //object1->AddComponent(new fw::RenderComponent(object1, getMesh("Square"), getMaterial("Red")));
    object1->AddComponent(new fw::TransformComponent(object1, vec3(position.x, position.y, 0.0f), vec3(0, 0, angle), vec3(1, 1, 0.0f)));
    object1->AddComponent(new fw::PhysicsComponent(object1, m_pWorld, false));
    object1->GetPhysicsComponent()->SetBox();

    
    if (angle >= 0)
    {
        object->GetPhysicsComponent()->CreatePrismaticJoint(object1,false, 3, -3, 100, 100, isMotorEnabled);
    }
    else
    {
        object->GetPhysicsComponent()->CreatePrismaticJoint(object1, false, 3, -3, -100, 100, isMotorEnabled);
    }
}

void PhysicsScene::CreateSensor(vec2 position, vec2 scale)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Sensor));

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];

    object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Blue")));
    object->AddComponent(new fw::TransformComponent(object, vec3(position.x, position.y, 0.0f), vec3(0, 0, 0), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, false));
    object->GetPhysicsComponent()->SetSensor();

}

void PhysicsScene::CreateObstacle(vec2 position, float rotation, vec2 scale, fw::PhysicsCategories category)
{
    Game* game = static_cast<Game*>(m_pGameCore);
    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    switch (category)
    {
    case (fw::PhysicsCategories::PhysicsCategory_RedObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_RedObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Red")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_BlueObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_BlueObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Blue")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_GreenObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_GreenObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Green")));
        break;
    }
    }

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];

    object->AddComponent(new fw::TransformComponent(object, vec3(position.x, position.y, 0.0f), vec3(0, 0, rotation), vec3(scale.x, scale.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, false));
    object->GetPhysicsComponent()->SetBox();
}




void PhysicsScene::CreateGears(vec2 position1, vec2 position2, vec2 scale1, vec2 scale2, float angle1, float angle2, float gearRatio, fw::PhysicsCategories category)
{
    Game* game = static_cast<Game*>(m_pGameCore);

    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>

    switch (category)
    {
    case (fw::PhysicsCategories::PhysicsCategory_RedObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_RedObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Red")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_BlueObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_BlueObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Blue")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_GreenObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_GreenObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Green")));
        break;
    }
    }

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];

    object->AddComponent(new fw::TransformComponent(object, vec3(position1.x, position1.y, 0.0f), vec3(0, 0, angle1), vec3(scale1.x, scale1.y, 0.0f)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, true));
    object->GetPhysicsComponent()->SetBox();

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Default));
    fw::GameObject* joint = m_Objects[m_Objects.size() - 1];

    joint->AddComponent(new fw::TransformComponent(joint, vec3(position1.x,position1.y, 0), vec3(0, 0, angle1), vec3(1, 1, 0)));
    joint->AddComponent(new fw::PhysicsComponent(joint, m_pWorld, false));
    joint->GetPhysicsComponent()->SetBox();

    joint->GetPhysicsComponent()->CreateRevolutionJoint(object, (0, 0), (0, 0));


    switch (category)
    {
    case (fw::PhysicsCategories::PhysicsCategory_RedObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_RedObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Red")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_BlueObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_BlueObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Blue")));
        break;
    }
    case (fw::PhysicsCategories::PhysicsCategory_GreenObstacle):
    {
        m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_GreenObstacle));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Square"), getMaterial("Green")));
        break;
    }
    }

    fw::GameObject* object1 = m_Objects[m_Objects.size() - 1];

    object1->AddComponent(new fw::TransformComponent(object1, vec3(position2.x, position2.y, 0), vec3(0, 0, angle2), vec3(scale2.x, scale2.y, 0.0f)));
    object1->AddComponent(new fw::PhysicsComponent(object1, m_pWorld, true));
    object1->GetPhysicsComponent()->SetBox();

    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Default));
    fw::GameObject* joint1 = m_Objects[m_Objects.size() - 1];

    joint1->AddComponent(new fw::TransformComponent(joint1, vec3(position2.x, position2.y, 0), vec3(0, 0, 0), vec3(1, 1, 0)));
    joint1->AddComponent(new fw::PhysicsComponent(joint1, m_pWorld, false));
    joint1->GetPhysicsComponent()->SetBox();

    joint1->GetPhysicsComponent()->CreateRevolutionJoint(object1, (0, 0), (0, 0));



    m_Objects.push_back(new fw::GameObject(this, fw::PhysicsCategories::PhysicsCategory_Default));
    fw::GameObject* joint2 = m_Objects[m_Objects.size() - 1];

    joint2->AddComponent(new fw::TransformComponent(joint2, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 0)));
    joint2->AddComponent(new fw::PhysicsComponent(joint2, m_pWorld, false));
    joint2->GetPhysicsComponent()->SetBox();

    joint2->GetPhysicsComponent()->CreateGearJoint(joint, joint1, gearRatio);
}

void PhysicsScene::CreateBall(fw::PhysicsCategories category, vec2 position)
{
    Game* game = static_cast<Game*>(m_pGameCore);

    #define getMesh game->GetResourceManager()->Get<fw::Mesh>
    #define getMaterial game->GetResourceManager()->Get<fw::Material>


    switch (category)
    {
    case (fw::PhysicsCategories::PhysicsCategory_RedBall):
    {
        m_Objects.push_back(new fw::GameObject(this, category));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Red")));
        break;

    }
    case (fw::PhysicsCategories::PhysicsCategory_BlueBall):
    {
        m_Objects.push_back(new fw::GameObject(this, category));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Blue")));
        break;

    }
    case (fw::PhysicsCategories::PhysicsCategory_GreenBall):
    {
        m_Objects.push_back(new fw::GameObject(this, category));
        fw::GameObject* object = m_Objects[m_Objects.size() - 1];

        object->AddComponent(new fw::RenderComponent(object, getMesh("Circle"), getMaterial("Green")));
        break;

    }
    }

    fw::GameObject* object = m_Objects[m_Objects.size() - 1];
    object->AddComponent(new fw::TransformComponent(object, vec3(position.x,position.y, 0), vec3(0, 0, 0), vec3(0.15, 0.15, 0)));
    object->AddComponent(new fw::PhysicsComponent(object, m_pWorld, true));
    object->GetPhysicsComponent()->SetCircle();
    m_balls.push_back(object);
}
