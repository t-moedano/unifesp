/****************************************************/
/* Thauany Moedano                                  */
/*                                                  */
/* Arquivo: cms.y                                   */
/****************************************************/

%{
    #define YYPARSER    
    #include "globals.h"
    #include "util.h"
    #include "scan.h"
    #include "parse.h"

    #define YYSTYPE TreeNode *
    static TreeNode * savedTree;   
    static int yylex(void);
%}

%token IF ELSE WHILE INT VOID RETURN
%token NUM ID
%token ASSIGN EQ NE LT LTE GT GTE PLUS MINUS TIMES OVER LPAREN RPAREN LBRACKET RBRACKET LKEYS RKEYS COMMA SEMI
%token ERROR ENDFILE

%% 

program            :   list_declaration
                       {
                          savedTree = $1;
                       }
                    ;
list_declaration    :   list_declaration declaration
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
		   	  			    {
                                while(t->sibling != NULL)
                                    t = t->sibling;
                                t->sibling = $2;
                                $$ = $1;
                            }
                            else
                                $$ = $2;
                        }
                    |   declaration
                        {
                           $$ = $1;
                        }
                    ;
declaration         :   var_declaration
                        {
                           $$ = $1;
                        }
                    |   fun_declaration
                        {
                           $$ = $1;
                        }
                    ;
var_declaration     :   INT ident SEMI
                        {	
                        	$$ = newExpNode(typeK);
                            $$->type = integerK;
                            $$->attr.name = "integer";
                            $$->child[0] = $2;
                            $2->nodekind = statementK;
                            $2->kind.stmt = variableK;
							$2->type = integerK;
                        }
                    |   INT ident LBRACKET num RBRACKET SEMI
                        {
                        	$$ = newExpNode(typeK);
                            $$->type = integerK;
                            $$->attr.name = "integer";
                            $$->child[0] = $2;
                            $2->nodekind = statementK;
                            $2->kind.stmt = variableK;
							$2->type = integerK; 
                            $2->attr.len = $4->attr.val;
                        }
                    ;
fun_declaration     :   INT ident LPAREN params RPAREN compound_decl
                        {
                        	$$ = newExpNode(typeK);
                            $$->type = integerK;
                            $$->attr.name = "integer";
                            $$->child[0] = $2;
                            $2->child[0] = $4;
                            $2->child[1] = $6;
                            $2->nodekind = statementK;
                            $2->kind.stmt = functionK;
							$2->type = integerK;
							$4->type = integerK;
							aggScope($2->child[0], $2->attr.name);
							aggScope($2->child[1], $2->attr.name);
                        }
                    |   VOID ident LPAREN params RPAREN compound_decl
                        {
                        	$$ = newExpNode(typeK);
                            $$->type = voidK;
                            $$->attr.name = "void";
                            $$->child[0] = $2;
                            $2->child[0] = $4;
                            $2->child[1] = $6;
                            $2->nodekind = statementK;
                            $2->kind.stmt = functionK;
							aggScope($2->child[0], $2->attr.name);
							aggScope($2->child[1], $2->attr.name);
                        }
                    ;
params              :   param_list
                        {
                           $$ = $1;
                        }
                    |   VOID
                        {
						  $$ = newExpNode(typeK);
           				  $$->attr.name = "void";
						}
                    ;
param_list          :   param_list COMMA param
                        {
                           YYSTYPE t = $1;
                           if(t != NULL)
						   {
                              while(t->sibling != NULL)
                                  t = t->sibling;
                              t->sibling = $3;
                              $$ = $1;
                            }
                            else
                              $$ = $3;
                        }
                    |   param
                        {
                            $$ = $1;
                        }
                    ;
param               :   INT ident
                        {
						   	
                           $$ = newExpNode(typeK);
					       $2->nodekind = statementK;
                           $2->kind.stmt = variableK;
                           $$->type = integerK;
						   $2->type = integerK; 	
                           $$->attr.name = "integer";
                           $$->child[0] = $2;
                        }
                    |   INT ident LBRACKET RBRACKET
                        {
							
                            $$ = newExpNode(typeK);
							$2->nodekind = statementK;
                            $2->kind.stmt = variableK;
                            $$->type = integerK;
                            $$->attr.name = "integer";
                            $$->child[0] = $2;
						    $2->type = integerK;
                        }
                    ;
compound_decl       :   LKEYS local_declarations statement_list RKEYS
                        {
                            YYSTYPE t = $2;
                            if(t != NULL)
						    {
                               while(t->sibling != NULL)
                                  t = t->sibling;
                                t->sibling = $3;
                                $$ = $2;
                            }
                            else
                               $$ = $3;
                        }
                    |   LKEYS local_declarations RKEYS
                        {
                            $$ = $2;
                        }
                    |   LKEYS statement_list RKEYS
                        {
                            $$ = $2;
                        }
                    |   LKEYS RKEYS
                        {
			   			}
                    ;
local_declarations  :   local_declarations var_declaration
                        {
                            YYSTYPE t = $1;
                            if(t != NULL)
							{
                            	while(t->sibling != NULL)
                                	 t = t->sibling;
                             	t->sibling = $2;
                             	$$ = $1;
                            }
                            else
                               $$ = $2;
                        }
                   |    var_declaration
                        {
                            $$ = $1;
                        }
                    ;
