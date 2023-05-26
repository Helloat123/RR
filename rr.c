/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "rr.y"

	#include <stdio.h>
	#include <string.h>
	#include "genpcode.h"
	int yylex(void);
	FILE *yyin;
	int yyerror(char*);
	extern int yylineno;
	extern char* yytext;
	#define MAXLOOP 16
	int cx1[MAXLOOP];//if的嵌套栈
	int cx1count=0;
	int cx2[MAXLOOP];//while的嵌套栈
	int cx2count=0;
	int cx3[MAXLOOP];//回标for语句中jpc用.每三条语句为一组，组内第一个记录for中第二个表达式之前的位置，第二个记录第二个表达式之后的位置，第三个记录stmt结束位置
	int cx3count=0;
	int cx4[MAXLOOP];//do while的嵌套栈
	int cx4count=0;
	int cx5[MAXLOOP];//repeat until的嵌套栈
	int cx5count=0;
	char error_info[1024];
	int var_cnt=0;

#line 94 "rr.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_RR_H_INCLUDED
# define YY_YY_RR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    RELOP = 260,
    INT = 261,
    BOOL = 262,
    CONST = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    DO = 267,
    FOR = 268,
    REPEAT = 269,
    UNTIL = 270,
    WRITE = 271,
    READ = 272,
    PLUS = 273,
    MINUS = 274,
    TIMES = 275,
    DIVIDES = 276,
    COMPLEMENT = 277,
    ODD = 278,
    XOR = 279,
    SPLUS = 280,
    SMINUS = 281,
    ASSIGN = 282,
    OR = 283,
    AND = 284,
    NOT = 285,
    SEMI = 286,
    LP = 287,
    RP = 288,
    LB = 289,
    RB = 290,
    LETTER = 291,
    DIGIT = 292,
    BLANK = 293,
    ANNO = 294,
    TRUE = 295,
    FALSE = 296
  };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define RELOP 260
#define INT 261
#define BOOL 262
#define CONST 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define DO 267
#define FOR 268
#define REPEAT 269
#define UNTIL 270
#define WRITE 271
#define READ 272
#define PLUS 273
#define MINUS 274
#define TIMES 275
#define DIVIDES 276
#define COMPLEMENT 277
#define ODD 278
#define XOR 279
#define SPLUS 280
#define SMINUS 281
#define ASSIGN 282
#define OR 283
#define AND 284
#define NOT 285
#define SEMI 286
#define LP 287
#define RP 288
#define LB 289
#define RB 290
#define LETTER 291
#define DIGIT 292
#define BLANK 293
#define ANNO 294
#define TRUE 295
#define FALSE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "rr.y"

	int var;
	char* name;

