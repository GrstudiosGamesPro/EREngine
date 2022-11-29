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
#include <OvDebug/Logger.h>
#include "DestroyTime.h"

#include "OvCore/ResourceManagement/ModelManager.h"
#include "OvCore/ResourceManagement/MaterialManager.h"


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

float TimeTotalDestroy;
float DefaultDestroytime;

CParticles::CParticles(ECS::Actor& p_owner) : AComponent(p_owner)
{
	auto& ModelManager = ServiceLocator::Get<OvCore::ResourceManagement::ModelManager>();
	const auto m_Model = ModelManager[":Models\\Plane.fbx"];
	m_model = m_Model;


	m_modelChangedEvent += [this]
	{
		if (auto materialRenderer = owner.GetComponent<CMaterialRenderer>())
			materialRenderer->UpdateMaterialList();
	};

	auto MaterialManager = ServiceLocator::Get<OvCore::ResourceManagement::MaterialManager>();
	m_material = MaterialManager[":Materials\\Default.ovmat"];
}

std::string CParticles::GetName() {
	return "Sistema De Particulas";
}

void CParticles::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	Serializer::SerializeFloat		(p_doc, p_node, "ParticlesSpeed", ParticlesSpeed);
	Serializer::SerializeFloat		(p_doc, p_node, "InstanceTime", InstanceTime);
	Serializer::SerializeFloat		(p_doc, p_node, "DestroyTimeSpeed", ParticlesSpeed);
	Serializer::SerializeFloat		(p_doc, p_node, "OpenAngle", OpenAngle);
	Serializer::SerializeVec3		(p_doc, p_node, "Direction", Direction);
	Serializer::SerializeModel	    (p_doc, p_node, "CurrentModel", m_model);
	Serializer::SerializeBoolean	(p_doc, p_node, "UseCol", UseCollision);
	Serializer::SerializeMaterial	(p_doc, p_node, "CurMat", m_material);
}

void CParticles::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	SetParticlesSpeed (Serializer::DeserializeFloat		     (p_doc, p_node, "ParticlesSpeed"));
	SetDestroyTime(Serializer::DeserializeFloat				 (p_doc, p_node, "DestroyTimeSpeed"));
	SetOpenAngle (Serializer::DeserializeFloat				 (p_doc, p_node, "OpenAngle"));
	SetInstanceTime (Serializer::DeserializeFloat			 (p_doc, p_node, "InstanceTime"));
	SetDirection(Serializer::DeserializeVec3				 (p_doc, p_node, "Direction"));
	SetModel(Serializer::DeserializeModel                    (p_doc, p_node, "CurrentModel"));
	UseColision (Serializer::DeserializeBoolean              (p_doc, p_node, "UseCol"));
	SetNewMaterial (Serializer::DeserializeMaterial          (p_doc, p_node, "CurMat"));
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

void CParticles::UseColision (bool Val)
{
	UseCollision = Val;
}

void CParticles::SetModel(OvRendering::Resources::Model* p_model)
{
	m_model = p_model;
	m_modelChangedEvent.Invoke();
	OVLOG_INFO ("Modelo De Particulas Cambiado");
}

void CParticles::SetNewMaterial (OvCore::Resources::Material* p_material)
{
	m_material = p_material;
	m_materialChangedEvent.Invoke();
	OVLOG_INFO("Modelo De Particulas Cambiado");
}


