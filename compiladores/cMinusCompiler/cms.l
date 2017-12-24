/****************************************************/
/*                                                  */
/* Analisador Léxico para C--                       */
/*                                                  */
/* Thauany Moedano                                  */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

char tokenString[MAXTOKENLEN+1];
static int yylex(void);
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%
"/*"            { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
  		            if (c == '*') 
                    { 
		                if(input() == '/')
		                break;
		            }		
                  } while (1);
                }
"if"            {return IF;}
"else"          {return ELSE;}
"int"		    {return INT;}
"return"	    {return RETURN;}
"void"		    {return VOID;}
"while"		    {return WHILE;}
"="             {return ASSIGN;}
"=="            {return EQ;}
"<"             {return LT;}
">"		        {return GT;}
"<="		    {return LTE;}
">="		    {return GTE;}
"!="	       	{return NE;}
"["		        {return LBRACKET;}
"]"		        {return RBRACKET;}
"{"		        {return LKEYS;}
"}"		        {return RKEYS;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
","		        {return COMMA;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {         }
.               {return ERROR;}

%%

TokenType getToken(void)
{ 
      static int firstTime = TRUE;
      TokenType currentToken;
      if (firstTime)
      { 
        firstTime = FALSE;
        lineno++;
        yyin = source;
        yyout = listing;
      }
      currentToken = yylex();
      strncpy(tokenString,yytext,MAXTOKENLEN);
      if (TraceScan) 
      {
        fprintf(listing,"\t%d: ",lineno);
        printToken(currentToken,tokenString);
      }
      return currentToken;
}

