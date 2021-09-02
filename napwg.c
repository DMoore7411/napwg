/*******************************************************************************
*                                                                              *
* NAPWG - Not Another PassWord Generator                                       *
* a program to generate strong passwords                                       *
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

#include <openrk.h>
#include "subboxter.h"

void print_about()
{
  printf("\nNAPWG - Not Another PassWord Generator - version 1.0\na program to generate strong passwords\n");
  printf("Copyright © 2021 David Moore\n");
  printf("This program comes with absolutely no warranty.\n");
  printf("See the GNU General Public License, version 3 or later for details.\n");
  printf("Please report bugs to <https://bugs.napwg.org>.\n");

  return;
}

void print_help()
{
  printf("\nNAPWG - Not Another PassWord Generator\na program to generate strong passwords\n");
  printf("Usage: napwg [ OPTIONS ] [ pw length ] [ pw num ]\n\nOption Summary\n");
  printf("-h -help         shows this information and quit\n");
  printf("-v -version      shows version and about information and quit\n\n");
  printf("-l -lower        include lowercase letters in the password\n");
  printf("-u -upper        include uppercase letters in the password\n");
  printf("-n -number       include numbers in the password\n");
  printf("-s -symbol       include symbols in the password\n");
  printf("-p -punctuation  include punctuation symbols in the password\n");
  printf("-b -bracket      include bracket symbols in the password\n");
  printf("-a -all          include all sets in the password\n\n");
  printf("-r -renew        renew generator state between passwords\n");
  printf("-i -info         shows entropy sources information\n");
  printf("-e -entropy      shows password entropy\n");
  printf("\n[ pw length ]    an integer number >= 8 (mandatory)\n");
  printf("\n[ pw num ]       if omitted napwg generates only one password\n");
  
  printf("\n");
    
  return;
}

int chk_arg_str(const char *arg, char args[], char argl[])
{
  size_t l;
  
  l = strlen(args);
  if((strncmp(arg, args, l)==0) && (strlen(arg)==l))
    return 1;

  l = strlen(argl);
  if((strncmp(arg, argl, l)==0) && (strlen(arg)==l))
    return 1;
  
  return 0;
}

int main (int argc, char *argv[], char *envp[])
{
  int i;
  int length;
  int num;
  int renew=0;
  int ifo=0;
  int ent=0;
  char *pw;
  
  sbbxtr_attr context;
  rk_mt64_t *rng;
  rk_error_t err;
  
  if(argc==1)
  {
    print_about();
    return 0;
  }
  
  sbbxtr_init(&context);
  
  for(i=1; i<argc; i++){
      
    if(chk_arg_str(argv[i], "-h", "-help"))
    {
      print_help();
      return 0;
    }
    
    if(chk_arg_str(argv[i], "-v", "-version"))
    {
      print_about();
      return 0;
    }
    
    if(chk_arg_str(argv[i], "-l", "-lower"))
      sbbxtr_use_lower(&context);
    
    if(chk_arg_str(argv[i], "-u", "-upper"))
      sbbxtr_use_upper(&context);
    
    if(chk_arg_str(argv[i], "-n", "-number"))
      sbbxtr_use_number(&context);
    
    if(chk_arg_str(argv[i], "-s", "-symbol"))
      sbbxtr_use_symbol(&context);
    
    if(chk_arg_str(argv[i], "-p", "-punctuation"))
      sbbxtr_use_punctuation(&context);
    
    if(chk_arg_str(argv[i], "-b", "-bracket"))
      sbbxtr_use_bracket(&context);
    
    if(chk_arg_str(argv[i], "-a", "-all"))
    {
      sbbxtr_use_lower(&context);
      sbbxtr_use_upper(&context);
      sbbxtr_use_number(&context);
      sbbxtr_use_symbol(&context);
      sbbxtr_use_punctuation(&context);
      sbbxtr_use_bracket(&context);
    }
    
    if(chk_arg_str(argv[i], "-r", "-renew"))
      renew=1;
    
    if(chk_arg_str(argv[i], "-i", "-info"))
      ifo=1;
      
    if(chk_arg_str(argv[i], "-e", "-entropy"))
      ent=1;  
  }
  
  if(argc==2)
  {
    length = atoi(argv[argc - 1]);
    if(length==0)
      return 0;
    num=1;        
  }
  else
  {
    length = atoi(argv[argc - 2]);
    if(length==0){
      length = atoi(argv[argc - 1]);
      if(length==0)
        return 0;
      num=1;
    }
    else
    {
      num = atoi(argv[argc - 1]);
      if(num==0)
        return 0;
    }
  }
  
  if(length<8)
    length=8;
  
  sbbxtr_set_length(&context, length);
  
  if(ifo)
  {
    uint64_t src = rkGetRandomizationSources();
    if(src & RK_RDZS_MTIME)
      printf("MICROTIME ");
    if(src & RK_RDZS_NTIME)
      printf("NANOTIME ");
    if(src & RK_RDZS_CPUCYCLE)
      printf("CPUCYCLES ");  
    if(src & RK_RDZS_RDRAND)
      printf("RDRAND ");
    if(src & RK_RDZS_RDSEED)
      printf("RDSEED ");    
  }
  
  if(ent)
    printf("- %i Bits", (int)sbbxtr_get_entropy(&context));
  
  if(ifo|ent)
    printf("\n"); 
  
  rkerrorInit(&err);
  rng = rkmt64New(&err);
  if(rng==NULL)
    return 0;
  
  /* strong fill the state of mt64  */
#if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
  rkRandomizeArray(RK_RDZS_MTIME | RK_RDZS_NTIME | RK_RDZS_CPUCYCLE | RK_RDZS_RDRAND | RK_RDZS_RDSEED,
#else
  rkRandomizeArray(RK_RDZS_MTIME | RK_RDZS_NTIME, 
#endif 
                   rng->k, 
                   312, 
                   RK_GFLAG_NOTALLZERO, 
                   &err);
  
  pw=malloc(length);
    
  for(i=0; i<num; i++)
  {
    if(sbbxtr_pass(&context, rng, pw)==-1)
      return 0;
    printf("%s\n", pw);
    if(renew==1 && i<num)
 #if defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
      rkRandomizeArray(RK_RDZS_MTIME | RK_RDZS_NTIME | RK_RDZS_CPUCYCLE | RK_RDZS_RDRAND | RK_RDZS_RDSEED,
#else
      rkRandomizeArray(RK_RDZS_MTIME | RK_RDZS_NTIME, 
#endif 
                       rng->k, 
                       312, 
                       RK_GFLAG_NOTALLZERO, 
                       &err);
  }
  
  free(pw);
  rkmt64Delete(rng);
    
  return 0;
}