void CParticles::OnInspector(WidgetContainer& p_root)
{

	GUIDrawer::DrawMesh     (p_root, "Modelo De Particulas", m_model, &m_modelChangedEvent);

	if (m_material != nullptr) {
		GUIDrawer::DrawMaterial(p_root, "Material", m_material, &m_modelChangedEvent);
	}

	GUIDrawer::DrawScalar<float>(p_root, "Velocidad", std::bind(&CParticles::ParticlesSpeed, this), std::bind(&CParticles::SetParticlesSpeed, this, std::placeholders::_1), 0.01f, 0.0f, 1000.0f);
	GUIDrawer::DrawScalar<float>(p_root, "Tiempo De Destruccion", DestroyTime, 0.005f, 0.f);
	GUIDrawer::DrawScalar<float>(p_root, "Tiempo De Creacion", std::bind(&CParticles::InstanceTime, this), std::bind(&CParticles::SetInstanceTime, this, std::placeholders::_1), 0.01f, 0.0f, 1000.0f);
	GUIDrawer::DrawScalar<float>(p_root, "Angulo", std::bind(&CParticles::OpenAngle, this), std::bind(&CParticles::SetOpenAngle, this, std::placeholders::_1), 0.01f, 0.1f, 1000.0f);
	GUIDrawer::DrawBoolean(p_root, "Usar Colision", std::bind(&CParticles::UseCollision, this), std::bind(&CParticles::UseColision, this, placeholders::_1));
	GUIDrawer::DrawVec3(p_root, "Direccion", Direction, 0.1f);
}

void CParticles::OnFixedUpdate (float deltaTime) 
{
	timeOutTotal -= 0.1f / 10;

	if (timeOutTotal <= 0.0f) {
		Actor& NewParticleModel = ServiceLocator::Get<SceneManager>().GetCurrentScene()->CreateActor("Particle");
		NewParticleModel.transform.ScaleLocal (OvMaths::FVector3 (0.3f, 0.3f, 0.3f));

		auto& ModelManager = ServiceLocator::Get<OvCore::ResourceManagement::ModelManager>();

		auto& NewMaterial = NewParticleModel.AddComponent<CMaterialRenderer>();
		const auto mat = m_material;

		if (mat) {
			NewMaterial.FillWithMaterial(*mat);
		}

		auto& NewModelRender = NewParticleModel.AddComponent <CModelRenderer>();

		NewModelRender.SetModel(m_model);

		if (UseCollision) {
			auto& NewPhysical = NewParticleModel.AddComponent<CPhysicalSphere>();
			NewPhysical.SetKinematic(true);
			NewPhysical.SetRadius(1.f);
		}

		NewParticleModel.SetName(to_string(owner.GetChildren().size()));
		NewParticleModel.SetParent(owner);

		OvMaths::FQuaternion NewRotation = OvMaths::FQuaternion(0.1f, 0.1f, 0.1f, 0.1f);

		if (OpenAngle <= 0.1f) {
			NewRotation = OvMaths::FQuaternion (0.1f, 0.1f, 0.1f, 0.1f);
		}
		else {
			NewRotation = OvMaths::FQuaternion(RandomFloatGenerate(0, OpenAngle), RandomFloatGenerate(0, OpenAngle),
											   RandomFloatGenerate(0, OpenAngle), RandomFloatGenerate(0, OpenAngle));
		}

		string random = "Random Generado: ";
		string r = random.append (to_string (RandomFloatGenerate(0, OpenAngle)));

		NewParticleModel.transform.SetWorldRotation (NewRotation);
		NewParticleModel.AddComponent<OvCore::ECS::Components::DestroyTime>().SetTime (DestroyTime);

		timeOutTotal = DefaultTime;
	}

	for (int i = 0; i < owner.GetChildren().size(); i++) {
		Actor* FD = owner.GetChildren()[i];
		FD->SetName ("Particle FX (Not Touch)");

		OvMaths::FVector3 dir = owner.transform.GetWorldPosition() - FD->transform.GetWorldPosition();
		FD->transform.SetWorldPosition(FD->transform.GetWorldPosition() + FD->transform.GetWorldForward() * ParticlesSpeed * deltaTime);
	}
}

void CParticles::OnEnable()
{
	timeOutTotal = InstanceTime;
	DefaultTime = InstanceTime;
	DefaultTime = timeOutTotal;
	timeOutTotal = 0;

	TimeTotalDestroy = DestroyTime;
	DefaultDestroytime = TimeTotalDestroy;
}

void CParticles::OnDisable()
{

}

void CParticles::Update() 
{
	
}

float CParticles::RandomFloatGenerate (float min, float max) 
{
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}