#pragma once

#ifndef _GRAPHICS_RTTSHADERLIST_H
#define _GRAPHICS_RTTSHADERLIST_H

#include <OgreMaterialManager.h>

namespace Ogre {
    class Technique;
    class Material;

    namespace RTShader {
        class ShaderGenerator;
    }
}

class RTShaderTecnhiqueResolveListener: public Ogre::MaterialManager::Listener
{
private:
    //Puntero a la instancia del ShaderGenerator
    Ogre::RTShader::ShaderGenerator* mShaderGenerator_;

public:
    //Constructora
    RTShaderTecnhiqueResolveListener(Ogre::RTShader::ShaderGenerator* pShaderGeneratorInstance);
    //Destructora
    virtual ~RTShaderTecnhiqueResolveListener();

    //Creacion de shaders en sistemas de renderizado que carecen de FixedPipeline
    Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName,
    Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend)override;
};

#endif