/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse xhpparse
#define yylex   xhplex
#define yyerror xhperror
#define yylval  xhplval
#define yychar  xhpchar
#define yydebug xhpdebug
#define yynerrs xhpnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_REQUIRE_ONCE = 258,
     T_REQUIRE = 259,
     T_EVAL = 260,
     T_INCLUDE_ONCE = 261,
     T_INCLUDE = 262,
     T_LOGICAL_OR = 263,
     T_LOGICAL_XOR = 264,
     T_LOGICAL_AND = 265,
     T_PRINT = 266,
     T_SR_EQUAL = 267,
     T_SL_EQUAL = 268,
     T_XOR_EQUAL = 269,
     T_OR_EQUAL = 270,
     T_AND_EQUAL = 271,
     T_MOD_EQUAL = 272,
     T_CONCAT_EQUAL = 273,
     T_DIV_EQUAL = 274,
     T_MUL_EQUAL = 275,
     T_MINUS_EQUAL = 276,
     T_PLUS_EQUAL = 277,
     T_BOOLEAN_OR = 278,
     T_BOOLEAN_AND = 279,
     T_IS_NOT_IDENTICAL = 280,
     T_IS_IDENTICAL = 281,
     T_IS_NOT_EQUAL = 282,
     T_IS_EQUAL = 283,
     T_IS_GREATER_OR_EQUAL = 284,
     T_IS_SMALLER_OR_EQUAL = 285,
     T_SR = 286,
     T_SL = 287,
     T_INSTANCEOF = 288,
     T_UNSET_CAST = 289,
     T_BOOL_CAST = 290,
     T_OBJECT_CAST = 291,
     T_ARRAY_CAST = 292,
     T_BINARY_CAST = 293,
     T_UNICODE_CAST = 294,
     T_STRING_CAST = 295,
     T_DOUBLE_CAST = 296,
     T_INT_CAST = 297,
     T_DEC = 298,
     T_INC = 299,
     T_CLONE = 300,
     T_NEW = 301,
     T_EXIT = 302,
     T_IF = 303,
     T_ELSEIF = 304,
     T_ELSE = 305,
     T_ENDIF = 306,
     T_LNUMBER = 307,
     T_DNUMBER = 308,
     T_STRING = 309,
     T_STRING_VARNAME = 310,
     T_VARIABLE = 311,
     T_NUM_STRING = 312,
     T_INLINE_HTML = 313,
     T_CHARACTER = 314,
     T_BAD_CHARACTER = 315,
     T_ENCAPSED_AND_WHITESPACE = 316,
     T_CONSTANT_ENCAPSED_STRING = 317,
     T_BACKTICKS_EXPR = 318,
     T_ECHO = 319,
     T_DO = 320,
     T_WHILE = 321,
     T_ENDWHILE = 322,
     T_FOR = 323,
     T_ENDFOR = 324,
     T_FOREACH = 325,
     T_ENDFOREACH = 326,
     T_DECLARE = 327,
     T_ENDDECLARE = 328,
     T_AS = 329,
     T_SWITCH = 330,
     T_ENDSWITCH = 331,
     T_CASE = 332,
     T_DEFAULT = 333,
     T_BREAK = 334,
     T_CONTINUE = 335,
     T_GOTO = 336,
     T_FUNCTION = 337,
     T_CONST = 338,
     T_RETURN = 339,
     T_TRY = 340,
     T_CATCH = 341,
     T_THROW = 342,
     T_USE = 343,
     T_GLOBAL = 344,
     T_PUBLIC = 345,
     T_PROTECTED = 346,
     T_PRIVATE = 347,
     T_FINAL = 348,
     T_ABSTRACT = 349,
     T_STATIC = 350,
     T_VAR = 351,
     T_UNSET = 352,
     T_ISSET = 353,
     T_EMPTY = 354,
     T_HALT_COMPILER = 355,
     T_CLASS = 356,
     T_INTERFACE = 357,
     T_EXTENDS = 358,
     T_IMPLEMENTS = 359,
     T_OBJECT_OPERATOR = 360,
     T_DOUBLE_ARROW = 361,
     T_LIST = 362,
     T_ARRAY = 363,
     T_CLASS_C = 364,
     T_METHOD_C = 365,
     T_FUNC_C = 366,
     T_LINE = 367,
     T_FILE = 368,
     T_COMMENT = 369,
     T_DOC_COMMENT = 370,
     T_OPEN_TAG = 371,
     T_OPEN_TAG_WITH_ECHO = 372,
     T_OPEN_TAG_FAKE = 373,
     T_CLOSE_TAG = 374,
     T_WHITESPACE = 375,
     T_START_HEREDOC = 376,
     T_END_HEREDOC = 377,
     T_HEREDOC = 378,
     T_DOLLAR_OPEN_CURLY_BRACES = 379,
     T_CURLY_OPEN = 380,
     T_PAAMAYIM_NEKUDOTAYIM = 381,
     T_BINARY_DOUBLE = 382,
     T_BINARY_HEREDOC = 383,
     T_NAMESPACE = 384,
     T_NS_C = 385,
     T_DIR = 386,
     T_NS_SEPARATOR = 387,
     T_XHP_WHITESPACE = 388,
     T_XHP_TEXT = 389,
     T_XHP_LT_DIV = 390,
     T_XHP_LT_DIV_GT = 391,
     T_XHP_ATTRIBUTE = 392,
     T_XHP_CATEGORY = 393,
     T_XHP_CHILDREN = 394,
     T_XHP_ANY = 395,
     T_XHP_EMPTY = 396,
     T_XHP_PCDATA = 397,
     T_XHP_COLON = 398,
     T_XHP_HYPHEN = 399,
     T_XHP_BOOLEAN = 400,
     T_XHP_NUMBER = 401,
     T_XHP_ARRAY = 402,
     T_XHP_STRING = 403,
     T_XHP_ENUM = 404,
     T_XHP_REQUIRED = 405
   };
#endif
/* Tokens.  */
#define T_REQUIRE_ONCE 258
#define T_REQUIRE 259
#define T_EVAL 260
#define T_INCLUDE_ONCE 261
#define T_INCLUDE 262
#define T_LOGICAL_OR 263
#define T_LOGICAL_XOR 264
#define T_LOGICAL_AND 265
#define T_PRINT 266
#define T_SR_EQUAL 267
#define T_SL_EQUAL 268
#define T_XOR_EQUAL 269
#define T_OR_EQUAL 270
#define T_AND_EQUAL 271
#define T_MOD_EQUAL 272
#define T_CONCAT_EQUAL 273
#define T_DIV_EQUAL 274
#define T_MUL_EQUAL 275
#define T_MINUS_EQUAL 276
#define T_PLUS_EQUAL 277
#define T_BOOLEAN_OR 278
#define T_BOOLEAN_AND 279
#define T_IS_NOT_IDENTICAL 280
#define T_IS_IDENTICAL 281
#define T_IS_NOT_EQUAL 282
#define T_IS_EQUAL 283
#define T_IS_GREATER_OR_EQUAL 284
#define T_IS_SMALLER_OR_EQUAL 285
#define T_SR 286
#define T_SL 287
#define T_INSTANCEOF 288
#define T_UNSET_CAST 289
#define T_BOOL_CAST 290
#define T_OBJECT_CAST 291
#define T_ARRAY_CAST 292
#define T_BINARY_CAST 293
#define T_UNICODE_CAST 294
#define T_STRING_CAST 295
#define T_DOUBLE_CAST 296
#define T_INT_CAST 297
#define T_DEC 298
#define T_INC 299
#define T_CLONE 300
#define T_NEW 301
#define T_EXIT 302
#define T_IF 303
#define T_ELSEIF 304
#define T_ELSE 305
#define T_ENDIF 306
#define T_LNUMBER 307
#define T_DNUMBER 308
#define T_STRING 309
#define T_STRING_VARNAME 310
#define T_VARIABLE 311
#define T_NUM_STRING 312
#define T_INLINE_HTML 313
#define T_CHARACTER 314
#define T_BAD_CHARACTER 315
#define T_ENCAPSED_AND_WHITESPACE 316
#define T_CONSTANT_ENCAPSED_STRING 317
#define T_BACKTICKS_EXPR 318
#define T_ECHO 319
#define T_DO 320
#define T_WHILE 321
#define T_ENDWHILE 322
#define T_FOR 323
#define T_ENDFOR 324
#define T_FOREACH 325
#define T_ENDFOREACH 326
#define T_DECLARE 327
#define T_ENDDECLARE 328
#define T_AS 329
#define T_SWITCH 330
#define T_ENDSWITCH 331
#define T_CASE 332
#define T_DEFAULT 333
#define T_BREAK 334
#define T_CONTINUE 335
#define T_GOTO 336
#define T_FUNCTION 337
#define T_CONST 338
#define T_RETURN 339
#define T_TRY 340
#define T_CATCH 341
#define T_THROW 342
#define T_USE 343
#define T_GLOBAL 344
#define T_PUBLIC 345
#define T_PROTECTED 346
#define T_PRIVATE 347
#define T_FINAL 348
#define T_ABSTRACT 349
#define T_STATIC 350
#define T_VAR 351
#define T_UNSET 352
#define T_ISSET 353
#define T_EMPTY 354
#define T_HALT_COMPILER 355
#define T_CLASS 356
#define T_INTERFACE 357
#define T_EXTENDS 358
#define T_IMPLEMENTS 359
#define T_OBJECT_OPERATOR 360
#define T_DOUBLE_ARROW 361
#define T_LIST 362
#define T_ARRAY 363
#define T_CLASS_C 364
#define T_METHOD_C 365
#define T_FUNC_C 366
#define T_LINE 367
#define T_FILE 368
#define T_COMMENT 369
#define T_DOC_COMMENT 370
#define T_OPEN_TAG 371
#define T_OPEN_TAG_WITH_ECHO 372
#define T_OPEN_TAG_FAKE 373
#define T_CLOSE_TAG 374
#define T_WHITESPACE 375
#define T_START_HEREDOC 376
#define T_END_HEREDOC 377
#define T_HEREDOC 378
#define T_DOLLAR_OPEN_CURLY_BRACES 379
#define T_CURLY_OPEN 380
#define T_PAAMAYIM_NEKUDOTAYIM 381
#define T_BINARY_DOUBLE 382
#define T_BINARY_HEREDOC 383
#define T_NAMESPACE 384
#define T_NS_C 385
#define T_DIR 386
#define T_NS_SEPARATOR 387
#define T_XHP_WHITESPACE 388
#define T_XHP_TEXT 389
#define T_XHP_LT_DIV 390
#define T_XHP_LT_DIV_GT 391
#define T_XHP_ATTRIBUTE 392
#define T_XHP_CATEGORY 393
#define T_XHP_CHILDREN 394
#define T_XHP_ANY 395
#define T_XHP_EMPTY 396
#define T_XHP_PCDATA 397
#define T_XHP_COLON 398
#define T_XHP_HYPHEN 399
#define T_XHP_BOOLEAN 400
#define T_XHP_NUMBER 401
#define T_XHP_ARRAY 402
#define T_XHP_STRING 403
#define T_XHP_ENUM 404
#define T_XHP_REQUIRED 405




/* Copy the first part of user declarations.  */
#line 18 "parser.y"

#include "xhp.hpp"
// PHP's if/else rules use right reduction rather than left reduction which
// means while parsing nested if/else's the stack grows until it the last
// statement is read. This is annoying, particularly because of a quirk in
// bison.
// http://www.gnu.org/software/bison/manual/html_node/Memory-Management.html
// Apparently if you compile a bison parser with g++ it can no longer grow
// the stack. The work around is to just make your initial stack ridiculously
// large. Unfortunately that increases memory usage while parsing which is
// dumb. Anyway, putting a TODO here to fix PHP's if/else grammar.
#define YYINITDEPTH 500
#line 32 "parser.y"

#undef yyextra
#define yyextra static_cast<yy_extra_type*>(xhpget_extra(yyscanner))
#undef yylineno
#define yylineno yyextra->first_lineno
#define cr(s) code_rope(s, yylineno)
#define push_state(s) xhp_new_push_state(s, (struct yyguts_t*) yyscanner)
#define pop_state() xhp_new_pop_state((struct yyguts_t*) yyscanner)
#define set_state(s) xhp_set_state(s, (struct yyguts_t*) yyscanner)
using namespace std;

static void yyerror(void* yyscanner, void* _, const char* error) {
  if (yyextra->terminated) {
    return;
  }
  yyextra->terminated = true;
  yyextra->error = error;
}

