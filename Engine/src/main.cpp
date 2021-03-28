#include <iostream>
#include <OgreRoot.h>
#include "Test.h"

using namespace Ogre;

#if (defined _DEBUG) || !(defined _WIN32)
int main() {

#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE zhInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif

	Root* root;

#ifdef _DEBUG
	root = new Root("OgreD/plugins.cfg");
#else
	root = new Root("Ogre/plugins.cfg");
#endif


	std::cout << "KEKW\n";

	Test* t = new Test();
	delete t;
	return 0;
}