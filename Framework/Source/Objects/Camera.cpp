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
#include "FWCore.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"
#include "EventSystem/EventManager.h"
#include "SceneSystem/Scene.h"

namespace fw {

    Camera::Camera(Scene* pScene, vec3 eye, vec3 up, vec3 at) :
        m_pScene(pScene),
        m_eye(eye),
        m_up(up),
        m_at(at)
    {
        FWCore* pFW = m_pScene->GetGameCore()->GetFramework();
        SetAspectRatio((float)pFW->GetWindowClientWidth() / pFW->GetWindowClientHeight());

        //Register For Events
        m_pScene->GetEventManager()->RegisterListener(WindowResizeEvent::GetStaticEventType(), this);
    }

    Camera::~Camera()
    {
    }

    void Camera::Update(float32 deltaTime)
    {
    }

    void Camera::ExecuteEvent(Event* pEvent)
    {
        if (pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType())
        {
            int width = m_pScene->GetGameCore()->GetFramework()->GetWindowClientWidth();
            int height = m_pScene->GetGameCore()->GetFramework()->GetWindowClientHeight();
            SetAspectRatio((float)width / height);
        }
    }

    void Camera::Enable(int viewID)
    {
        Uniforms* pUniforms = m_pScene->GetGameCore()->GetUniforms();

        mat4 viewMatrix;
        viewMatrix.CreateLookAtView(m_eye + vec3(0,0,-25), m_up, m_eye + m_at);
       // viewMatrix.CreateLookAtView(m_eye, m_up, m_eye + m_at);

        bgfx::setUniform(pUniforms->GetUniform("u_MatView"), &viewMatrix, 1);

        mat4 projMatrix;
        projMatrix.CreatePerspectiveVFoV(45, m_AspectRatio, 0.01f, 300.0f);
        bgfx::setUniform(pUniforms->GetUniform("u_MatProj"), &projMatrix);
    }

} // namespace fw