static void replacestr(string &source, const string &find, const string &rep) {
  size_t j;
  while ((j = source.find(find)) != std::string::npos) {
    source.replace(j, find.length(), rep);
  }
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 455 "parser.yacc.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7749

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  178
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  156
/* YYNRULES -- Number of rules.  */
#define YYNRULES  480
/* YYNRULES -- Number of states.  */
#define YYNSTATES  953

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   405

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,   177,     2,   175,    47,    31,     2,
     170,   171,    45,    42,     8,    43,    44,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,   172,
      36,    13,    37,    25,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,   176,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   173,    29,   174,    50,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     9,    10,    11,    12,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    27,    28,
      32,    33,    34,    35,    38,    39,    40,    41,    49,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    15,    17,    19,
      21,    26,    30,    36,    41,    45,    48,    52,    54,    56,
      60,    63,    68,    74,    79,    82,    83,    85,    87,    89,
      94,    96,    99,   101,   103,   105,   109,   117,   128,   134,
     142,   152,   158,   161,   165,   168,   172,   175,   179,   183,
     187,   191,   195,   197,   200,   206,   215,   224,   230,   232,
     246,   250,   254,   256,   257,   259,   262,   271,   273,   277,
     279,   281,   283,   284,   286,   296,   304,   311,   313,   316,
     319,   320,   323,   325,   326,   329,   330,   333,   335,   339,
     340,   343,   345,   348,   350,   355,   357,   362,   364,   369,
     373,   379,   383,   388,   393,   399,   400,   406,   411,   413,
     415,   417,   422,   423,   430,   431,   439,   440,   443,   444,
     448,   450,   451,   454,   458,   464,   469,   474,   480,   488,
     495,   496,   498,   500,   502,   503,   505,   507,   510,   514,
     518,   523,   527,   529,   531,   534,   539,   543,   549,   551,
     555,   558,   559,   563,   566,   567,   577,   579,   583,   585,
     587,   588,   590,   592,   595,   597,   599,   601,   603,   605,
     607,   611,   617,   619,   623,   629,   634,   638,   640,   641,
     643,   647,   649,   656,   660,   665,   672,   676,   679,   683,
     687,   691,   695,   699,   703,   707,   711,   715,   719,   723,
     726,   729,   732,   735,   739,   743,   747,   751,   755,   759,
     763,   767,   771,   775,   779,   783,   787,   791,   795,   799,
     802,   805,   808,   811,   815,   819,   823,   827,   831,   835,
     839,   843,   847,   851,   857,   862,   864,   867,   870,   873,
     876,   879,   882,   885,   888,   891,   894,   897,   899,   904,
     906,   909,   919,   930,   932,   933,   938,   942,   947,   949,
     952,   957,   964,   970,   977,   984,   991,   998,  1003,  1005,
    1007,  1011,  1014,  1016,  1020,  1023,  1025,  1027,  1032,  1034,
    1037,  1038,  1041,  1042,  1045,  1049,  1050,  1054,  1056,  1058,
    1060,  1062,  1064,  1066,  1068,  1070,  1072,  1074,  1076,  1078,
    1080,  1084,  1087,  1090,  1093,  1098,  1100,  1104,  1106,  1108,
    1110,  1114,  1117,  1119,  1120,  1123,  1124,  1126,  1132,  1136,
    1140,  1142,  1144,  1146,  1148,  1150,  1152,  1158,  1160,  1163,
    1164,  1168,  1172,  1173,  1175,  1178,  1182,  1186,  1188,  1190,
    1192,  1194,  1197,  1199,  1204,  1209,  1211,  1213,  1218,  1219,
    1221,  1223,  1225,  1230,  1235,  1237,  1239,  1243,  1245,  1248,
    1252,  1254,  1256,  1261,  1262,  1263,  1266,  1272,  1276,  1280,
    1282,  1289,  1294,  1299,  1302,  1307,  1312,  1315,  1318,  1323,
    1326,  1329,  1331,  1335,  1339,  1343,  1345,  1347,  1351,  1356,
    1360,  1364,  1366,  1369,  1371,  1374,  1375,  1377,  1380,  1384,
    1386,  1387,  1388,  1394,  1395,  1398,  1402,  1403,  1408,  1409,
    1410,  1416,  1417,  1419,  1420,  1424,  1425,  1428,  1429,  1433,
    1434,  1438,  1440,  1444,  1448,  1450,  1454,  1458,  1460,  1461,
    1462,  1463,  1474,  1475,  1480,  1482,  1486,  1491,  1494,  1496,
    1498,  1500,  1502,  1504,  1506,  1507,  1508,  1515,  1517,  1521,
    1524,  1527,  1528,  1530,  1531,  1532,  1537,  1540,  1545,  1546,
    1551,  1553,  1555,  1557,  1561,  1566,  1571,  1576,  1578,  1580,
    1583,  1586,  1589,  1593,  1597,  1599,  1601,  1604,  1607,  1610,
    1613
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     179,     0,    -1,   180,    -1,   180,   182,    -1,    -1,    73,
      -1,   181,   151,    73,    -1,   188,    -1,   195,    -1,   196,
      -1,   119,   170,   171,   172,    -1,   148,   181,   172,    -1,
     148,   181,   173,   180,   174,    -1,   148,   173,   180,   174,
      -1,   107,   183,   172,    -1,   185,   172,    -1,   183,     8,
     184,    -1,   184,    -1,   181,    -1,   181,    93,    73,    -1,
     151,   181,    -1,   151,   181,    93,    73,    -1,   185,     8,
      73,    13,   255,    -1,   102,    73,    13,   255,    -1,   186,
     187,    -1,    -1,   188,    -1,   195,    -1,   196,    -1,   119,
     170,   171,   172,    -1,   189,    -1,    73,    26,    -1,   135,
      -1,   136,    -1,   137,    -1,   173,   186,   174,    -1,    67,
     170,   261,   171,   188,   216,   218,    -1,    67,   170,   261,
     171,    26,   186,   217,   219,    70,   172,    -1,    85,   170,
     261,   171,   215,    -1,    84,   188,    85,   170,   261,   171,
     172,    -1,    87,   170,   239,   172,   239,   172,   239,   171,
     208,    -1,    94,   170,   261,   171,   212,    -1,    98,   172,
      -1,    98,   261,   172,    -1,    99,   172,    -1,    99,   261,
     172,    -1,   103,   172,    -1,   103,   241,   172,    -1,   103,
     265,   172,    -1,   108,   225,   172,    -1,   114,   227,   172,
      -1,    83,   238,   172,    -1,    77,    -1,   261,   172,    -1,
     116,   170,   193,   171,   172,    -1,    89,   170,   265,    93,
     207,   206,   171,   209,    -1,    89,   170,   241,    93,   265,
     206,   171,   209,    -1,    91,   170,   211,   171,   210,    -1,
     172,    -1,   104,   173,   186,   174,   105,   170,   247,    75,
     171,   173,   186,   174,   190,    -1,   106,   261,   172,    -1,
     100,    73,   172,    -1,   191,    -1,    -1,   192,    -1,   191,
     192,    -1,   105,   170,   247,    75,   171,   173,   186,   174,
      -1,   194,    -1,   193,     8,   194,    -1,   265,    -1,   198,
      -1,   199,    -1,    -1,    31,    -1,   242,   197,    73,   170,
     220,   171,   173,   186,   174,    -1,   200,    73,   201,   204,
     173,   228,   174,    -1,   202,    73,   203,   173,   228,   174,
      -1,   120,    -1,   113,   120,    -1,   112,   120,    -1,    -1,
     122,   247,    -1,   121,    -1,    -1,   122,   205,    -1,    -1,
     123,   205,    -1,   247,    -1,   205,     8,   247,    -1,    -1,
     125,   207,    -1,   265,    -1,    31,   265,    -1,   188,    -1,
      26,   186,    88,   172,    -1,   188,    -1,    26,   186,    90,
     172,    -1,   188,    -1,    26,   186,    92,   172,    -1,    73,
      13,   255,    -1,   211,     8,    73,    13,   255,    -1,   173,
     213,   174,    -1,   173,   172,   213,   174,    -1,    26,   213,
      95,   172,    -1,    26,   172,   213,    95,   172,    -1,    -1,
     213,    96,   261,   214,   186,    -1,   213,    97,   214,   186,
      -1,    26,    -1,   172,    -1,   188,    -1,    26,   186,    86,
     172,    -1,    -1,   216,    68,   170,   261,   171,   188,    -1,
      -1,   217,    68,   170,   261,   171,    26,   186,    -1,    -1,
      69,   188,    -1,    -1,    69,    26,   186,    -1,   221,    -1,
      -1,   222,    75,    -1,   222,    31,    75,    -1,   222,    31,
      75,    13,   255,    -1,   222,    75,    13,   255,    -1,   221,
       8,   222,    75,    -1,   221,     8,   222,    31,    75,    -1,
     221,     8,   222,    31,    75,    13,   255,    -1,   221,     8,
     222,    75,    13,   255,    -1,    -1,   247,    -1,   127,    -1,
     224,    -1,    -1,   241,    -1,   265,    -1,    31,   263,    -1,
     224,     8,   241,    -1,   224,     8,   265,    -1,   224,     8,
      31,   263,    -1,   225,     8,   226,    -1,   226,    -1,    75,
      -1,   175,   262,    -1,   175,   173,   261,   174,    -1,   227,
       8,    75,    -1,   227,     8,    75,    13,   255,    -1,    75,
      -1,    75,    13,   255,    -1,   228,   229,    -1,    -1,   232,
     236,   172,    -1,   237,   172,    -1,    -1,   233,   242,   230,
     197,    73,   170,   220,   171,   231,    -1,   172,    -1,   173,
     186,   174,    -1,   234,    -1,   115,    -1,    -1,   234,    -1,
     235,    -1,   234,   235,    -1,   109,    -1,   110,    -1,   111,
      -1,   114,    -1,   113,    -1,   112,    -1,   236,     8,    75,
      -1,   236,     8,    75,    13,   255,    -1,    75,    -1,    75,
      13,   255,    -1,   237,     8,    73,    13,   255,    -1,   102,
      73,    13,   255,    -1,   238,     8,   261,    -1,   261,    -1,
      -1,   240,    -1,   240,     8,   261,    -1,   261,    -1,   126,
     170,   281,   171,    13,   261,    -1,   265,    13,   261,    -1,
     265,    13,    31,   265,    -1,   265,    13,    31,    65,   248,
     253,    -1,    65,   248,   253,    -1,    64,   261,    -1,   265,
      24,   261,    -1,   265,    23,   261,    -1,   265,    22,   261,
      -1,   265,    21,   261,    -1,   265,    20,   261,    -1,   265,
      19,   261,    -1,   265,    18,   261,    -1,   265,    17,   261,
      -1,   265,    16,   261,    -1,   265,    15,   261,    -1,   265,
      14,   261,    -1,   264,    62,    -1,    62,   264,    -1,   264,
      61,    -1,    61,   264,    -1,   261,    27,   261,    -1,   261,
      28,   261,    -1,   261,     9,   261,    -1,   261,    11,   261,
      -1,   261,    10,   261,    -1,   261,    29,   261,    -1,   261,
      31,   261,    -1,   261,    30,   261,    -1,   261,    44,   261,
      -1,   261,    42,   261,    -1,   261,    43,   261,    -1,   261,
      45,   261,    -1,   261,    46,   261,    -1,   261,    47,   261,
      -1,   261,    41,   261,    -1,   261,    40,   261,    -1,    42,
     261,    -1,    43,   261,    -1,    48,   261,    -1,    50,   261,
      -1,   261,    33,   261,    -1,   261,    32,   261,    -1,   261,
      35,   261,    -1,   261,    34,   261,    -1,   261,    36,   261,
      -1,   261,    39,   261,    -1,   261,    37,   261,    -1,   261,
      38,   261,    -1,   261,    49,   248,    -1,   170,   261,   171,
      -1,   261,    25,   261,    26,   261,    -1,   261,    25,    26,
     261,    -1,   285,    -1,    60,   261,    -1,    59,   261,    -1,
      58,   261,    -1,    57,   261,    -1,    56,   261,    -1,    55,
     261,    -1,    54,   261,    -1,    53,   261,    -1,    52,   261,
      -1,    66,   252,    -1,    51,   261,    -1,   257,    -1,   127,
     170,   283,   171,    -1,    82,    -1,    12,   261,    -1,   242,
     197,   170,   220,   171,   243,   173,   186,   174,    -1,   114,
     242,   197,   170,   220,   171,   243,   173,   186,   174,    -1,
     101,    -1,    -1,   107,   170,   244,   171,    -1,   244,     8,
      75,    -1,   244,     8,    31,    75,    -1,    75,    -1,    31,
      75,    -1,   181,   170,   223,   171,    -1,   148,   151,   181,
     170,   223,   171,    -1,   151,   181,   170,   223,   171,    -1,
     246,   145,    73,   170,   223,   171,    -1,   271,   145,    73,
     170,   223,   171,    -1,   271,   145,   269,   170,   223,   171,
      -1,   246,   145,   269,   170,   223,   171,    -1,   269,   170,
     223,   171,    -1,   114,    -1,   181,    -1,   148,   151,   181,
      -1,   151,   181,    -1,   181,    -1,   148,   151,   181,    -1,
     151,   181,    -1,   246,    -1,   249,    -1,   273,   124,   277,
     250,    -1,   273,    -1,   250,   251,    -1,    -1,   124,   277,
      -1,    -1,   170,   171,    -1,   170,   261,   171,    -1,    -1,
     170,   223,   171,    -1,    71,    -1,    72,    -1,    81,    -1,
     131,    -1,   132,    -1,   150,    -1,   128,    -1,   129,    -1,
     130,    -1,   149,    -1,   142,    -1,   254,    -1,   181,    -1,
     148,   151,   181,    -1,   151,   181,    -1,    42,   255,    -1,
      43,   255,    -1,   127,   170,   258,   171,    -1,   256,    -1,
     246,   145,    73,    -1,    74,    -1,   287,    -1,   181,    -1,
     148,   151,   181,    -1,   151,   181,    -1,   254,    -1,    -1,
     260,   259,    -1,    -1,     8,    -1,   260,     8,   255,   125,
     255,    -1,   260,     8,   255,    -1,   255,   125,   255,    -1,
     255,    -1,   262,    -1,   241,    -1,   265,    -1,   265,    -1,
     265,    -1,   272,   124,   277,   268,   266,    -1,   272,    -1,
     266,   267,    -1,    -1,   124,   277,   268,    -1,   170,   223,
     171,    -1,    -1,   274,    -1,   280,   274,    -1,   246,   145,
     269,    -1,   271,   145,   269,    -1,   274,    -1,   273,    -1,
     245,    -1,   274,    -1,   280,   274,    -1,   270,    -1,   274,
      63,   276,   176,    -1,   274,   173,   261,   174,    -1,   275,
      -1,    75,    -1,   175,   173,   261,   174,    -1,    -1,   261,
      -1,   278,    -1,   269,    -1,   278,    63,   276,   176,    -1,
     278,   173,   261,   174,    -1,   279,    -1,    73,    -1,   173,
     261,   174,    -1,   175,    -1,   280,   175,    -1,   281,     8,
     282,    -1,   282,    -1,   265,    -1,   126,   170,   281,   171,
      -1,    -1,    -1,   284,   259,    -1,   284,     8,   261,   125,
     261,    -1,   284,     8,   261,    -1,   261,   125,   261,    -1,
     261,    -1,   284,     8,   261,   125,    31,   263,    -1,   284,
       8,    31,   263,    -1,   261,   125,    31,   263,    -1,    31,
     263,    -1,   117,   170,   286,   171,    -1,   118,   170,   265,
     171,    -1,     7,   261,    -1,     6,   261,    -1,     5,   170,
     261,   171,    -1,     4,   261,    -1,     3,   261,    -1,   265,
      -1,   286,     8,   265,    -1,   246,   145,    73,    -1,   271,
     145,    73,    -1,   288,    -1,   289,    -1,   290,   294,   291,
      -1,   292,   298,    46,    37,    -1,   292,   298,    37,    -1,
     154,   307,    37,    -1,   155,    -1,    36,   305,    -1,   153,
      -1,   293,   153,    -1,    -1,   293,    -1,   294,   295,    -1,
     294,   295,   293,    -1,   288,    -1,    -1,    -1,   173,   296,
     261,   174,   297,    -1,    -1,   298,   299,    -1,   309,    13,
     300,    -1,    -1,   177,   301,   304,   177,    -1,    -1,    -1,
     173,   302,   261,   303,   174,    -1,    -1,   293,    -1,    -1,
     306,   313,   315,    -1,    -1,   308,   313,    -1,    -1,   310,
     314,   315,    -1,    -1,   312,   313,   315,    -1,    73,    -1,
     313,   162,    73,    -1,   313,   163,    73,    -1,    73,    -1,
     314,   162,    73,    -1,   314,   163,    73,    -1,   152,    -1,
      -1,    -1,    -1,   200,    26,   305,   201,   204,   173,   316,
     228,   317,   174,    -1,    -1,   156,   318,   319,   172,    -1,
     320,    -1,   319,     8,   320,    -1,   321,   309,   325,   326,
      -1,   162,   305,    -1,   167,    -1,   164,    -1,   165,    -1,
     166,    -1,   246,    -1,   115,    -1,    -1,    -1,   168,   173,
     322,   324,   323,   174,    -1,   254,    -1,   324,     8,   254,
      -1,    13,   254,    -1,    13,    73,    -1,    -1,   169,    -1,
      -1,    -1,   157,   327,   328,   172,    -1,    47,   305,    -1,
     328,     8,    47,   305,    -1,    -1,   158,   329,   330,   172,
      -1,   331,    -1,   159,    -1,   160,    -1,   170,   332,   171,
      -1,   170,   332,   171,    45,    -1,   170,   332,   171,    25,
      -1,   170,   332,   171,    42,    -1,   331,    -1,   333,    -1,
     333,    45,    -1,   333,    25,    -1,   333,    42,    -1,   332,
       8,   332,    -1,   332,    29,   332,    -1,   159,    -1,   161,
      -1,   162,   311,    -1,    47,   311,    -1,   162,   305,    -1,
     162,   305,    -1,   261,    63,   276,   176,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   204,   207,   213,   214,   220,   221,   222,
     223,   226,   229,   232,   235,   238,   244,   247,   251,   252,
     255,   258,   264,   267,   273,   276,   282,   283,   284,   285,
     291,   292,   295,   296,   297,   303,   306,   309,   312,   315,
     318,   321,   324,   327,   330,   333,   336,   339,   342,   345,
     348,   351,   354,   355,   358,   361,   364,   367,   370,   371,
     374,   377,   383,   384,   390,   391,   397,   403,   404,   410,
     414,   418,   422,   425,   429,   435,   438,   444,   445,   448,
     454,   457,   463,   467,   470,   476,   479,   485,   486,   492,
     495,   501,   502,   508,   509,   515,   516,   522,   523,   529,
     532,   538,   541,   544,   547,   553,   556,   559,   565,   566,
     570,   571,   577,   580,   586,   589,   595,   598,   604,   607,
     613,   614,   620,   623,   626,   629,   632,   635,   638,   641,
     647,   650,   653,   659,   660,   666,   667,   668,   671,   674,
     677,   683,   686,   690,   691,   694,   700,   703,   706,   707,
     713,   716,   722,   725,   728,   728,   738,   739,   745,   746,
     752,   755,   761,   762,   768,   769,   770,   771,   772,   773,
     777,   780,   783,   784,   790,   793,   799,   802,   806,   809,
     814,   817,   821,   824,   827,   830,   833,   836,   839,   842,
     845,   848,   851,   854,   857,   860,   863,   866,   869,   872,
     875,   878,   881,   884,   887,   890,   893,   896,   899,   902,
     905,   908,   911,   914,   917,   920,   923,   926,   929,   932,
     935,   938,   941,   944,   947,   950,   953,   956,   959,   962,
     965,   968,   971,   974,   977,   980,   981,   984,   987,   990,
     993,   996,   999,  1002,  1005,  1008,  1011,  1014,  1015,  1018,
    1019,  1022,  1025,  1031,  1034,  1036,  1042,  1045,  1048,  1049,
    1055,  1058,  1061,  1064,  1067,  1070,  1073,  1076,  1082,  1083,
    1084,  1087,  1093,  1094,  1097,  1103,  1104,  1108,  1111,  1115,
    1118,  1124,  1130,  1133,  1136,  1142,  1145,  1151,  1152,  1153,
    1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1165,  1166,
    1167,  1170,  1173,  1176,  1179,  1182,  1186,  1192,  1193,  1194,
    1195,  1198,  1201,  1205,  1208,  1212,  1215,  1219,  1222,  1225,
    1228,  1232,  1233,  1237,  1241,  1245,  1249,  1252,  1256,  1259,
    1265,  1271,  1274,  1280,  1281,  1287,  1290,  1296,  1300,  1301,
    1305,  1306,  1309,  1313,  1316,  1319,  1323,  1324,  1330,  1333,
    1337,  1338,  1342,  1345,  1348,  1352,  1353,  1359,  1360,  1366,
    1369,  1373,  1374,  1377,  1383,  1386,  1390,  1393,  1396,  1399,
    1400,  1403,  1406,  1409,  1415,  1418,  1421,  1424,  1427,  1430,
    1433,  1439,  1440,  1446,  1449,  1459,  1466,  1467,  1479,  1492,
    1501,  1519,  1531,  1538,  1539,  1545,  1548,  1552,  1556,  1563,
    1564,  1567,  1564,  1578,  1582,  1588,  1594,  1594,  1597,  1597,
    1597,  1603,  1606,  1614,  1614,  1621,  1621,  1628,  1628,  1635,
    1635,  1642,  1647,  1650,  1656,  1661,  1664,  1670,  1671,  1676,
    1681,  1676,  1704,  1704,  1713,  1714,  1718,  1723,  1731,  1734,
    1737,  1740,  1743,  1746,  1749,  1749,  1749,  1755,  1759,  1766,
    1770,  1774,  1780,  1783,  1790,  1790,  1802,  1805,  1812,  1812,
    1820,  1823,  1826,  1832,  1835,  1838,  1841,  1847,  1848,  1851,
    1854,  1857,  1860,  1863,  1869,  1872,  1875,  1878,  1885,  1894,
    1908
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_REQUIRE_ONCE", "T_REQUIRE", "T_EVAL",
  "T_INCLUDE_ONCE", "T_INCLUDE", "','", "T_LOGICAL_OR", "T_LOGICAL_XOR",
  "T_LOGICAL_AND", "T_PRINT", "'='", "T_SR_EQUAL", "T_SL_EQUAL",
  "T_XOR_EQUAL", "T_OR_EQUAL", "T_AND_EQUAL", "T_MOD_EQUAL",
  "T_CONCAT_EQUAL", "T_DIV_EQUAL", "T_MUL_EQUAL", "T_MINUS_EQUAL",
  "T_PLUS_EQUAL", "'?'", "':'", "T_BOOLEAN_OR", "T_BOOLEAN_AND", "'|'",
  "'^'", "'&'", "T_IS_NOT_IDENTICAL", "T_IS_IDENTICAL", "T_IS_NOT_EQUAL",
  "T_IS_EQUAL", "'<'", "'>'", "T_IS_GREATER_OR_EQUAL",
  "T_IS_SMALLER_OR_EQUAL", "T_SR", "T_SL", "'+'", "'-'", "'.'", "'*'",
  "'/'", "'%'", "'!'", "T_INSTANCEOF", "'~'", "'@'", "T_UNSET_CAST",
  "T_BOOL_CAST", "T_OBJECT_CAST", "T_ARRAY_CAST", "T_BINARY_CAST",
  "T_UNICODE_CAST", "T_STRING_CAST", "T_DOUBLE_CAST", "T_INT_CAST",
  "T_DEC", "T_INC", "'['", "T_CLONE", "T_NEW", "T_EXIT", "T_IF",
  "T_ELSEIF", "T_ELSE", "T_ENDIF", "T_LNUMBER", "T_DNUMBER", "T_STRING",
  "T_STRING_VARNAME", "T_VARIABLE", "T_NUM_STRING", "T_INLINE_HTML",
  "T_CHARACTER", "T_BAD_CHARACTER", "T_ENCAPSED_AND_WHITESPACE",
  "T_CONSTANT_ENCAPSED_STRING", "T_BACKTICKS_EXPR", "T_ECHO", "T_DO",
  "T_WHILE", "T_ENDWHILE", "T_FOR", "T_ENDFOR", "T_FOREACH",
  "T_ENDFOREACH", "T_DECLARE", "T_ENDDECLARE", "T_AS", "T_SWITCH",
  "T_ENDSWITCH", "T_CASE", "T_DEFAULT", "T_BREAK", "T_CONTINUE", "T_GOTO",
  "T_FUNCTION", "T_CONST", "T_RETURN", "T_TRY", "T_CATCH", "T_THROW",
  "T_USE", "T_GLOBAL", "T_PUBLIC", "T_PROTECTED", "T_PRIVATE", "T_FINAL",
  "T_ABSTRACT", "T_STATIC", "T_VAR", "T_UNSET", "T_ISSET", "T_EMPTY",
  "T_HALT_COMPILER", "T_CLASS", "T_INTERFACE", "T_EXTENDS", "T_IMPLEMENTS",
  "T_OBJECT_OPERATOR", "T_DOUBLE_ARROW", "T_LIST", "T_ARRAY", "T_CLASS_C",
  "T_METHOD_C", "T_FUNC_C", "T_LINE", "T_FILE", "T_COMMENT",
  "T_DOC_COMMENT", "T_OPEN_TAG", "T_OPEN_TAG_WITH_ECHO", "T_OPEN_TAG_FAKE",
  "T_CLOSE_TAG", "T_WHITESPACE", "T_START_HEREDOC", "T_END_HEREDOC",
  "T_HEREDOC", "T_DOLLAR_OPEN_CURLY_BRACES", "T_CURLY_OPEN",
  "T_PAAMAYIM_NEKUDOTAYIM", "T_BINARY_DOUBLE", "T_BINARY_HEREDOC",
  "T_NAMESPACE", "T_NS_C", "T_DIR", "T_NS_SEPARATOR", "T_XHP_WHITESPACE",
  "T_XHP_TEXT", "T_XHP_LT_DIV", "T_XHP_LT_DIV_GT", "T_XHP_ATTRIBUTE",
  "T_XHP_CATEGORY", "T_XHP_CHILDREN", "T_XHP_ANY", "T_XHP_EMPTY",
  "T_XHP_PCDATA", "T_XHP_COLON", "T_XHP_HYPHEN", "T_XHP_BOOLEAN",
  "T_XHP_NUMBER", "T_XHP_ARRAY", "T_XHP_STRING", "T_XHP_ENUM",
  "T_XHP_REQUIRED", "'('", "')'", "';'", "'{'", "'}'", "'$'", "']'",
  "'\"'", "$accept", "start", "top_statement_list", "namespace_name",
  "top_statement", "use_declarations", "use_declaration",
  "constant_declaration", "inner_statement_list", "inner_statement",
  "statement", "unticked_statement", "additional_catches",
  "non_empty_additional_catches", "additional_catch", "unset_variables",
  "unset_variable", "function_declaration_statement",
  "class_declaration_statement", "is_reference",
  "unticked_function_declaration_statement",
  "unticked_class_declaration_statement", "class_entry_type",
  "extends_from", "interface_entry", "interface_extends_list",
  "implements_list", "interface_list", "foreach_optional_arg",
  "foreach_variable", "for_statement", "foreach_statement",
  "declare_statement", "declare_list", "switch_case_list", "case_list",
  "case_separator", "while_statement", "elseif_list", "new_elseif_list",
  "else_single", "new_else_single", "parameter_list",
  "non_empty_parameter_list", "optional_class_type",
  "function_call_parameter_list", "non_empty_function_call_parameter_list",
  "global_var_list", "global_var", "static_var_list",
  "class_statement_list", "class_statement", "@1", "method_body",
  "variable_modifiers", "method_modifiers", "non_empty_member_modifiers",
  "member_modifier", "class_variable_declaration",
  "class_constant_declaration", "echo_expr_list", "for_expr",
  "non_empty_for_expr", "expr_without_variable", "function",
  "lexical_vars", "lexical_var_list", "function_call", "class_name",
  "fully_qualified_class_name", "class_name_reference",
  "dynamic_class_name_reference", "dynamic_class_name_variable_properties",
  "dynamic_class_name_variable_property", "exit_expr", "ctor_arguments",
  "common_scalar", "static_scalar", "static_class_constant", "scalar",
  "static_array_pair_list", "possible_comma",
  "non_empty_static_array_pair_list", "expr", "r_variable", "w_variable",
  "rw_variable", "variable", "variable_properties", "variable_property",
  "method_or_not", "variable_without_objects", "static_member",
  "variable_class_name", "base_variable_with_function_calls",
  "base_variable", "reference_variable", "compound_variable", "dim_offset",
  "object_property", "object_dim_list", "variable_name",
  "simple_indirect_reference", "assignment_list",
  "assignment_list_element", "array_pair_list",
  "non_empty_array_pair_list", "internal_functions_in_yacc",
  "isset_variables", "class_constant", "xhp_tag_expression",
  "xhp_singleton", "xhp_tag_open", "xhp_tag_close", "xhp_tag_start",
  "xhp_literal_text", "xhp_children", "xhp_child", "@2", "@3",
  "xhp_attributes", "xhp_attribute", "xhp_attribute_value", "@4", "@5",
  "@6", "xhp_attribute_quoted_value", "xhp_label_immediate", "@7",
  "xhp_label_no_space", "@8", "xhp_label_pass", "@9", "xhp_label", "@10",
  "xhp_label_", "xhp_label_pass_", "xhp_whitespace_hack", "@11", "@12",
  "@13", "xhp_attribute_decls", "xhp_attribute_decl",
  "xhp_attribute_decl_type", "@14", "@15", "xhp_attribute_enum",
  "xhp_attribute_default", "xhp_attribute_is_required", "@16",
  "xhp_category_list", "@17", "xhp_children_decl",
  "xhp_children_paren_expr", "xhp_children_decl_expr",
  "xhp_children_decl_tag", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    44,   263,
     264,   265,   266,    61,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,    63,    58,   278,   279,   124,
      94,    38,   280,   281,   282,   283,    60,    62,   284,   285,
     286,   287,    43,    45,    46,    42,    47,    37,    33,   288,
     126,    64,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,    91,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
      40,    41,    59,   123,   125,    36,    93,    34
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   178,   179,   180,   180,   181,   181,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   183,   183,   184,   184,
     184,   184,   185,   185,   186,   186,   187,   187,   187,   187,
     188,   188,   188,   188,   188,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   190,   190,   191,   191,   192,   193,   193,   194,
     195,   196,   197,   197,   198,   199,   199,   200,   200,   200,
     201,   201,   202,   203,   203,   204,   204,   205,   205,   206,
     206,   207,   207,   208,   208,   209,   209,   210,   210,   211,
     211,   212,   212,   212,   212,   213,   213,   213,   214,   214,
     215,   215,   216,   216,   217,   217,   218,   218,   219,   219,
     220,   220,   221,   221,   221,   221,   221,   221,   221,   221,
     222,   222,   222,   223,   223,   224,   224,   224,   224,   224,
     224,   225,   225,   226,   226,   226,   227,   227,   227,   227,
     228,   228,   229,   229,   230,   229,   231,   231,   232,   232,
     233,   233,   234,   234,   235,   235,   235,   235,   235,   235,
     236,   236,   236,   236,   237,   237,   238,   238,   239,   239,
     240,   240,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   242,   243,   243,   244,   244,   244,   244,
     245,   245,   245,   245,   245,   245,   245,   245,   246,   246,
     246,   246,   247,   247,   247,   248,   248,   249,   249,   250,
     250,   251,   252,   252,   252,   253,   253,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   255,   255,
     255,   255,   255,   255,   255,   255,   256,   257,   257,   257,
     257,   257,   257,   258,   258,   259,   259,   260,   260,   260,
     260,   261,   261,   262,   263,   264,   265,   265,   266,   266,
     267,   268,   268,   269,   269,   270,   270,   271,   272,   272,
     273,   273,   273,   274,   274,   274,   275,   275,   276,   276,
     277,   277,   278,   278,   278,   279,   279,   280,   280,   281,
     281,   282,   282,   282,   283,   283,   284,   284,   284,   284,
     284,   284,   284,   284,   285,   285,   285,   285,   285,   285,
     285,   286,   286,   287,   287,   241,   288,   288,   289,   290,
     291,   291,   292,   293,   293,   294,   294,   294,   294,   295,
     296,   297,   295,   298,   298,   299,   301,   300,   302,   303,
     300,   304,   304,   306,   305,   308,   307,   310,   309,   312,
     311,   313,   313,   313,   314,   314,   314,   315,   315,   316,
     317,   196,   318,   229,   319,   319,   320,   320,   321,   321,
     321,   321,   321,   321,   322,   323,   321,   324,   324,   325,
     325,   325,   326,   326,   327,   229,   328,   328,   329,   229,
     330,   330,   330,   331,   331,   331,   331,   332,   332,   332,
     332,   332,   332,   332,   333,   333,   333,   333,   246,   247,
     241
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     3,     1,     1,     1,
       4,     3,     5,     4,     3,     2,     3,     1,     1,     3,
       2,     4,     5,     4,     2,     0,     1,     1,     1,     4,
       1,     2,     1,     1,     1,     3,     7,    10,     5,     7,
       9,     5,     2,     3,     2,     3,     2,     3,     3,     3,
       3,     3,     1,     2,     5,     8,     8,     5,     1,    13,
       3,     3,     1,     0,     1,     2,     8,     1,     3,     1,
       1,     1,     0,     1,     9,     7,     6,     1,     2,     2,
       0,     2,     1,     0,     2,     0,     2,     1,     3,     0,
       2,     1,     2,     1,     4,     1,     4,     1,     4,     3,
       5,     3,     4,     4,     5,     0,     5,     4,     1,     1,
       1,     4,     0,     6,     0,     7,     0,     2,     0,     3,
       1,     0,     2,     3,     5,     4,     4,     5,     7,     6,
       0,     1,     1,     1,     0,     1,     1,     2,     3,     3,
       4,     3,     1,     1,     2,     4,     3,     5,     1,     3,
       2,     0,     3,     2,     0,     9,     1,     3,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     3,     5,     4,     3,     1,     0,     1,
       3,     1,     6,     3,     4,     6,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     4,     1,
       2,     9,    10,     1,     0,     4,     3,     4,     1,     2,
       4,     6,     5,     6,     6,     6,     6,     4,     1,     1,
       3,     2,     1,     3,     2,     1,     1,     4,     1,     2,
       0,     2,     0,     2,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     4,     1,     3,     1,     1,     1,
       3,     2,     1,     0,     2,     0,     1,     5,     3,     3,
       1,     1,     1,     1,     1,     1,     5,     1,     2,     0,
       3,     3,     0,     1,     2,     3,     3,     1,     1,     1,
       1,     2,     1,     4,     4,     1,     1,     4,     0,     1,
       1,     1,     4,     4,     1,     1,     3,     1,     2,     3,
       1,     1,     4,     0,     0,     2,     5,     3,     3,     1,
       6,     4,     4,     2,     4,     4,     2,     2,     4,     2,
       2,     1,     3,     3,     3,     1,     1,     3,     4,     3,
       3,     1,     2,     1,     2,     0,     1,     2,     3,     1,
       0,     0,     5,     0,     2,     3,     0,     4,     0,     0,
       5,     0,     1,     0,     3,     0,     2,     0,     3,     0,
       3,     1,     3,     3,     1,     3,     3,     1,     0,     0,
       0,    10,     0,     4,     1,     3,     4,     2,     1,     1,
       1,     1,     1,     1,     0,     0,     6,     1,     3,     2,
       2,     0,     1,     0,     0,     4,     2,     4,     0,     4,
       1,     1,     1,     3,     4,     4,     4,     1,     1,     2,
       2,     2,     3,     3,     1,     1,     2,     2,     2,     2,
       4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     0,     0,
     413,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   282,
       0,   287,   288,     5,   307,   346,    52,   289,   249,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,     0,     0,     0,     0,   268,     0,
       0,     0,     0,    77,    82,     0,     0,   293,   294,   295,
     290,   291,    32,    33,    34,   297,     0,   296,   292,     0,
     413,     0,    58,    25,   357,   309,     3,     0,     7,    30,
       8,     9,    70,    71,     0,     0,   322,    72,   339,     0,
     312,   247,     0,   321,     0,   323,     0,   342,     0,   327,
     338,   340,   345,     0,   235,   308,   385,   386,   395,   403,
       5,   268,     0,    72,   380,   379,     0,   377,   376,   250,
     392,     0,   219,   220,   221,   222,   246,   244,   243,   242,
     241,   240,   239,   238,   237,   236,   268,     0,     0,   269,
       0,   202,   325,     0,   200,   187,     0,     0,   269,   275,
     285,   276,     0,   278,   340,     0,     0,   245,     0,    31,
       0,   177,     0,     0,   178,     0,     0,     0,    42,     0,
      44,     0,     0,     0,    46,   322,     0,   323,    25,     0,
       0,    18,     0,    17,   143,     0,     0,   142,    79,    78,
     148,     0,    72,     0,     0,     0,     0,   363,   364,     0,
       4,     0,   311,   478,     0,     0,     0,     0,   134,     0,
      15,   413,    80,    83,    73,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   348,    53,   201,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,     0,   348,     0,   358,   341,   393,   396,     0,   417,
       0,     0,   421,   428,     0,   271,     0,     0,     0,   271,
       0,   134,   186,     0,     0,   341,   283,     0,     0,     0,
      51,     0,     0,     0,   179,   181,   322,   323,     0,     0,
       0,    43,    45,    61,     0,    47,    48,     0,    60,    20,
       0,     0,    14,     0,   144,   323,     0,    49,     0,     0,
      50,     0,     0,    67,    69,   381,     0,     0,     0,     0,
     361,     0,   360,     0,   369,     0,   315,   310,     0,    11,
       4,   134,   232,     0,    35,    24,    26,    27,    28,     0,
       6,     0,     0,   133,   322,   323,     0,    80,     0,    85,
       0,     0,     0,   130,   383,   335,   333,     0,   205,   207,
     206,     0,     0,   203,   204,   208,   210,   209,   224,   223,
     226,   225,   227,   229,   230,   228,   218,   217,   212,   213,
     211,   214,   215,   216,   231,   349,     0,     0,   183,   198,
     197,   196,   195,   194,   193,   192,   191,   190,   189,   188,
       0,   384,   336,   355,     0,   351,   332,   350,   354,     0,
       0,   394,   415,   391,   400,   399,   387,   397,   389,     0,
     404,     0,     0,   378,   427,     0,     0,   414,   270,     0,
       0,   270,   335,     0,   336,   280,   284,     0,   176,     0,
       0,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   299,     0,   298,    23,   305,     0,
       0,    19,    16,     0,   141,   149,   146,   130,     0,     0,
       0,   374,   375,    10,   363,   363,     0,   373,   324,     0,
     248,   316,   365,   134,    13,     0,     0,     0,   347,   137,
     260,     0,     0,    85,     0,     0,   413,   272,    81,     0,
       0,    84,    87,   151,   130,   132,     0,   120,     0,   131,
     134,   134,   334,   234,     0,   480,     0,   184,   267,   134,
     134,     0,   134,   329,   348,     0,   343,   344,     0,     0,
       0,   398,   388,     0,   424,   428,   422,   423,   286,   277,
      25,   112,     0,    25,   110,    38,     0,   180,    89,     0,
      89,    91,    99,     0,    25,    97,    57,   105,   105,    41,
     302,   303,   313,     0,   301,     0,     0,    21,   145,     0,
       0,    68,    54,   382,     0,   359,     0,     0,   368,     0,
     367,     0,    12,   262,     0,     0,   322,   323,    22,     0,
       0,   274,   479,    86,   151,     0,   160,     0,   254,   130,
       0,   122,     0,     0,   233,   285,     0,     0,   356,     0,
     326,     0,     0,   390,   416,     0,   408,   406,   405,     0,
       0,   418,     0,   279,   114,   116,     0,     0,   178,     0,
       0,    92,     0,     0,     0,   105,     0,   105,     0,   320,
       0,   315,   300,   306,     0,   147,   254,   362,   182,   372,
     371,     0,   261,    29,   140,   429,   273,   160,    88,     0,
     164,   165,   166,   169,   168,   167,   159,   432,   454,   458,
      76,   150,     0,     0,   158,   162,     0,     0,     0,     0,
       0,   123,     0,   263,   266,   185,   264,   265,   331,     0,
     328,   352,   353,   401,     0,   411,   425,   426,   281,   118,
       0,     0,    36,    39,     0,     0,    90,     0,     0,   100,
       0,     0,     0,     0,     0,     0,   101,     0,   304,   316,
     314,     0,     0,     0,   366,   151,    75,     0,     0,     0,
       0,   172,     0,   154,   163,     0,   153,    25,     0,    25,
       0,   126,     0,   125,   332,   402,   409,   412,     0,     0,
       0,     0,     0,   117,   111,     0,    25,    95,    56,    55,
      98,     0,   103,     0,   108,   109,    25,   102,   319,   318,
       0,    25,   370,   160,     0,   443,   413,   439,   440,   441,
     438,     0,   442,     0,   434,   417,   413,     0,   461,   462,
       0,     0,   460,     0,     0,   152,    72,     0,     0,     0,
     258,     0,     0,   127,     0,   124,   330,     0,   407,     0,
      25,     0,     0,    25,    93,    40,     0,   104,    25,   107,
       0,     0,     0,     0,   175,   437,   444,     0,   433,   451,
     456,     0,   455,   419,   474,   475,   419,   467,     0,   468,
     459,   173,   170,     0,     0,    74,   259,     0,   255,   251,
       0,   129,   410,     0,   119,    37,     0,     0,     0,   106,
     317,    25,   252,   431,     0,   435,     0,   453,   413,   477,
       0,   476,     0,     0,   463,   470,   471,   469,     0,     0,
     174,     0,   256,   128,     0,   113,     0,    96,     0,   447,
     445,   450,   449,   452,   436,   457,   428,   472,   473,   465,
     466,   464,   171,   130,   257,    25,    94,    63,     0,     0,
     420,     0,   115,     0,    59,    62,    64,   448,   446,     0,
       0,    65,   156,    25,   155,     0,     0,     0,   157,     0,
      25,     0,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    85,    86,   192,   193,    87,   215,   355,
     356,    89,   934,   935,   936,   332,   333,   357,   358,   225,
      92,    93,    94,   369,    95,   371,   520,   521,   650,   570,
     835,   778,   576,   309,   579,   656,   786,   565,   645,   719,
     722,   771,   526,   527,   528,   362,   363,   196,   197,   201,
     616,   691,   816,   944,   692,   693,   694,   695,   752,   696,
     170,   303,   304,    96,   123,   699,   821,    98,    99,   529,
     160,   161,   559,   643,   167,   292,   100,   477,   478,   101,
     660,   502,   661,   102,   103,   497,   104,   105,   630,   710,
     543,   106,   107,   108,   109,   110,   111,   112,   406,   426,
     427,   428,   113,   341,   342,   345,   346,   114,   336,   115,
     116,   117,   118,   436,   119,   277,   278,   437,   550,   765,
     279,   440,   638,   715,   714,   827,   768,   130,   131,   548,
     549,   441,   442,   889,   890,   283,   555,   447,   745,   843,
     748,   803,   804,   805,   884,   929,   910,   887,   914,   749,
     807,   750,   811,   857,   858,   859
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -577
static const yytype_int16 yypact[] =
{
    -577,    72,  1927,  -577,  6240,  6240,   -60,  6240,  6240,  6240,
    -577,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,
    6240,  6240,  6240,  6240,  6240,   385,   385,  6240,   429,   -52,
     -48,  -577,  -577,    99,  -577,  -577,  -577,  -577,  -577,  6240,
    4587,   -30,   -27,    44,    73,    86,  1226,  4727,    88,  -577,
     119,  4858,     6,  6240,    68,    -8,    79,   125,    15,   115,
     117,   134,   139,  -577,  -577,   141,   143,  -577,  -577,  -577,
    -577,  -577,  -577,  -577,  -577,  -577,    -7,  -577,  -577,   135,
    -577,  6240,  -577,  -577,   145,   -47,  -577,    16,  -577,  -577,
    -577,  -577,  -577,  -577,    65,   243,  -577,   314,  -577,   204,
    -577,  -577,  6679,  -577,   120,  1410,   183,  -577,   221,   245,
    -577,   -19,  -577,     8,  -577,  -577,  -577,  -577,   229,  -577,
    -577,   273,   227,   314,  7464,  7464,  6240,  7464,  7464,  7578,
    -577,   312,   320,   320,    38,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,  -577,   237,   135,   -59,
     241,  -577,  -577,   251,  -577,  -577,   239,   135,   246,   254,
     231,  -577,   257,   285,   -13,     8,  4989,  -577,  6240,  -577,
      18,  7464,   329,  6240,  6240,  6240,   342,  6240,  -577,  6723,
    -577,  6784,   244,   406,  -577,   252,  7464,  1023,  -577,  6825,
     135,   -31,    21,  -577,  -577,   225,    22,  -577,  -577,  -577,
     410,    23,   314,   385,   385,   385,   255,   281,  5138,   135,
    -577,   -44,   -46,  -577,  6869,  2067,  6240,   355,  5278,   357,
    -577,  -577,   309,   311,  -577,    -5,     9,  6240,  6240,  6240,
    5409,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,
    6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,
    6240,  6240,   429,  6240,  -577,  -577,  -577,  5549,  6240,  6240,
    6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  6240,  5278,
      58,     5,  6240,  6240,   145,   -11,  -577,   283,    -9,    63,
     264,  6930,  -577,   106,   135,   -55,    61,    62,   135,   246,
      46,  5278,  -577,    46,     5,     0,  -577,  6971,  7014,  6240,
    -577,   268,  7075,   269,   432,  7464,   349,  1299,   431,    33,
    7116,  -577,  -577,  -577,  1308,  -577,  -577,  2207,  -577,    -4,
     375,    68,  -577,  6240,  -577,  -577,    -8,  -577,  1308,   374,
    -577,   280,    34,  -577,  -577,  -577,    35,   286,   282,   303,
    -577,    39,  -577,   385,  7304,   304,   466,   -43,  1647,  -577,
    -577,  5278,  -577,   317,  -577,  -577,  -577,  -577,  -577,  6389,
    -577,   385,   308,   472,    41,   878,   468,   309,   166,   363,
     166,   315,   321,   213,   325,   328,     0,     8,  7504,  7541,
    7578,  6240,  7408,  7651,  7686,  4780,  4911,  5042,  5191,  5191,
    5191,  5191,  1103,  1103,  1103,  1103,   643,   643,   359,   359,
     359,    38,    38,    38,  -577,  7464,   306,   345,  7578,  7578,
    7578,  7578,  7578,  7578,  7578,  7578,  7578,  7578,  7578,  7578,
     334,   330,   339,  -577,  6240,  -577,   341,     2,  -577,   337,
    6430,  -577,  -577,  -577,  -577,  -577,  -577,   229,  -577,   480,
    -577,   508,   452,  -577,  -577,   454,   455,  -577,    87,   325,
     330,   246,  -577,   358,  -577,  -577,  -577,  3887,  7464,  6240,
    4027,  6240,  6240,   385,   176,  1308,   457,  4167,    -3,  1308,
    1308,   364,   384,   135,    66,   392,  -577,  -577,  -577,   433,
     467,  -577,  -577,  6471,  -577,  -577,   528,   213,   385,   370,
     385,  -577,  -577,  -577,   281,   281,   531,  -577,  -577,  5689,
    -577,  5829,  -577,  5278,  -577,  1787,   381,   382,  -577,  -577,
    -577,  5969,  1308,   363,   394,   135,  -577,   246,  -577,   166,
     373,   549,  -577,  -577,   213,  -577,   390,   554,    75,  -577,
    5278,  5278,     0,  7615,  6240,  -577,   429,  -577,  -577,  5278,
    5278,  6512,  5278,  -577,  6240,  6240,  -577,  -577,   529,   312,
    6240,   283,  -577,    71,  -577,   208,  -577,  -577,  -577,   445,
    -577,  -577,  7159,  -577,  -577,  -577,   401,  7464,   450,   385,
     450,  -577,  -577,   565,  -577,  -577,  -577,   411,   413,  -577,
    -577,  -577,  1308,   135,    90,   509,   416,  -577,  -577,  1308,
     417,  -577,  -577,  -577,    47,  -577,  6240,   385,  7464,   385,
    7365,   419,  -577,  -577,   423,   385,    49,   994,  -577,   425,
     135,   246,  -577,   549,  -577,   166,  1304,   428,   493,   127,
     530,   593,   436,   439,  7615,   231,   440,   441,  -577,   442,
     490,   444,  6556,  -577,   -68,  6597,  -577,  -577,  -577,   542,
     543,  -577,     5,  -577,  3747,   184,   446,  2347,  6240,   176,
     451,  -577,   453,  1308,  2487,  -577,   297,  -577,   -22,   496,
     456,   615,   186,  -577,   166,  -577,   493,  -577,  7578,  -577,
    -577,  6109,  -577,  -577,  -577,  -577,   246,  1400,  -577,   553,
    -577,  -577,  -577,  -577,  -577,  -577,  -577,  -577,  -577,  -577,
    -577,  -577,   555,   273,   352,  -577,    24,   460,   458,   461,
      81,   623,  1308,  -577,  -577,  -577,  -577,  -577,  -577,     5,
    -577,  -577,  -577,  -577,  6240,   229,  -577,  -577,  -577,   233,
     469,  4587,  -577,  -577,   465,   470,  -577,  4307,  4307,  -577,
     471,   316,   476,  6240,    -1,    52,  -577,  1308,  -577,  1308,
    -577,   563,   478,   385,  7464,  -577,  -577,   627,   759,   597,
     122,   636,    25,  -577,  -577,   580,  -577,  -577,    82,  -577,
     579,   645,  1308,  -577,   341,  -577,  7464,   283,   479,   491,
     634,   592,  6240,  -577,  -577,  4447,  -577,  -577,  -577,  -577,
    -577,   492,  -577,  6638,  -577,  -577,  -577,  -577,  -577,   538,
     495,  -577,  -577,  1450,  1308,  -577,  -577,  -577,  -577,  -577,
    -577,   494,  -577,    26,  -577,  -577,  -577,    29,  -577,  -577,
      70,   498,  -577,  1308,   596,  -577,   314,   655,  2627,   599,
    -577,    51,  2767,   659,  1308,  -577,  -577,   501,  -577,  6240,
    -577,   504,  7220,  -577,  -577,  -577,  2907,  -577,  -577,  3747,
    1308,   506,  3047,   503,  -577,   607,  -577,   759,  -577,   668,
    -577,   635,  -577,  -577,  -577,  -577,  -577,  -577,    31,   205,
    -577,  -577,   670,   620,  1308,  -577,  -577,    83,  -577,  -577,
    1308,  -577,  -577,  7261,  3747,  -577,  4587,  3187,   522,  3747,
    -577,  -577,  -577,  -577,   669,  -577,   642,   527,  -577,  -577,
     312,  -577,    70,    70,   249,  -577,  -577,  -577,  1308,   532,
    -577,   622,  -577,  -577,   675,  -577,   535,  -577,  3327,  -577,
     695,  -577,  -577,  -577,  -577,  -577,   106,   679,  -577,  -577,
    -577,  -577,  -577,   213,  -577,  -577,  -577,   605,   669,   537,
    -577,   541,  3747,   546,  -577,   605,  -577,  -577,  -577,   148,
     166,  -577,  -577,  -577,  -577,   649,  3467,   547,  -577,   556,
    -577,  3607,  -577
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -577,  -577,  -182,   -18,  -577,  -577,   399,  -577,  -183,  -577,
      11,  -577,  -577,  -577,  -209,  -577,   240,    14,    17,  -121,
    -577,  -577,  -577,   366,  -577,  -577,   224,   215,   173,    97,
    -577,    27,  -577,  -577,  -577,  -481,   -35,  -577,  -577,  -577,
    -577,  -577,  -484,  -577,   130,  -198,  -577,  -577,   426,  -577,
    -576,  -577,  -577,  -577,  -577,  -577,  -577,    57,  -577,  -577,
    -577,  -439,  -577,    28,    -2,    92,  -577,  -577,    20,  -356,
    -237,  -577,  -577,  -577,  -577,   128,   235,   266,  -577,  -577,
    -577,    93,  -577,   943,   561,  -326,   310,  1042,  -577,  -577,
       1,  -217,  -577,    60,  -577,   -24,   -10,  -577,  -251,  -274,
    -577,  -577,    36,   267,   271,  -577,  -577,  -577,  -577,  -577,
     484,  -577,  -577,  -577,  -577,  -420,  -577,  -577,  -577,  -577,
    -577,  -577,  -577,  -577,  -577,  -577,  -577,   -79,  -577,  -577,
    -577,   -41,  -577,   -87,  -577,  -543,  -577,  -544,  -577,  -577,
    -577,  -577,   -72,  -577,  -577,  -577,  -577,  -577,  -577,  -577,
    -577,  -577,  -577,    30,  -535,  -577
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -479
static const yytype_int16 yytable[] =
{
      97,   213,   280,   590,   163,   317,   634,   149,   149,   375,
     158,   641,   518,    88,   522,   404,    90,   551,   164,    91,
     455,   429,   566,   577,   219,   784,   299,    10,   348,   321,
     326,   329,   755,   814,   847,   509,   191,   851,   677,   892,
     617,   466,   488,   490,   272,   150,   150,   495,   159,  -135,
     272,   172,   272,   422,   425,   495,   202,  -138,   211,   867,
     893,   212,   320,   272,   165,   544,   120,   194,   372,   375,
     422,   420,     3,   452,   733,   734,   454,   425,   423,   185,
      35,   331,   374,    35,    35,   153,   153,   252,   162,   480,
     200,   221,   217,   453,   445,   446,   217,   658,  -269,  -271,
     438,   253,  -270,   275,   217,   217,   620,   217,   217,   439,
     126,   218,   760,   819,   901,   351,    49,   853,   166,   202,
     217,    35,   168,   218,   351,   169,  -337,   503,   349,   350,
     285,   421,  -337,    35,   449,   450,    35,    35,   222,   289,
     173,   120,   367,   174,   209,   432,   433,   217,   733,   734,
     621,  -333,   736,   506,   273,   295,   761,   820,   902,  -334,
     273,   182,   273,   522,   434,   373,   210,   195,   505,   793,
     578,   785,   319,   273,   731,   545,   735,   149,   424,   188,
      84,   255,   256,   274,    84,   149,   149,   149,   220,   149,
     300,   347,   183,   322,   327,   330,   756,   815,   848,   198,
     120,   852,   894,   306,   467,   489,   491,   569,   120,   725,
     496,  -269,  -135,    97,   175,   150,   376,   217,   667,   190,
    -138,    84,   868,   150,   150,   150,   787,   150,   163,   854,
     895,   855,   856,    84,   158,  -271,    84,    84,   217,   120,
     810,   217,   164,   176,   636,   199,   364,   896,   637,   120,
     897,    35,   720,   721,   525,   153,   177,   503,   444,   678,
     376,   376,   377,   153,   153,   153,   448,   153,   445,   446,
     451,   669,   159,   670,   919,   514,   376,   376,   515,   674,
     376,   808,   809,   376,   376,   203,   120,   204,   165,   516,
     146,   920,   810,   631,   921,   767,   474,   364,   120,   625,
      35,   769,   770,   191,   205,   601,   377,   377,   741,   206,
     474,   207,   162,   208,   514,    97,   223,   515,   216,   364,
     942,   943,   377,   377,   147,   149,   377,   148,   516,   377,
     377,  -270,   622,   623,   475,   151,   154,   217,    80,   146,
     525,   626,   627,   149,   629,   224,    97,   916,   475,   226,
     517,    84,   517,   269,   120,   517,    35,   917,   918,    88,
     444,   514,    90,   150,   515,    91,   270,   532,   718,   271,
     639,   640,   930,   147,    49,   516,   148,   644,   209,   364,
     647,   150,   276,   253,  -121,   282,   286,    80,   284,   149,
     288,   654,   732,   733,   734,   146,   287,   217,   323,   290,
      84,   291,   293,   153,   249,   250,   251,   339,   252,   294,
     536,   781,   733,   734,   301,   308,   313,   792,   120,   314,
      35,   153,   253,   328,   315,   425,   338,   150,   360,   147,
     366,   368,   148,   370,   373,   764,   431,   612,   459,   931,
     462,   461,   463,    80,   465,   149,   149,   474,   481,   486,
     487,   474,   474,  -161,   493,   584,    84,   492,   120,   146,
      35,   680,   681,   682,   683,   684,   685,   153,   561,   517,
     149,   564,   149,   494,   501,   500,   149,   149,   575,   510,
     511,   512,   535,   150,   150,   475,   519,   507,   523,   475,
     475,   524,   425,   147,   474,   530,   148,   611,   531,   146,
     539,   517,   120,    97,    35,   538,   517,    80,   150,   540,
     150,   542,   163,   546,   150,   150,    88,   552,   158,    90,
      84,   553,    91,   153,   153,   554,   164,   556,   557,   558,
     573,   364,   475,   147,   582,   583,   148,   585,   586,   606,
     587,   589,   592,   146,   596,   610,   614,    80,   153,   476,
     153,   149,   603,   604,   153,   153,   159,   615,   364,   364,
      84,   618,   619,   476,   474,   662,   633,   364,   364,   642,
     364,   474,   165,   648,   818,   649,   822,   156,   653,   149,
     157,   149,   663,   655,   945,   657,   664,   149,   666,   150,
     672,    80,   676,   836,   485,   673,   162,   517,   675,   697,
     698,   517,   475,   839,    84,   701,   702,   703,   842,   475,
     704,   706,   707,   708,   709,   716,   717,   150,   723,   150,
     711,   737,   727,   739,   728,   150,   747,   738,   758,   153,
     751,   149,   376,   757,   759,   474,   762,   774,   790,   772,
     794,   775,    97,   780,   806,    97,   517,   874,   782,   813,
     877,   791,    97,   817,   823,   879,   828,   153,   824,   153,
     830,   829,   831,   840,   837,   153,   841,   846,   864,   150,
     860,   862,   870,   475,   866,   872,   875,   883,   377,   881,
    -478,   886,   888,   898,   474,   246,   247,   248,   249,   250,
     251,   753,   252,   899,   907,   863,   913,   924,   908,   376,
     476,   925,   923,   928,   476,   476,   253,   926,   893,   153,
     933,   938,   939,    31,    32,   911,   940,   845,   949,   474,
     482,   474,   475,    37,   947,   149,   941,   850,   591,   950,
     158,   572,   773,   513,   613,   580,   581,   609,   777,   777,
      31,    32,   932,   652,   474,   377,   726,   476,   838,   700,
      37,   754,   484,   705,   740,   779,   324,   475,   742,   475,
     946,   594,   435,   150,   849,   826,   595,   951,   802,   891,
      67,    68,    69,    70,    71,   885,   474,     0,   608,     0,
     812,     0,   475,     0,    75,     0,   834,     0,     0,     0,
       0,    77,    78,     0,     0,   474,     0,    67,    68,    69,
      70,    71,     0,   153,     0,     0,   474,     0,     0,   915,
       0,    75,     0,     0,   475,     0,    97,   476,    77,    78,
      97,     0,   474,     0,   476,     0,     0,     0,     0,   158,
       0,     0,   120,   475,    97,     0,     0,    97,     0,     0,
      97,     0,     0,     0,   475,     0,   474,     0,   659,     0,
       0,     0,   474,     0,     0,   665,     0,     0,     0,     0,
     475,     0,     0,     0,     0,     0,     0,   802,     0,     0,
       0,     0,    97,   146,   795,    97,     0,    97,     0,     0,
     474,     0,     0,     0,   475,     0,  -136,   905,   476,     0,
     475,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,     0,     0,   517,    97,   156,     0,     0,
     157,     0,     0,     0,     0,     0,     0,     0,   475,   729,
       0,   796,   517,   797,   798,   799,   800,   801,     0,     0,
      97,     0,     0,     0,     0,     0,     0,   476,     0,  -325,
    -325,     0,     0,     0,    97,     0,     0,   124,   125,    97,
     127,   128,   129,     0,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   763,     0,
     155,     0,   476,     0,   476,     0,     0,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,     0,   179,
     181,     0,     0,     0,   186,     0,   189,   476,     0,     0,
       0,     0,  -139,   788,     0,   789,     0,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,     0,
       0,     0,     0,     0,   214,     0,     0,     0,   825,   476,
       0,     0,     0,     0,     0,     0,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   476,  -136,
       0,     0,     0,     0,     0,  -325,  -325,     0,     0,   476,
     844,     0,     0,     0,     0,     0,     0,   152,   152,   281,
       0,     0,     0,     0,     0,   476,     0,     0,     0,   861,
       0,     0,     0,     0,  -325,  -325,     0,     0,     0,     0,
     871,     0,     0,   187,     0,     0,     0,     0,     0,   476,
       0,     0,     0,     0,     0,   476,   880,     0,     0,   297,
       0,   298,     0,     0,     0,     0,   302,   305,   186,   909,
     310,   912,     0,     0,     0,     0,     0,     0,     0,     0,
     900,     0,     0,   476,     0,     0,   903,     0,     0,  -479,
    -479,  -479,  -479,   244,   245,   246,   247,   248,   249,   250,
     251,   344,   252,     0,     0,     0,     0,     0,     0,   359,
       0,   186,     0,   937,   922,  -139,   253,     0,     0,     0,
     378,   379,   380,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   316,   405,     0,     0,     0,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   186,     0,     0,   405,   430,   307,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,   186,     0,     0,   325,     9,     0,
       0,     0,   458,     0,     0,   334,   335,   337,     0,   340,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     365,     0,    10,     0,     0,     0,   483,     0,    11,    12,
       0,     0,     0,     0,    13,     0,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     0,
      27,    28,    29,     0,   186,     0,     0,    31,    32,   120,
      34,    35,     0,     0,     0,     0,     0,    37,    38,     0,
       0,   365,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   533,     0,     0,    49,     0,     0,
       0,     0,     0,   365,     0,     0,     0,     0,     0,     0,
     121,     0,     0,    60,    61,     0,     0,     0,     0,     0,
     469,   470,    65,    66,    67,    68,    69,    70,    71,     0,
    -325,  -325,     0,     0,     0,     0,     0,   541,    75,     0,
       0,     0,     0,     0,   122,    77,    78,    79,     0,    31,
      32,   120,     0,     0,     0,   498,     0,     0,    80,    37,
       0,     0,   464,   365,     0,     0,    81,     0,   178,     0,
       0,    84,   562,   498,   305,   567,   679,     0,     0,     0,
       0,     0,     0,   680,   681,   682,   683,   684,   685,   686,
       0,     0,   146,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   471,    67,    68,    69,    70,
      71,     0,   598,     0,   600,     0,   186,     0,     0,   537,
      75,     0,     0,     0,   186,     0,   472,    77,    78,   473,
     687,   688,   689,     0,     0,     0,     0,     0,     0,     0,
      80,  -325,  -325,   186,   186,     0,     0,   624,   690,     0,
       0,     0,   186,   186,     0,   186,     0,   405,   632,     0,
       0,     0,     0,   635,     0,     0,     0,     0,     0,     0,
       0,     0,   679,     0,     0,   568,   571,     0,     0,   680,
     681,   682,   683,   684,   685,   686,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     334,     0,   593,     0,     0,     0,   340,   340,     0,   668,
       0,     0,     0,     0,     0,   365,     0,     0,     0,     0,
       0,     0,   679,   607,     0,     0,   687,   688,   689,   680,
     681,   682,   683,   684,   685,   686,     0,     0,     0,     0,
       0,     0,   365,   365,   746,     0,     0,     0,     0,     0,
       0,   365,   365,     0,   365,     0,     0,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   687,   688,   689,     0,
       0,   651,     0,     0,   744,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -430,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   498,
       0,   498,     0,     0,     0,     0,     0,   498,     0,     0,
       4,     5,     6,     7,     8,     0,     0,   766,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   783,     0,     0,     0,
       0,     0,     0,    10,     0,     0,     0,     0,     0,    11,
      12,   571,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,   832,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,    50,
      51,    52,     0,    53,    54,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,    62,    63,    64,     0,
       0,     0,   873,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,   498,     0,     0,     0,    75,
       4,     5,     6,     7,     8,    76,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   504,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,    50,
      51,    52,     0,    53,    54,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,    76,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   602,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,    50,
      51,    52,     0,    53,    54,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,    76,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   354,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   479,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,   724,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,   730,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   865,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   869,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,   878,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   882,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,   906,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   927,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   948,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,   952,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,    56,
      57,    58,     0,    59,    60,    61,   353,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   560,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   563,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   574,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   776,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,   833,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,    30,     0,     0,     0,    31,    32,
      33,    34,    35,     0,    36,     0,     0,     0,    37,    38,
      39,    40,    41,     0,    42,     0,    43,     0,    44,     0,
       0,    45,     0,     0,     0,    46,    47,    48,    49,     0,
      51,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    58,     0,    59,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     0,    72,    73,    74,     0,     0,     0,     0,    75,
       4,     5,     6,     7,     8,   122,    77,    78,    79,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,     0,    82,
      83,     0,    84,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       0,    27,    28,    29,     0,     0,     0,     0,    31,    32,
     120,    34,    35,     0,     0,     0,     0,     0,    37,    38,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,    49,   252,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   121,     0,   253,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
       0,     4,     5,     6,     7,     8,     0,     0,     0,    75,
       9,     0,     0,     0,     0,   122,    77,    78,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,    10,     0,     0,    81,     0,   180,
      11,    12,    84,     0,     0,     0,    13,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     0,    27,    28,    29,     0,     0,     0,     0,    31,
      32,   120,    34,    35,     0,     0,     0,     0,     0,    37,
      38,     0,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,    49,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,   253,    60,    61,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      71,     0,     4,     5,     6,     7,     8,     0,     0,     0,
      75,     9,     0,     0,     0,     0,   122,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,    10,     0,     0,    81,     0,
     184,    11,    12,    84,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
      49,   252,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,   253,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,   122,    77,    78,
      79,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       9,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     296,     0,     0,     0,    84,     0,     0,     0,     0,   343,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
      11,    12,     0,     0,     0,     0,    13,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     0,    27,    28,    29,     0,     0,     0,     0,    31,
      32,   120,    34,    35,     0,     0,     0,     0,     0,    37,
      38,     0,     0,  -479,  -479,  -479,  -479,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,    49,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,   253,    60,    61,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     4,     5,     6,     7,     8,   122,    77,    78,    79,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,     0,     0,    81,   361,
       0,     0,     0,    84,    10,     0,     0,     0,     0,     0,
      11,    12,     0,     0,     0,     0,    13,     0,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     0,    27,    28,    29,     0,     0,     0,     0,    31,
      32,   120,    34,    35,     0,     0,     0,     0,     0,    37,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,     0,    60,    61,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      71,     0,     4,     5,     6,     7,     8,     0,     0,     0,
      75,     9,     0,     0,     0,     0,   122,    77,    78,    79,
       0,     0,     0,     0,     0,   381,     0,     0,     0,     0,
      80,     0,     0,     0,     0,    10,     0,     0,    81,     0,
       0,    11,    12,    84,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     4,     5,     6,     7,     8,   122,    77,    78,
      79,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     407,     0,     0,     0,    84,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     4,     5,     6,     7,     8,   122,    77,    78,
      79,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     597,     0,     0,     0,    84,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     4,     5,     6,     7,     8,   122,    77,    78,
      79,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     599,     0,     0,     0,    84,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     4,     5,     6,     7,     8,   122,    77,    78,
      79,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     605,     0,     0,     0,    84,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     4,     5,     6,     7,     8,   122,    77,    78,
      79,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
     743,     0,     0,     0,    84,    10,     0,     0,     0,     0,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     0,    27,    28,    29,     0,     0,     0,     0,
      31,    32,   120,    34,    35,     0,     0,     0,     0,     0,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,     0,     4,     5,     6,     7,     8,     0,     0,
       0,    75,     9,     0,     0,     0,     0,   122,    77,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,     0,    10,     0,     0,    81,
       0,     0,    11,    12,    84,     0,     0,     0,    13,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,     0,    27,    28,    29,     0,     0,     0,
       0,    31,    32,   120,    34,    35,     0,     0,     0,     0,
       0,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,     0,     0,    60,    61,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    67,    68,
      69,    70,    71,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,   122,    77,
      78,    79,     0,     0,     0,     0,     0,     0,   227,   228,
     229,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,   230,    84,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,     0,   252,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,   230,     0,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,     0,   252,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   253,     0,     0,   230,     0,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,     0,
     252,   227,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   253,     0,     0,   230,     0,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
       0,   252,     0,   508,     0,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,   253,     0,     0,     0,     0,
       0,   230,     0,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   547,   252,   227,   228,   229,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,   230,     0,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   588,   252,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     253,     0,     0,   230,   784,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   628,   252,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   253,     0,     0,   230,     0,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,     0,   252,     0,
     712,     0,   227,   228,   229,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,     0,     0,     0,   230,     0,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   713,   252,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   253,     0,     0,     0,
       0,     0,     0,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     785,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,     0,   252,   227,   228,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   253,     0,     0,
     230,   254,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,     0,   252,     0,     0,     0,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,   253,     0,
       0,     0,     0,     0,   230,   311,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,     0,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,     0,     0,     0,     0,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   230,   312,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,     0,   252,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   253,     0,     0,   230,   318,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,     0,
     252,     0,     0,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,   230,
     352,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,     0,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   253,     0,     0,
       0,     0,     0,     0,   227,   228,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   443,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,     0,   252,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   253,     0,
       0,   230,   456,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,     0,   252,     0,     0,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,   230,   457,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,     0,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   253,     0,     0,     0,     0,     0,     0,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   230,   460,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,     0,   252,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   253,     0,     0,   230,   468,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,     0,
     252,     0,     0,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,   230,
     646,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,     0,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   253,     0,     0,
       0,     0,     0,     0,   227,   228,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   876,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,     0,   252,     0,     0,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,   253,   499,
       0,     0,   904,   230,   534,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,     0,   252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   253,     0,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     671,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,     0,   252,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   253,     0,   230,
       0,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   229,   252,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   253,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,     0,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,   253,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,     0,   252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   253,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,     0,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   253,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,     0,
     252,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   253,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,     0,   252,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253
};

static const yytype_int16 yycheck[] =
{
       2,    80,   123,   487,    28,   188,   549,    25,    26,   226,
      28,   555,   368,     2,   370,   252,     2,   437,    28,     2,
     294,   272,   461,    26,     8,    26,     8,    36,   210,     8,
       8,     8,     8,     8,     8,   361,    54,     8,   614,     8,
     524,     8,     8,     8,    63,    25,    26,     8,    28,     8,
      63,    40,    63,   270,   271,     8,    58,     8,    76,     8,
      29,    79,    93,    63,    28,    63,    73,    75,    73,   286,
     287,   269,     0,   290,    96,    97,   293,   294,    73,    51,
      75,   202,    73,    75,    75,    25,    26,    49,    28,    93,
      75,    26,   151,   291,   162,   163,   151,   578,   145,   145,
      37,    63,   145,   113,   151,   151,    31,   151,   151,    46,
     170,   170,    31,    31,    31,   170,   101,    47,   170,   121,
     151,    75,   170,   170,   170,    26,   145,   170,   172,   173,
     148,    73,   145,    75,    73,    73,    75,    75,    73,   157,
     170,    73,   221,   170,   151,   154,   155,   151,    96,    97,
      75,   170,   174,   351,   173,   165,    75,    75,    75,   170,
     173,    73,   173,   519,   173,   170,   173,   175,   350,   745,
     173,   172,   190,   173,   655,   173,   657,   195,   173,   173,
     175,    61,    62,   175,   175,   203,   204,   205,   172,   207,
     172,   209,    73,   172,   172,   172,   172,   172,   172,   120,
      73,   172,   171,   175,   171,   171,   171,    31,    73,   648,
     171,   145,   171,   215,   170,   195,   226,   151,   171,   151,
     171,   175,   171,   203,   204,   205,   174,   207,   252,   159,
      25,   161,   162,   175,   252,   145,   175,   175,   151,    73,
     170,   151,   252,   170,   173,   120,   218,    42,   177,    73,
      45,    75,    68,    69,   127,   195,   170,   170,   152,   615,
     270,   271,   226,   203,   204,   205,   284,   207,   162,   163,
     288,   597,   252,   599,    25,   148,   286,   287,   151,   605,
     290,   159,   160,   293,   294,   170,    73,   170,   252,   162,
     114,    42,   170,   544,    45,   715,   314,   269,    73,   536,
      75,    68,    69,   321,   170,   503,   270,   271,   664,   170,
     328,   170,   252,   170,   148,   317,    73,   151,   173,   291,
     172,   173,   286,   287,   148,   343,   290,   151,   162,   293,
     294,   145,   530,   531,   314,    25,    26,   151,   162,   114,
     127,   539,   540,   361,   542,    31,   348,   890,   328,   145,
     368,   175,   370,   170,    73,   373,    75,   892,   893,   348,
     152,   148,   348,   343,   151,   348,   145,   377,   642,   124,
     162,   163,   916,   148,   101,   162,   151,   560,   151,   351,
     563,   361,   153,    63,   171,    73,   145,   162,   151,   407,
     151,   574,    95,    96,    97,   114,   145,   151,   173,   145,
     175,   170,   145,   343,    45,    46,    47,   126,    49,   124,
      65,    95,    96,    97,    85,    73,   172,   743,    73,    13,
      75,   361,    63,    13,   172,   642,   171,   407,    73,   148,
      73,   122,   151,   122,   170,   709,   153,   516,   170,   923,
       8,   172,    93,   162,    13,   463,   464,   465,    73,    75,
     170,   469,   470,   101,   172,   473,   175,   171,    73,   114,
      75,   109,   110,   111,   112,   113,   114,   407,   457,   487,
     488,   460,   490,   170,     8,   171,   494,   495,   467,   171,
       8,    13,   176,   463,   464,   465,   123,   170,   173,   469,
     470,   170,   709,   148,   512,   170,   151,   515,   170,   114,
     170,   519,    73,   505,    75,   171,   524,   162,   488,   170,
     490,   170,   536,   176,   494,   495,   505,    37,   536,   505,
     175,    13,   505,   463,   464,    73,   536,    73,    73,   171,
      73,   503,   512,   148,   170,   151,   151,   145,   105,   511,
      73,    13,   172,   114,    13,   151,   173,   162,   488,   314,
     490,   569,   171,   171,   494,   495,   536,     8,   530,   531,
     175,   171,     8,   328,   582,   583,    37,   539,   540,   124,
     542,   589,   536,   172,   757,   125,   759,   148,    13,   597,
     151,   599,    73,   172,   940,   172,   170,   605,   171,   569,
     171,   162,   610,   776,   328,   172,   536,   615,   173,   171,
     107,   619,   582,   786,   175,    75,    13,   171,   791,   589,
     171,   171,   171,   171,   124,    73,    73,   597,   172,   599,
     176,   125,   171,     8,   171,   605,    73,   171,   170,   569,
      75,   649,   642,   173,   173,   653,    13,   172,    75,   170,
      13,   171,   644,   172,    47,   647,   664,   830,   172,    13,
     833,   173,   654,    73,    75,   838,   177,   597,    13,   599,
      26,   170,    70,   125,   172,   605,   171,   173,    13,   649,
     172,    75,    13,   653,    75,   174,   172,   174,   642,   173,
      73,    13,    47,    13,   702,    42,    43,    44,    45,    46,
      47,   693,    49,    73,   172,   816,   169,    75,   881,   709,
     465,    26,   170,     8,   469,   470,    63,   172,    29,   649,
     105,   174,   171,    71,    72,    73,   170,   796,   171,   737,
     321,   739,   702,    81,    75,   743,   935,   806,   488,   173,
     748,   465,   721,   367,   519,   469,   470,   513,   727,   728,
      71,    72,   925,   570,   762,   709,   649,   512,   783,   619,
      81,   694,   326,   625,   661,   728,   195,   737,   666,   739,
     943,   494,   278,   743,   805,   764,   495,   950,   748,   856,
     128,   129,   130,   131,   132,   847,   794,    -1,   512,    -1,
     750,    -1,   762,    -1,   142,    -1,   775,    -1,    -1,    -1,
      -1,   149,   150,    -1,    -1,   813,    -1,   128,   129,   130,
     131,   132,    -1,   743,    -1,    -1,   824,    -1,    -1,   888,
      -1,   142,    -1,    -1,   794,    -1,   818,   582,   149,   150,
     822,    -1,   840,    -1,   589,    -1,    -1,    -1,    -1,   847,
      -1,    -1,    73,   813,   836,    -1,    -1,   839,    -1,    -1,
     842,    -1,    -1,    -1,   824,    -1,   864,    -1,   582,    -1,
      -1,    -1,   870,    -1,    -1,   589,    -1,    -1,    -1,    -1,
     840,    -1,    -1,    -1,    -1,    -1,    -1,   847,    -1,    -1,
      -1,    -1,   874,   114,   115,   877,    -1,   879,    -1,    -1,
     898,    -1,    -1,    -1,   864,    -1,     8,   876,   653,    -1,
     870,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,   923,   908,   148,    -1,    -1,
     151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   898,   653,
      -1,   162,   940,   164,   165,   166,   167,   168,    -1,    -1,
     932,    -1,    -1,    -1,    -1,    -1,    -1,   702,    -1,    61,
      62,    -1,    -1,    -1,   946,    -1,    -1,     4,     5,   951,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   702,    -1,
      27,    -1,   737,    -1,   739,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    51,    -1,    53,   762,    -1,    -1,
      -1,    -1,     8,   737,    -1,   739,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,   762,   794,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   813,   171,
      -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,   824,
     794,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,   126,
      -1,    -1,    -1,    -1,    -1,   840,    -1,    -1,    -1,   813,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,
     824,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,   864,
      -1,    -1,    -1,    -1,    -1,   870,   840,    -1,    -1,   166,
      -1,   168,    -1,    -1,    -1,    -1,   173,   174,   175,   884,
     177,   886,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     864,    -1,    -1,   898,    -1,    -1,   870,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   208,    49,    -1,    -1,    -1,    -1,    -1,    -1,   216,
      -1,   218,    -1,   928,   898,   171,    63,    -1,    -1,    -1,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   172,   253,    -1,    -1,    -1,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,    -1,    -1,   272,   273,   175,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,   291,    -1,    -1,   195,    12,    -1,
      -1,    -1,   299,    -1,    -1,   203,   204,   205,    -1,   207,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     218,    -1,    36,    -1,    -1,    -1,   323,    -1,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,   351,    -1,    -1,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,   269,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   381,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,   117,   118,    -1,    -1,    -1,    -1,    -1,
      42,    43,   126,   127,   128,   129,   130,   131,   132,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,   424,   142,    -1,
      -1,    -1,    -1,    -1,   148,   149,   150,   151,    -1,    71,
      72,    73,    -1,    -1,    -1,   343,    -1,    -1,   162,    81,
      -1,    -1,    93,   351,    -1,    -1,   170,    -1,   172,    -1,
      -1,   175,   459,   361,   461,   462,   102,    -1,    -1,    -1,
      -1,    -1,    -1,   109,   110,   111,   112,   113,   114,   115,
      -1,    -1,   114,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   127,   128,   129,   130,   131,
     132,    -1,   499,    -1,   501,    -1,   503,    -1,    -1,   407,
     142,    -1,    -1,    -1,   511,    -1,   148,   149,   150,   151,
     156,   157,   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    61,    62,   530,   531,    -1,    -1,   534,   174,    -1,
      -1,    -1,   539,   540,    -1,   542,    -1,   544,   545,    -1,
      -1,    -1,    -1,   550,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,   463,   464,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     488,    -1,   490,    -1,    -1,    -1,   494,   495,    -1,   596,
      -1,    -1,    -1,    -1,    -1,   503,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   511,    -1,    -1,   156,   157,   158,   109,
     110,   111,   112,   113,   114,   115,    -1,    -1,    -1,    -1,
      -1,    -1,   530,   531,   174,    -1,    -1,    -1,    -1,    -1,
      -1,   539,   540,    -1,   542,    -1,    -1,    -1,    -1,    -1,
      -1,   648,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,    -1,
      -1,   569,    -1,    -1,   671,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   597,
      -1,   599,    -1,    -1,    -1,    -1,    -1,   605,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,   714,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   733,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,   649,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,   772,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,   106,   107,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,   829,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,   743,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,   106,   107,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,   106,   107,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    92,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    90,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    88,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,   174,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,   117,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    26,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    26,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    26,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    26,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    26,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    -1,    89,    -1,    91,    -1,
      -1,    94,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
     103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,   114,    -1,   116,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,   142,
       3,     4,     5,     6,     7,   148,   149,   150,   151,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    -1,   172,
     173,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,    82,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   101,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    63,   117,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,   128,   129,   130,   131,   132,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,   142,
      12,    -1,    -1,    -1,    -1,   148,   149,   150,   151,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,    -1,    -1,    -1,    36,    -1,    -1,   170,    -1,   172,
      42,    43,   175,    -1,    -1,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   101,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    63,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
     142,    12,    -1,    -1,    -1,    -1,   148,   149,   150,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,    -1,    -1,    -1,    36,    -1,    -1,   170,    -1,
     172,    42,    43,   175,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
     101,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    63,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,    -1,    -1,    -1,    -1,    -1,   148,   149,   150,
     151,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
     171,    -1,    -1,    -1,   175,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   101,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    63,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,     3,     4,     5,     6,     7,   148,   149,   150,   151,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,    31,
      -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,   131,
     132,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
     142,    12,    -1,    -1,    -1,    -1,   148,   149,   150,   151,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
     162,    -1,    -1,    -1,    -1,    36,    -1,    -1,   170,    -1,
      -1,    42,    43,   175,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     3,     4,     5,     6,     7,   148,   149,   150,
     151,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
      31,    -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     3,     4,     5,     6,     7,   148,   149,   150,
     151,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
      31,    -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     3,     4,     5,     6,     7,   148,   149,   150,
     151,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
      31,    -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     3,     4,     5,     6,     7,   148,   149,   150,
     151,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
      31,    -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,     3,     4,     5,     6,     7,   148,   149,   150,
     151,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,
      31,    -1,    -1,    -1,   175,    36,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,   142,    12,    -1,    -1,    -1,    -1,   148,   149,   150,
     151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,    -1,    -1,    -1,    36,    -1,    -1,   170,
      -1,    -1,    42,    43,   175,    -1,    -1,    -1,    48,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,
     130,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,   148,   149,
     150,   151,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     170,    -1,    -1,    -1,    25,   175,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,   174,    -1,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,   174,    49,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    25,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   174,    49,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,   174,    49,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
     174,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   174,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
     172,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      25,   172,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    25,   172,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,   172,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    25,   172,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    25,
     171,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,   171,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    25,   171,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    25,   171,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,   171,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    25,   171,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    25,
     171,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,   171,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,   125,
      -1,    -1,   171,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,
     125,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    11,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    63,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    63,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   179,   180,     0,     3,     4,     5,     6,     7,    12,
      36,    42,    43,    48,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    64,    65,    66,
      67,    71,    72,    73,    74,    75,    77,    81,    82,    83,
      84,    85,    87,    89,    91,    94,    98,    99,   100,   101,
     102,   103,   104,   106,   107,   108,   112,   113,   114,   116,
     117,   118,   119,   120,   121,   126,   127,   128,   129,   130,
     131,   132,   135,   136,   137,   142,   148,   149,   150,   151,
     162,   170,   172,   173,   175,   181,   182,   185,   188,   189,
     195,   196,   198,   199,   200,   202,   241,   242,   245,   246,
     254,   257,   261,   262,   264,   265,   269,   270,   271,   272,
     273,   274,   275,   280,   285,   287,   288,   289,   290,   292,
      73,   114,   148,   242,   261,   261,   170,   261,   261,   261,
     305,   306,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   114,   148,   151,   181,
     246,   264,   265,   271,   264,   261,   148,   151,   181,   246,
     248,   249,   271,   273,   274,   280,   170,   252,   170,    26,
     238,   261,   188,   170,   170,   170,   170,   170,   172,   261,
     172,   261,    73,    73,   172,   241,   261,   265,   173,   261,
     151,   181,   183,   184,    75,   175,   225,   226,   120,   120,
      75,   227,   242,   170,   170,   170,   170,   170,   170,   151,
     173,   181,   181,   305,   261,   186,   173,   151,   170,     8,
     172,    26,    73,    73,    31,   197,   145,     9,    10,    11,
      25,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    49,    63,   172,    61,    62,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   170,
     145,   124,    63,   173,   175,   274,   153,   293,   294,   298,
     197,   261,    73,   313,   151,   181,   145,   145,   151,   181,
     145,   170,   253,   145,   124,   274,   171,   261,   261,     8,
     172,    85,   261,   239,   240,   261,   241,   265,    73,   211,
     261,   172,   172,   172,    13,   172,   172,   186,   172,   181,
      93,     8,   172,   173,   262,   265,     8,   172,    13,     8,
     172,   197,   193,   194,   265,   265,   286,   265,   171,   126,
     265,   281,   282,    31,   261,   283,   284,   181,   180,   172,
     173,   170,   171,   119,   174,   187,   188,   195,   196,   261,
      73,    31,   223,   224,   241,   265,    73,   305,   122,   201,
     122,   203,    73,   170,    73,   269,   274,   280,   261,   261,
     261,    26,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   248,   261,   276,    31,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     223,    73,   269,    73,   173,   269,   277,   278,   279,   276,
     261,   153,   154,   155,   173,   288,   291,   295,    37,    46,
     299,   309,   310,   171,   152,   162,   163,   315,   181,    73,
      73,   181,   269,   223,   269,   277,   171,   171,   261,   170,
     171,   172,     8,    93,    93,    13,     8,   171,   171,    42,
      43,   127,   148,   151,   181,   246,   254,   255,   256,   174,
      93,    73,   184,   261,   226,   255,    75,   170,     8,   171,
       8,   171,   171,   172,   170,     8,   171,   263,   265,   125,
     171,     8,   259,   170,   174,   180,   223,   170,   174,   263,
     171,     8,    13,   201,   148,   151,   162,   181,   247,   123,
     204,   205,   247,   173,   170,   127,   220,   221,   222,   247,
     170,   170,   274,   261,    26,   176,    65,   265,   171,   170,
     170,   261,   170,   268,    63,   173,   176,   174,   307,   308,
     296,   293,    37,    13,    73,   314,    73,    73,   171,   250,
      26,   188,   261,    26,   188,   215,   239,   261,   265,    31,
     207,   265,   255,    73,    26,   188,   210,    26,   173,   212,
     255,   255,   170,   151,   181,   145,   105,    73,   174,    13,
     220,   194,   172,   265,   281,   282,    13,    31,   261,    31,
     261,   223,   174,   171,   171,    31,   241,   265,   255,   204,
     151,   181,   305,   205,   173,     8,   228,   220,   171,     8,
      31,    75,   223,   223,   261,   248,   223,   223,   174,   223,
     266,   276,   261,    37,   313,   261,   173,   177,   300,   162,
     163,   315,   124,   251,   186,   216,   171,   186,   172,   125,
     206,   265,   206,    13,   186,   172,   213,   172,   213,   255,
     258,   260,   181,    73,   170,   255,   171,   171,   261,   263,
     263,   125,   171,   172,   263,   173,   181,   228,   247,   102,
     109,   110,   111,   112,   113,   114,   115,   156,   157,   158,
     174,   229,   232,   233,   234,   235,   237,   171,   107,   243,
     222,    75,    13,   171,   171,   253,   171,   171,   171,   124,
     267,   176,   174,   174,   302,   301,    73,    73,   277,   217,
      68,    69,   218,   172,    86,   239,   207,   171,   171,   255,
      92,   213,    95,    96,    97,   213,   174,   125,   171,     8,
     259,   247,   243,    31,   261,   316,   174,    73,   318,   327,
     329,    75,   236,   242,   235,     8,   172,   173,   170,   173,
      31,    75,    13,   255,   277,   297,   261,   293,   304,    68,
      69,   219,   170,   188,   172,   171,    26,   188,   209,   209,
     172,    95,   172,   261,    26,   172,   214,   174,   255,   255,
      75,   173,   263,   228,    13,   115,   162,   164,   165,   166,
     167,   168,   246,   319,   320,   321,    47,   328,   159,   160,
     170,   330,   331,    13,     8,   172,   230,    73,   186,    31,
      75,   244,   186,    75,    13,   255,   268,   303,   177,   170,
      26,    70,   261,    26,   188,   208,   186,   172,   214,   186,
     125,   171,   186,   317,   255,   305,   173,     8,   172,   309,
     305,     8,   172,    47,   159,   161,   162,   331,   332,   333,
     172,   255,    75,   197,    13,   174,    75,     8,   171,   174,
      13,   255,   174,   261,   186,   172,   171,   186,    90,   186,
     255,   173,   174,   174,   322,   320,    13,   325,    47,   311,
     312,   311,     8,    29,   171,    25,    42,    45,    13,    73,
     255,    31,    75,   255,   171,   188,    88,   172,   186,   254,
     324,    73,   254,   169,   326,   305,   313,   332,   332,    25,
      42,    45,   255,   170,    75,    26,   172,   174,     8,   323,
     315,   220,   186,   105,   190,   191,   192,   254,   174,   171,
     170,   192,   172,   173,   231,   247,   186,    75,   174,   171,
     173,   186,   174
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (yyscanner, root, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, yyscanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, yyscanner, root); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* yyscanner, code_rope* root)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yyscanner, root)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void* yyscanner;
    code_rope* root;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yyscanner);
  YYUSE (root);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* yyscanner, code_rope* root)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yyscanner, root)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void* yyscanner;
    code_rope* root;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yyscanner, root);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void* yyscanner, code_rope* root)
