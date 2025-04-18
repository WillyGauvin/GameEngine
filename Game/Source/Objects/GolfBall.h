//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "DataTypes.h"
class HeightMapMesh;

class VirtualController;

class GolfBall : public fw::GameObject
{
public:
    GolfBall(fw::Scene* pScene, vec3 position, vec3 rotation, vec3 scale);

    virtual ~GolfBall();

    void SetController(VirtualController* pController);

    virtual void Update(float deltaTime) override;

    void ChargeSwing(float deltaTime);

    bool IsSwinging() { return isSwinging; }
    float GetPower() { return m_Power; }
    float GetMaxPower() { return m_MaxPower; }

    void Reset();

protected:
    VirtualController* m_pController = nullptr;

    bool isSwinging = false;

    float m_Power = 0.0f;
    bool isIncreasing = true;

    float m_MaxPower = 1.0f;
    float m_MinPower = 0.0f;

    vec3 m_startingPosition;
};
