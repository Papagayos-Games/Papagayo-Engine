#include "Component.h"
#include <string>

class LuaComponent : public Component {
private:
	std::string methodId;


public:
	LuaComponent();
	virtual ~LuaComponent();

	virtual void init()override;
	virtual void load(const nlohmann::json& params) override;
	virtual void update() override;

};
