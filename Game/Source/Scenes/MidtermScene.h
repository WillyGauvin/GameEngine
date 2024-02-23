#pragma once

#include "Framework.h"
#include "DataTypes.h"


enum CurrentSide
{
	LeftSide,
	RightSide
};
class MidtermScene : public fw::Scene
{
public:

	MidtermScene(fw::GameCore* pGameCore);
	virtual ~MidtermScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	fw::GameObject* m_pPlayer;
	fw::GameObject* m_pLeftBox;
	fw::GameObject* m_pRightBox;
	fw::GameObject* m_pLeftSensor;
	fw::GameObject* m_pRightSensor;

	CurrentSide side = LeftSide;
};