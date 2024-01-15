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
#include "Objects/Scene.h"

namespace fw {

    Camera::Camera(Scene* pScene, vec3 pos)
        : GameObject( pScene, "Camera", pos, nullptr, nullptr )
    {
        FWCore* pFW = m_pScene->GetGameCore()->GetFramework();
        SetAspectRatio( (float)pFW->GetWindowClientWidth()/pFW->GetWindowClientHeight() );

        //Register For Events
        m_pScene->GetGameCore()->GetEventManager()->RegisterListener(WindowResizeEvent::GetStaticEventType(), this);
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
        vec2 scaleWithAspectRatio = m_ProjectionScale * vec2( 1.0f/m_AspectRatio, 1 );
    
        // Setup uniforms.
        bgfx::setUniform( pUniforms->GetUniform("u_CameraPosition"), &m_Position, 1 );
        bgfx::setUniform( pUniforms->GetUniform("u_ProjectionScale"), &scaleWithAspectRatio, 1 );
    }

} // namespace fw