#else
static void
yy_reduce_print (yyvsp, yyrule, yyscanner, root)
    YYSTYPE *yyvsp;
    int yyrule;
    void* yyscanner;
    code_rope* root;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , yyscanner, root);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, yyscanner, root); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void* yyscanner, code_rope* root)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yyscanner, root)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void* yyscanner;
    code_rope* root;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yyscanner);
  YYUSE (root);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void* yyscanner, code_rope* root);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void* yyscanner, code_rope* root)
#else
int
yyparse (yyscanner, root)
    void* yyscanner;
    code_rope* root;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 198 "parser.y"
    {
    *root = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 3:
#line 204 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 4:
#line 207 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 6:
#line 214 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 10:
#line 223 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 11:
#line 226 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 12:
#line 229 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + " " + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 13:
#line 232 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 14:
#line 235 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 15:
#line 238 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 16:
#line 244 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 19:
#line 252 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 20:
#line 255 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 21:
#line 258 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + " " + (yyvsp[(3) - (4)]) + " " + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 22:
#line 264 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 23:
#line 267 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + " " + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 24:
#line 273 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 25:
#line 276 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 29:
#line 285 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 31:
#line 292 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 34:
#line 297 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 35:
#line 303 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 36:
#line 306 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (7)]) + (yyvsp[(2) - (7)]) + (yyvsp[(3) - (7)]) + (yyvsp[(4) - (7)]) + (yyvsp[(5) - (7)]) + (yyvsp[(6) - (7)]) + (yyvsp[(7) - (7)]);
  ;}
    break;

  case 37:
