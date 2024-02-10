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

	void CreateBumper(vec2 position, vec2 scale);
	void CreateWall(vec2 position, float rotation, vec2 scale);
	void CreatePaddle(vec2 position, vec2 scale, float upperLimit, float LowerLimit, int direction);

protected:
	//All Paddles Swining in the ClockWise direction
	std::vector<fw::GameObject*> m_ClockWisePaddles;

	//All Paddles Swining in the CounterClockWise direction
	std::vector<fw::GameObject*> m_CounterClockWisePaddles;

	float m_BumperImpulse = 10.0f;
	float m_WallImpulse = 2.0f;

	vec2 m_ballExtraGravity = vec2(0.0f,-2.0f);
	vec2 m_paddleExtraGravity = vec2(0.0f,-60.0f);

	std::vector<fw::GameObject*> m_balls;
};