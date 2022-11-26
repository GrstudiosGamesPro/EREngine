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
#include "OvCore/SceneSystem/Scene.h"

#include <OvUI/Widgets/Plots/PlotLines.h>
#include <OvUI/Widgets/Drags/DragFloat.h>
#include "OvCore/ECS/Actor.h"
#include <OvCore/Global/ServiceLocator.h>
#include <OvTools/Filesystem/IniFile.h>
#include <OvTools/Utils/PathParser.h>


#include "OvCore/ECS/Components/CTransform.h"
#include "OvCore/ECS/Components/CCamera.h"
#include "OvCore/ECS/Components/CPhysicalBox.h"
#include "OvCore/ECS/Components/CPhysicalSphere.h"
#include "OvCore/ECS/Components/CPhysicalCapsule.h"
#include "OvCore/ECS/Components/CDirectionalLight.h"
#include "OvCore/ECS/Components/CPointLight.h"
#include "OvCore/ECS/Components/CSpotLight.h"
#include "OvCore/ECS/Components/CAmbientBoxLight.h"
#include "OvCore/ECS/Components/CAmbientSphereLight.h"
#include "OvCore/ECS/Components/CModelRenderer.h"
#include "OvCore/ECS/Components/CMaterialRenderer.h"
#include "OvCore/ECS/Components/CAudioSource.h"
#include "OvCore/ECS/Components/CAudioListener.h"


#include <filesystem>
#include <iostream>
#include <fstream>

#include <OvDebug/Logger.h>

#include <OvCore/ECS/Components/CPhysicalBox.h>
#include <OvCore/ECS/Components/CPhysicalSphere.h>
#include <OvCore/ECS/Components/CPhysicalCapsule.h>
#include <OvCore/ECS/Components/CModelRenderer.h>
#include <OvCore/ECS/Components/CMaterialRenderer.h>
#include <OvCore/ECS/Components/CAudioSource.h>

#include <OvWindowing/Dialogs/OpenFileDialog.h>
#include <OvWindowing/Dialogs/SaveFileDialog.h>
#include <OvWindowing/Dialogs/MessageBox.h>

#include <OvTools/Utils/PathParser.h>
#include <OvTools/Utils/String.h>
#include <OvTools/Utils/SystemCalls.h>





using namespace std;
using namespace OvCore::Helpers;
using namespace OvCore::ECS::Components;
using namespace OvMaths;
using namespace OvUI::Internal;
using namespace OvCore::ECS;
using namespace OvCore::Global;
using namespace OvCore::SceneSystem;
using namespace OvRendering::Resources;


float timeOutTotal;
float DefaultTime;

CParticles::CParticles(ECS::Actor& p_owner) : AComponent(p_owner)
{

}

std::string CParticles::GetName() {
	return "Particles System";
}

void CParticles::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::SerializeFloat		(p_doc, p_node, "ParticlesSpeed", ParticlesSpeed);
	Serializer::SerializeFloat		(p_doc, p_node, "InstanceTime", InstanceTime);
	Serializer::SerializeFloat		(p_doc, p_node, "DestroyTimeSpeed", ParticlesSpeed);
	Serializer::SerializeFloat		(p_doc, p_node, "OpenAngle", OpenAngle);
	Serializer::SerializeVec3		(p_doc, p_node, "Direction", Direction);
}

void CParticles::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	SetParticlesSpeed (Serializer::DeserializeFloat		     (p_doc, p_node, "ParticlesSpeed"));
	SetDestroyTime(Serializer::DeserializeFloat				 (p_doc, p_node, "DestroyTimeSpeed"));
	SetOpenAngle (Serializer::DeserializeFloat				 (p_doc, p_node, "OpenAngle"));
	SetInstanceTime (Serializer::DeserializeFloat			 (p_doc, p_node, "InstanceTime"));
	SetDirection(Serializer::DeserializeVec3				 (p_doc, p_node, "Direction"));
}

void CParticles::SetOpenAngle (float p_Angle) 
{
	OpenAngle = p_Angle;
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
	GUIDrawer::DrawScalar<float>(p_root, "Instance Time", std::bind(&CParticles::InstanceTime, this), std::bind(&CParticles::SetInstanceTime, this, std::placeholders::_1), 0.01f, 0.0f, 1000.0f);
	GUIDrawer::DrawScalar<float>(p_root, "Open Angle", std::bind(&CParticles::OpenAngle, this), std::bind(&CParticles::SetOpenAngle, this, std::placeholders::_1), 0.01f, 0.0f, 1000.0f);
	GUIDrawer::DrawVec3(p_root, "Direction", Direction, 0.1f);
}

void CParticles::OnFixedUpdate (float deltaTime) 
{
	timeOutTotal -= 0.1f / 10;

	if (timeOutTotal <= 0.0f) {

		Actor& foo = ServiceLocator::Get<SceneManager>().GetCurrentScene()->CreateActor("Particle");
		foo.SetName(to_string(owner.GetChildren().size()));
		foo.SetParent(owner);

		OvMaths::FQuaternion NewRotation = OvMaths::FQuaternion(15.f, 15.f, 15.f, 0.f);
		foo.transform.SetLocalRotation(NewRotation);

		timeOutTotal = DefaultTime;
	}

	//MOVE PARTICLES

	for (int i = 0; i < owner.GetChildren().size(); i++) {
		Actor* FD = owner.GetChildren()[i];
		FD->SetName ("Particle FX");
		FD->transform.SetLocalPosition (FD->transform.GetLocalPosition().Forward * ParticlesSpeed * deltaTime);
	}
}

void CParticles::OnEnable()
{
	timeOutTotal = InstanceTime;
	DefaultTime = InstanceTime;
	DefaultTime = timeOutTotal;
	timeOutTotal = 0;
}

void CParticles::OnDisable()
{

}

void CParticles::Update() 
{
	
}