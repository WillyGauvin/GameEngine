#include "Framework.h"
#include "DataTypes.h"

class OrbitCameraScene : public fw::Scene
{
public:

	OrbitCameraScene(fw::GameCore* pGameCore);
	virtual ~OrbitCameraScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


protected:

	fw::GameObject* m_pPlayer = nullptr;
};