/****************************************************/
/*                                                  */
/*                                                  */
/* Thauany Moedano                                  */
/*                                                  */
/*                                                  */
/****************************************************/


#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



#ifndef YYPARSER


#include "cms.tab.h"


#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 6

extern FILE* source; 
extern FILE* listing; 
extern FILE* code; 

extern int lineno; 


typedef int TokenType;

typedef enum
{
	statementK, expressionK 
} NodeKind;

typedef enum
{
	ifK, whileK, assignK, variableK, functionK, callK, returnK, numberK

} StatementKind;

typedef enum
{
	operationK, constantK, idK, vectorK, vectorIdK, typeK

} ExpressionIdentifier;

/* ExpType is used for type checking */
typedef enum
{

	voidK, integerK, booleanK
	
} ExpressionType;


#define MAXCHILDREN 3


typedef struct treeNode
{ 
	 struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;

     union 
     { 
		StatementKind stmt; 
        ExpressionIdentifier exp;
     } kind;

     struct 
     { 
	    TokenType op;
        int val;
        int len;
        char* name; 
        char* scope;	
     } attr;

     ExpressionType type; /* for type checking of exps */
} TreeNode;


extern int EchoSource;

extern int TraceScan;

extern int TraceParse;

extern int TraceAnalyze;

extern int TraceCode;

extern int Error; 
#endif
