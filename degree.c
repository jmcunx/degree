/*
 * Copyright (c) 2009 2010 2011 ... 2021 2022
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* convert degrees  of type fahrenheit, centigrade, Kelvin and Rankine */

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

#ifndef _AIX
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "degree.h"

#define ARG_SIZE 80

/*
 * show_temp() -- save the temperature
 */
void show_temp(struct s_work *w)

{

  switch (w->from_type)
    {
      case FROM_FAHR:
	if (! w->quiet)
	  fprintf(stdout, SHOW_DEGREE_01, w->f, LIT_FAHR);
	if (w->quiet)
	  fprintf(stdout, "%.2f", w->c);
	else
	  {
	    fprintf(stdout, SHOW_DEGREE_04, w->c, LIT_CENT);
	    fprintf(stdout, SHOW_DEGREE_06, w->r, LIT_RANK);
	    fprintf(stdout, SHOW_DEGREE_05, w->k, LIT_KELV);
	  }
	break;
      case FROM_CENT:
	if (! w->quiet)
	  fprintf(stdout, SHOW_DEGREE_01, w->c, LIT_CENT);
	if (w->quiet)
	  fprintf(stdout, "%.2f", w->f);
	else
	  {
	    fprintf(stdout, SHOW_DEGREE_04, w->f, LIT_FAHR);
	    fprintf(stdout, SHOW_DEGREE_05, w->k, LIT_KELV);
	    fprintf(stdout, SHOW_DEGREE_06, w->r, LIT_RANK);
	  }
	break;
      case FROM_KELV:
	if (! w->quiet)
	  fprintf(stdout, SHOW_DEGREE_02, w->k, LIT_KELV);
	if (w->quiet)
	  fprintf(stdout, "%.2f", w->f);
	else
	  {
	    fprintf(stdout, SHOW_DEGREE_04, w->f, LIT_FAHR);
	    fprintf(stdout, SHOW_DEGREE_04, w->c, LIT_CENT);
	    fprintf(stdout, SHOW_DEGREE_06, w->r, LIT_RANK);
	  }
	break;
      case FROM_RANK:
	if (! w->quiet)
	  fprintf(stdout, SHOW_DEGREE_03, w->r, LIT_RANK);
	if (w->quiet)
	  fprintf(stdout, "%.2f", w->f);
	else
	  {
	    fprintf(stdout, SHOW_DEGREE_04, w->f, LIT_FAHR);
	    fprintf(stdout, SHOW_DEGREE_04, w->c, LIT_CENT);
	    fprintf(stdout, SHOW_DEGREE_05, w->k, LIT_KELV);
	  }
	break;
    }
  
} /* show_temp() */

/*
 * show_brief_help()
 */
int show_brief_help(FILE *fp, char *pname)

{

  fprintf(fp, USG_MSG_USAGE_6, pname);
  fprintf(fp, "\t%s\n", MSG_HELP_11);
  fprintf(fp, USG_MSG_OPTIONS);

  fprintf(fp, USG_MSG_ARG_CENT,       SWITCH_CHAR, ARG_CENT);
  fprintf(fp, USG_MSG_ARG_FAHR,       SWITCH_CHAR, ARG_FAHR);
  fprintf(fp, USG_MSG_ARG_KELV,       SWITCH_CHAR, ARG_KELV);
  fprintf(fp, USG_MSG_ARG_RANK,       SWITCH_CHAR, ARG_RANK);
  fprintf(fp, USG_MSG_ARG_HELP,       SWITCH_CHAR, ARG_HELP);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT, SWITCH_CHAR, ARG_PRT_FORMAT);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_A_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_B_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_C_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_D_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_E_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_F_DEG);
  fprintf(fp, USG_MSG_ARG_PRT_FORMAT_Z_DEG);
  fprintf(fp, USG_MSG_ARG_QUIET_4,    SWITCH_CHAR, ARG_QUIET);
  fprintf(fp, USG_MSG_ARG_VERSION,    SWITCH_CHAR, ARG_VERSION);

  fprintf(fp, "\n%s\n", MSG_HELP_12);
  fprintf(fp, "%s\n",   MSG_HELP_13);
  fprintf(fp, "               %s %c%c 40-\n\n", 
          pname, SWITCH_CHAR, ARG_CENT);

  return(EXIT_FAILURE);

}  /* show_brief_help() */

