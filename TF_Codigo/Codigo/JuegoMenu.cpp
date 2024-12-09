#include "JuegoMenu.h"
using namespace Codigo;

int main() {
	srand(time(NULL));
	Application::EnableVisualStyles();
	Application::Run(gcnew JuegoMenu());

	return 0;
}
