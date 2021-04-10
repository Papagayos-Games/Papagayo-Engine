#include <map>

class Component;

class Entity
{
private:
	std::map<ecs::CmpId, Component*> componentMap;

public:
	//constructor
	Entity();
	//destructor
	~Entity(); //TODO: decidir si los componentes se borran desde entity o desde los managers

	// añade un componente
	void addComponent(Component* comp);

	// devuelve el compenente asociado a esa id
	Component* getComponent(ecs::CmpId id);
		
    // comprueba si la entidad tiene el componente id
	bool hasComponent(ecs::CmpId id);

	// solo deberia llamar a este metodo un Manager
	bool removeComponent(ecs::CmpId id);
};