/*
 * show_rev()
 */
int show_rev(FILE *fp, char *pname)

{

  fprintf(fp,"%s %s:\n", pname, LIT_REV);

#ifdef J_LIB2_H
  fprintf(fp,"\t%s %s\n", LIT_INFO_02, j2_get_build());
#endif

#ifdef OSTYPE
  fprintf(fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE  */
#ifdef PRETTY_NAME
  fprintf(fp,"\t%s\n",PRETTY_NAME);
#endif  /* PRETTY_NAME  */
  fprintf(fp, LIT_INFO_01, __DATE__, __TIME__);

  return(EXIT_FAILURE);

}  /* show_rev() */

/*
 * process_arg() -- process arguments
 */
void process_arg(int argc, char **argv, struct s_work *w)

{
  char ckarg[ARG_SIZE];
  int opt;
  int ok;
  int display_help = (int) FALSE;
  int display_rev  = (int) FALSE;

  w->quiet     = (int) FALSE;
  w->from_type = FROM_NONE;
  w->f = (double) 0;
  w->c = (double) 0;
  w->k = (double) 0;
  w->r = (double) 0;
  w->fmt       = ' ';
  w->prog_name = j2_get_prgname(argv[0], PROG_NAME);

  snprintf(ckarg, ARG_SIZE, "%c%c%c%c%c%c%c%c:", 
	   ARG_QUIET, ARG_HELP, ARG_VERSION, ARG_FAHR, ARG_CENT, ARG_KELV, ARG_RANK, ARG_PRT_FORMAT);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_QUIET:
	    w->quiet = (int) TRUE;
	    break;
	  case ARG_FAHR:
	    w->from_type = FROM_FAHR;
	    break;
	  case ARG_CENT:
	    w->from_type = FROM_CENT;
	    break;
	  case ARG_RANK:
	    w->from_type = FROM_RANK;
	    break;
	  case ARG_PRT_FORMAT:
	    if (strlen(optarg) == 1)
	      w->fmt = (*optarg);
	    break;
	  case ARG_KELV:
	    w->from_type = FROM_KELV;
	    break;
	  case ARG_HELP:
	    display_help = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    display_rev = (int) TRUE;
	    break;
	  default:
	    fprintf(stderr, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	    exit(EXIT_FAILURE);
	    break;
	}
    }

  /*** show help/rev and exit ? ***/
  ok = EXIT_SUCCESS;
  if (display_help)
    ok = show_brief_help(stdout, w->prog_name);
  if (display_rev)
    ok = show_rev(stdout, w->prog_name);
  if (ok != EXIT_SUCCESS)
    exit(ok);

  if ( w->from_type == FROM_NONE)
    w->from_type = FROM_CENT;

} /* process_arg() */

/*
 * save_temp() -- convert argument to a temp
 */
double save_temp(char *arg, char *prog_name)
{
  char *arg_cp = (char *) NULL;
  double temp = (double) 0;

  arg_cp = strdup(arg);

  /* strip out C frim sysctl(8) */
  if (arg_cp[(strlen(arg) - 1)] == 'C')
    arg_cp[(strlen(arg) - 1)] = ' ';

  if ( j2_fix_numr(arg_cp, THOUSAND_SEP, DECIMAL_POINT) == (int) TRUE)
    temp = atof(arg_cp);
  else
    fprintf(stderr, MSG_ERR_E070, arg_cp);

  free(arg_cp);
  return(temp);

} /* save_temp() */

/*
 * get_temp() -- save the temperature
 */
int get_temp(char *raw_temp, struct s_work *w)

