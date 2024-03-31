#include "LightComponent.h"




fw::LightComponent::LightComponent(GameObject* pGameObject, float range, float ambientPerc, float falloffExp, float specExp) :
	Component(pGameObject),
	m_LightRange(range),
	m_AmbientPerc(ambientPerc),
	m_FalloffExp(falloffExp),
	m_SpecularExp(specExp)
{
}

fw::LightComponent::~LightComponent()
{
}