#line 233 "rr.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RR_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    35,    35,    35,    42,    43,    42,    49,    49,    52,
      57,    62,    67,    72,    79,    79,    82,   106,   130,   134,
     130,   138,   141,   144,   138,   149,   149,   189,   196,   189,
     203,   210,   203,   217,   221,   227,   240,   252,   255,   255,
     262,   271,   274,   277,   280,   281,   286,   289,   292,   295,
     298,   309,   312,   317,   320,   321,   326,   329,   332,   342,
     345,   348,   351,   354,   357,   360,   378
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "RELOP", "INT", "BOOL",
  "CONST", "IF", "ELSE", "WHILE", "DO", "FOR", "REPEAT", "UNTIL", "WRITE",
  "READ", "PLUS", "MINUS", "TIMES", "DIVIDES", "COMPLEMENT", "ODD", "XOR",
  "SPLUS", "SMINUS", "ASSIGN", "OR", "AND", "NOT", "SEMI", "LP", "RP",
  "LB", "RB", "LETTER", "DIGIT", "BLANK", "ANNO", "TRUE", "FALSE",
  "$accept", "program", "$@1", "block", "$@2", "$@3", "decls", "decl",
  "stmts", "stmt", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "elses", "$@14", "aexpr", "aterm", "afactor",
  "bexpr", "bterm", "bfactor", "rel", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF (-54)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -54,     8,   -13,   -54,   -54,   -54,   -54,   123,    30,    32,
      53,   -54,   -54,     7,    22,    36,    38,    92,   -54,   -54,
      55,    60,   107,    68,   -54,   -54,    75,   -54,    15,   106,
     -54,   -54,   -54,   117,    27,    94,   110,     3,     9,   111,
      11,   138,    11,   -54,   118,    15,    54,   115,   -54,   113,
     116,   120,   121,   -54,   -54,   141,    70,    26,    51,     3,
     -54,   -54,    93,   -14,   124,   -54,   -54,   141,     4,     9,
     -17,     9,   137,   122,   135,    15,    46,    26,    26,    26,
     -54,    26,    26,    26,   -54,   -54,   -54,   -54,    15,    15,
       3,   -54,   -54,   149,   -54,    43,   -54,    51,   -54,    51,
       9,   -54,    56,   125,    15,   126,    33,   -54,   115,   115,
     115,   -54,   -54,   -54,    33,    33,   127,   -54,   124,   -54,
      11,   -54,     9,    97,     9,   -54,    11,    85,   -54,    86,
     146,   -54,   -54,   119,   -54,   -54,   128,   129,   130,   149,
     131,   132,    11,   -54,   -54,   -54,   -54,   -54,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     4,     3,     8,     5,     0,     0,
       0,    15,     7,     0,     0,     0,     0,     0,     9,    10,
       0,     0,     0,     0,    21,    27,     0,    30,     0,     0,
       6,    37,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    50,     0,     0,    44,    49,     0,
       0,     0,     0,    35,    36,    51,    50,     0,     0,     0,
      59,    60,     0,     0,    54,    57,    64,     0,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,    34,    11,    12,    13,     0,     0,
       0,    50,    62,    58,    61,     0,    16,     0,    17,     0,
       0,    18,     0,     0,     0,     0,    45,    52,    41,    42,
      43,    46,    47,    48,    66,    65,    55,    63,    53,    56,
       0,    22,     0,     0,     0,    19,     0,     0,    25,     0,
      40,    23,    28,     0,    31,    38,     0,     0,     0,     0,
       0,     0,     0,    20,    24,    29,    26,    32,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -54,   162,   -54,   -54,   -54,   -54,   -54,   -40,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -27,    61,    12,   -34,    69,   -53,    34
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    31,     6,    11,     7,    12,    17,    32,
     120,   130,    39,   126,   137,   133,    40,   138,    42,   141,
     136,   142,    76,    47,    48,    95,    64,    65,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    46,    74,    63,    70,    94,    55,    56,     3,    89,
      62,    97,    67,    68,    97,    22,   101,    98,    43,    44,
      23,     4,    24,    25,    26,    27,    57,    28,    29,    43,
      91,   100,    57,    58,    13,    59,    14,   102,    18,    58,
      20,    69,    21,    60,    61,     4,   119,    45,   106,    60,
      61,    77,    78,    19,    67,    93,   116,    79,    45,    15,
      16,   114,   115,   106,    77,    78,   116,    51,    52,    92,
      79,    97,    77,    78,    57,    89,   117,   123,    79,   107,
     125,    58,    33,    69,    97,    80,   131,    34,   127,   121,
     129,    60,    61,   111,   112,   113,    22,    90,   -58,   -58,
      38,    23,   148,    24,    25,    26,    27,    41,    28,    29,
      49,    77,    78,    97,    97,    77,    78,    79,   132,   134,
      50,    79,    67,   139,    96,    53,     4,    30,   128,     8,
       9,    10,    35,    36,    37,    81,    82,    83,   108,   109,
     110,    54,    73,    71,    84,    75,    88,    85,   103,   104,
     105,    86,    87,    99,    89,    97,   135,   122,   124,   143,
     144,   145,   146,   147,     5,     0,   118,   140
};

