/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvCore/Scripting/LuaComponentBinder.h"

#include "OvCore/ECS/Actor.h"

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
#include "../Components/CParticles.h";

void OvCore::Scripting::LuaComponentBinder::BindComponent(sol::state & p_luaState)
{
	using namespace OvMaths;
	using namespace OvCore::ECS;
	using namespace OvCore::ECS::Components;

	p_luaState.new_usertype<AComponent>("Componente",
		"ObtenerLIDER", [](AComponent& p_component) -> Actor& { return p_component.owner; }
	);

	p_luaState.new_usertype <CParticles>("Particulas",
		sol::base_classes, sol::bases<AComponent>(),
		"CambiarVelocidad", &CParticles::SetParticlesSpeed,
		"CambiarAnguloDeApertura", &CParticles::SetOpenAngle,
		"CambiarTiempoDeDestruccion", &CParticles::SetDestroyTime,
		"CambiarTiempoDeCreacion", &CParticles::SetInstanceTime,
		"CambiarUsoDeColision", &CParticles::UseColision,

		"ObtenerVelocidad", &CParticles::GetParticlesSpeed,
		"ObtenerAnguloDeApertura", &CParticles::GetOpenAngle,
		"ObtenerTiempoDeDestruccion", &CParticles::GetDestroyTime,
		"ObtenerTiempoDeCreacion", &CParticles::GetInstanceTime,
		"ObtenerUsoDeColisiones", &CParticles::GetColisionUse
		);

	p_luaState.new_usertype<CTransform>("Transformador",
		sol::base_classes, sol::bases<AComponent>(),
		/* Methods */
		"CambiarPosicion", &CTransform::SetLocalPosition,
		"CambiarRotacion", &CTransform::SetLocalRotation,
		"CambiarEscala", &CTransform::SetLocalScale,
		"CambiarPosicionLocal", &CTransform::SetLocalPosition,
		"CambiarRotacionLocal", &CTransform::SetLocalRotation,
		"CambiarEscalaLocal", &CTransform::SetLocalScale,
		"CambiarPosicionDeMundo", &CTransform::SetWorldPosition,
		"CambiarRotacionDeMundo", &CTransform::SetWorldRotation,
		"CambiarEscalaDeMundo", &CTransform::SetWorldScale,
		"ObtenerPosicion", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldPosition(); },
		"ObtenerRotacion", [](CTransform& p_this) -> FQuaternion { return p_this.GetWorldRotation(); },
		"ObtenerEscala", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldScale(); },
		"ObtenerPosicionLocal", [](CTransform& p_this) -> FVector3 { return p_this.GetLocalPosition(); },
		"ObtenerRotacionLocal", [](CTransform& p_this) -> FQuaternion { return p_this.GetLocalRotation(); },
		"ObtenerEscalaLocal", [](CTransform& p_this) -> FVector3 { return p_this.GetLocalScale(); },
		"ObtenerPosicionDeMundo", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldPosition(); },
		"ObtenerRotacionDeMundo", [](CTransform& p_this) -> FQuaternion { return p_this.GetWorldRotation(); },
		"ObtenerEscalaDeMundo", [](CTransform& p_this) -> FVector3 { return p_this.GetWorldScale(); },
		"ObtenerAvance", &CTransform::GetWorldForward,
		"ObtenerLevanto", &CTransform::GetWorldUp,
		"ObtenerDerecha", &CTransform::GetWorldRight,
		"ObtenerAvanceLocal", &CTransform::GetLocalForward,
		"ObtenerLevantoLocal", &CTransform::GetLocalUp,
		"ObtenerDerechaLocal", &CTransform::GetLocalRight,
		"MundoAvanza", &CTransform::GetWorldForward,
		"SubeMundo", &CTransform::GetWorldUp,
		"MundoAlaDerecha", &CTransform::GetWorldRight
		);

    
    p_luaState.new_enum<OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour>("FrustumBehaviour",
        {
            {"DISABLED",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::DISABLED},
            {"CULL_MODEL",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_MODEL},
            {"CULL_MESHES",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_MESHES},
            {"CULL_CUSTOM",		OvCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_CUSTOM}
        });

	p_luaState.new_usertype<CModelRenderer>("ModeloDeRender",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerModelo", &CModelRenderer::GetModel,
		"CambiarModelo", &CModelRenderer::SetModel,
		"ObtenerComportamientoDeFrustum", &CModelRenderer::GetFrustumBehaviour,
		"CambiarComportamientoDeFrustum", &CModelRenderer::SetFrustumBehaviour
	);

	p_luaState.new_usertype<CMaterialRenderer>("MaterialDeRender",
		sol::base_classes, sol::bases<AComponent>(),
		"CambiarMaterial", &CMaterialRenderer::SetMaterialAtIndex,
		"CambiarMatrizDeElementosDeUsuario", &CMaterialRenderer::SetUserMatrixElement,
		"ObtenerMatrizDeElementosDeUsurario", &CMaterialRenderer::GetUserMatrixElement
	);

	p_luaState.new_enum<OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode>("ModoDetectorDeColisiones",
		{
			{"DISCRETO",		OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode::DISCRETE},
			{"CONTINUO",		OvPhysics::Entities::PhysicalObject::ECollisionDetectionMode::CONTINUOUS}
		});

	p_luaState.new_usertype<CPhysicalObject>("FisicasObjetos",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerMasa", &CPhysicalObject::GetMass,
		"CambiarMasa", &CPhysicalObject::SetMass,
		"ObtenerFriccion", &CPhysicalObject::GetFriction,
		"CambiarFriccion", &CPhysicalObject::SetFriction,
		"ObtenerRebote", &CPhysicalObject::GetBounciness,
		"CambiarRebote", &CPhysicalObject::SetBounciness,
		"CambiarVelocidadLineal", &CPhysicalObject::SetLinearVelocity,
		"CambiarVelocidadAngular", &CPhysicalObject::SetAngularVelocity,
		"ObtenerVelocidadLineal", &CPhysicalObject::GetLinearVelocity,
		"ObtenerVelocidadAngular", &CPhysicalObject::GetAngularVelocity,
		"CambiarFactorLineal", &CPhysicalObject::SetLinearFactor,
		"CambiarFactorAngular", &CPhysicalObject::SetAngularFactor,
		"ObtenerFactorLineal", &CPhysicalObject::GetLinearFactor,
		"ObtenerFactorAngular", &CPhysicalObject::GetAngularFactor,
		"EsColisionador", &CPhysicalObject::IsTrigger,
		"UsarColisionDeInteraccion", &CPhysicalObject::SetTrigger,
		"AgregarFuerza", &CPhysicalObject::AddForce,
		"AgregarImpulso", &CPhysicalObject::AddImpulse,
		"EliminarFuerzas", &CPhysicalObject::ClearForces,
		"CambiarDectorDeColisiones", &CPhysicalObject::SetCollisionDetectionMode,
		"ObtenerModoDeColision", &CPhysicalObject::GetCollisionDetectionMode,
		"CambiarKinematic", &CPhysicalObject::SetKinematic
		);

	p_luaState.new_usertype<CPhysicalBox>("PhysicalBox",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerSize", &CPhysicalBox::GetSize,
		"CambiarSize", &CPhysicalBox::SetSize
		);

	p_luaState.new_usertype<CPhysicalSphere>("PhysicalSphere",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerRadio", &CPhysicalSphere::GetRadius,
		"CambiarRadio", &CPhysicalSphere::SetRadius
		);

	p_luaState.new_usertype<CPhysicalCapsule>("PhysicalCapsule",
		sol::base_classes, sol::bases<CPhysicalObject>(),
		"ObtenerRadio", &CPhysicalCapsule::GetRadius,
		"CambiarRadio", &CPhysicalCapsule::SetRadius,
		"ObtenerAltura", &CPhysicalCapsule::GetHeight,
		"CambiarAltura", &CPhysicalCapsule::SetHeight
		);

    p_luaState.new_enum<OvRendering::Settings::EProjectionMode>("ProjectionMode",
    {
        {"ORTHOGRAPHIC",	OvRendering::Settings::EProjectionMode::ORTHOGRAPHIC},
        {"PERSPECTIVE",		OvRendering::Settings::EProjectionMode::PERSPECTIVE}
    });

	p_luaState.new_usertype<CCamera>("Camera",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerFov", &CCamera::GetFov,
		"ObtenerSize", &CCamera::GetSize,
		"ObtenerCerca", &CCamera::GetNear,
		"ObtenerLejos", &CCamera::GetFar,
		"ObtenerColorDespejado", &CCamera::GetClearColor,
		"CambiarFov", &CCamera::SetFov,
		"CambiarSize", &CCamera::SetSize,
		"CambiarCerca", &CCamera::SetNear,
		"CambiarLejos", &CCamera::SetFar,
		"CambiarColorDespejado", &CCamera::SetClearColor,
        "HasFrustumGeometryCulling", &CCamera::HasFrustumGeometryCulling,
        "HasFrustumLightCulling", &CCamera::HasFrustumLightCulling,
        "ObtenerModoProyeccion", &CCamera::GetProjectionMode,
        "SetFrustumGeometryCulling", &CCamera::SetFrustumGeometryCulling,
        "SetFrustumLightCulling", &CCamera::SetFrustumLightCulling,
        "CambiarModoProyeccion", &CCamera::SetProjectionMode
		);

	p_luaState.new_usertype<CLight>("Luz",
		sol::base_classes, sol::bases<AComponent>(),
		"ObtenerColor", &CPointLight::GetColor,
		"ObtenerIntensidad", &CPointLight::GetIntensity,
		"CambiarColor", &CPointLight::SetColor,
		"CambiarIntensidad", &CPointLight::SetIntensity
		);

	p_luaState.new_usertype<CPointLight>("PuntoDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerConstante", &CPointLight::GetConstant,
		"ObtenerLineal", &CPointLight::GetLinear,
		"ObtenerCuadratica", &CPointLight::GetQuadratic,
		"CambiarConstante", &CPointLight::SetConstant,
		"CambiarLineal", &CPointLight::SetLinear,
		"CambiarCuadratica", &CPointLight::SetQuadratic
		);

	p_luaState.new_usertype<CSpotLight>("LugarDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerConstante", &CSpotLight::GetConstant,
		"ObtenerLineal", &CSpotLight::GetLinear,
		"ObtenerCuadratica", &CSpotLight::GetQuadratic,
		"ObtenerCorte", &CSpotLight::GetCutoff,
		"ObtenerCorteExterno", &CSpotLight::GetOuterCutoff,
		"CambiarConstante", &CSpotLight::SetConstant,
		"CambiarLineal", &CSpotLight::SetLinear,
		"CambiarCuadratica", &CSpotLight::SetQuadratic,
		"CambiarCorte", &CSpotLight::SetCutoff,
		"CambiarCorteExterno", &CSpotLight::SetOuterCutoff
		);

	p_luaState.new_usertype<CAmbientBoxLight>("CajaAmbientalDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerSize", &CAmbientBoxLight::GetSize,
		"CambiarSize", &CAmbientBoxLight::SetSize
		);

	p_luaState.new_usertype<CAmbientSphereLight>("EsferaAmbientalDeLuz",
		sol::base_classes, sol::bases<CLight>(),
		"ObtenerRadio", &CAmbientSphereLight::GetRadius,
		"CambiarRadio", &CAmbientSphereLight::SetRadius
		);

	p_luaState.new_usertype<CDirectionalLight>("LuzDireccional",
		sol::base_classes, sol::bases<CLight>()
		);

	p_luaState.new_usertype<CAudioSource>("RecursoDeAudio",
		sol::base_classes, sol::bases<AComponent>(),
		"Empezar", &CAudioSource::Play,
		"Detener", &CAudioSource::Stop,
		"Pausa", &CAudioSource::Pause,
		"Reanudar", &CAudioSource::Resume,
		"ObtenerSonido", &CAudioSource::GetSound,
		"ObtenerVolumen", &CAudioSource::GetVolume,
		"ObtenerPan", &CAudioSource::GetPan,
		"EsLooped", &CAudioSource::IsLooped,
		"ObtenerPitch", &CAudioSource::GetPitch,
		"EstaTerminado", &CAudioSource::IsFinished,
		"EsEspacial", &CAudioSource::IsSpatial,
		"ObtenerUmbralDeAtenuacion", &CAudioSource::GetAttenuationThreshold,
		"CambiarSonido", &CAudioSource::SetSound,
		"CambiarVolumen", &CAudioSource::SetVolume,
		"CambiarPan", &CAudioSource::SetPan,
		"CambiarLooped", &CAudioSource::SetLooped,
		"CambiarPitch", &CAudioSource::SetPitch,
		"CambiarEspacial", &CAudioSource::SetSpatial,
		"CambiarUmbralDeAtenuacion", &CAudioSource::SetAttenuationThreshold
		);

	p_luaState.new_usertype<CAudioListener>("AudioListener",
		sol::base_classes, sol::bases<AComponent>()
		);
}
