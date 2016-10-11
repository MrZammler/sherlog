#include <stdio.h>
#define __USE_XOPEN
#include <time.h>

#include "config.h"

int is_valid_param (char p, char *value, struct tm *res)
{
  if (p == 'f' || p == 't')
    {
      //basic format should be like DT_FORMAT
      if (!strptime (value, DT_FORMAT, res))
	{
	  return 0;
	}
    }
  
  return 1;
}
