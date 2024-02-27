#pragma once

#include "Framework.h"
#include "DataTypes.h"


enum CurrentSide
{
	LeftSide,
	RightSide
};
namespace MidtermCollisionProfile
{
	enum PhysicsCategory
	{
		Box = 1 << 0,
		LeftSensor = 1 << 1,
		RightSensor = 1 << 2,
	};
	enum PhysicsMasks
	{
		BoxProfile = Box | LeftSensor | RightSensor,
		LeftSensorProfile = Box,
		RightSensorProfile = Box
	};
}
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