#include "Camera.h"
#include <OgreCamera.h>
#include "RenderManager.h"
#include "OgreContext.h"
#include <checkML.h>
#include "Ogre.h"
#include "OgreSceneNode.h"
#include "Vector3.h"
#include "CommonManager.h"
#include "Entity.h"
#include "Transform.h"
#include <algorithm>

void Camera::init()
{
	camNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
}

Camera::Camera() : Component(RenderManager::getInstance(), (int)RenderManager::RenderCmpId::Camera)
{
	init();
}

Camera::~Camera()
{
	if (mCamera_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroyCamera(mCamera_);
	if (camNode_ != nullptr) OgreContext::getInstance()->getSceneManager()->destroySceneNode(camNode_);
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

void Camera::load(const nlohmann::json& params)
{
	//PARAMETRO NOMBRE OBLIGATORIO
	auto it = params.find("camName");
	if (it != params.end()) {
		name_ = it->get<std::string>();
		mCamera_ = OgreContext::getInstance()->getSceneManager()->createCamera(name_);
		camNode_->attachObject(mCamera_);
	}
	else {
		throw std::runtime_error("Cannot create camera without specified name\n");
	}

	//Posición de la cámara
	//TO DO: Probably lo lleve el transform
	it = params.find("camPosition");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		camNode_->setPosition(pos[0], pos[1], pos[2]);
	}

	//Posición hacia la que está mirando la cámara
	it = params.find("lookAt");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		camNode_->lookAt(Ogre::Vector3(pos[0], pos[1], pos[2]), Ogre::Node::TS_WORLD);
	}

	//Tipo de camara
	it = params.find("camType");
	if (it != params.end()) {
		int type = it->get<int>();
		if (type == 0 || type == 1) type_ = (CameraType)type;
	}

	//Configurar el viewport para que no ocupe toda la ventana
	it = params.find("viewport");
	if (it != params.end() && it->is_object()) {

		int zOrder = 0;
		float left = 0.0, top = 0.0, width = 1.0, height = 1.0;

		//zOrder
		auto aux = it->find("zOrder");
		if (aux != it->end()) {
			zOrder = aux->get<int>();
		}

		float value;
		aux = it->find("left");
		if (aux != it->end()) {
			value = aux->get<float>();
			if (value >= 0.0f && value <= 1.0f)
				left = value;
		}

		aux = it->find("top");
		if (aux != it->end()) {
			value = aux->get<float>();
			if (value >= 0.0f && value <= 1.0f)
				top = value;
		}

		aux = it->find("width");
		if (aux != it->end()) {
			value = aux->get<float>();
			if (value >= 0.0f && value <= 1.0f)
				width = value;
		}

		aux = it->find("height");
		if (aux != it->end()) {
			value = aux->get<float>();
			if (value >= 0.0f && value <= 1.0f)
				height = value;
		}

		vp_ = OgreContext::getInstance()->getRenderWindow()->addViewport(mCamera_, zOrder, left, top, width, height);
	}
	//Viewport por defecto
	else vp_ = OgreContext::getInstance()->getRenderWindow()->addViewport(mCamera_);

	//Color del viewPort
	it = params.find("viewportColor");
	if (it != params.end()) {
		std::vector<float> color = it->get<std::vector<float>>();
		vp_->setBackgroundColour(Ogre::ColourValue(color[0], color[1], color[2], color[3]));
	}

	//AspectRatio automatico
	it = params.find("autoAspectRatio");
	if (it != params.end()) {
		bool autoAspectRatio = it->get<bool>();
		mCamera_->setAutoAspectRatio(autoAspectRatio);
	}
	//Por defecto si no, siempre se ajusta
	else mCamera_->setAutoAspectRatio(true);

	//NearClipDistance
	it = params.find("nearClipDistance");
	if (it != params.end()) {
		int near = it->get<int>();
		mCamera_->setNearClipDistance(near);
	}
	else mCamera_->setNearClipDistance(1);

	//FarClipDistance
	it = params.find("farClipDistance");
	if (it != params.end()) {
		int far = it->get<int>();
		mCamera_->setFarClipDistance(far);
	}
	else mCamera_->setFarClipDistance(10000);

}

void Camera::setCameraPosition(const Vector3& newPos)
{
	camNode_->setPosition(Ogre::Vector3(newPos.x, newPos.y, newPos.z));
}

void Camera::setCameraDir(Vector3& newDir)
{
	newDir.normalize();
	camNode_->lookAt(Ogre::Vector3(newDir.x, newDir.y, newDir.z), Ogre::Node::TS_WORLD);
}

void Camera::setBackgroundColor(const Vector3& newColor, float alpha)
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

const Vector3& Camera::getCameraPosition()
{
	Ogre::Vector3 aux = camNode_->getPosition();
	return Vector3(aux.x, aux.y, aux.z);
}

const Vector3& Camera::getCameraPosition() const
{
	Ogre::Vector3 aux = camNode_->getPosition();
	return Vector3(aux.x, aux.y, aux.z);
}

Ogre::Camera* Camera::getCamera() {
	return mCamera_;
}

Ogre::Camera* Camera::getCamera() const {
	return mCamera_;
}