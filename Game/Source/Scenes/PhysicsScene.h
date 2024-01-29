#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "../Libraries/box2d/include/box2d/box2d.h"

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
	b2World* m_pWorld = nullptr;
	b2Body* m_groundBody = nullptr;
};