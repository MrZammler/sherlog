#include <stdio.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>

#include "validate_params.h"
#include "parser.h"
#include "config.h"

void show_usage()
{
  printf("Usage: sherlog -f {FROMDT} -t {TODT} logfile\n");
}

int main(int argc, char *argv[])
{
  char *from_value = NULL, *to_value = NULL;
  char *logfile = NULL;
  FILE *fp;
  
  int c;

  struct tm f_tm, t_tm;
  
  opterr = 0;

  if (argc<4)
    {
      show_usage();
      return 1;
    }

  while ((c = getopt (argc, argv, "f:t:")) != -1)
    switch (c)
      {
      case 'f':
        from_value = optarg;
        break;
      case 't':
        to_value = optarg;
        break;
      case '?':
        if (optopt == 'f')
	  {
	    show_usage();
	    return 1;
	  }
	else if (optopt == 't')
	  {
	    show_usage();
	    return 1;
	  }
        else if (isprint (optopt))
          {
	    show_usage();
	    return 1;
	  }
        else
          {
	    show_usage();
	    return 1;
	  }
        return 1;
      default:
        show_usage();
      }

  //last opt should be the logfile
  logfile = argv[argc-1];

  printf("Running from [%s] to [%s] on [%s]\n", from_value, to_value, logfile);

  if (!is_valid_param('f', from_value, &f_tm))
    {
      printf("Invalid value for -f parameter.\n");
      return 1;
    }

  //t is not required
  if (to_value && !is_valid_param('t', to_value, &t_tm))
    {
      printf("Invalid value for -t parameter.\n");
      return 1;
    }
  /*
  printf("tm_hour:  %d\n",f_tm.tm_hour);
  printf("tm_min:  %d\n",f_tm.tm_min);
  printf("tm_sec:  %d\n",f_tm.tm_sec);
  printf("tm_mon:  %d\n",f_tm.tm_mon+1);
  printf("tm_mday:  %d\n",f_tm.tm_mday);
  printf("tm_year:  %d\n",f_tm.tm_year+1900);
  printf("tm_yday:  %d\n",f_tm.tm_yday);
  printf("tm_wday:  %d\n",f_tm.tm_wday);
  
  printf("tm_hour:  %d\n",t_tm.tm_hour);
  printf("tm_min:  %d\n",t_tm.tm_min);
  printf("tm_sec:  %d\n",t_tm.tm_sec);
  printf("tm_mon:  %d\n",t_tm.tm_mon+1);
  printf("tm_mday:  %d\n",t_tm.tm_mday);
  printf("tm_year:  %d\n",t_tm.tm_year+1900);
  printf("tm_yday:  %d\n",t_tm.tm_yday);
  printf("tm_wday:  %d\n",t_tm.tm_wday);
  */
  if (to_value)
    {
      //t must be > than f
      time_t ftm, ttm;
      ftm = mktime(&f_tm);
      ttm = mktime(&t_tm);
      
      if (difftime(ftm, ttm)>0)
	{
	  fprintf(stderr, "Value of -t parameter must be larger than -f.\n");
	  exit(1);
	}
    }

  fp = fopen(logfile, "r");

  if (!fp)
    {
      fprintf(stderr, "Error, could not open %s.\n", logfile);
      exit(1);
    }

  parse_log_f_t(&f_tm, &t_tm, fp);
   
  fclose(fp);
  exit(0);
}