static const yytype_int16 yycheck[] =
{
      40,    28,    42,    37,    38,    58,     3,     4,     0,     5,
      37,    28,     3,     4,    28,     4,    33,    31,     3,     4,
       9,    34,    11,    12,    13,    14,    23,    16,    17,     3,
       4,    27,    23,    30,     4,    32,     4,    71,    31,    30,
       4,    32,     4,    40,    41,    34,    99,    32,    75,    40,
      41,    18,    19,    31,     3,     4,    90,    24,    32,     6,
       7,    88,    89,    90,    18,    19,   100,    40,    41,    57,
      24,    28,    18,    19,    23,     5,    33,   104,    24,    33,
     120,    30,    27,    32,    28,    31,   126,    27,   122,    33,
     124,    40,    41,    81,    82,    83,     4,    27,    28,    29,
      32,     9,   142,    11,    12,    13,    14,    32,    16,    17,
       4,    18,    19,    28,    28,    18,    19,    24,    33,    33,
       3,    24,     3,     4,    31,    31,    34,    35,    31,     6,
       7,     8,    25,    26,    27,    20,    21,    22,    77,    78,
      79,    31,     4,    32,    31,    27,     5,    31,    11,    27,
      15,    31,    31,    29,     5,    28,    10,    32,    32,    31,
      31,    31,    31,    31,     2,    -1,    97,   133
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    44,     0,    34,    45,    46,    48,     6,     7,
       8,    47,    49,     4,     4,     6,     7,    50,    31,    31,
       4,     4,     4,     9,    11,    12,    13,    14,    16,    17,
      35,    45,    51,    27,    27,    25,    26,    27,    32,    54,
      58,    32,    60,     3,     4,    32,    64,    65,    66,     4,
       3,    40,    41,    31,    31,     3,     4,    23,    30,    32,
      40,    41,    64,    67,    68,    69,    70,     3,     4,    32,
      67,    32,    51,     4,    51,    27,    64,    18,    19,    24,
      31,    20,    21,    22,    31,    31,    31,    31,     5,     5,
      27,     4,    66,     4,    69,    67,    31,    28,    31,    29,
      27,    33,    67,    11,    27,    15,    64,    33,    65,    65,
      65,    66,    66,    66,    64,    64,    67,    33,    68,    69,
      52,    33,    32,    64,    32,    51,    55,    67,    31,    67,
      53,    51,    33,    57,    33,    10,    62,    56,    59,     4,
      70,    61,    63,    31,    31,    31,    31,    31,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    44,    43,    46,    47,    45,    48,    48,    49,
      49,    49,    49,    49,    50,    50,    51,    51,    52,    53,
      51,    54,    55,    56,    51,    57,    51,    58,    59,    51,
      60,    61,    51,    51,    51,    51,    51,    51,    63,    62,
      62,    64,    64,    64,    64,    64,    65,    65,    65,    65,
      66,    66,    66,    67,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     0,     6,     2,     0,     3,
       3,     6,     6,     6,     2,     0,     4,     4,     0,     0,
       9,     0,     0,     0,     9,     0,     9,     0,     0,     9,
       0,     0,     9,     3,     3,     3,     3,     1,     0,     3,
       0,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       1,     2,     2,     3,     1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 35 "rr.y"
                {
		gen(jmp,0,1);
	}
#line 1508 "rr.c"
    break;

  case 3:
#line 37 "rr.y"
              {
		gen(opr,0,0);
	}
#line 1516 "rr.c"
    break;

  case 4:
#line 42 "rr.y"
                 {
	}
#line 1523 "rr.c"
    break;

  case 5:
#line 43 "rr.y"
              {
		if (var_cnt) gen(inn,0,var_cnt);
		var_cnt=0;
	}
#line 1532 "rr.c"
    break;

  case 9:
#line 52 "rr.y"
                         {
		id=(yyvsp[-1].name);
		var_cnt++;
		enter(variable,int_t); //into id table
	}
#line 1542 "rr.c"
    break;

  case 10:
#line 57 "rr.y"
                    {
		id=(yyvsp[-1].name);
		var_cnt++;
		enter(variable,bool_t);
	}
#line 1552 "rr.c"
    break;

  case 11:
#line 62 "rr.y"
                                    {
		id=(yyvsp[-3].name);
		temp_num=(yyvsp[-1].var);
		enter(constant,int_t);
	}
#line 1562 "rr.c"
    break;

  case 12:
#line 67 "rr.y"
                                      {
		id=(yyvsp[-3].name);
		temp_num=1;
		enter(constant,bool_t);
	}
#line 1572 "rr.c"
    break;

  case 13:
#line 72 "rr.y"
                                       {
		id=(yyvsp[-3].name);
		temp_num=0;
		enter(constant,bool_t);
	}
#line 1582 "rr.c"
    break;

  case 16:
#line 82 "rr.y"
                                  {
		//<aid> = <aexpr>
		int t=position((yyvsp[-3].name));
		if (t>0){
			if (table[t].kind!=variable)
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s must be a variable!",(yyvsp[-3].name));
				yyerror(error_info);
			}
			else if (table[t].type!=int_t) 
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s and the expression is not the same type!",(yyvsp[-3].name));
				yyerror(error_info);
			}
			gen(sto,0,getaddr(t));
		}
		else{
			strcpy (error_info,"");
			sprintf(error_info,"The variable %s does not exist!",(yyvsp[-3].name));
			yyerror(error_info);
		}
	}
