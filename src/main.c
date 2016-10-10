#include <stdio.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <ctype.h>

#include "validate_params.h"
#include "config.h"

void show_usage()
{
  printf("Usage: sherlog -f {FROMDT} -t {TODT} logfile\n");
}

int main(int argc, char *argv[])
{
  char *from_value = NULL, *to_value = NULL;
  char *logfile = NULL;
  int index;
  int c;

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

  if (!is_valid_param('f', from_value))
    {
      printf("Invalid value for -f parameter.\n");;
      return 1;
    }


  
  return 0;
}