{
  double t = (double) 0;

  w->f  = (double) 0;
  w->c  = (double) 0;
  w->r  = (double) 0;
  w->k  = (double) 0;
  t     = save_temp(raw_temp, w->prog_name);

  switch (w->from_type)
    {
      case FROM_FAHR:
	w->f  = t;
	if (w->f < (double) -459.67)
	  {
	    fprintf(stderr, MSG_ERR_E004LD, w->f, SWITCH_CHAR, ARG_FAHR);
	    return((int) FALSE);
	  }
	break;
      case FROM_CENT:
	w->c  = t;
	if (w->c < (double) -273.15)
	  {
	    fprintf(stderr, MSG_ERR_E004LD, w->c, SWITCH_CHAR, ARG_CENT);
	    return((int) FALSE);
	  }
	break;
      case FROM_RANK:
	w->r  = t;
	if (w->r < (double) 0)
	  {
	    fprintf(stderr, MSG_ERR_E004LD, w->r, SWITCH_CHAR, ARG_RANK);
	    return((int) FALSE);
	  }
	break;
      case FROM_KELV:
	w->k  = t;
	if (w->k < (double) 0)
	  {
	    fprintf(stderr, MSG_ERR_E004LD, w->k, SWITCH_CHAR, ARG_KELV);
	    return((int) FALSE);
	  }
	break;
    }
  return((int) TRUE);
  
} /* get_temp() */

/*
 * calc_temp() -- save the temperature
 */
void calc_temp(struct s_work *w)

{

  switch (w->from_type)
    {
      case FROM_FAHR:
	w->c = (w->f - (double) 32) * ((double) 5 / (double) 9);
	w->k = w->c + 273.15;
	w->r = w->f + 459.67;
	break;
      case FROM_CENT:
	w->f = (w->c * ((double) 9 / (double) 5)) + 32;
	w->k = w->c + 273.15;
	w->r = w->f + 459.67;
	break;
      case FROM_KELV:
	w->c = w->k - 273.15;
	w->f = (w->c * ((double) 9 / (double) 5)) + 32;
	w->r = w->f + 459.67;
	break;
      case FROM_RANK:
	w->f = w->r - 459.67;
	w->c = (w->f - 32) * ((double) 5 / (double) 9);
	w->k = w->c + 273.15;
	w->r = w->f + 459.67;
	break;
    }
  
} /* calc_temp() */

/*
 * show_brief() -- save the temperature
 */
void show_brief(struct s_work *w)

{
  double degree = (double) 0;
  char degchar = 'F';
  
  switch (w->from_type)
    {
      case FROM_FAHR:
	degchar = 'C';
	degree  = w->c;
	break;
      default:
	degree  = w->f;
	break;
    }
  switch (w->fmt)
    {
      case 'a':
	fprintf(stdout, "%.2f", degree);
	break;
      case 'b':
	fprintf(stdout, "%.0f", degree);
	break;
      case 'c':
	fprintf(stdout, "%.2f%c", degree, degchar);
	break;
      case 'd':
	fprintf(stdout, "%.0f%c", degree, degchar);
	break;
      case 'e':
	fprintf(stdout, "%.2f%c", degree, degchar);
	break;
      case 'f':
	fprintf(stdout, "%.0f%c", degree, degchar);
	break;
      default:
	show_temp(w);
	break;
    }

} /* show_brief() */

/*
 * process_file() -- reads temps from stdin
 */
void process_file(struct s_work *w)

{
  char *buf    = (char *) NULL;
  int rec      = 0;
  size_t bsize = (size_t) 0;

  /*** process file ***/
  while (getline(&buf, &bsize, stdin) > (ssize_t) -1)
    {
      rec++;
      if (rec > 1)
	fprintf(stdout, "\n");
      j2_justleft(buf);
      j2_rtw(buf);
      if ( get_temp(buf, w) == (int) TRUE)
	{
	  calc_temp(w);
	  show_brief(w);
	}
    }

  if (rec > 1)
    fprintf(stdout, "\n");

} /* process_file() */

/*
 * main()
 */
int main(int argc, char **argv)

{
  struct s_work w;
  int i;

#ifdef OpenBSD
  if(pledge("stdio",NULL) == -1)
    err(1,"pledge\n");
#endif

  process_arg(argc, argv, &w);

  /*** process files ***/
  for (i = optind; i < argc; i++)
    {
      if ( get_temp(argv[i], &w) == (int) TRUE)
	{
	  calc_temp(&w);
	  show_brief(&w);
	}
    }

  /*** get from stdin ***/
  if (i == optind)
    process_file(&w);

  /*** done ***/
  exit(EXIT_SUCCESS);

}  /* main() */
