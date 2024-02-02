//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"


#include "Camera.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"
#include "SceneSystem/Scene.h"
#include "Component/ComponentManager.h"
#include "Component/TransformComponent.h"

namespace fw {

    GameObject::GameObject(Scene* scene, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial)
        : m_pScene(scene)
        , m_Name( name )
        , m_Position( pos )
        , m_pMesh( pMesh )
        , m_pMaterial( pMaterial )
    {
       

   
    }

    GameObject::~GameObject()
    {
        for (Component* component : m_Components)
        {
            m_pScene->GetComponentManager()->RemoveComponent(component);
        }
    }

    void GameObject::Update(float deltaTime)
    {
        if (m_pBody != nullptr)
        {
            b2Vec2 m_b2Pos = m_pBody->GetPosition();
            m_Position = vec3(m_b2Pos.x, m_b2Pos.y, 0.0f);
        }
    }

    void GameObject::Draw(Camera* pCamera)
    {
        Uniforms* pUniforms = m_pScene->GetGameCore()->GetUniforms();

        mat4 transform;
        transform.CreateSRT(m_Scale, m_Rotation, m_Position);
        bgfx::setUniform(pUniforms->GetUniform("u_MatWorld"), &transform);

        m_pMesh->Draw( 0, pUniforms, m_pMaterial);
    }

    void GameObject::Enable()
    {
        for (Component* component : m_Components)
        {
            m_pScene->GetComponentManager()->RemoveComponent(component);
            m_pScene->GetComponentManager()->AddComponent(component);
        }
    }

    void GameObject::Disable()
    {
        for (Component* component : m_Components)
        {
            m_pScene->GetComponentManager()->RemoveComponent(component);
        }
    }

    void GameObject::AddComponent(Component* pComponent)
    {
        m_Components.push_back(pComponent);
        m_pScene->GetComponentManager()->AddComponent(pComponent);
    }

    fw::TransformComponent* GameObject::GetTransformComponent()
    {
        for (fw::Component* component : m_Components)
        {
            if (component->GetType() == "TransformComponent")
            {
                return static_cast<fw::TransformComponent*>(component);
            }
        }
        return nullptr;
    }

    void GameObject::CreateBody(bool isDynamic)
    {
        b2BodyDef bodyDef;
        if (isDynamic == true)
        {
            bodyDef.type = b2_dynamicBody;
        }
        else
        {
            bodyDef.type = b2_kinematicBody;
        }

        bodyDef.position = b2Vec2(m_Position.x, m_Position.y);
        m_pBody = m_pScene->GetWorld()->CreateBody(&bodyDef);

        b2CircleShape circleShape;
        circleShape.m_radius = 1.0f;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = 1.0f;
        m_pBody->CreateFixture(&fixtureDef);
    }

} // namespace fw
