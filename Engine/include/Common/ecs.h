#pragma once
#include <ctime>

namespace ecs {

	
	using CmpIdType = std::size_t;

	enum CmpId : CmpIdType {
		Transform = 0,
		Gravity,
		Rigidbody,
		BoxColider,
		SphereCollider,
		Camera,
		Light,
		Image,
		Mesh,
		Button,
		Text,
		AudioComponent,
	
		//
		// Este ultimo tipo es para identificar el numero maximo de componentes
		LastCmptId
	};
	constexpr std::size_t maxComponents = LastCmptId;

	// these two should be used to get a component via the field
	// entity
//#define GETCMP2(id,type)  GETCMP3(entity,id,type)
//#define GETCMP1(type)     GETCMP3(entity_,ecs::type,type)

// these two should be used to get a component via an
// entity e provided as a parameter
//#define GETCMP2(e,type) GETCMP3(e,ecs::type,type)
//#define GETCMP3(e,id,type) e->getComponent<type>(id)

}