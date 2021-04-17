#pragma once
#include "Component.h"
#include <string>

class SceneManager;
class Transform;

namespace Ogre {
	class SceneNode;
	class Entity;
	
}

class MeshComponent: public Component
{
private:

	Ogre::SceneNode* mNode_ = nullptr;		
	Ogre::SceneNode* parentNode_ = nullptr; 
	Ogre::Entity* ogreEnt_ = nullptr;
	Transform* tr_;
	
protected:
	//metodo que crea e inicia la camara co los valores por defacto
	virtual void init()override {}

public:
	//constructora por defecto
	MeshComponent();
	//consructora para crear un nodo hijo de otro nodo
	MeshComponent(Ogre::SceneNode* parentNode,const std::string meshName);
	//constructora para crear un nodo hijo der root
	MeshComponent(const std::string meshName);

	//metodo para desactivar el componente y su nodo
	virtual void setActive( bool act) override;
	

	virtual ~MeshComponent();
	virtual void update() override;
	virtual void setUp() override;

	//metodo para asignar un material nuevo a la entidad
	void setMaterial(std::string matName);
};