#line 309 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (10)]) + (yyvsp[(2) - (10)]) + (yyvsp[(3) - (10)]) + (yyvsp[(4) - (10)]) + (yyvsp[(5) - (10)]) + (yyvsp[(6) - (10)]) + (yyvsp[(7) - (10)]) + (yyvsp[(8) - (10)]) + (yyvsp[(9) - (10)]) + (yyvsp[(10) - (10)]);
  ;}
    break;

  case 38:
#line 312 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 39:
#line 315 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (7)]) + " " + (yyvsp[(2) - (7)]) + (yyvsp[(3) - (7)]) + (yyvsp[(4) - (7)]) + (yyvsp[(5) - (7)]) + (yyvsp[(6) - (7)]) + (yyvsp[(7) - (7)]);
  ;}
    break;

  case 40:
#line 318 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (9)]) + (yyvsp[(2) - (9)]) + (yyvsp[(3) - (9)]) + (yyvsp[(4) - (9)]) + (yyvsp[(5) - (9)]) + (yyvsp[(6) - (9)]) + (yyvsp[(7) - (9)]) + (yyvsp[(8) - (9)]) + (yyvsp[(9) - (9)]);
  ;}
    break;

  case 41:
#line 321 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 42:
#line 324 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 43:
#line 327 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 44:
#line 330 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 45:
#line 333 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 46:
#line 336 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 47:
#line 339 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 48:
#line 342 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 49:
#line 345 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 50:
#line 348 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 51:
#line 351 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 53:
#line 355 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 54:
#line 358 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 55:
#line 361 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (8)]) + (yyvsp[(2) - (8)]) + (yyvsp[(3) - (8)]) + " " + (yyvsp[(4) - (8)]) + " " + (yyvsp[(5) - (8)]) + (yyvsp[(6) - (8)]) + (yyvsp[(7) - (8)]) + (yyvsp[(8) - (8)]);
  ;}
    break;

  case 56:
