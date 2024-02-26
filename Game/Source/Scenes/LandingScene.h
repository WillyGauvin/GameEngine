#pragma once

#include "Framework.h"
#include "DataTypes.h"

class VirtualController;

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
	

	std::vector<fw::GameObject*> m_Obstacles;

	fw::GameObject* m_pArrow;
};