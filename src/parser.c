#include <stdio.h>
#define __USE_XOPEN
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

void parse_log_f_t (struct tm *f, struct tm *t, FILE *fp)
{
  char wstr[1000], file_date[100]; //we'll see.
  time_t tt, ftm, ttm;
  struct tm *tmp=NULL, file_tm;
  unsigned int dt_length;

  //check if t is null
  ftm = mktime(f);
  if (t) ttm = mktime(t);
  
  //check how many bytes long DT_CONFIG is.
  //it's the same as from_value (if it's standard), but anyway...
  tt = time(NULL);
  tmp = localtime(&tt);

  strftime (wstr, sizeof(wstr), DT_FORMAT, tmp);
  //check for errors...
  printf("[%s]\n", wstr);
  dt_length = strlen(wstr);
  tmp=NULL;

  //malloc file_date with size dt_length please
  
  do
    {
      if (fgets (wstr, sizeof(wstr), fp)==NULL) { break;}

      //dirty
      strncpy(file_date, wstr+DT_START, dt_length);
      

      if (strptime (file_date, DT_FORMAT, &file_tm))
	{
	  
	  tt = mktime(&file_tm);
	  if (t)
	    {
	      if (difftime(ftm, tt) <= 0 && difftime(ttm, tt) >= 0)
		printf("%s", wstr);
	    }
	  else
	      if (difftime(ftm, tt) <= 0)
		printf("%s", wstr);
	      
	}
      
    }while(1);
  
  

}
