/*
Based on https://stackoverflow.com/a/63666076
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        std::cout << "Requires refresh rare parameter\n";
        return -1;
    }

    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
    {
        cout << "DisplayFrequency before setting = " << dm.dmDisplayFrequency << endl;
        dm.dmDisplayFrequency = atoi(argv[1]); //set the DisplayFrequency
        LONG ret = ChangeDisplaySettingsEx(NULL, &dm, NULL, 0, NULL);
        std::cout << "ChangeDisplaySettingsEx returned " << ret << '\n';
        if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
        {
            cout << "DisplayFrequency after setting = " << dm.dmDisplayFrequency << endl;
        }
        switch (ret)
        {
        case DISP_CHANGE_SUCCESSFUL:
            std::cout << "display successfully changed\n";
            break;
        case DISP_CHANGE_BADDUALVIEW:
            std::cout << "The settings change was unsuccessful because the system is DualView capable\n";
            break;
        case DISP_CHANGE_BADFLAGS:
            std::cout << "An invalid set of flags was passed in.\n";
            break;
        case DISP_CHANGE_BADMODE:
            std::cout << "The graphics mode is not supported.\n";
            break;
        case DISP_CHANGE_BADPARAM:
            std::cout << "An invalid parameter was passed in. This can include an invalid flag or combination of flags.\n";
            break;
        case DISP_CHANGE_FAILED:
            std::cout << "The display driver failed the specified graphics mode.\n";
            break;
        case DISP_CHANGE_NOTUPDATED:
            std::cout << "Unable to write settings to the registry.\n";
            break;
        case DISP_CHANGE_RESTART:
            std::cout << "The computer must be restarted for the graphics mode to work.\n";
            break;
        }
    }
    system("pause");
}