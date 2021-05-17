#include <iostream>
#include "PapagayoEngine.h"

int main(){
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	try {
		if (!PapagayoEngine::setupInstance("PAPAGAYO ENGINE"))
			throw std::exception("Couldn't Initialize Papagayo Engine\n");
		PapagayoEngine::getInstance()->init();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
		return -1;
	}
	catch (const std::string& e) {
		std::cout << e << "\n";
		return -1;
	}
	catch (...) {
		std::cout << "EXCEPCION NO CONTROLADA\n";
		return -1;
	}
	try {
		PapagayoEngine::getInstance()->run();
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
	try {
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