statement_list      :   statement_list statement
                        {
                           YYSTYPE t = $1;
                           if(t != NULL)
						   {
                              while(t->sibling != NULL)
                                   t = t->sibling;
                              t->sibling = $2;
                              $$ = $1;
                           }
                           else
                             $$ = $2;
                        }
                    |   statement
                        {
                           $$ = $1;
                        }
                    ;
statement           :   expression_decl
                        {
                           $$ = $1;
                        }
                    |   compound_decl
                        {
                           $$ = $1;
                        }
                    |   selection_decl
                        {
                           $$ = $1;
                        }
                    |   iterator_decl
                        {
                           $$ = $1;
                        }
                    |   return_decl
                        {
                           $$ = $1;
                        }
                    ;
expression_decl     :   expression SEMI 
                        {
                           $$ = $1;
                        }
                    |   SEMI
                        {
						}
                    ;
selection_decl      :   IF LPAREN expression RPAREN statement 
                        {
                             $$ = newStmtNode(ifK);
                             $$->child[0] = $3;
                             $$->child[1] = $5;
                        }
                    |   IF LPAREN expression RPAREN statement ELSE statement
                        {
							 
                             $$ = newStmtNode(ifK);
                             $$->child[0] = $3;
                             $$->child[1] = $5;
                             $$->child[2] = $7;
                        }
                    ;
iterator_decl       :   WHILE LPAREN expression RPAREN statement
                        {
                             $$ = newStmtNode(whileK);
                             $$->child[0] = $3;
                             $$->child[1] = $5;
                        }
                   ;
return_decl        :   RETURN SEMI
                       {
                            $$ = newStmtNode(returnK);
							$$->type = voidK;
                       }
                   |   RETURN expression SEMI
                       {
                            $$ = newStmtNode(returnK);
                            $$->child[0] = $2;
                       }
                   ;
expression         :   var ASSIGN expression
                       {
                            $$ = newStmtNode(assignK);
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                       }
                   |   simple_expression
                       {
                            $$ = $1;
                       }
                   ;
var                :   ident
                       {
                            $$ = $1;
                       }
                   |   ident LBRACKET expression RBRACKET
                       {
                            $$ = $1;
                            $$->child[0] = $3;
                            $$->kind.exp = vectorK;
							$$->type = integerK;
                       }
                    ;
simple_expression   : sum_expression relational sum_expression
                       {
                            $$ = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                       }
                    |  sum_expression
                       {
                            $$ = $1;
                       }
                    ;
relational          :  EQ
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = EQ;  
							$$->type = booleanK;                          
                       }
                    |  NE
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = NE;
							$$->type = booleanK;                            
                       }
                    |  LT
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = LT;                            
							$$->type = booleanK;
                       }
                    |  LTE
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = LTE;                            
							$$->type = booleanK;
                       }
                    |  GT
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = GT;                            
							$$->type = booleanK;
                       }
                    |  GTE
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = GTE;                            
							$$->type = booleanK;
                       }
                    ;
sum_expression      :  sum_expression sum term
                       {
                            $$ = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                       }
                    |  term
                       {
                            $$ = $1;
                       }
                    ;
sum                 :  PLUS
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = PLUS;                            
                       }
                    |  MINUS
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = MINUS;                            
                       }
                    ;
term                :  term mult factor
                       {
                            $$ = $2;
                            $$->child[0] = $1;
                            $$->child[1] = $3;
                       }
                   |   factor
                       {
                            $$ = $1;
                       }
                    ;
mult                :  TIMES
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = TIMES;                            
                       }
                   |   OVER
                       {
                            $$ = newExpNode(operationK);
                            $$->attr.op = OVER;                            
                       }
                    ;
factor              :  LPAREN expression RPAREN
                       {
                            $$ = $2;
                       }
                   |   var
                       {
                            $$ = $1;
                       }
                   |   activation
                       {
                            $$ = $1;
                       }
                   |   num
                       {
                            $$ = $1;
                       }
                    ;
activation          :  ident LPAREN arg_list RPAREN
                       {
                            $$ = $1;
                            $$->child[0] = $3;
                            $$->nodekind = statementK;
                            $$->kind.stmt = callK;
                       }
                    |  ident LPAREN RPAREN 
					   {
                            $$ = $1;
                            $$->nodekind = statementK;
                            $$->kind.stmt = callK;
                       }
                       
                    ;
arg_list            :  arg_list COMMA expression
                       {
                            YYSTYPE t = $1;
                             if(t != NULL)
							 {
                                while(t->sibling != NULL)
                                   t = t->sibling;
                                 t->sibling = $3;
                                 $$ = $1;
                             }
                             else
                                 $$ = $3;
                        }
                    |   expression
                        {
                             $$ = $1;
                        }
                    ;
ident               :   ID
                        {
                             $$ = newExpNode(idK);
                             $$->attr.name = copyString(tokenString);
                        }
                    ;
num                 :   NUM
                        {
                             $$ = newExpNode(constantK);
                             $$->attr.val = atoi(tokenString);
							 $$->type = integerK;
						}
                    ;

%%

int yyerror(char* message){
    fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
    fprintf(listing,"Current token: ");
    printToken(yychar,tokenString);
    Error = TRUE;
    return 0;
}


static int yylex(void){
    return getToken();
}

TreeNode * parse(void){
    yyparse();
    return savedTree;
}
