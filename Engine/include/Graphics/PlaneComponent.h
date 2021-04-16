#pragma once
#include <Component.h>
#include <string>


class Vector3;
namespace Ogre {
    class SceneNode;
    class Entity;
    class MovablePlane;
}

enum class PLANE_DIR
{
    PLANE_X, PLANE_Y, PLANE_Z
};

class PlaneComponent :
    public Component
{
private:
    Ogre::SceneNode* mNode_ = nullptr;
    Ogre::Entity* ent_ = nullptr;
public:
    PlaneComponent(std::string name, std::string materialName, int width, int height, PLANE_DIR type = PLANE_DIR::PLANE_Y);

    void setTexture(std::string textName);
    virtual void init() {};
    virtual void update() {};
};