#line 1611 "rr.c"
    break;

  case 17:
#line 106 "rr.y"
                            {
		//<bid> = <bexpr>
		int t=position((yyvsp[-3].name));
		if (t>0){
			if(table[t].kind!=variable)
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s must be a variable!",(yyvsp[-3].name));
				yyerror(error_info);
			}
			else if (table[t].type!=bool_t) 
			{
				strcpy (error_info,"");
				sprintf(error_info,"The identifier %s and the expression is not the same type!",(yyvsp[-3].name));
				yyerror(error_info);
			}
			gen(sto,0,getaddr(t));
		}
		else{
			strcpy (error_info,"");
			sprintf(error_info,"The variable %s does not exist!",(yyvsp[-3].name));
			yyerror(error_info);
		}
	}
#line 1640 "rr.c"
    break;

  case 18:
#line 130 "rr.y"
                       {
		//if (<bexpr>) <stmt>
		cx1[cx1count++]=code_cnt;
		gen(jpc,0,0);
	}
#line 1650 "rr.c"
    break;

  case 19:
#line 134 "rr.y"
              {
		cx1[cx1count++]=code_cnt;
		gen(jmp,0,0);
	}
#line 1659 "rr.c"
    break;

  case 21:
#line 138 "rr.y"
              {
		//while (<bexpr>) <stmt>
		cx2[cx2count++]=code_cnt;
	}
#line 1668 "rr.c"
    break;

  case 22:
#line 141 "rr.y"
                     {
		cx2[cx2count++]=code_cnt;
		gen(jpc,0,0);
	}
#line 1677 "rr.c"
    break;

  case 23:
#line 144 "rr.y"
             {
		gen(jmp,0,cx2[cx2count-2]);
		code[cx2[cx2count-1]].a=code_cnt;
		cx2count-=2;
	}
#line 1687 "rr.c"
    break;

  case 25:
#line 149 "rr.y"
                                   {
		//need to rewrite
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//for (<stmt>;<bexpr>;<stmt>) <stmt>;
		/*
		int t = position($3);
		if(t > 0){
			if(table[t].kind != variable)
				yyerror("this identifier should be a variable!");
			else if(table[t].type == 1){
				if(!(judgeeq(1,$5)||judgeeq(0,$5))) {
					yyerror("this bool variable cannot be assigned by number excepts 1 and 0");
				}
				else gen(sto,0,getaddr(t),bool_t);
			}
			else gen(sto,0,getaddr(t),gettype(t));
		}
		else yyerror("this variable don't exists.");
		cx3[cx3count] = cx;
		cx3count+=1;
		*/
	}
#line 1714 "rr.c"
    break;

  case 26:
#line 170 "rr.y"
                  {
		/*
		gen(jpc,0,0,int_t);//不满足跳到stmt后结束循环
		gen(jmp,0,0,int_t);//否则执行stmt
		cx3[cx3count] = cx;//注意gen和cx[cxcount]语句的先后，此时存储的是jmp后的那一条语句的位置。
		cx3count+=1; 
	}selfop {
		gen(jmp,0,cx3[cx3count-2],int_t);//跳到第二个表达式前
		cx3[cx3count] = cx;
		cx3count+=1;
		code[cx3[cx3count-2]-1].a = cx;
	}RP stmt{
		int temp;
		//跳到第二个表达式后
		gen(jmp,0,cx3[cx3count-2],int_t);
		code[cx3[cx3count-2]-2].a = cx;
		cx3count -= 3;
		*/
	}
#line 1738 "rr.c"
    break;

  case 27:
