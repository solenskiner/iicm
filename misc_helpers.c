/***************************************************************************
 *   Copyright (C) 2010 by Henrik Asp					   *
 *   solenskiner@gmail.com						   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "misc_helpers.h"
#include <stdlib.h>
#include <assert.h>
#include "misc_bool.h"

/////////////////////////////////////////////////////////////////////////////////////////////

int max_i(int a, int b) {
  if (a > b) return a;
  else return b;
}

int min_i(int a, int b) {
  if (a > b) return b;
  else return a;
}

float max_f(float a, float b) {
  if (a > b) return a;
  else return b;
}

float min_f(float a, float b) {
  if (a > b) return b;
  else return a;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int even(int n) {
  if ( ( (int) ( ((float) n) / 2.0 + 0.5)) == ( (int) ( ((float) n) / 2.0))) return true;
  else return false;
}
int odd(int n) {
  if (even(n)) return false;
  else return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int compare_desc_f( const void* a, const void* b ) {
  if      ( *( (const float*) a) < *( (const float*) b) ) return  1;
  else if ( *( (const float*) a) > *( (const float*) b) ) return -1;
  else                                                    return  0;
}

int compare_desc_i( const void* a, const void* b ) {
  if      ( *( (const int*) a) < *( (const int*) b) ) return  1;
  else if ( *( (const int*) a) > *( (const int*) b) ) return -1;
  else                                                return  0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void array_init_i(int elements, int value, int* array) {
  for (int i = 0; i < elements; i++) {
    array[i] = value;
  }
}
void array_init_f(int elements, float value, float* array) {
  for (int i = 0; i < elements; i++) {
    array[i] = value;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void array_shift_left_f(int elements, float* array) {
  float temp = array[0];
  for (int i = 0; i < elements - 1; i++) {
    array[i] = array[i+1];
  }
  array[elements-1] = temp;
}

float array_sum_f(int elements, float* array) {
  float sum = 0;
  for (int i = 0; i < elements; i++) {
    sum += array[i];
  }
  return sum;
}

float array_sum_i(int elements, int* array) {
  int sum = 0;
  for (int i = 0; i < elements; i++) {
    sum += array[i];
  }
  return sum;
}

float array_mean_f(float * in, int x) {
  float out = 0;
  for (int i = 0; i < x; i++) {
    out += in[i] / x;
  }
  return out;
}

float* array2_mean_array_f(float ** in, int x, int y) {
  float* out = (float*) malloc(sizeof(float) * y);
  array_init_f(y, 0, out);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      out[j] += in[i][j] / x;
    }
  }
  return out;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//start is inclusive, end is exclusive
float* array_slice_f(int start, int end, float* array) {
  assert(start <= end);
  float* slice = (float*) malloc(sizeof(float) * end-start);
  for (int i = 0; i < end - start; i++) {
    slice[i] = array[i + start];
  }
  return slice;
}

// destructive!
float* array_append_f(int num1, float* array1, int num2, float* array2) {
  assert(num1 >= 0);
  assert(num2 >= 0);
  float* array = (float*) realloc(array1, sizeof(float) * (num1 + num2));
  for(int i = 0; i < num2; i++) {
    array[i+num1] = array2[i];
  }
  free(array2);
  return array;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void array2_free_f(float ** arr, int x) {
  for (int i = 0; i < x; i++) {
    free(arr[i]);
  }
  free(arr);
}
void array2_free_i(int ** arr, int x) {
  for (int i = 0; i < x; i++) {
    free(arr[i]);
  }
  free(arr);
}

////////////////////////////////////////////////////////////////////////////////

float* array_gather_f (int num, void* first, void* second, float fn(void*)) {
  float* arr = (float*) malloc(num * sizeof(float));
  unsigned int dist = (unsigned int)second - (unsigned int)first;
  for (int i = 0; i < num; i++) {
    arr[i] = fn((int)first + dist * i);
  }
  return arr;
}