#line 364 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (8)]) + (yyvsp[(2) - (8)]) + (yyvsp[(3) - (8)]) + " " + (yyvsp[(4) - (8)]) + " " + (yyvsp[(5) - (8)]) + (yyvsp[(6) - (8)]) + (yyvsp[(7) - (8)]) + (yyvsp[(8) - (8)]);
  ;}
    break;

  case 57:
#line 367 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 59:
#line 371 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (13)]) + (yyvsp[(2) - (13)]) + (yyvsp[(3) - (13)]) + (yyvsp[(4) - (13)]) + (yyvsp[(5) - (13)]) + (yyvsp[(6) - (13)]) + (yyvsp[(7) - (13)]) + " " + (yyvsp[(8) - (13)]) + (yyvsp[(9) - (13)]) + (yyvsp[(10) - (13)]) + (yyvsp[(11) - (13)]) + (yyvsp[(12) - (13)]) + (yyvsp[(13) - (13)]);
  ;}
    break;

  case 60:
#line 374 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 61:
#line 377 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 63:
#line 384 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 65:
#line 391 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 66:
#line 397 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (8)]) + (yyvsp[(2) - (8)]) + (yyvsp[(3) - (8)]) + " " + (yyvsp[(4) - (8)]) + (yyvsp[(5) - (8)]) + (yyvsp[(6) - (8)]) + (yyvsp[(7) - (8)]) + (yyvsp[(8) - (8)]);
  ;}
    break;

  case 68:
