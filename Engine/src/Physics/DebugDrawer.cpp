#include "DebugDrawer.h"

inline btVector3 convertVector(const Ogre::Vector3& V) {
    return btVector3(V.x, V.y, V.z);
}

inline Ogre::Vector3 cvt(const btVector3& V) {
    return Ogre::Vector3(V.x(), V.y(), V.z());
}

inline btQuaternion convertVector(const Ogre::Quaternion& Q) {
    return { Q.x, Q.y, Q.z, Q.w };
};

inline Ogre::Quaternion convertVector(const btQuaternion& Q) {
    return Ogre::Quaternion(Q.w(), Q.x(), Q.y(), Q.z());
};

bool OgreDebugDrawer::frameStarted(const Ogre::FrameEvent& evt)
{
    const size_t now = Ogre::Root::getSingleton().getTimer()->getMilliseconds();
    std::vector<ContactPoint>* newCP = mContactPoints_ == &mContactPoints1_
        ? &mContactPoints2_
        : &mContactPoints1_;
    for (auto i = mContactPoints_->begin(); i < mContactPoints_->end(); ++i) {
        ContactPoint& cp = *i;
        mLines_->position(cp.from);
        mLines_->colour(cp.color);
        mLines_->position(cp.to);
        if (now <= cp.dieTime)
            newCP->push_back(cp);
    }
    mContactPoints_->clear();
    mContactPoints_ = newCP;

    mLines_->end();
    mTriangles_->end();

    return true;
}

bool OgreDebugDrawer::frameEnded(const Ogre::FrameEvent& evt)
{
    mLines_->beginUpdate(0);
    mTriangles_->beginUpdate(0);
    return true;
}

OgreDebugDrawer::OgreDebugDrawer(Ogre::SceneManager* scm)
{
    mContactPoints1_ = {};
    mContactPoints2_ = {};
    mContactPoints_ = &mContactPoints1_;
    mLines_ = new Ogre::ManualObject("physics lines");
    mTriangles_ = new Ogre::ManualObject("physics triangles");
    mLines_->setDynamic(true);
    mTriangles_->setDynamic(true);

    scm->getRootSceneNode()->attachObject(mLines_);
    scm->getRootSceneNode()->attachObject(mTriangles_);

    static auto matName = "OgreBulletCollisionsDebugDefault";
    Ogre::MaterialPtr mtl =
        Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
    mtl->setReceiveShadows(false);
    mtl->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    mtl->setDepthBias(0.1f, 0.0f);
    Ogre::TextureUnitState* tu =
        mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
    tu->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE);
    mtl->getTechnique(0)->setLightingEnabled(false);

    mLines_->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
    mLines_->position(Ogre::Vector3::ZERO);
    mLines_->colour(Ogre::ColourValue::Blue);
    mLines_->position(Ogre::Vector3::ZERO);
    mLines_->colour(Ogre::ColourValue::Blue);

    mTriangles_->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    mTriangles_->position(Ogre::Vector3::ZERO);
    mTriangles_->colour(Ogre::ColourValue::Blue);
    mTriangles_->position(Ogre::Vector3::ZERO);
    mTriangles_->colour(Ogre::ColourValue::Blue);
    mTriangles_->position(Ogre::Vector3::ZERO);
    mTriangles_->colour(Ogre::ColourValue::Blue);

    mDebugModes_ = DBG_DrawWireframe;
    Ogre::Root::getSingleton().addFrameListener(this);
}

OgreDebugDrawer::~OgreDebugDrawer()
{
    Ogre::Root::getSingleton().removeFrameListener(this);
    delete mLines_;
    delete mTriangles_;
}

void OgreDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    Ogre::ColourValue c(color.getX(), color.getY(), color.getZ());
    c.saturate();
    mLines_->position(cvt(from));
    mLines_->colour(c);
    mLines_->position(cvt(to));
    mLines_->colour(c);
}

void OgreDebugDrawer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha)
{
    Ogre::ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
    c.saturate();
    mTriangles_->position(cvt(v0));
    mTriangles_->colour(c);
    mTriangles_->position(cvt(v1));
    mTriangles_->colour(c);
    mTriangles_->position(cvt(v2));
    mTriangles_->colour(c);
}

void OgreDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    mContactPoints_->resize(mContactPoints_->size() + 1);
    auto& p = *(mContactPoints_->end() - 1);
    p.from = cvt(PointOnB);
    p.to = p.from + cvt(normalOnB) * distance;
    p.dieTime = Ogre::Root::getSingleton().getTimer()->getMilliseconds() + lifeTime;
    p.color.r = color.x();
    p.color.g = color.y();
    p.color.b = color.z();
}

void OgreDebugDrawer::reportErrorWarning(const char* warningString)
{
    Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
}

void OgreDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
}

void OgreDebugDrawer::setDebugMode(int debugMode)
{
    mDebugModes_ = static_cast<DebugDrawModes>(debugMode);
}

int OgreDebugDrawer::getDebugMode() const
{
    return mDebugModes_;
}
