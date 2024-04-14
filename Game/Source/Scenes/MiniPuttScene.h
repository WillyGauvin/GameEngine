#include "Framework.h"
#include "DataTypes.h"

class VirtualController;
class OrbitCamera;
class GolfBall;

class MiniPuttScene : public fw::Scene
{
	using Super = fw::Scene;

public:

	MiniPuttScene(fw::GameCore* pGameCore);
	virtual ~MiniPuttScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual fw::Camera* GetCamera() override;

protected:
	fw::JoltWorldBundle* m_pWorldBundle = nullptr;

	JPH::Body* m_pCourseBody = nullptr;
	JPH::Body* m_pBallBody = nullptr;

	VirtualController* m_pController = nullptr;
	GolfBall* m_pGolfBall = nullptr;
	OrbitCamera* m_pOrbitCamera;

	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pLight = nullptr;

	fw::GameObject* m_pCourse = nullptr;

};