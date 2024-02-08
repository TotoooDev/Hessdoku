#include <Frontend/FileDialog.h>
#include <Frontend/SDL/tinyfiledialogs/tinyfiledialogs.h>
#include <Log.h>
#include <stdlib.h>

#ifdef SUDOKU_WINDOWS
#include <processthreadsapi.h>
#endif

#ifdef SUDOKU_LINUX
#include <unistd.h>
#endif

const char* openFileDialog()
{
    return tinyfd_openFileDialog("Open file...", "./", 0, NULL, NULL, 0);
}

void openFileInDefaultApp(const char* filename)
{
    // Opening a file with the default program is OS dependant.

#ifdef SUDOKU_WINDOWS
    // STARTUPINFO info={sizeof(info)};
    // PROCESS_INFORMATION processInfo;
    // if (!CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &info, &processInfo))
    //     LOG("Failed to open actions file!");
    // return;
#endif

#ifdef SUDOKU_LINUX
    int child = fork();
    if (child == 0)
        if (execl("/bin/xdg-open", "xdg-open", filename, NULL) == -1)
            LOG("Failed to open actions file!");
    return;
#endif

    LOG("Unsupported OS!");
}
