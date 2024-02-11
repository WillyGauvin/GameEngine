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
	void CreateGate(vec2 position, vec2 scale, float angle, bool isMotorEnabled);
	void CreateSensor(vec2 position, vec2 scale);
	void CreateObstacle(vec2 position, float rotation, vec2 scale, fw::PhysicsCategories category);
	void CreateGears(vec2 position1, vec2 position2, vec2 scale1, vec2 scale2, float angle1, float angle2, float gearRatio, fw::PhysicsCategories category);
	void CreateBall(fw::PhysicsCategories category, vec2 position);

protected:
	//All Paddles Swining in the ClockWise direction
	std::vector<fw::GameObject*> m_ClockWisePaddles;

	//All Paddles Swining in the CounterClockWise direction
	std::vector<fw::GameObject*> m_CounterClockWisePaddles;

	float m_BumperImpulse = 4.0f;
	float m_WallImpulse = 1.5f;
	float m_ObstacleImpulse = 0.5f;

	vec2 m_ballExtraGravity = vec2(0.0f,-2.0f);
	vec2 m_paddleExtraGravity = vec2(0.0f,-1000.0f);

	std::vector<fw::GameObject*> m_balls;
	std::vector<fw::GameObject*> m_gates;
};