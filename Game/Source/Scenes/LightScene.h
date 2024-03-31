#include "Framework.h"
#include "DataTypes.h"

class LightScene : public fw::Scene
{
public:

	LightScene(fw::GameCore* pGameCore);
	virtual ~LightScene();

	virtual void ExecuteEvent(fw::Event* pEvent) override;
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


protected:

	fw::GameObject* m_pCube;
	fw::GameObject* m_pLight;

	vec3 m_cameraAt;
	vec3 m_cameraEye;
};