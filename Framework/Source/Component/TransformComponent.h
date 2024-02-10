#pragma once

#include "CoreHeaders.h"
#include "Math/Matrix.h"
#include "Component.h"

namespace fw
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pGameObject, vec3 position, vec3 rotation, vec3 scale);
		virtual ~TransformComponent();

		static const char* GetStaticType() { return "TransformComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }

		void UpdatePosition(vec3 position) { m_position = position; }
		void UpdateRotation(vec3 rotation) { m_rotation = rotation; }
		void UpdateSRT();
	
	public:
		vec3 m_scale;
		vec3 m_rotation;
		vec3 m_position;
		mat4 m_transform;
	};
}