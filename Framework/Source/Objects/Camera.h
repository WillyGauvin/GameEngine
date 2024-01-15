//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Matrix.h"
#include "Objects/GameObject.h"
#include "EventSystem/EventListener.h"

namespace fw {

    class Scene;

    class Camera : public GameObject, public EventListener
    {
    public:
        Camera(Scene* pScene, vec3 pos);
        virtual ~Camera();

        virtual void Update(float32 deltaTime) override;
        virtual void ExecuteEvent(Event* pEvent) override;


        void Enable(int viewID);

        // Setters.
        void SetProjectionScale(vec2 scale) { m_ProjectionScale = scale; }
        void SetAspectRatio(float32 aspectRatio) { m_AspectRatio = aspectRatio; }

    protected:
        vec2 m_ProjectionScale = { 0.1f, 0.1f };
        float32 m_AspectRatio = 1.0f;
    };

} // namespace fw
