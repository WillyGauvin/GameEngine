#pragma once

#include "Framework.h"
#include "DataTypes.h"

class PhysicsScene : public fw::Scene
{
public:
	PhysicsScene(fw::GameCore* pGameCore);
	virtual ~PhysicsScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
};