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

    /** This is the hook point where shader based technique will be created.
    It will be called whenever the material manager won't find appropriate
    technique that satisfy the target scheme name. If the scheme name is out
    target RT Shader System scheme name we will try to create shader generated
    technique for it.
    */
    Ogre::Technique* handleSchemeNotFound(
        unsigned short schemeIndex, const Ogre::String& schemeName,
        Ogre::Material* originalMaterial, unsigned short lodIndex,
        const Ogre::Renderable* rend) override;
};

#endif