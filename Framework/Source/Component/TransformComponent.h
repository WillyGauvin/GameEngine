#pragma once

#include "CoreHeaders.h"

#include "Component.h"

namespace fw
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pGameObject);
		virtual ~TransformComponent();

		static const char* GetStaticType() { return "TransformComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }
	
	public:
		vec3 m_scale;
		vec3 m_rotation;
		vec3 m_position;
		mat4 m_transform;
	};
}