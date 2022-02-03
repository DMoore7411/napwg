/*******************************************************************************
*                                                                              *
* NAPWG - Not Another PassWord Generator                                       *
* subboxter.h - napwg component                                                *
*                                                                              *
* Copyright (C) 2021-2022 David Moore                                          *
*                                                                              *
* This program is free software: you can redistribute it and/or modify it      *
* under the terms of the GNU General Public License as published by the Free   *
* Software Foundation, either version 3 of the License, or (at your option)    *
* any later version.                                                           *
*                                                                              *
* This program is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for     *
* more details.                                                                *
*                                                                              *
* You should have received a copy of the GNU General Public License along with *
* this program. If not, see <https://www.gnu.org/licenses/>.                   *
*                                                                              *
* Any feedback is very welcome.                                                *
* https://github.com/DMoore7411/napwg                                          *
* email: davidmoore7411 @ gmail.com (remove spaces)                            *
*                                                                              *
*******************************************************************************/

#include <string.h>
#include <inttypes.h>
#include <openrk.h>

typedef struct 
{        
  int lower;
  int upper;
  int number;
  int symbol;
  int punctuation;
  int bracket;
  
  int len;
    
} sbbxtr_attr;

void sbbxtr_init(sbbxtr_attr* attr);

void sbbxtr_use_lower(sbbxtr_attr* attr);
void sbbxtr_use_upper(sbbxtr_attr* attr);
void sbbxtr_use_number(sbbxtr_attr* attr);
void sbbxtr_use_symbol(sbbxtr_attr* attr);
void sbbxtr_use_punctuation(sbbxtr_attr* attr);
void sbbxtr_use_bracket(sbbxtr_attr* attr);

void sbbxtr_set_length(sbbxtr_attr* attr, int length);

double sbbxtr_get_entropy(sbbxtr_attr* attr);

int sbbxtr_pass(sbbxtr_attr* attr, rk_mt64_t *st, char *pw);






