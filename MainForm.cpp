
#include "MainForm.h"

using namespace System;
using namespace AdvancedFileSeeker;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    MainForm^ mainForm = gcnew MainForm();
    Application::Run(mainForm);

    return 0;
}