#line 189 "rr.y"
           {
		//do <stmt> while (<bexpr>)
		/*
		cx4[cx4count] = cx;
		cx4count += 1;
		*/
	}
#line 1750 "rr.c"
    break;

  case 28:
#line 196 "rr.y"
                          { 	
		/*
		gen(jpc2,0,code[cx4[cx4count-1]].a,int_t);
		cx4count -= 1;
		int temp;
		*/
	}
#line 1762 "rr.c"
    break;

  case 30:
#line 203 "rr.y"
               {
		//repeat <stmt> until (<bexpr>)
		/*
		cx5[cx5count] = cx;
		cx5count += 1;
		*/
	}
#line 1774 "rr.c"
    break;

  case 31:
#line 210 "rr.y"
                          { 	
		/*
		gen(jpc,0,code[cx5[cx5count-1]].a,int_t);
		cx5count -= 1;
		int temp;
		*/
	}
#line 1786 "rr.c"
    break;

  case 33:
#line 217 "rr.y"
                        {
		//write <aexpr>
		gen(wri,0,0);
	}
#line 1795 "rr.c"
    break;

  case 34:
#line 221 "rr.y"
                    {
		//read x
		int t=position((yyvsp[-1].name));
		if (t>0) gen(red,gettype(t),getaddr(t));
		else yyerror("The variable does not exists!");
	}
#line 1806 "rr.c"
    break;

  case 35:
#line 227 "rr.y"
                     {
		//x++
		int t=position((yyvsp[-2].name));
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else yyerror("It is not a variable");
		}
		else yyerror("The variable does not exists!"); 		
		gen(lit,0,1);
		gen(opr,0,2);
		gen(sto,0,getaddr(t));
	}
#line 1824 "rr.c"
    break;

  case 36:
#line 240 "rr.y"
                      {
		//x--
		int t=position((yyvsp[-2].name));
		if (t>0) 
		{
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else yyerror("It is not a variable");
		}
		gen(lit,0,1);
		gen(opr,0,3);
		gen(sto,0,getaddr(t));
	}
#line 1841 "rr.c"
    break;

  case 38:
#line 255 "rr.y"
                  {
		//else <stmt>
		code[cx1[cx1count-2]].a=code_cnt;
	}
#line 1850 "rr.c"
    break;

  case 39:
#line 258 "rr.y"
             {
		code[cx1[cx1count-1]].a=code_cnt;
		cx1count-=2;
	}
#line 1859 "rr.c"
    break;

  case 40:
#line 262 "rr.y"
                  {
		//no else
		cx1count-=1;
		code[cx1[cx1count]].a=code_cnt;
		cx1count-=1;
		code[cx1[cx1count]].a=code_cnt;
	}
#line 1871 "rr.c"
    break;

  case 41:
#line 271 "rr.y"
                               {
		gen(opr,0,2);
	}
#line 1879 "rr.c"
    break;

  case 42:
#line 274 "rr.y"
                         {
		gen(opr,0,3);
	}
#line 1887 "rr.c"
    break;

  case 43:
#line 277 "rr.y"
                       {
		gen(opr,0,15);
	}
#line 1895 "rr.c"
    break;

  case 45:
#line 281 "rr.y"
                       {
		yyerror("assign symbol do not have return value in CXR!");
	}
#line 1903 "rr.c"
    break;

  case 46:
#line 286 "rr.y"
                                  {
		gen(opr,0,4);
	}
#line 1911 "rr.c"
    break;

  case 47:
#line 289 "rr.y"
                             {
		gen(opr,0,5);
	}
#line 1919 "rr.c"
    break;

  case 48:
#line 292 "rr.y"
                                {
		gen(opr,0,14);
	}
#line 1927 "rr.c"
    break;

  case 50:
#line 298 "rr.y"
                   {
		int t=position((yyvsp[0].name));
		if (t>0) 
		{
			if (table[t].type==bool_t) yyerror("type error");
			else if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in afactor");
		}
		else yyerror("this identifier don't exists."); 		
	}
#line 1943 "rr.c"
    break;

  case 51:
#line 309 "rr.y"
           {
		gen(lit,0,(yyvsp[0].var));
	}
#line 1951 "rr.c"
    break;

  case 52:
