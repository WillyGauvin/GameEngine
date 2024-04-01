#include "Framework.h"
#include "DataTypes.h"
#include "VirtualController.h"

class OrbitCamera : public fw::Camera
{
    using Super = fw::Camera;
public:
    OrbitCamera(fw::Scene* pScene, vec3 eye, vec3 up, vec3 at, VirtualController* pController, fw::GameObject* pTarget);
    virtual ~OrbitCamera();

    virtual void Update(float32 deltaTime) override;
    virtual void ExecuteEvent(fw::Event* pEvent) override;

    virtual void Enable(int viewID) override;


protected:
    fw::GameObject* m_pTarget = nullptr;
    float m_Distance = 10.0f;
    vec3 m_Rotation = vec3(0.0f, 0.0f, 0.0f);
    VirtualController* m_pController = nullptr;
};
 // namespace fw