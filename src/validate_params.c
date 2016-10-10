#include <stdio.h>
#define __USE_XOPEN
#include <time.h>

#include "config.h"

int is_valid_param (char p, char *value)
{
  char *b;
  struct tm result;
  
  if (p == 'f')
    {
      printf("Here\n");

      //basic format should be like DT_FORMAT
      b = strptime (value, DT_FORMAT, &result);

      printf("tm_hour:  %d\n",result.tm_hour);
          printf("tm_min:  %d\n",result.tm_min);
          printf("tm_sec:  %d\n",result.tm_sec);
          printf("tm_mon:  %d\n",result.tm_mon+1);
          printf("tm_mday:  %d\n",result.tm_mday);
          printf("tm_year:  %d\n",result.tm_year+1900);
          printf("tm_yday:  %d\n",result.tm_yday);
          printf("tm_wday:  %d\n",result.tm_wday);

      printf("[%s]\n", b);



    }



}
