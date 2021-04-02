#include <iostream>
#include "PapagayoEngine.h"

/*#if (defined _DEBUG) || !(defined _WIN32)
int main() {

#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
*/

int main(){
	try {
		PapagayoEngine::getInstance()->run();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}