#line 312 "rr.y"
                   {
		(yyval.var)=(yyvsp[-1].var);
	}
#line 1959 "rr.c"
    break;

  case 53:
#line 317 "rr.y"
                             {
		gen(opr,0,17);
	}
#line 1967 "rr.c"
    break;

  case 55:
#line 321 "rr.y"
                       {
		yyerror("assign symbol do not have return value in CXR!");
	}
#line 1975 "rr.c"
    break;

  case 56:
#line 326 "rr.y"
                                {
		gen(opr,0,16);
	}
#line 1983 "rr.c"
    break;

  case 58:
#line 332 "rr.y"
                   {
		int t=position((yyvsp[0].name));
		if (t>0){
			if (table[t].type!=bool_t) yyerror("this variable is not boolean type.");
			else if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in bfactor");
		}
		else yyerror("this variable don't exists"); 	
	}
#line 1998 "rr.c"
    break;

  case 59:
#line 342 "rr.y"
            {
		gen(lit,0,1);
	}
#line 2006 "rr.c"
    break;

  case 60:
#line 345 "rr.y"
             {
		gen(lit,0,0);
	}
#line 2014 "rr.c"
    break;

  case 61:
#line 348 "rr.y"
                   {
		gen(opr,0,1);
	}
#line 2022 "rr.c"
    break;

  case 62:
#line 351 "rr.y"
                   {
		gen(opr,0,6); 	
	}
#line 2030 "rr.c"
    break;

  case 63:
#line 354 "rr.y"
                   {
		(yyval.var)=(yyvsp[-1].var);
	}
#line 2038 "rr.c"
    break;

  case 65:
#line 360 "rr.y"
                           {
		int t=position((yyvsp[-2].name));
		if (t>0) 
		{
			if (table[t].type!=int_t) yyerror("this variable don't have correct type.");		
			if (table[t].kind==variable) gen(lod,0,getaddr(t));
			else if (table[t].kind==constant) gen(lit,0,getv(t));
			else yyerror("unknown error in rel");
		}
		else yyerror("this variable don't exists."); 	
		if (strcmp((yyvsp[-1].name),"<")==0) gen(opr,0,10);
		else if (strcmp((yyvsp[-1].name),"<=")==0) gen(opr,0,13);
		else if (strcmp((yyvsp[-1].name),">")==0) gen(opr,0,12);
		else if (strcmp((yyvsp[-1].name),">=")==0) gen(opr,0,11);
		else if (strcmp((yyvsp[-1].name),"==")==0) gen(opr,0,8);
		else if (strcmp((yyvsp[-1].name),"!=")==0) gen(opr,0,9);
		else yyerror("wrong relop type\n");	
	 }
#line 2061 "rr.c"
    break;

  case 66:
#line 378 "rr.y"
                        {
		//num,relop,expr
		gen(lit,0,(yyvsp[-2].var));
		if (strcmp((yyvsp[-1].name),"<")==0) gen(opr,0,10);
		else if (strcmp((yyvsp[-1].name),"<=")==0) gen(opr,0,13);
		else if (strcmp((yyvsp[-1].name),">")==0) gen(opr,0,12);
		else if (strcmp((yyvsp[-1].name),">=")==0) gen(opr,0,11);
		else if (strcmp((yyvsp[-1].name),"==")==0) gen(opr,0,8);
		else if (strcmp((yyvsp[-1].name),"!=")==0) gen(opr,0,9);
		else yyerror("wrong relop type\n");
	 }
#line 2077 "rr.c"
    break;


#line 2081 "rr.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 391 "rr.y"

int iferror=0;
int main(int argc, char *argv[])
{
	for (int i=0;i<argc;i++){
		if (strcmp(argv[i],"-f")==0&&argc>i)
			yyin=fopen(argv[++i],"r");
	}
	#ifdef debug
		printf("**********CX Compiler:************\n");
	#endif
	yyparse();
	if (iferror) return 0;
	#ifdef debug
		printf("************pcode:****************\n");
	#endif
	printpcode();
	return 0;
}
int yyerror(char *msg)
{
	printf("Error encountered: %d:  %s at %s\n", yylineno, msg, yytext);
	iferror=1;
	return 1;
}
