grammar HarshX;

program:				call_start
						;

call_start : 					externalDeclaration			#callstextDec
						| externalDeclaration call_start	#callstextDecCallst
						;

externalDeclaration:    declaration 	#extdecDecaration
						| statement 	#extdecstatement
						| function 		#extdecfunction
						;

list:                   declaration list 	#listdeclist
                        | statement list 	#liststatementlist
                        | statement 		#liststatement
                        | declaration		#listdeclaration
						;

function:               typeSpecifier ID '(' declarationList ')' compoundStatement	#func1
						| typeSpecifier ID '('')' compoundStatement					#func2
						;

declarationList:        declarator							#decllistdecl
                        | declarator ',' declarationList	#decllistdecl2
						;

declarator:             typeSpecifier ID 					#decltypespeci
                        | typeSpecifier ID '[' ']'			#decltypespeci2
						;

statement:              inputStatement						#stateinput
                        | printStatement					#stateprint
                        | returnStatement					#statereturn
                        | expressionStatement				#stateexpr
                        | compoundStatement					#statecomp
						| controlStatement					#statecont
						| functionCall ';'					#statefunc
						| STOP ';'							#statestop
						;

compoundStatement:      '{' list '}'		#compstatelist
						| '{' '}'			#compstateempty
						;

controlStatement:       conditional			#contstatecondition
						| loop				#contstateloop
						;

functionCall:           ID '(' parameterList ')' 			#functcall1
						| ID '(' ')' 						#functcall2
						;

parameterList:          operationExpression					#paralistopexpr
                        | operationExpression ',' parameterList	 #paralistopexpr2
						;

declaration:			typeSpecifier iDlist ';'		#declarationtypespeci
						;

inputStatement:         SCAN '(' expression ')' ';'		#inpstatescan
						;

printStatement:         PRINT '(' operationExpression ')' ';'	#pristateprint
						;

returnStatement:        RETURN operationExpression ';'	 #retstateret
						;

expressionStatement:    assignmentExpression ';'	#exprstateassignexpr
						;


typeSpecifier:          INTEGER 		#typespeciint
						| BOOLEAN		#typespecibool
                        | CHARACTER		#typespecichar
                        | UINTEGER		#typespeciuint
						;

iDlist:                 variable		#idlistvar
                        | variable ',' iDlist 	#idlistvar2
						;

variable:				ID									#var
						| ID '[' NUMBER ']'					#var1darray
						| ID '[' NUMBER ']'	'[' NUMBER ']'	#var2darray
						;

operationExpression:    arithmeticExpression	#opexpraritexpr
                        | expression			#opexprexpr
                        | NUMBER				#opexprnum
						| TRUE					#opexprtrue
						| FALSE					#opexprfalse
						| booleanExpression		#opexprboolexpr
						| optionExpression		#opexpropexpr
						;

arithmeticExpression:   '(' operationExpression ')' arithmeticOperator '(' operationExpression ')'		#aritexpr
						;

booleanExpression:      '(' operationExpression ')' booleanOperator '(' operationExpression ')'		#boolexpr
						;
optionExpression:       '(' conditionalExpression ')' '?' operationExpression ':' operationExpression		#opexprter
						;

conditionalExpression:  condition						#condexprcond
                        | '(' conditionalExpression ')' logicalOperator '(' conditionalExpression ')' 			#condexprcond2
						;

assignmentExpression:   expression assignmentOperator operationExpression	 #assignexpr1
                        | expression EQUAL '"' ID '"'						 #assignexpr2
						| expression assignmentOperator functionCall 		 #assignexpr3
						;

condition:              operationExpression comparisonOperator operationExpression		#condopexprcom
						;

expression:				ID																#expr
						| ID '[' operationExpression ']'								#expr1darray
						| ID '[' operationExpression ']' '[' operationExpression ']' 	#expr2darray
						;

