/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void expr(void);
void term(void);
void factor(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define MOD_OP 27

#define AT 28
#define DOLLAR 29
#define PERL_IDENT 30
#define COMMA 31
#define SINGLE_QUOTE 32
#define DOUBLE_QUOTE 33

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	  do {
	 	  lex();
	  } while (nextToken != EOF);
	 }
	 return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;
     case '@':
       addChar();
       nextToken = AT;
       break;
     case '$':
       addChar();
       nextToken = DOLLAR;
       break;
     case ',':
       addChar();
       nextToken = COMMA;
       break;   
     case '\'':
       addChar();
       nextToken = SINGLE_QUOTE;
       break; 
     case '"':
       addChar();
       nextToken = DOUBLE_QUOTE;
       break;    
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class 
 
 This language transitions on every possible character
 */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar)) 
     /// (nextChar >= 65 && nextChar <= 90 ) ||
     /// (nextChar >= 97 && nextChar <= 122) || 
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
     /// (nextChar >= 48 && nextChar <= 57) || 
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
 int x;
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
   int x;
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = IDENT;
			 break;

		/* Integer literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = INT_LIT;
		 	break;
		/* Parentheses and operators */
		 case UNKNOWN:
			 lookup(nextChar);
       if(nextToken == AT || nextToken == DOLLAR || nextToken == MOD_OP){
       getChar();
       if(charClass == LETTER){
         addChar();
         getChar();
          while(charClass == LETTER || charClass == DIGIT){
            addChar();
            getChar();
          }
        nextToken = PERL_IDENT;
        }
       }
			 getChar();
			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */

// void expr(void) {
// 	 printf("Enter <expr>\n");
// 	/* Parse the first term */
// 	 term();
// 	/* As long as the next token is + or -, get
// 	 the next token and parse the next term */
// 	 while (nextToken == ADD_OP || nextToken == SUB_OP) {
// 		 lex();
// 		 term();
// 	 }
// 	 printf("Exit <expr>\n");
// }

// /* term
//  Parses strings in the language generated by the rule:
//  <term> -> <factor> {(* | / | % ) <factor>}
//  */
// void term(void) {
// 	 printf("Enter <term>\n");
// 	/* Parse the first factor */
// 	 factor();
// 	/* As long as the next token is * or /, get the
// 	 next token and parse the next factor */
// 	 while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
// 		 lex();
// 		 factor();
// 	 }
// 	 printf("Exit <term>\n");
// }

// /* factor
//  Parses strings in the language generated by the rule:
//  <factor> -> id | int_constant | ( <expr> )
//  */
// void factor(void) {
// 	 printf("Enter <factor>\n");
// 	/* Determine which RHS */
// 	 if (nextToken == IDENT || nextToken == INT_LIT)
// 		/* Get the next token */
// 		 lex();
// 		/* If the RHS is ( <expr> ), call lex to pass over the
// 		 left parenthesis, call expr, and check for the right
// 		 parenthesis */
// 	 else { if (nextToken == LEFT_PAREN) {
// 		 lex();
// 		 expr();
// 		 if (nextToken == RIGHT_PAREN)
// 		 	lex();
// 		 else
// 		 	error();
// 		 }
// 		/* It was not an id, an integer literal, or a left
// 		 parenthesis */
// 		 else
// 		 error();
// 	 }
// 	 printf("Exit <factor>\n");
// } 
