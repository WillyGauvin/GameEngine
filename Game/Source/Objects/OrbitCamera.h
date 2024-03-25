#include "Framework.h"
#include "DataTypes.h"

namespace fw {

    class OrbitCamera : public fw::Camera
    {
        using Super = fw::Camera;
    public:
        OrbitCamera(Scene* pScene, vec3 eye, vec3 up, vec3 at);
        virtual ~OrbitCamera();

        virtual void Update(float32 deltaTime) override;
        virtual void ExecuteEvent(Event* pEvent) override;


        virtual void Enable(int viewID) override;

        // Setters.
        void SetEye(vec3 eye) { m_eye = eye; }
        void SetAt(vec3 at) { m_at = at; }
        void SetProjectionScale(vec2 scale) { m_ProjectionScale = scale; }
        void SetAspectRatio(float32 aspectRatio) { m_AspectRatio = aspectRatio; }

        vec3 GetEye() { return m_eye; }
        vec3 GetUp() { return m_up; }
        vec3 GetAt() { return m_at; }

    protected:

        Scene* m_pScene = nullptr;

        vec3 m_eye;
        vec3 m_up;
        vec3 m_at;

        vec2 m_ProjectionScale = { 0.1f, 0.1f };
        float32 m_AspectRatio = 1.0f;
    };

} // namespace fw