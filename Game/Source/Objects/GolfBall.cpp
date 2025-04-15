//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "Game.h"
#include "GameCore.h"
#include "Objects/GolfBall.h"
#include "Objects/VirtualController.h"
#include "Events/GameEvents.h"

GolfBall::GolfBall(fw::Scene* pScene, vec3 position, vec3 rotation, vec3 scale)
    : fw::GameObject(pScene)
{
    Game* game = static_cast<Game*>(m_pScene->GetGameCore());
#define getMesh game->GetResourceManager()->Get<fw::Mesh>
#define getMaterial game->GetResourceManager()->Get<fw::Material>

    m_startingPosition = position;

    AddComponent(new fw::TransformComponent(this, position, rotation, scale));
    AddComponent(new fw::RenderComponent(this, getMesh("GolfBall"), getMaterial("GolfBall")));
    AddComponent(new fw::PhysicsComponent(fw::PhysicsLibrary::Jolt, this, fw::ShapeType::Sphere));
    GetPhysicsComponent()->SetFriction(0.5f);
}

GolfBall::~GolfBall()
{
}

void GolfBall::SetController(VirtualController* pController)
{
    m_pController = pController;
    if (m_pController)
    {
        m_pController->SetControlledObject(this);
    }
}

void GolfBall::Update(float deltaTime)
{
    float speed = 4.0f;

    vec3 dir;

    if (m_pFollowCamera)
    {
        vec3 forwardDirection = (GetTransformComponent()->m_position - m_pFollowCamera->GetEye()).Normalize();
        forwardDirection.y = 0;
        vec3 upDirection = vec3(0.0f, 1.0f, 0.0f);
        vec3 leftDirection = forwardDirection.Cross(upDirection);

        if (m_pController != nullptr)
        {
            if (m_pController->isActionHeld(VirtualController::Swing))
            {
                isSwinging = true;
                ChargeSwing(deltaTime);
            }
            else if (m_pController->WasActionReleased(VirtualController::Swing))
            {   
                isSwinging = false;
                vec3 force = forwardDirection * (m_Power);
                GetPhysicsComponent()->AddForce(force, fw::ForceMode::Impulse);
                m_Power = 0.0f;
            }
            if (m_pController->isActionHeld(VirtualController::Reset))
            {
                ResetGameEvent* reset = new ResetGameEvent();
                GetScene()->GetEventManager()->AddEvent(reset);
            }
        }
    }
    
    else
    {
        if (m_pController != nullptr)
        {
            if (m_pController->isActionHeld(VirtualController::Up)) dir.z++;
            if (m_pController->isActionHeld(VirtualController::Down)) dir.z--;
            if (m_pController->isActionHeld(VirtualController::Left)) dir.x--;
            if (m_pController->isActionHeld(VirtualController::Right)) dir.x++;

        }

        dir.Normalize();

        GetTransformComponent()->m_position += dir * speed * deltaTime;
    }
}

void GolfBall::ChargeSwing(float deltaTime)
{
    if (isIncreasing)
    {
        m_Power += deltaTime * 1;

        if (m_Power >= m_MaxPower)
        {
            m_Power = m_MaxPower;
            isIncreasing = false;
        }
    }
    else if (!isIncreasing)
    {
        m_Power -= deltaTime * 1;
        
        if (m_Power <= m_MinPower)
        {
            m_Power = m_MinPower;
            isIncreasing = true;
        }
    }

}

void GolfBall::Reset()
{
    GetTransformComponent()->m_position = m_startingPosition;
    GetTransformComponent()->m_rotation = vec3(0.0f, 0.0f, 0.0f);
    GetPhysicsComponent()->Reset();
}