#line 404 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 72:
#line 422 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 74:
#line 429 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (9)]) + " " + (yyvsp[(2) - (9)]) + (yyvsp[(3) - (9)]) + (yyvsp[(4) - (9)]) + (yyvsp[(5) - (9)]) + (yyvsp[(6) - (9)]) + (yyvsp[(7) - (9)]) + (yyvsp[(8) - (9)]) + (yyvsp[(9) - (9)]);
  ;}
    break;

  case 75:
#line 435 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (7)]) + " " + (yyvsp[(2) - (7)]) + (yyvsp[(3) - (7)]) + (yyvsp[(4) - (7)]) + (yyvsp[(5) - (7)]) + (yyvsp[(6) - (7)]) + (yyvsp[(7) - (7)]);
  ;}
    break;

  case 76:
#line 438 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + " " + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 78:
#line 445 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 79:
#line 448 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 80:
#line 454 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 81:
#line 457 "parser.y"
    {
    (yyval) = " " + (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 83:
#line 467 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 84:
#line 470 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 85:
#line 476 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 86:
#line 479 "parser.y"
    {
    (yyval) = " " + (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 88:
#line 486 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 89:
#line 492 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 90:
#line 495 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 92:
#line 502 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 94:
#line 509 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 96:
#line 516 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 98:
#line 523 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 99:
#line 529 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 100:
#line 532 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 101:
#line 538 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 102:
#line 541 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 103:
#line 544 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 104:
#line 547 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 105:
#line 553 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 106:
#line 556 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + " " + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 107:
#line 559 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 111:
#line 571 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 112:
#line 577 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 113:
#line 580 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 114:
#line 586 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 115:
#line 589 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (7)]) + (yyvsp[(2) - (7)]) + (yyvsp[(3) - (7)]) + (yyvsp[(4) - (7)]) + (yyvsp[(5) - (7)]) + (yyvsp[(6) - (7)]) + (yyvsp[(7) - (7)]);
  ;}
    break;

  case 116:
#line 595 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 117:
#line 598 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 118:
#line 604 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 119:
#line 607 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 121:
#line 614 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 122:
#line 620 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 123:
#line 623 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 124:
#line 626 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 125:
#line 629 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 126:
#line 632 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 127:
#line 635 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 128:
#line 638 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (7)]) + (yyvsp[(2) - (7)]) + (yyvsp[(3) - (7)]) + (yyvsp[(4) - (7)]) + (yyvsp[(5) - (7)]) + (yyvsp[(6) - (7)]) + (yyvsp[(7) - (7)]);
  ;}
    break;

  case 129:
#line 641 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 130:
#line 647 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 131:
#line 650 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (1)]) + " ";
  ;}
    break;

  case 132:
#line 653 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (1)]) + " ";
  ;}
    break;

  case 134:
