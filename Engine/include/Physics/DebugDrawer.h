#pragma once

#ifndef _PHYSICS_DEBUGDRAWER_H
#define _PHYSICS_DEBUGDRAWER_H

#include "LinearMath/btIDebugDraw.h"
#include <Ogre.h>

class OgreDebugDrawer final : public btIDebugDraw, public Ogre::FrameListener {
    struct ContactPoint {
        Ogre::Vector3 from;
        Ogre::Vector3 to;
        Ogre::ColourValue color;
        size_t dieTime;
    };
    DebugDrawModes mDebugModes_;
    Ogre::ManualObject* mLines_;
    Ogre::ManualObject* mTriangles_;
    std::vector<ContactPoint>* mContactPoints_;
    std::vector<ContactPoint> mContactPoints1_;
    std::vector<ContactPoint> mContactPoints2_;

protected:
    bool frameStarted(const Ogre::FrameEvent& evt) override;
    bool frameEnded(const Ogre::FrameEvent& evt) override;

public:
    OgreDebugDrawer(Ogre::SceneManager* scm);
    ~OgreDebugDrawer();

    //Dibuja lineas
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
    //Dibuja triangulos
    void drawTriangle(const btVector3& v0, const btVector3& v1, 
        const btVector3& v2, const btVector3& color, btScalar alpha) override;
    //Dibuja puntos de contacto
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
        btScalar distance, int lifeTime, const btVector3& color) override;
    //Reporta errores
    void reportErrorWarning(const char* warningString) override;
    //Dibuja texto en 3D
    void draw3dText(const btVector3& location, const char* textString) override;
    //Asignar modo debug
    void setDebugMode(int debugMode) override;
    //Obtener modo debug
    int getDebugMode() const override;
};

#endif