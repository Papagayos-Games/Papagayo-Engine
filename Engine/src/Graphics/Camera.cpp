#include "Graphics/Camera.h"
#include <OgreCamera.h>
#include "Managers/RenderManager.h"
#include "Graphics/OgreContext.h"
#include "Graphics/WindowGenerator.h"
#include "Ogre.h"
#include "OgreSceneNode.h"
#include "Vector3.h"

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

Camera::~Camera()
{

}

void Camera::update()
{
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