conditional:			IF '(' conditionalExpression ')' compoundStatement							#condif	
						| IF '(' conditionalExpression ')' compoundStatement ELSE conditional		#condifelse
                        | IF '(' conditionalExpression ')' compoundStatement ELSE compoundStatement	 #condifelse2
						;

loop:					WHILE '(' conditionalExpression ')' compoundStatement		#loopwhile1											
						| WHILE '(' ')' compoundStatement							#loopwhile2								
						| FOR '(' ';' ';' ')' compoundStatement						#loopfor1											
                        | FOR '(' assignmentExpression ';' ';' ')' compoundStatement		#loopfor2									
                        | FOR '(' ';' conditionalExpression ';' ')' compoundStatement		#loopfor3							
                        | FOR '(' ';' ';' assignmentExpression ')' compoundStatement		#loopfor4							
                        | FOR '(' assignmentExpression ';' conditionalExpression ';' ')' 	compoundStatement													#loopfor5
                        | FOR '(' assignmentExpression ';' ';' assignmentExpression ')' compoundStatement													#loopfor6
                        | FOR '(' ';' conditionalExpression ';' assignmentExpression ')' compoundStatement													 #loopfor7
                        | FOR '(' assignmentExpression ';' conditionalExpression ';' assignmentExpression ')' compoundStatement							 #loopfor8
						;


arithmeticOperator:		PLUS		#aritopplus
						| MINUS		#aritopminus
                        | MUL		#aritopmul
                        | DIV		#aritopdiv
                        | MOD		#aritopmod
						;

comparisonOperator:     LT				#compoplt
                        | GT			#compopgt
                        | EQ			#compopeq
                        | NOTEQ			#compopnoteq
                        | LTE			#compoplte
                        | GTE			#compopgte
						;

booleanOperator:        AND				#boolopand
                        | OR			#boolopor
                        | XOR			#boolopxor
                        | LEFTSHIFT		#booloplsft
                        | RIGHTSHIFT 	#booloprsft
						;

logicalOperator:        ANDC		#logopandc
                        | ORC		#logoporc
						;

assignmentOperator:     EQUAL					#assignopeq
                        | PLUSE					#assignoppl
                        | MINUSE				#assignopmi
                        | MULE					#assignopmu
                        | DIVE					#assignopdi
                        | MODE					#assignopmo
                        | ANDE					#assignopande
                        | ORE					#assignopore
                        | XORE					#assignopxore
                        | LEFTSHIFTE			#assignoplsft
                        | RIGHTSHIFTE			#assignoprsft
						;

PRINT    :   'print';
SCAN      :  'scan';
RETURN    :  'return';
PLUS      :  '+';
PLUSE     :   '+=';
MINUS      : '-';
MINUSE     :  '-=';
MUL        : '*';
MULE       :  '*=';
DIV        : '/';
DIVE      :   '/=';
MOD       :  '%';
MODE      :   '%=';
AND       :  '&';
ANDE      :   '&=';
OR        :  '|';
ORE       :   '|=';
XOR       :  '^';
XORE       :  '^=';
LEFTSHIFT  : '<<';
LEFTSHIFTE :  '<<=';
RIGHTSHIFT : '>>';
RIGHTSHIFTE : '>>=';
EQUAL      : '=';
INTEGER    : 'int';
UINTEGER   : 'uint';
CHARACTER  : 'char';
BOOLEAN    : 'bool';
ANDC       : 'and';
ORC        : 'or';
LT         : '<';
GT         : '>';
EQ         : '==';
NOTEQ      : '!=';
LTE        : '<=';
GTE        : '>=';
IF         : 'if';
ELSE       : 'else';
WHILE      : 'while';
FOR        : 'for';
STOP       : 'stop';
TRUE       : 'true';
FALSE      : 'false';

/*Tokens*/

ID  : [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER : ('0' .. '9') + ('.' ('0' .. '9') +)? ;
COMMENT : '//' ~[\r\n]*->skip;
NS : [ \t\n]+ -> skip;