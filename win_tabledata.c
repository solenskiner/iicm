#include "win_tabledata.h"
#include "misc_bool.h"

#include <windows.h>
#include <winuser.h>
#include <string.h>

char* get_window_title(HWND hwnd) {
  char* title = (char*) malloc(sizeof(char) * 100);
  SendMessage(hwnd, WM_GETTEXT, sizeof(title), (LPARAM)title);
  title = (char*) realloc(title, sizeof(char) * (strlen(title) + 1));
  return title;
}

char* get_id(char* title) {
  // TODO
  return title;
}

BOOL callback_function(HWND hwnd, LPARAM lparam) {
  callback_data* data = ((callback_data*) lparam);

  if ((!hwnd) || (!IsWindowVisible(hwnd))) goto callback_function_end;

  char* title;
  for (int i = 0; i < data->names_num; i++) {
    title = get_window_title(hwnd);
    if (strstr(title, data->table_names[i])) {
      data->table_IDs[data->IDs_num] = get_id(title);
      data->IDs_num++;
    }
    free(title);
  }

  callback_function_end:
  return false;
}

char** get_open_tournements(int* out_num) {
  callback_data *data = (callback_data*) malloc(sizeof(callback_data));
  data->table_names = sql_gettourneys(&(data->names_num));
  data->IDs_num = 0;
  data->table_IDs = (char**) malloc(sizeof(char*) * data->names_num);

  EnumWindows((WNDENUMPROC) &callback_function, (LPARAM) data);

  data->table_IDs = (char**) realloc(data->table_IDs, sizeof(char*) * data->IDs_num);

  free(data->table_names);
  char** IDs = data->table_IDs;
  *out_num = data->IDs_num;
  free(data);
  return IDs;
}
