#include "CParticles.h"

#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Drags/DragMultipleFloats.h>
#include "../../OvCore/include/OvCore/ECS/Components/AComponent.h"
#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include <OvUI/Widgets/Selection/ColorEdit.h>
#include <OvUI/Widgets/Buttons/Button.h>
#include <OvUI/Widgets/Layout/Group.h>
#include "OvCore/ECS/Actor.h"
#include "OvCore/Global/ServiceLocator.h"
#include "OvCore/SceneSystem/SceneManager.h"
#include <OvUI/Widgets/Plots/PlotLines.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include "OvCore/ECS/Actor.h"

using namespace std;
using namespace OvCore::Helpers;
using namespace OvCore::ECS::Components;
using namespace OvMaths;
using namespace OvUI::Internal;

CParticles::CParticles(ECS::Actor& p_owner) : AComponent(p_owner)
{

}

std::string CParticles::GetName() {
	return "Particles System";
}

void CParticles::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::SerializeFloat(p_doc, p_node, "ParticlesSpeed", ParticlesSpeed);
	Serializer::SerializeFloat(p_doc, p_node, "InstanceTime", InstanceTime);
	Serializer::SerializeFloat(p_doc, p_node, "DestroyTimeSpeed", ParticlesSpeed);
	Serializer::SerializeVec3(p_doc, p_node, "Direction", Direction);
}

void CParticles::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	SetParticlesSpeed (Serializer::DeserializeFloat(p_doc, p_node, "ParticlesSpeed"));
	SetDestroyTime(Serializer::DeserializeFloat(p_doc, p_node, "DestroyTimeSpeed"));
	SetDestroyTime(Serializer::DeserializeFloat(p_doc, p_node, "DestroyTimeSpeed"));
	SetDirection(Serializer::DeserializeVec3(p_doc, p_node, "Direction"));
	SetInstanceTime (Serializer::DeserializeFloat(p_doc, p_node, "InstanceTime"));
}

void CParticles::SetParticlesSpeed (float p_Speed) {
	ParticlesSpeed = p_Speed;
}

void CParticles::SetDestroyTime (float p_Speed) {
	DestroyTime = p_Speed;
}

void CParticles::SetDirection(FVector3 p_Dir) {
	Direction = p_Dir;
}

void CParticles::SetInstanceTime(float p_Time) {
	InstanceTime = p_Time;
}


void CParticles::OnInspector(WidgetContainer& p_root)
{
	GUIDrawer::DrawScalar<float>(p_root, "Particles Speed", std::bind(&CParticles::ParticlesSpeed, this), std::bind(&CParticles::SetParticlesSpeed, this, std::placeholders::_1), 0.01f, 0.0f, 1.0f);
	GUIDrawer::DrawScalar<float>(p_root, "Destroy Time", DestroyTime, 0.005f, 0.f);
	GUIDrawer::DrawVec3(p_root, "Direction", Direction, 0.1f);
}

void CParticles::OnEnable()
{

	OVLOG_INFO ("Starting Particles");
}

void CParticles::OnDisable()
{

}

void CParticles::Update() 
{
	OVLOG_INFO("Updating Particles");
}