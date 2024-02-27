#pragma once

#include "Framework.h"
#include "DataTypes.h"

class VirtualController;

namespace LunarCollisionProfile
{
	enum PhysicsCategory
	{
		Ship = 1 << 0,
		Landing = 1 << 1,
		Obstacle  = 1 << 2,
	};
	enum PhysicsMasks
	{
		maskCollideAll = Ship | Landing | Obstacle
	};
}

class LandingScene : public fw::Scene
{
public:

	LandingScene(fw::GameCore* pGameCore);
	virtual ~LandingScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void Reset();
	
	void CreateObstacles();

protected:

	VirtualController* m_pController;
	fw::GameObject* m_pPlayer;
	fw::GameObject* m_pLeftEngine;
	fw::GameObject* m_pRightEngine;
	fw::Material* m_pOff;
	fw::Material* m_pLeft;
	fw::Material* m_pRight;
	fw::Material* m_pBoth;
	fw::Material* m_pCrash;
	fw::Material* m_pLanded;
	
	bool m_hasTouchedDown = false;
	bool m_hasCrashed = false;
	bool m_hasSafeLanded = false;
	float m_ShipSpeed = 0.0f;
	float m_ShipAngle = 0.0f;
	std::string m_ReasonForCrash = "";
	std::vector<fw::GameObject*> m_Obstacles;

	fw::GameObject* m_pArrow;
};