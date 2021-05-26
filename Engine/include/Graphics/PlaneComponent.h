#pragma once

#ifndef _GRAPHICS_PLANECOMP_H
#define _GRAPHICS_PLANECOMP_H

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
    virtual ~PlaneComponent();

    //Cambiar el material asociado al plano
    void setMaterial(const std::string& matName);
    virtual void init();
    virtual void update(float deltaTime);
    virtual void load(const nlohmann::json& params)override;
};

#endif