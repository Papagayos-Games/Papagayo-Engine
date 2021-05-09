#pragma once
#include <Ogre.h>
#include <SDL_events.h>
#include "Manager.h"
#include <string.h>
#include <glm/glm.hpp>

namespace CEGUI {
	class GUIContext;
	class Window;
	class WindowManager;
	class OgreRenderer;
	enum MouseButton;
} // namespace CEGUI

class UIManager : public Ogre::FrameListener, public Manager
{
private:
	static UIManager* instance_;

	std::string schemeName_;

	//Ventana de ogre
	Ogre::RenderWindow* oWindow = nullptr;
	//Root de ogre
	Ogre::Root* oRoot = nullptr;
	//CEGUI context
	CEGUI::GUIContext* guiContext = nullptr;
	//Ventana de cegui
	CEGUI::Window* guiWindow = nullptr;
	//Manager de la ventana de cegui
	CEGUI::WindowManager* guiWindowManager = nullptr;
	//CEGUI + Ogre Renderer
	CEGUI::OgreRenderer* guiRenderer = nullptr;

	UIManager();
	~UIManager();

public:
	static UIManager* getInstance();
	static void clean();

	//void init();

	virtual void start();
	virtual void update();

	//Captura el input dentro de la UI
	void captureInput(const SDL_Event& event);
	//Permite cargar la configuracion propia de la interfaz
	void loadScheme(const std::string& schemeName,
		const std::string& schemeFile);
	//Anade una nueva fuente
	void setFont(const std::string& fontFile);

	CEGUI::Window* createButton(const std::string& text, glm::vec2 position,
		glm::vec2 size, const std::string& name);

	CEGUI::Window* createSlider(glm::vec2 position, glm::vec2 size,
		const std::string& name);

	CEGUI::Window* createLabel(const std::string& text, glm::vec2 position,
		glm::vec2 size, const std::string& name = "");

	CEGUI::Window* createImage(const std::string& image, glm::vec2 position,
		glm::vec2 size, const std::string& name = "");

	static void setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
		glm::vec2 size);

	void setMouseImage(const std::string& imageFile);

	void setMouseVisibility(bool b);

	void createFrameListener();

	void windowResized(Ogre::RenderWindow* rw);

	// Getters and setters
	CEGUI::OgreRenderer* getRenderer() const;
	CEGUI::GUIContext* getContext() const;
};

