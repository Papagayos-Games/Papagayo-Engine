#pragma once
#include "Manager.h"
#include <Ogre.h>
#include <SDL_events.h>

namespace CEGUI {
	class GUIContext;
	class Window;
	class WindowManager;
	class OgreRenderer;
	class System;
	class Scheme;
} // namespace CEGUI

using vector2 = std::pair<float, float>;

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
	//Referencia al scheme actual
	CEGUI::Scheme* sch = nullptr;

	UIManager();
	virtual ~UIManager();

	static void setWidgetDestRect(CEGUI::Window* widget, vector2 position,
		vector2 size);
public:
#pragma region Generales
	//Devuelve el singleton de UIManager
	static UIManager* getInstance();
	static bool setUpInstance();
	//Elimina el UIManager y todos sus sistemas internos
	static void clean();
	static void destroy();

	virtual void start();
	virtual void update(float deltaTime);

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
	/// Se le aplica un tama�o 2D y un nombre que lo represente. Termina 
	/// devolviendo un elemento CEGUI de tipo Window*
	/// </summary>
	CEGUI::Window* createButton(const std::string& text, const vector2& position, const vector2& size,
		const std::string& name, const std::string& type);

	/// <summary>
	/// Crea un deslizador en una posicion en 2D con un tama�o 2D y 
	/// un nombre que lo represente. Termina devolviendo un elemento CEGUI
	/// de tipo Window*
	/// </summary>
	CEGUI::Window* createSlider(const vector2& position, const vector2& size,
		const std::string& name, const std::string& type);
	/// <summary>
	/// Crea un etiqueta que contiene un texto y se coloca en el canvas en
	/// una posicion y tama�o en 2D y con un nombre que lo represente
	/// </summary>
	CEGUI::Window* createLabel(const std::string& text, const vector2& position, const vector2& size,
		const std::string& name, const std::string& type);
	/// <summary>
	/// Crea una imagen a partir de una ruta especifica que le diga d�nde 
	/// se encuentra la fuente. Hace falta una posicion y un tama�o en 2D y tambien
	/// un nombre que lo represente
	/// </summary>
	CEGUI::Window* createImage(const vector2& position, const vector2& size,
		const std::string& name, const std::string& type);
#pragma endregion

#pragma region INPUT
	
	//Captura el input dentro de la UI
	void captureInput(const SDL_Event& event);

	void createFrameListener();

#pragma endregion

#pragma region Get/Set

	CEGUI::OgreRenderer* getRenderer() const;
	CEGUI::GUIContext* getContext() const;
	CEGUI::WindowManager* getWindowMngr() const;
#pragma endregion

};