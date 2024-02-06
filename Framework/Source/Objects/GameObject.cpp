//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"

#include "Camera.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"
#include "SceneSystem/Scene.h"
#include "Component/ComponentManager.h"
#include "Component/TransformComponent.h"
#include "MyContactListener.h"

namespace fw {

    GameObject::GameObject(Scene* scene, std::string name)
        : m_pScene(scene)
        , m_Name( name )
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

} // namespace fw
