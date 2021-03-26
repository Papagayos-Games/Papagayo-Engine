#include <iostream>
#include "WindowGenerator.h"

using namespace Ogre;

#if (defined _DEBUG) || !(defined _WIN32)
int main() {

#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try {
		WindowGenerator* wGenerator = new WindowGenerator();
		system("PAUSE");
		std::cout << "KEKW\n";
		delete wGenerator;
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}