#line 660 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 137:
#line 668 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 138:
#line 671 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 139:
#line 674 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 140:
#line 677 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 141:
#line 683 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 144:
#line 691 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 145:
#line 694 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 146:
#line 700 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 147:
#line 703 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 149:
#line 707 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 150:
#line 713 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 151:
#line 716 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 152:
#line 722 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 153:
#line 725 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 154:
#line 728 "parser.y"
    {
    yyextra->old_expecting_xhp_class_statements = yyextra->expecting_xhp_class_statements;
    yyextra->expecting_xhp_class_statements = false;
  ;}
    break;

  case 155:
#line 731 "parser.y"
    {
    yyextra->expecting_xhp_class_statements = yyextra->old_expecting_xhp_class_statements;
    (yyval) = (yyvsp[(1) - (9)]) + (yyvsp[(2) - (9)]) + " " + (yyvsp[(4) - (9)]) + (yyvsp[(5) - (9)]) + (yyvsp[(6) - (9)]) + (yyvsp[(7) - (9)]) + (yyvsp[(8) - (9)]) + (yyvsp[(9) - (9)]);
  ;}
    break;

  case 157:
#line 739 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 159:
#line 746 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (1)]) + " ";
  ;}
    break;

  case 160:
#line 752 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 161:
#line 755 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (1)]) + " ";
  ;}
    break;

  case 163:
#line 762 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 170:
#line 777 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 171:
#line 780 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 173:
#line 784 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 174:
#line 790 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 175:
#line 793 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + " " + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 176:
#line 799 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 178:
#line 806 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 180:
#line 814 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 182:
#line 821 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 183:
#line 824 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 184:
#line 827 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 185:
#line 830 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + " " + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 186:
#line 833 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 187:
#line 836 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 188:
#line 839 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 189:
#line 842 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 190:
#line 845 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 191:
#line 848 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 192:
#line 851 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 193:
#line 854 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 194:
#line 857 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 195:
#line 860 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 196:
#line 863 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 197:
#line 866 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 198:
#line 869 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 199:
#line 872 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 200:
#line 875 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 201:
#line 878 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 202:
#line 881 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 203:
#line 884 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 204:
#line 887 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 205:
#line 890 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 206:
#line 893 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 207:
#line 896 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 208:
#line 899 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 209:
#line 902 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 210:
#line 905 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 211:
#line 908 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 212:
#line 911 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 213:
#line 914 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 214:
#line 917 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 215:
#line 920 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 216:
#line 923 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 217:
#line 926 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 218:
#line 929 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 219:
#line 932 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 220:
#line 935 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 221:
#line 938 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 222:
#line 941 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 223:
#line 944 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 224:
#line 947 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 225:
#line 950 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 226:
#line 953 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 227:
#line 956 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 228:
#line 959 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 229:
#line 962 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 230:
#line 965 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 231:
#line 968 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + " " + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 232:
#line 971 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 233:
#line 974 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 234:
#line 977 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 236:
#line 981 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 237:
#line 984 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 238:
#line 987 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 239:
#line 990 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 240:
#line 993 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 241:
#line 996 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 242:
#line 999 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 243:
#line 1002 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 244:
#line 1005 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 245:
#line 1008 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 246:
#line 1011 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 248:
#line 1015 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 250:
#line 1019 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 251:
#line 1022 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (9)]) + (yyvsp[(2) - (9)]) + (yyvsp[(3) - (9)]) + (yyvsp[(4) - (9)]) + (yyvsp[(5) - (9)]) + (yyvsp[(6) - (9)]) + (yyvsp[(7) - (9)]) + (yyvsp[(8) - (9)]) + (yyvsp[(9) - (9)]);
  ;}
    break;

  case 252:
#line 1025 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (10)]) + " " + (yyvsp[(2) - (10)]) + (yyvsp[(3) - (10)]) + (yyvsp[(4) - (10)]) + (yyvsp[(5) - (10)]) + (yyvsp[(6) - (10)]) + (yyvsp[(7) - (10)]) + (yyvsp[(8) - (10)]) + (yyvsp[(9) - (10)]) + (yyvsp[(10) - (10)]);
  ;}
    break;

  case 255:
#line 1036 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 256:
#line 1042 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 257:
#line 1045 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 259:
#line 1049 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 260:
#line 1055 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 261:
#line 1058 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 262:
#line 1061 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 263:
#line 1064 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 264:
#line 1067 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 265:
#line 1070 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 266:
#line 1073 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 267:
#line 1076 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 270:
#line 1084 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 271:
#line 1087 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 273:
#line 1094 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 274:
#line 1097 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 277:
#line 1108 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 279:
#line 1115 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 280:
#line 1118 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 281:
#line 1124 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 282:
#line 1130 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 283:
#line 1133 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 284:
#line 1136 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 285:
#line 1142 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 286:
#line 1145 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 300:
#line 1167 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 301:
#line 1170 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 302:
#line 1173 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 303:
#line 1176 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 304:
#line 1179 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 306:
#line 1186 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 310:
#line 1195 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 311:
#line 1198 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 313:
#line 1205 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 315:
#line 1212 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 317:
#line 1219 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 318:
#line 1222 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 319:
#line 1225 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 326:
#line 1249 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 328:
#line 1256 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 329:
#line 1259 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 330:
#line 1265 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 331:
#line 1271 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 332:
#line 1274 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 334:
#line 1281 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 335:
#line 1287 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 336:
#line 1290 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 341:
#line 1306 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 343:
#line 1313 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 344:
#line 1316 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]);
  ;}
    break;

  case 347:
#line 1324 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 348:
#line 1330 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 352:
#line 1342 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 353:
#line 1345 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 356:
#line 1353 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 358:
#line 1360 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 359:
#line 1366 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 362:
#line 1374 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 363:
#line 1377 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 364:
#line 1383 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 366:
#line 1390 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (5)]) + (yyvsp[(2) - (5)]) + (yyvsp[(3) - (5)]) + (yyvsp[(4) - (5)]) + (yyvsp[(5) - (5)]);
  ;}
    break;

  case 367:
