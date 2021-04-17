#include "Camera.h"
#include <OgreCamera.h>
#include "RenderManager.h"
#include "OgreContext.h"
#include "WindowGenerator.h"
#include "Ogre.h"
#include "OgreSceneNode.h"
#include "Vector3.h"
#include "CommonManager.h"
#include "Entity.h"
#include "Transform.h"

void Camera::init()
{
	mCamera_ = OgreContext::getInstance()->getSceneManager()->createCamera(name);
	mCamera_->setNearClipDistance(1);
	mCamera_->setFarClipDistance(10000);
	//mCamera_->lookAt(0, 0, -1);
	mCamera_->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	camNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(name+"Node");
	camNode_->attachObject(mCamera_);

	camNode_->setPosition(0, 0, 1000);
	camNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	vp_ = WindowGenerator::getInstance()->getRenderWindow()->addViewport(mCamera_);
	vp_->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0, 1.0));//cambia el color del fondo
}

Camera::Camera(): Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Camera)
{
	init();

}

Camera::Camera(std::string cameraName) : Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Camera),name(cameraName)
{
	init();
}

Camera::Camera(Ogre::SceneNode* parentNode,std::string cameraName) : Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Camera), name(cameraName)
{
	mCamera_ = OgreContext::getInstance()->getSceneManager()->createCamera(name);
	mCamera_->setNearClipDistance(1);
	mCamera_->setFarClipDistance(10000);
	//mCamera_->lookAt(0, 0, -1);
	mCamera_->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	camNode_ = parentNode->createChildSceneNode(name + "Node");
	camNode_->attachObject(mCamera_);

	camNode_->setPosition(0, 0, 1000);
	camNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	vp_ = WindowGenerator::getInstance()->getRenderWindow()->addViewport(mCamera_);
	vp_->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0, 1.0));//cambia el color del fondo
}

Camera::~Camera()
{

}

void Camera::update()
{
	//posicion
	Vector3 pos = tr_->getPos();
	camNode_->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	Vector3 rot = tr_->getRot();
	//rotaciones //TO DO: revisar
	camNode_->resetOrientation();
	camNode_->yaw(Ogre::Degree(rot.y), Ogre::Node::TS_WORLD);//ejeY
	camNode_->pitch(Ogre::Degree(rot.x), Ogre::Node::TS_WORLD);//ejex
	camNode_->roll(Ogre::Degree(rot.z), Ogre::Node::TS_WORLD);//ejez
	//escala
	Vector3 scale = tr_->getDimensions();
	camNode_->scale(Ogre::Vector3(scale.x, scale.y, scale.z));
}

void Camera::setUp()
{
	tr_ = static_cast<Transform*>(_entity->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
}

void Camera::setCameraPosition(Vector3 newPos)
{
	camNode_->setPosition(Ogre::Vector3(newPos.x, newPos.y, newPos.z));
}

void Camera::setCameraDir(Vector3 newDir)
{
	newDir.normalize();
	camNode_->lookAt(Ogre::Vector3(newDir.x, newDir.y, newDir.z), Ogre::Node::TS_WORLD);
}

void Camera::setBackgroundColor(Vector3 newColor, float alpha)
{
	vp_->setBackgroundColour(Ogre::ColourValue(newColor.x, newColor.y, newColor.z, alpha));//cambia el color del fondo
}

void Camera::setNearClipDistance(int distance)
{
	mCamera_->setNearClipDistance(distance);

}

void Camera::setFarClipDistance(int distance)
{
	
	mCamera_->setFarClipDistance(distance);
}

Vector3 Camera::getCameraPosition()
{
	Ogre::Vector3 aux = camNode_->getPosition();
	return Vector3(aux.x, aux.y, aux.z);
}

Ogre::Camera* Camera::getCamera() {
	return mCamera_;
}
