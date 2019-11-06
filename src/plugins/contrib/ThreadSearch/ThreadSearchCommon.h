#ifndef THREAD_SEARCH_COMMON_H
#define THREAD_SEARCH_COMMON_H

#include <wx/string.h>

/// @return A string with the path to the icon images, it takes into account the size of the images.
wxString GetImagePrefix(bool toolbar, wxWindow *window = nullptr);

#endif // THREAD_SEARCH_COMMON_H
