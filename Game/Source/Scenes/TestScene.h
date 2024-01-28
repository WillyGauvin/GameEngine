#pragma once

#include "Framework.h"
#include "DataTypes.h"

class TestScene : public fw::Scene
{
public:
	TestScene(fw::GameCore* pGameCore);
	virtual ~TestScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
};