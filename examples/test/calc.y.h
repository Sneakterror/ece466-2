/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CALC_Y_H_INCLUDED
# define YY_YY_CALC_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    HYPHEN = 258,                  /* HYPHEN  */
    ONE = 259,                     /* ONE  */
    TWO = 260,                     /* TWO  */
    THREE = 261,                   /* THREE  */
    FOUR = 262,                    /* FOUR  */
    FIVE = 263,                    /* FIVE  */
    SIX = 264,                     /* SIX  */
    SEVEN = 265,                   /* SEVEN  */
    EIGHT = 266,                   /* EIGHT  */
    NINE = 267,                    /* NINE  */
    ZERO = 268,                    /* ZERO  */
    TWENTY = 269,                  /* TWENTY  */
    THIRTY = 270,                  /* THIRTY  */
    FORTY = 271,                   /* FORTY  */
    FIFTY = 272,                   /* FIFTY  */
    SIXTY = 273,                   /* SIXTY  */
    SEVENTY = 274,                 /* SEVENTY  */
    EIGHTY = 275,                  /* EIGHTY  */
    NINETY = 276,                  /* NINETY  */
    HUNDRED = 277,                 /* HUNDRED  */
    TEN = 278,                     /* TEN  */
    ELEVEN = 279,                  /* ELEVEN  */
    TWELVE = 280,                  /* TWELVE  */
    THIRTEEN = 281,                /* THIRTEEN  */
    FOURTEEN = 282,                /* FOURTEEN  */
    FIFTEEN = 283,                 /* FIFTEEN  */
    SIXTEEN = 284,                 /* SIXTEEN  */
    SEVENTEEN = 285,               /* SEVENTEEN  */
    EIGHTEEN = 286,                /* EIGHTEEN  */
    NINETEEN = 287,                /* NINETEEN  */
    NEWLINE = 288                  /* NEWLINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define HYPHEN 258
#define ONE 259
#define TWO 260
#define THREE 261
#define FOUR 262
#define FIVE 263
#define SIX 264
#define SEVEN 265
#define EIGHT 266
#define NINE 267
#define ZERO 268
#define TWENTY 269
#define THIRTY 270
#define FORTY 271
#define FIFTY 272
#define SIXTY 273
#define SEVENTY 274
#define EIGHTY 275
#define NINETY 276
#define HUNDRED 277
#define TEN 278
#define ELEVEN 279
#define TWELVE 280
#define THIRTEEN 281
#define FOURTEEN 282
#define FIFTEEN 283
#define SIXTEEN 284
#define SEVENTEEN 285
#define EIGHTEEN 286
#define NINETEEN 287
#define NEWLINE 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "calc.y"

  int val;

#line 137 "calc.y.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALC_Y_H_INCLUDED  */
