#include "RTShaderTecnhiqueResolveListener.h"
#include <OgreShaderGenerator.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>

RTShaderTecnhiqueResolveListener::RTShaderTecnhiqueResolveListener(Ogre::RTShader::ShaderGenerator* pShaderGeneratorInstance)
{
	mShaderGenerator_ = pShaderGeneratorInstance;
}

RTShaderTecnhiqueResolveListener::~RTShaderTecnhiqueResolveListener() {}

Ogre::Technique* RTShaderTecnhiqueResolveListener::handleSchemeNotFound(
    unsigned short /*schemeIndex*/, const Ogre::String& schemeName,
    Ogre::Material* originalMaterial, unsigned short /*lodIndex*/,
    const Ogre::Renderable* /*rend*/) {
    Ogre::Technique* generatedTech = nullptr;

    // Case this is the default shader generator scheme.
    if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME) {
        // Create shader generated technique for this material.
        const bool techniqueCreated =
            mShaderGenerator_->createShaderBasedTechnique(
                *originalMaterial, Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                schemeName);

        // Case technique registration succeeded.
        if (techniqueCreated) {
            // Force creating the shaders for the generated technique.
            mShaderGenerator_->validateMaterial(schemeName,
                originalMaterial->getName());

            // Grab the generated technique.
            Ogre::Material::Techniques itTech =
                originalMaterial->getTechniques();

            for (auto curTech : itTech) {
                if (curTech->getSchemeName() == schemeName) {
                    generatedTech = curTech;
                    break;
                }
            }
        }
    }

    return generatedTech;
}