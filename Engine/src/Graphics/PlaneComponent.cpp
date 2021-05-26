#include "PlaneComponent.h"
#include "RenderManager.h"
#include "OgreMeshManager.h"
#include "Vector3.h"
#include "OgreSceneNode.h"
#include "OgreContext.h"
#include <checkML.h>
#include "OgreEntity.h"
#include "OgreSceneManager.h"

PlaneComponent::PlaneComponent():
	Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Plane)
{
	init();
}

PlaneComponent::~PlaneComponent()
{
	if (ent_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroyEntity(ent_);
	if (mNode_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroySceneNode(mNode_);
}

void PlaneComponent::init(){
	mNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}

void PlaneComponent::update(float deltaTime){}
void PlaneComponent::setMaterial(const std::string& matName)
{
	try {
		ent_->setMaterialName(matName);
	}
	catch (const std::exception& e) {
		throw std::runtime_error("The texture " + matName + " no exist. " + e.what());
	}
}

void PlaneComponent::load(const nlohmann::json& params)
{
	std::string name;
	auto it = params.find("planeName");
	if (it != params.end()) {
		 name = it->get<std::string>();
	}
	else {
		throw std::runtime_error("Cannot create plane without name\n");
	}
	
	float width, height = 1;


	it = params.find("width");
	if (it != params.end()) {
		
	   width = it->get<float>();
	}

	it = params.find("height");
	if (it != params.end()) {

		height = it->get<float>();
	}

	PLANE_DIR planedir_;
	Ogre::Vector3 normalPlane= Ogre::Vector3::UNIT_Y;
	Ogre::Vector3 upVector= Ogre::Vector3::UNIT_Z;
	it = params.find("planeDir");
	if (it != params.end()) {
		int type = it->get<int>();
		planedir_ = (PLANE_DIR)type;

		switch (planedir_)
		{
		case PLANE_DIR::PLANE_X:
			 normalPlane = Ogre::Vector3::UNIT_X;
			 upVector = Ogre::Vector3::UNIT_Z;

			break;
		case PLANE_DIR::PLANE_Y:
			normalPlane = Ogre::Vector3::UNIT_Y;
			upVector = Ogre::Vector3::UNIT_Z;
			break;
		case PLANE_DIR::PLANE_Z:
			normalPlane = Ogre::Vector3::UNIT_Z;
			upVector = Ogre::Vector3::UNIT_Y;
			break;
		}
	}

	Ogre::MeshManager::getSingleton().createPlane(name,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(normalPlane, 0), width, height,
		1, 1, true, 1, 1.0, 1.0,upVector);

	ent_ = OgreContext::getInstance()->getSceneManager()->createEntity(name);
	
	it = params.find("planeMaterial");
	if (it != params.end()) {
		std::string mat = it->get<std::string>();
		setMaterial(mat);
	}
	mNode_->attachObject(ent_);
}

 