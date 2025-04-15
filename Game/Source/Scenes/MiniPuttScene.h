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

	void ResetGame();

protected:

	VirtualController* m_pController = nullptr;
	GolfBall* m_pGolfBall = nullptr;
	OrbitCamera* m_pOrbitCamera;

	fw::GameObject* m_pPlane = nullptr;
	fw::GameObject* m_pLight = nullptr;
	fw::GameObject* m_pRedLight = nullptr;
	fw::GameObject* m_pBlueLight = nullptr;
	fw::GameObject* m_pHole = nullptr;

	fw::GameObject* m_pCourse = nullptr;

	int m_StrokeCount = 0;

	bool m_hasWon = false;

	vec3 m_golfballStartingPos = vec3(0.7f, 0.6f, 0.8f);
};