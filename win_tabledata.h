#ifndef WIN_TABLEDATA_H
#define WIN_TABLEDATA_H

#include "win_tabledata.h"
#include "misc_bool.h"

#include <windows.h>
#include <winuser.h>
#include <string.h>

typedef struct {
  char** table_names;
  int names_num;
  char** table_IDs;
  int IDs_num;
} callback_data;

char* get_window_title(HWND hwnd);

BOOL callback_function(HWND hwnd, LPARAM lparam);

char** get_open_tournements(int* out_num);

#endif // WIN_TABLEDATA_H
