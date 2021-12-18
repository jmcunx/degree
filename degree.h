/*
 * Copyright (c) 2009 2010 2011 ... 2020 2021
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

#define DEGREE_H "$Id: degree.h,v 3.2 2020/06/14 14:09:04 jmccue Exp $"

#define PROG_NAME "degree"

#define FROM_NONE 0
#define FROM_CENT 1
#define FROM_KELV 2
#define FROM_FAHR 3
#define FROM_RANK 4

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

/*** types and globals ***/
#define MSG_HELP_11 "Convert temperature to different types"
#define MSG_HELP_12 "Note, to convert negative temperatures, put the minus sign after the number."
#define MSG_HELP_13 "      Example: For -40 degrees specify '40-' instead, see:"
#define SHOW_DEGREE_01 "Conversion from %11.2f   -- %s:\n"
#define SHOW_DEGREE_02 "Conversion from %11.2fK  -- %s:\n"
#define SHOW_DEGREE_03 "Conversion from %11.2fRa -- %s:\n"
#define SHOW_DEGREE_04 "         equals %11.2f   -- %s\n"
#define SHOW_DEGREE_05 "         equals %11.2fK  -- %s\n"
#define SHOW_DEGREE_06 "         equals %11.2fRa -- %s\n"

#endif /* DEGREE_H */
