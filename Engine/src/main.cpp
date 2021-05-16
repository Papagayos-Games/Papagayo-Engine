#include <iostream>
#include "PapagayoEngine.h"

int main(){
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	try {
		PapagayoEngine::getInstance()->run();
		PapagayoEngine::getInstance()->destroy();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	catch (const std::string& e) {
		std::cout << e << "\n";
	}
	catch (...) {
		std::cout << "EXCEPCION NO CONTROLADA\n";
	}

	return 0;
}