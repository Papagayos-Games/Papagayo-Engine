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
	class System;
} // namespace CEGUI

class UIManager : public Ogre::FrameListener, public Manager
{
private:
	static UIManager* instance_;

	//Nombre de la configuracion del GUI
	std::string schemeName;


	//Ventana de ogre
	Ogre::RenderWindow* oWindow = nullptr;
	//Root de ogre
	Ogre::Root* oRoot = nullptr;

	//CEGUI context
	CEGUI::GUIContext* guiContext = nullptr;
	//Ventana de cegui
	CEGUI::Window* winRoot = nullptr;
	//Manager de la ventana de cegui
	CEGUI::WindowManager* guiWinMng = nullptr;
	//CEGUI + Ogre Renderer
	CEGUI::OgreRenderer* guiRenderer = nullptr;

	UIManager();
	~UIManager();

	static void setWidgetDestRect(CEGUI::Window* widget, glm::vec2 position,
		glm::vec2 size);
public:

#pragma region Generales
	//Devuelve el singleton de UIManager
	static UIManager* getInstance();
	//Elimina el UIManager y todos sus sistemas internos
	static void clean();

	virtual void start();
	virtual void update();

	void windowResized(Ogre::RenderWindow* rw);

	//Permite cargar la configuracion propia de la interfaz
	void loadScheme(const std::string& schemeName,
		const std::string& schemeFile);

	void loadFont(const std::string& filename);

	void loadLayout(const std::string& layaoutName);

	//Aplica una nueva fuente
	void setFont(const std::string& fontFile);

	enum class UICmpId : int {
		Button = 0,
		Slider,
		Label,
		Image,
		Pointer,
		LastUICmpId
	};
#pragma endregion

#pragma region Mouse
	
	//Aplica una imagen al cursor a partir de una ruta donde 
	//se encuentre la fuente
	void setMouseImage(const std::string& imageFile);

	/// <summary>
	/// Habilita/Deshabilita el cursor
	/// </summary>
	/// <param name="b">
	/// == true -> cursor visble /
	/// b == false -> cursor invisible
	/// </param>
	void setMouseVisibility(bool b);
#pragma endregion

#pragma region CreateWidget
	/// <summary>
	/// Crea un boton que muestra un texto (text) en una posicion en 2D.
	/// Se le aplica un tamaño 2D y un nombre que lo represente. Termina 
	/// devolviendo un elemento CEGUI de tipo Window*
	/// </summary>
	CEGUI::Window* createButton(const std::string& text, glm::vec2 position,
		glm::vec2 size, const std::string& name);

	/// <summary>
	/// Crea un deslizador en una posicion en 2D con un tamaño 2D y 
	/// un nombre que lo represente. Termina devolviendo un elemento CEGUI
	/// de tipo Window*
	/// </summary>
	CEGUI::Window* createSlider(glm::vec2 position, glm::vec2 size,
		const std::string& name);
	/// <summary>
	/// Crea un etiqueta que contiene un texto y se coloca en el canvas en
	/// una posicion y tamaño en 2D y con un nombre que lo represente
	/// </summary>
	CEGUI::Window* createLabel(const std::string& text, glm::vec2 position,
		glm::vec2 size, const std::string& name = "");
	/// <summary>
	/// Crea una imagen a partir de una ruta especifica que le diga dónde 
	/// se encuentra la fuente. Hace falta una posicion y un tamaño en 2D y tambien
	/// un nombre que lo represente
	/// </summary>
	CEGUI::Window* createImage(const std::string& image, glm::vec2 position,
		glm::vec2 size, const std::string& name = "");
#pragma endregion

#pragma region INPUT
	
	//Captura el input dentro de la UI
	void captureInput(const SDL_Event& event);

	void createFrameListener();

#pragma endregion

#pragma region Get/Set

	CEGUI::OgreRenderer* getRenderer() const;
	CEGUI::GUIContext* getContext() const;

#pragma endregion

};