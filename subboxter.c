/*******************************************************************************
*                                                                              *
* NAPWG - Not Another PassWord Generator                                       *
* subboxter.c - napwg component                                                *
*                                                                              *
* Copyright (C) 2021 David Moore                                               *
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

#include <math.h>
#include "subboxter.h"

void sbbxtr_init(sbbxtr_attr* attr)
{
  attr->lower=0;
  attr->upper=0;
  attr->number=0;
  attr->symbol=0;
  attr->punctuation=0;
  attr->bracket=0;
  
  return;
}

void sbbxtr_use_lower(sbbxtr_attr* attr)
{
  attr->lower=1;
  return;
}

void sbbxtr_use_upper(sbbxtr_attr* attr)
{
  attr->upper=1;
  return;
}

void sbbxtr_use_number(sbbxtr_attr* attr){
  attr->number=1;
}

void sbbxtr_use_symbol(sbbxtr_attr* attr)
{
  attr->symbol=1;
  return;
}

void sbbxtr_use_punctuation(sbbxtr_attr* attr)
{
  attr->punctuation=1;
  return;
}

void sbbxtr_use_bracket(sbbxtr_attr* attr)
{
  attr->bracket=1;
  return;
}

void sbbxtr_set_length(sbbxtr_attr* attr, int length)
{
  attr->len=length;
  return;
}

void sbbxtr_chk(sbbxtr_attr* attr)
{
  int i=0;
  
  i += attr->lower;
  i += attr->upper;
  i += attr->number;
  i += attr->symbol;
  i += attr->punctuation;
  i += attr->bracket;

  if(i==0)sbbxtr_use_lower(attr);

  return;   
}

double sbbxtr_get_entropy(sbbxtr_attr* attr)
{
  double r=0.0;
  double s=0.0;
  
  sbbxtr_chk(attr);
  
  if(attr->lower==1)
    s += 26.0;
   
  if(attr->upper==1)
    s += 26.0;
  
  if(attr->number==1)
    s += 10.0;
    
  if(attr->symbol==1)
    s += 6.0;
    
  if(attr->punctuation==1)
    s += 16.0;
    
  if(attr->bracket==1)
    s += 6.0;
    
  r = log(pow(s,(double)attr->len));
  
  return r;  
}

int tdr_mk(sbbxtr_attr* attr, char tdr[])
{
  int i;
  int cnt=0;
  
  for(i=0; i<128; i++)
    tdr[i] = 0;
  
  if(attr->lower==1)
    for(i=0; i<26; i++)
    {
      tdr[cnt] = 97 + i;
      cnt++;
    }
    
  if(attr->upper==1)
    for(i=0; i<26; i++)
    {
      tdr[cnt] = 65 + i;
      cnt++;
    }

  if(attr->number==1)
    for(i=0; i<10; i++)
    {
      tdr[cnt] = 48 + i;
      cnt++;
    }
  
  if(attr->symbol==1)
  {
    char tmp[] = {36,43,61,94,124,126};
    for(i=0; i<6; i++)
    {
      tdr[cnt] = tmp[i];
      cnt++;
    }
  }
  
  if(attr->punctuation==1)
  {
    char tmp[] = {33,34,35,37,38,42,44,45,46,47,58,59,63,64,92,95};
    for(i=0; i<16; i++)
    {
      tdr[cnt] = tmp[i];
      cnt++;
    }
  }
  
  if(attr->bracket==1)
  {
    char tmp[] = {40,41,60,62,91,93,123,125};
    for(i=0; i<8; i++)
    {
      tdr[cnt] = tmp[i];
      cnt++;
    }
  }

  return cnt;
}

int sbbxtr_pass(sbbxtr_attr* attr, rk_mt64_t *st, char *pw)
{
  int i;
  int cnt=0;
  char tdr[128];
  uint h;
  
  sbbxtr_chk(attr);
  
  for(i=0; i<attr->len; i++)
  {
    cnt = tdr_mk(attr, tdr);
    rkShuffleU8(st, &rkmt64Get, (uint8_t *)tdr, cnt, cnt);
    do 
      h = rkmt64Get(st) % 127;
        while(h>=cnt);
    pw[i] = tdr[h];
  }
    
  return 0;
}
