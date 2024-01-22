#include <Frontend/FileDialog.h>
#include <Frontend/SDL/tinyfiledialogs/tinyfiledialogs.h>
#include <stdlib.h>

const char* openFileDialog()
{
    return tinyfd_openFileDialog("Open file...", "./", 0, NULL, NULL, 0);
}
