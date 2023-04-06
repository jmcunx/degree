/*
 * Copyright (c) 2009 2010 2011 ... 2023 2024
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

#ifndef DEGREE_H

#define DEGREE_H "INCLIDED"

#define PROG_NAME "degree"

#define FROM_NONE 0
#define FROM_CENT 1
#define FROM_KELV 2
#define FROM_FAHR 3
#define FROM_RANK 4

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

/*** types ***/
struct s_work
  {
    char *prog_name;                /* real program name     */
    int from_type;
    int quiet;
    char fmt;                       /* format                */
    double f;
    double c;
    double k;
    double r;
  } ;

/*** messages ***/
#define MSG_HELP_11 "Convert temperature to different types"
#define MSG_HELP_12 "Note, to convert negative temperatures, put the minus sign after the number."
#define MSG_HELP_13 "      Example: For -40 degrees specify '40-' instead, see:"
#define SHOW_DEGREE_01 "Conversion from %11.2f   -- %s:\n"
#define SHOW_DEGREE_02 "Conversion from %11.2fK  -- %s:\n"
#define SHOW_DEGREE_03 "Conversion from %11.2fRa -- %s:\n"
#define SHOW_DEGREE_04 "         equals %11.2f   -- %s\n"
#define SHOW_DEGREE_05 "         equals %11.2fK  -- %s\n"
#define SHOW_DEGREE_06 "         equals %11.2fRa -- %s\n"

#ifdef NO_JLIB
#define ARG_CENT          'C'  /* degree is type Centigrade          */
#define ARG_FAHR          'F'  /* degree is type Fahrenheit          */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_KELV          'K'  /* degree is type Kelvin              */
#define ARG_PRT_FORMAT    'p'  /* Output Format                      */
#define ARG_QUIET         'q'  /* Quiet Mode                         */
#define ARG_RANK          'R'  /* degree is type Rankine             */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define LIT_CENT          "Centigrade"
#define LIT_FAHR          "Fahrenheit"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_KELV          "Kelvin"
#define LIT_RANK          "Rankine"
#define LIT_REV           "Revision"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E004LD    "ERROR E004: value %lf invalid value for %c%c\n"
#define MSG_ERR_E070      "ERROR E070: '%s' invalid, must be numeric\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_CENT                 "\t%c%c\t\t: Convert from degrees Centigrade\n"
#define USG_MSG_ARG_FAHR                 "\t%c%c\t\t: Convert from degrees Fahrenheit\n"
#define USG_MSG_ARG_HELP                 "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_KELV                 "\t%c%c\t\t: Convert from degrees Kelvin\n"
#define USG_MSG_ARG_PRT_FORMAT           "\t%c%c c\t\t: Optional Output Format, where 'c' is:\n"
#define USG_MSG_ARG_PRT_FORMAT_A_DEG     "\t\t\t    'a' = '32.00'\n"
#define USG_MSG_ARG_PRT_FORMAT_B_DEG     "\t\t\t    'b' = '32'\n"
#define USG_MSG_ARG_PRT_FORMAT_C_DEG     "\t\t\t    'c' = '32.00x'  (x = Degree Unit)\n"
#define USG_MSG_ARG_PRT_FORMAT_D_DEG     "\t\t\t    'd' = '32x'     (x = Degree Unit)\n"
#define USG_MSG_ARG_PRT_FORMAT_E_DEG     "\t\t\t    'e' = '32.00x'  (x = Degree Unit)\n"
#define USG_MSG_ARG_PRT_FORMAT_F_DEG     "\t\t\t    'f' = '32x'     (x = Degree Unit)\n"
#define USG_MSG_ARG_PRT_FORMAT_Z_DEG     "\t\t\t  Default show verbose Output\n"
#define USG_MSG_ARG_QUIET                "\t%c%c\t\t: quiet, do not print results.\n"
#define USG_MSG_ARG_QUIET_4              "\t%c%c\t\t: print summary\n"
#define USG_MSG_ARG_RANK                 "\t%c%c\t\t: Convert from degrees Rankine\n"
#define USG_MSG_ARG_VERSION              "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS                  "Options\n"
#define USG_MSG_USAGE_6                  "usage:\t%s [OPTIONS] temperature1 [temperature2...]\n"
#endif /* NO_JLIB */

#ifndef DECIMAL_POINT
#define DECIMAL_POINT    '.'
#endif
#ifndef THOUSAND_SEP
#define THOUSAND_SEP     ','
#endif

/*** prototypes ***/
#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
char *j2_get_prgname(char *argv_0, char *default_name);
int j2_bye_char(char *buffer, char c);
int j2_fix_numr(char *buffer, char thousand, char decimal_point);
long int j2_clr_str(char *s, char c, int size);
long int j2_justleft(char *s);
long int j2_rtw(char *buffer);
#endif /* NO_JLIB */

#endif /* DEGREE_H */
