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

#include "calc_icm.h"
#include <stdlib.h>
#include <assert.h>
#include "misc_helpers.h"

// prize must be sorted, player[0]s ICM is returned
float calc_icm_single(int players, float* player, int prizes, float* prize) {
  assert(prizes > 0);
  if (players > 1) {
    float value = (player[0] / array_sum_f(players, player)) * prize[0];
    if (prizes > 1) {
      float* rec_prize = array_slice_f(1, prizes, prize);
      float* rec_player;
      for (int i = 1; i < players; i++) {
        rec_player = array_append_f(i,
                                    array_slice_f(0, i, player),
                                    (players-(i+1)),
                                    array_slice_f((i+1), players, player));
        value += (player[i] / array_sum_f(players, player)) *
                 calc_icm_single(players - 1, rec_player, prizes - 1, rec_prize);
        free(rec_player);
      }
    }
    return value;
  }
  else
    return prize[0];
  //
}

float* calc_icm(int players, float* player, int prizes, float* prize) {
  qsort((void*) prize, prizes, sizeof(float), &compare_desc_f);
  float* icm = (float*) malloc(sizeof(float)*players);
  for (int i = 0; i < players; i++) {
    icm[i] = calc_icm_single(players, player, prizes, prize);
    array_shift_left_f(players, player);
  }
  return icm;
}
