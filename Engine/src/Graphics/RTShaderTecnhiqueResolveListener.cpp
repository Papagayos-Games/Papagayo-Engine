#include "RTShaderTecnhiqueResolveListener.h"
#include <OgreShaderGenerator.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>

RTShaderTecnhiqueResolveListener::RTShaderTecnhiqueResolveListener(Ogre::RTShader::ShaderGenerator* pShaderGeneratorInstance)
{
	mShaderGenerator_ = pShaderGeneratorInstance;
}

RTShaderTecnhiqueResolveListener::~RTShaderTecnhiqueResolveListener() {}

Ogre::Technique* RTShaderTecnhiqueResolveListener::handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName,
	Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend)
{

	// Create shader generated technique for this material.
	bool techniqueCreated =
		mShaderGenerator_->createShaderBasedTechnique(*originalMaterial, Ogre::MaterialManager::DEFAULT_SCHEME_NAME, schemeName);

	//No created technique
	if (!techniqueCreated)return nullptr;

	//Force creating the shaders for the generated technique.
	mShaderGenerator_->validateMaterial(schemeName, *originalMaterial);

	// Grab the generated technique.
	Ogre::Material::Techniques itTech = originalMaterial->getTechniques();

	for (auto curTech : itTech) {
		Ogre::String currSchemeName = curTech->getSchemeName();
		if (currSchemeName == schemeName) {
			return curTech; //SHADERS CREATED
		}
	}

	//If it reaches this point -> ERROR
	return nullptr;

}