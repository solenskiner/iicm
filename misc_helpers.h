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

#ifndef MISC_HELPERS_H
#define MISC_HELPERS_H


int max_i(int a, int b);
int min_i(int a, int b);
float max_f(float a, float b);
float min_f(float a, float b);

int even(int n);
int odd(int n);

int compare_desc_f( const void* a, const void* b );
int compare_desc_i( const void* a, const void* b );

void array_init_i(int elements, int value, int* array);
void array_init_f(int elements, float value, float* array);

void array_shift_left_f(int elements, float* array);

float array_sum_f(int elements, float* array);
float array_sum_i(int elements, int* array);
float array_mean_f(float * in, int x);
float* array2_mean_array_f(float ** in, int x, int y);

//start is inclusive, end is exclusive
float* array_slice_f(int start, int end, float* array);
// destructive!
float* array_append_f(int num1, float* array1, int num2, float* array2);

void array2_free_i(int ** arr, int x);
void array2_free_f(float ** arr, int x);

float* array_gather_f (int num, void* first, void* second, float fn(void*));

#endif // MISC_HELPERS_H