#line 1393 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 368:
#line 1396 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 370:
#line 1400 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (6)]) + (yyvsp[(2) - (6)]) + (yyvsp[(3) - (6)]) + (yyvsp[(4) - (6)]) + (yyvsp[(5) - (6)]) + (yyvsp[(6) - (6)]);
  ;}
    break;

  case 371:
#line 1403 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 372:
#line 1406 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 373:
#line 1409 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 374:
#line 1415 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 375:
#line 1418 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 376:
#line 1421 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 377:
#line 1424 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 378:
#line 1427 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
  ;}
    break;

  case 379:
#line 1430 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 380:
#line 1433 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + " " + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 382:
#line 1440 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 383:
#line 1446 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 384:
#line 1449 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 385:
#line 1459 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (1)]);
    yyextra->used = true;
  ;}
    break;

  case 387:
#line 1467 "parser.y"
    {
    if (yyextra->include_debug) {
      char line[16];
      sprintf(line, "%lu", (unsigned long)(yyvsp[(1) - (3)]).lineno());
      (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + "), __FILE__, " + line +")";
    } else {
      (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + "))";
    }
  ;}
    break;

  case 388:
#line 1479 "parser.y"
    {
    pop_state(); // XHP_ATTRS
    if (yyextra->include_debug) {
      char line[16];
      sprintf(line, "%lu", (unsigned long)(yyvsp[(1) - (4)]).lineno());
      (yyval) = "new xhp_" + (yyvsp[(1) - (4)]) + "(array(" + (yyvsp[(2) - (4)]) + "), array(), __FILE__, " + line + ")";
    } else {
      (yyval) = "new xhp_" + (yyvsp[(1) - (4)]) + "(array(" + (yyvsp[(2) - (4)]) + "), array())";
    }
  ;}
    break;

  case 389:
#line 1492 "parser.y"
    {
    pop_state(); // XHP_ATTRS
    push_state(XHP_CHILD_START);
    yyextra->pushTag((yyvsp[(1) - (3)]).c_str());
    (yyval) = "new xhp_" + (yyvsp[(1) - (3)]) + "(array(" + (yyvsp[(2) - (3)]) + "), array(";
  ;}
    break;

  case 390:
#line 1501 "parser.y"
    {
    pop_state(); // XHP_CHILD_START
    if (yyextra->peekTag() != (yyvsp[(2) - (3)]).c_str()) {
      string e1 = (yyvsp[(2) - (3)]).c_str();
      string e2 = yyextra->peekTag();
      replacestr(e1, "__", ":");
      replacestr(e1, "_", "-");
      replacestr(e2, "__", ":");
      replacestr(e2, "_", "-");
      string e = "syntax error, mismatched tag </" + e1 + ">, expecting </" + e2 +">";
      yyerror(yyscanner, NULL, e.c_str());
      yyextra->terminated = true;
    }
    yyextra->popTag();
    if (yyextra->haveTag()) {
      set_state(XHP_CHILD_START);
    }
  ;}
    break;

  case 391:
#line 1519 "parser.y"
    {
    // empty end tag -- SGML SHORTTAG
    pop_state(); // XHP_CHILD_START
    yyextra->popTag();
    if (yyextra->haveTag()) {
      set_state(XHP_CHILD_START);
    }
    (yyval) = "))";
  ;}
    break;

  case 392:
#line 1531 "parser.y"
    {
    (yyval) = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 394:
#line 1539 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 395:
#line 1545 "parser.y"
    {
    (yyval) = "";
  ;}
    break;

  case 396:
#line 1548 "parser.y"
    {
    set_state(XHP_CHILD_START);
    (yyval) = "'" + (yyvsp[(1) - (1)]) + "',";
  ;}
    break;

  case 397:
#line 1552 "parser.y"
    {
    set_state(XHP_CHILD_START);
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]) + ",";
  ;}
    break;

  case 398:
#line 1556 "parser.y"
    {
    set_state(XHP_CHILD_START);
    (yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(2) - (3)]) + ",'" + (yyvsp[(3) - (3)]) + "',";
  ;}
    break;

  case 400:
#line 1564 "parser.y"
    {
    push_state(PHP);
    yyextra->pushStack();
  ;}
    break;

  case 401:
#line 1567 "parser.y"
    {
    pop_state();
    yyextra->popStack();
  ;}
    break;

  case 402:
#line 1570 "parser.y"
    {
    set_state(XHP_CHILD_START);
    (yyval) = (yyvsp[(3) - (5)]);
  ;}
    break;

  case 403:
#line 1578 "parser.y"
    {
    (yyval) = "";
    push_state(XHP_ATTRS);
  ;}
    break;

  case 404:
#line 1582 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (2)]) + (yyvsp[(2) - (2)]) + ",";
  ;}
    break;

  case 405:
#line 1588 "parser.y"
    {
    (yyval) = "'" + (yyvsp[(1) - (3)]) + "' => " + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 406:
#line 1594 "parser.y"
    { push_state(XHP_ATTR_VAL); ;}
    break;

  case 407:
#line 1594 "parser.y"
    {
    (yyval) = (yyvsp[(3) - (4)]);
  ;}
    break;

  case 408:
#line 1597 "parser.y"
    { push_state(PHP); ;}
    break;

  case 409:
#line 1597 "parser.y"
    { pop_state(); ;}
    break;

  case 410:
#line 1597 "parser.y"
    {
    (yyval) = (yyvsp[(3) - (5)]);
  ;}
    break;

  case 411:
#line 1603 "parser.y"
    {
    (yyval) = "''";
  ;}
    break;

  case 412:
#line 1606 "parser.y"
    {
    // XHP_ATTR_VAL is popped by the time this code runs
    (yyval) = "'" + (yyvsp[(1) - (1)]) + "'";
  ;}
    break;

  case 413:
#line 1614 "parser.y"
    { push_state(XHP_LABEL); ;}
    break;

  case 414:
#line 1614 "parser.y"
    {
    pop_state();
    (yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 415:
#line 1621 "parser.y"
    { push_state(XHP_LABEL); ;}
    break;

  case 416:
#line 1621 "parser.y"
    {
    pop_state();
    (yyval) = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 417:
#line 1628 "parser.y"
    { push_state(XHP_LABEL_WHITESPACE); ;}
    break;

  case 418:
#line 1628 "parser.y"
    {
    pop_state();
    (yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 419:
#line 1635 "parser.y"
    { push_state(XHP_LABEL_WHITESPACE); ;}
    break;

  case 420:
#line 1635 "parser.y"
    {
    pop_state();
    (yyval) = (yyvsp[(2) - (3)]);
  ;}
    break;

  case 421:
#line 1642 "parser.y"
    {
    // XHP_LABEL is popped in the scanner on " ", ">", "/", or "="
    push_state(XHP_LABEL);
    (yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 422:
#line 1647 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + "__" + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 423:
#line 1650 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + "_" + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 424:
#line 1656 "parser.y"
    {
    // XHP_LABEL is popped in the scanner on " ", ">", "/", or "="
    push_state(XHP_LABEL);
    (yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 425:
#line 1661 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + ":" + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 426:
#line 1664 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (3)]) + "-" + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 429:
#line 1676 "parser.y"
    {
    yyextra->expecting_xhp_class_statements = true;
    yyextra->attribute_decls = "";
    yyextra->attribute_inherit = "";
    yyextra->used_attributes = false;
  ;}
    break;

  case 430:
#line 1681 "parser.y"
    {
    yyextra->expecting_xhp_class_statements = false;
  ;}
    break;

  case 431:
#line 1683 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (10)]) + " xhp_" + (yyvsp[(3) - (10)]) + (yyvsp[(4) - (10)]) + (yyvsp[(5) - (10)]) + (yyvsp[(6) - (10)]) + (yyvsp[(8) - (10)]);
    if (yyextra->used_attributes) {
      (yyval) = (yyval) +
        "protected static function &__xhpAttributeDeclaration() {" +
          "static $_ = -1;" +
          "if ($_ === -1) {" +
            "$_ = array_merge(parent::__xhpAttributeDeclaration(), " +
              yyextra->attribute_inherit +
              "array(" + yyextra->attribute_decls + "));" +
          "}" +
          "return $_;"
        "}";
    }
    (yyval) = (yyval) + (yyvsp[(10) - (10)]);
    yyextra->used = true;
  ;}
    break;

  case 432:
#line 1704 "parser.y"
    { push_state(XHP_ATTR_TYPE_DECL); ;}
    break;

  case 433:
#line 1704 "parser.y"
    {
    pop_state();
    yyextra->used = true;
    yyextra->used_attributes = true;
    (yyval) = ""; // this will be injected when the class closes
  ;}
    break;

  case 434:
#line 1713 "parser.y"
    {;}
    break;

  case 435:
#line 1714 "parser.y"
    {;}
    break;

  case 436:
#line 1718 "parser.y"
    {
    (yyvsp[(2) - (4)]).strip_lines();
    yyextra->attribute_decls = yyextra->attribute_decls +
      "'" + (yyvsp[(2) - (4)]) + "'=>array(" + (yyvsp[(1) - (4)]) + "," + (yyvsp[(3) - (4)]) + ", " + (yyvsp[(4) - (4)]) + "),"
  ;}
    break;

  case 437:
#line 1723 "parser.y"
    {
    (yyvsp[(2) - (2)]).strip_lines();
    yyextra->attribute_inherit = yyextra->attribute_inherit +
      "xhp_" + (yyvsp[(2) - (2)]) + "::__xhpAttributeDeclaration(),";
  ;}
    break;

  case 438:
#line 1731 "parser.y"
    {
    (yyval) = "1, null";
  ;}
    break;

  case 439:
#line 1734 "parser.y"
    {
    (yyval) = "2, null";
  ;}
    break;

  case 440:
#line 1737 "parser.y"
    {
    (yyval) = "3, null";
  ;}
    break;

  case 441:
#line 1740 "parser.y"
    {
    (yyval) = "4, null";
  ;}
    break;

  case 442:
#line 1743 "parser.y"
    {
    (yyval) = "5, '" + (yyvsp[(1) - (1)]) + "'";
  ;}
    break;

  case 443:
#line 1746 "parser.y"
    {
    (yyval) = "6, null";
  ;}
    break;

  case 444:
#line 1749 "parser.y"
    { push_state(PHP); ;}
    break;

  case 445:
#line 1749 "parser.y"
    { pop_state(); ;}
    break;

  case 446:
#line 1749 "parser.y"
    {
    (yyval) = "7, array(" + (yyvsp[(4) - (6)]) + ")";
  ;}
    break;

  case 447:
#line 1755 "parser.y"
    {
    (yyvsp[(1) - (1)]).strip_lines();
    (yyval) = (yyvsp[(1) - (1)]);
  ;}
    break;

  case 448:
#line 1759 "parser.y"
    {
    (yyvsp[(3) - (3)]).strip_lines();
    (yyval) = (yyvsp[(1) - (3)]) + ", " + (yyvsp[(3) - (3)]);
  ;}
    break;

  case 449:
#line 1766 "parser.y"
    {
    (yyvsp[(2) - (2)]).strip_lines();
    (yyval) = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 450:
#line 1770 "parser.y"
    {
    (yyvsp[(2) - (2)]).strip_lines();
    (yyval) = (yyvsp[(2) - (2)]);
  ;}
    break;

  case 451:
#line 1774 "parser.y"
    {
    (yyval) = "null";
  ;}
    break;

  case 452:
#line 1780 "parser.y"
    {
    (yyval) = "1";
  ;}
    break;

  case 453:
#line 1783 "parser.y"
    {
    (yyval) = "0";
  ;}
    break;

  case 454:
#line 1790 "parser.y"
    { push_state(PHP_NO_RESERVED_WORDS_PERSIST); ;}
    break;

  case 455:
#line 1790 "parser.y"
    {
    pop_state();
    yyextra->used = true;
    (yyval) =
      "protected function &__xhpCategoryDeclaration() {\
         static $_ = array(" + (yyvsp[(3) - (4)]) + ");" +
        "return $_;" +
      "}";
  ;}
    break;

  case 456:
#line 1802 "parser.y"
    {
    (yyval) = "'" + (yyvsp[(2) - (2)]) + "' => 1";
  ;}
    break;

  case 457:
#line 1805 "parser.y"
    {
    (yyval) = (yyvsp[(1) - (4)]) + ",'" + (yyvsp[(4) - (4)]) + "' => 1";
  ;}
    break;

  case 458:
#line 1812 "parser.y"
    { push_state(XHP_CHILDREN_DECL); ;}
    break;

  case 459:
#line 1812 "parser.y"
    {
    // XHP_CHILDREN_DECL is popped in the scanner on ';'
    yyextra->used = true;
    (yyval) = "protected function &__xhpChildrenDeclaration() {" + (yyvsp[(3) - (4)]) + "}";
  ;}
    break;

  case 460:
#line 1820 "parser.y"
    {
    (yyval) = "static $_ = " + (yyvsp[(1) - (1)]) + "; return $_;";
  ;}
    break;

  case 461:
#line 1823 "parser.y"
    {
    (yyval) = "static $_ = 1; return $_;";
  ;}
    break;

  case 462:
#line 1826 "parser.y"
    {
    (yyval) = "static $_ = 0; return $_;";
  ;}
    break;

  case 463:
#line 1832 "parser.y"
    {
    (yyval) = "array(0, 5, " + (yyvsp[(2) - (3)]) + ")";
  ;}
    break;

  case 464:
#line 1835 "parser.y"
    {
    (yyval) = "array(1, 5, " + (yyvsp[(2) - (4)]) + ")";
  ;}
    break;

  case 465:
#line 1838 "parser.y"
    {
    (yyval) = "array(2, 5, " + (yyvsp[(2) - (4)]) + ")";
  ;}
    break;

  case 466:
#line 1841 "parser.y"
    {
    (yyval) = "array(3, 5, " + (yyvsp[(2) - (4)]) + ")";
  ;}
    break;

  case 468:
#line 1848 "parser.y"
    {
    (yyval) = "array(0, " + (yyvsp[(1) - (1)]) + ")";
  ;}
    break;

  case 469:
#line 1851 "parser.y"
    {
    (yyval) = "array(1, " + (yyvsp[(1) - (2)]) + ")";
  ;}
    break;

  case 470:
#line 1854 "parser.y"
    {
    (yyval) = "array(2, " + (yyvsp[(1) - (2)]) + ")";
  ;}
    break;

  case 471:
#line 1857 "parser.y"
    {
    (yyval) = "array(3, " + (yyvsp[(1) - (2)]) + ")";
  ;}
    break;

  case 472:
#line 1860 "parser.y"
    {
    (yyval) = "array(4, " + (yyvsp[(1) - (3)]) + "," + (yyvsp[(3) - (3)]) + ")"
  ;}
    break;

  case 473:
#line 1863 "parser.y"
    {
    (yyval) = "array(5, " + (yyvsp[(1) - (3)]) + "," + (yyvsp[(3) - (3)]) + ")"
  ;}
    break;

  case 474:
#line 1869 "parser.y"
    {
    (yyval) = "1, null";
  ;}
    break;

  case 475:
#line 1872 "parser.y"
    {
    (yyval) = "2, null";
  ;}
    break;

  case 476:
#line 1875 "parser.y"
    {
    (yyval) = "3, \'xhp_" + (yyvsp[(2) - (2)]) + "\'";
  ;}
    break;

  case 477:
#line 1878 "parser.y"
    {
    (yyval) = "4, \'" + (yyvsp[(2) - (2)]) + "\'";
  ;}
    break;

  case 478:
#line 1885 "parser.y"
    {
    pop_state();
    push_state(PHP);
    yyextra->used = true;
    (yyval) = "xhp_" + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 479:
#line 1894 "parser.y"
    {
    pop_state();
    push_state(PHP);
    yyextra->used = true;
    (yyval) = "xhp_" + (yyvsp[(2) - (2)]);
  ;}
    break;

  case 480:
#line 1908 "parser.y"
    {
    if (yyextra->idx_expr) {
      yyextra->used = true;
      (yyval) = "__xhp_idx(" + (yyvsp[(1) - (4)]) + ", " + (yyvsp[(3) - (4)]) + ")";
    } else {
      (yyval) = (yyvsp[(1) - (4)]) + (yyvsp[(2) - (4)]) + (yyvsp[(3) - (4)]) + (yyvsp[(4) - (4)]);
    }
  ;}
    break;


/* Line 1267 of yacc.c.  */
#line 6603 "parser.yacc.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (yyscanner, root, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yyscanner, root, yymsg);
	  }
	else
	  {
	    yyerror (yyscanner, root, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, yyscanner, root);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yyscanner, root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (yyscanner, root, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, yyscanner, root);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yyscanner, root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1919 "parser.y"


const char* yytokname(int tok) {
  if (tok < 255) {
    return NULL;
  }
  return yytname[YYTRANSLATE(tok)];
}

