#include "MainForm.h"
#include "utilities.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);	
	CLRHack::MainForm form;
	Application::Run(% form);
}