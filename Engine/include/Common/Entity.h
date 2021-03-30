
#include "Component.h"
#include <map>


using namespace std;

class Entity
{
private:

	map<ecs::CmpId, Component*> componentMap;

public:
	//constructor
	Entity() {};
	//destructor
	~Entity() {}; //TODO: decidir si los componentes se borran desde entity o desde los managers

	//añade un componente
	void addComponent(Component* comp);

	//devuelve el compenente asociado a esa id
	Component* getComponent(ecs::CmpId id);
		
   //comprueba si la entidad tiene el componente id
	bool hasComponent(ecs::CmpId id);




};




