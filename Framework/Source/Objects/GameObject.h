//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Vector.h"
#define B2_USER_SETTINGS
#include "../Libraries/box2d/include/box2d/box2d.h"


namespace fw {

    class Camera;
    class GameCore;
    class Material;
    class Mesh;
    class Uniforms;
    class Scene;
    class Component;
    class TransformComponent;
    class PhysicsComponent;
    class RenderComponent;
    class LightComponent;
    class MyContactListener;

    class GameObject
    {
    public:
        GameObject(Scene* scene);

        virtual ~GameObject();

        virtual void Update(float deltaTime);

        // Getters.
        Scene* GetScene() { return m_pScene; }
        fw::TransformComponent* GetTransformComponent();
        fw::PhysicsComponent* GetPhysicsComponent();
        fw::RenderComponent* GetRenderComponent();
        fw::LightComponent* GetLightComponent();

        void Enable();
        void Disable();

        // Setters.
        void SetCamera(fw::Camera* followCam) { m_pFollowCamera = followCam; }
        void AddComponent(Component* pComponent);



    protected:
        Camera* m_pFollowCamera = nullptr;
        Scene* m_pScene = nullptr;

        std::vector<Component*> m_Components;

    };

} // namespace fw
