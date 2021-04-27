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
    PlaneComponent();

    void setMaterial(std::string matName);
    virtual void init();
    virtual void update() {};
    virtual void load(nlohmann::json params)override;

};

