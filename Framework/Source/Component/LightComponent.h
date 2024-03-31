#pragma once

#include "CoreHeaders.h"

#include "Component/Component.h"


namespace fw
{

	class LightComponent : public Component
	{
	public:
		LightComponent(GameObject* pGameObject, float range, float ambientPerc, float falloffExp, float specExp);
		virtual ~LightComponent();

		static const char* GetStaticType() { return "LightComponent"; }
		virtual const char* GetType() override { return GetStaticType(); }

	public:

		float m_LightRange;
		float m_AmbientPerc;
		float m_FalloffExp;
		float m_SpecularExp;
	};
}