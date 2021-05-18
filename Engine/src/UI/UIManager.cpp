#include "UIManager.h"
//INCLUDE COMPONENTS
#include "UIButton.h"
#include "UISlider.h"
#include "UILabel.h"
#include "UIImage.h"
#include "UIPointer.h"

//INCLUDE CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "CEGUI/RendererModules/Ogre/ResourceProvider.h"
#include <glm/glm.hpp>

//ADDITIONAL INCLUDES
#include "OgreContext.h"
#include <iostream>


#pragma region Generales

inline glm::vec2 cvt(const vector2& V) {
	return glm::vec2(V.first, V.second);
}

inline vector2 cvt(const glm::vec2& V) {
	return vector2(V.x, V.y);
}

UIManager* UIManager::instance_ = nullptr;

UIManager::UIManager() : Manager(ManID::UI)
{
	registerComponent("Button", (int)UIManager::UICmpId::Button, []() -> UIButton* { return new UIButton(); });
	registerComponent("Slider", (int)UIManager::UICmpId::Slider, []() -> UISlider* { return new UISlider(); });
	registerComponent("Label", (int)UIManager::UICmpId::Label, []() -> UILabel* { return new UILabel(); });
	registerComponent("Image", (int)UIManager::UICmpId::Image, []() -> UIImage* { return new UIImage(); });
	registerComponent("Pointer", (int)UIManager::UICmpId::Pointer, []() -> UIPointer* { return new UIPointer(); });

	//Ogre
	oRoot = OgreContext::getInstance()->getOgreRoot();
	oWindow = OgreContext::getInstance()->getRenderWindow();
	
	//Cegui
	guiRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*OgreContext::getInstance()->getRenderTarget());
	guiRenderer->setUsingShaders(true);
	guiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("Looknfeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::AnimationManager::setDefaultResourceGroup("Animations");

	guiWinMng = &CEGUI::WindowManager::getSingleton();
	winRoot = guiWinMng->createWindow("DefaultWindow", "rootWindow");
	guiContext->setRootWindow(winRoot);
	
	createFrameListener();
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	return instance_;
}

bool UIManager::setUpInstance() {
	if (instance_ == nullptr) {
		try {
			instance_ = new UIManager();
		}
		catch (...) {
			return false;
		}
	}
	return true;
}

void UIManager::clean()
{
	//if (instance_->sch != nullptr)
	//	delete instance_->sch;

	instance_->destroyAllComponents();
}

void UIManager::destroy()
{
	clean();
	CEGUI::OgreRenderer::destroySystem();
	delete instance_;
}

void UIManager::start()
{
}

void UIManager::update()
{
}

void UIManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width = 0, height = 0, depth = 0;
	int left = 0, top = 0;
	rw->getMetrics(width, height, depth, left, top);
	CEGUI::Sizef newSize(width, height);

	CEGUI::System::getSingleton().notifyDisplaySizeChanged(newSize);
}

void UIManager::loadScheme(const std::string& schemeName_, const std::string& schemeFile)
{
	schemeName = schemeName_;
	
	//if (sch != nullptr)
	//	delete sch;
	
	sch = &CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void UIManager::loadFont(const std::string& filename)
{
	CEGUI::FontManager::getSingleton().createFromFile(filename);
}

void UIManager::loadLayout(const std::string& layaoutFile) {
	try {
		CEGUI::Window* layout = guiWinMng->loadLayoutFromFile(layaoutFile);
		winRoot->addChild(layout);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

}

void UIManager::setFont(const std::string& fontFile)
{
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	guiContext->setDefaultFont(fontFile);

	guiContext->getDefaultFont()->setAutoScaled(
		CEGUI::AutoScaledMode::ASM_Disabled);
}

#pragma endregion

#pragma region Mouse

void UIManager::setMouseImage(const std::string& imageFile)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(imageFile);

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage(imageFile);
}

void UIManager::setMouseVisibility(bool b)
{
	if (b)
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	else
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

#pragma endregion

#pragma region Widget

CEGUI::Window* UIManager::createButton(const std::string& text, vector2 position,
	vector2 size, const std::string& name)
{
	CEGUI::Window* button = NULL;
	button = guiWinMng->createWindow(schemeName + "/Button", name);  // Create Window

	setWidgetDestRect(button, position, size);

	button->setText(text);
	winRoot->addChild(button);
	return button;
}

CEGUI::Window* UIManager::createSlider(vector2 position, vector2 size, const std::string& name)
{
	CEGUI::Window* slider = CEGUI::WindowManager::getSingleton().createWindow(
		schemeName + "/Slider");
	setWidgetDestRect(slider, position, size);
	slider->setRotation(CEGUI::Quaternion(1, 0, 0, 0.71));
	slider->setName(name);
	winRoot->addChild(slider);

	return slider;
}

CEGUI::Window* UIManager::createLabel(const std::string& text, vector2 position, vector2 size, const std::string& name)
{
	CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow(
		schemeName + "/Label", name);
	setWidgetDestRect(label, position, size);

	label->setText(text);

	//label->setProperty("FrameEnabled", "false");
	//label->setProperty("BackgroundEnabled", "false");

	winRoot->addChild(label);

	return label;
}

CEGUI::Window* UIManager::createImage(const std::string& image, vector2 position, vector2 size, const std::string& name)
{
	CEGUI::Window* staticImage =
		CEGUI::WindowManager::getSingleton().createWindow(
			schemeName + "/StaticImage", name);
	setWidgetDestRect(staticImage, position, size);

	staticImage->setProperty("FrameEnabled", "false");
	staticImage->setProperty("BackgroundEnabled", "false");
	staticImage->setProperty("Image", image);

	winRoot->addChild(staticImage);

	return staticImage;
}

void UIManager::setWidgetDestRect(CEGUI::Window* widget, vector2 position, vector2 size)
{
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(cvt(position).x, 0),
		CEGUI::UDim(cvt(position).y, 0)));
	widget->setSize(
		CEGUI::USize(CEGUI::UDim(0, cvt(size).x), CEGUI::UDim(0, cvt(size).y)));
}

#pragma endregion

#pragma region INPUT

void UIManager::captureInput(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT)
			guiContext->injectMouseButtonDown(CEGUI::LeftButton);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			guiContext->injectMouseButtonDown(CEGUI::RightButton);

	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT)
			guiContext->injectMouseButtonUp(CEGUI::LeftButton);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			guiContext->injectMouseButtonUp(CEGUI::RightButton);

	}
	else if (event.type == SDL_MOUSEMOTION) {
		guiContext->injectMousePosition((event.motion.x), (event.motion.y));

	}
	else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
		event.window.event == SDL_WINDOWEVENT_RESIZED ||
		event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		windowResized(oWindow);
}

void UIManager::createFrameListener()
{
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	oWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;

	// Set initial mouse clipping size
	windowResized(oWindow);

	oRoot->addFrameListener(this);
}

#pragma endregion

#pragma region Get/Set

CEGUI::OgreRenderer* UIManager::getRenderer() const
{
	return guiRenderer;
}

CEGUI::GUIContext* UIManager::getContext() const
{
	return guiContext;
}

CEGUI::WindowManager* UIManager::getWindowMngr() const
{
	return guiWinMng;
}

#pragma endregion