#include <iostream>
#include <fstream>
#include <cstdlib> 
using namespace std;

ifstream infp;
enum Tokens { A, B, C, ENDFILE=80, UNKNOWN=99 };
			
const int SIZE = 100;
Tokens nextToken;
string lexeme;
char nextChar;

int errors = 0; // counter for error messages
int line = 1;   // variable to keep track of the line number from the source code

/******************************************************/
/*   Helping function to display the token as a string */
void prt (Tokens nt) {
	switch (nt) {
		case A: cout << "<A>"; break;
		case B: cout << "<B>"; break;
		case C: cout << "<C>"; break;
		case ENDFILE: cout << "<ENDFILE>"; break;
		case UNKNOWN: cout << "<UNKNOWN>"; break;
		default: break;
	}
};

/* errMsg - function to display the error message with the line number of the error detected. */
void errMsg (string msg) {
	cout << "Error at line: " << line << ": " << msg << endl;
	errors++;
	
}

/*****************************************************/
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(char nextChar) {
	lexeme += nextChar;
	if (lexeme.size() > 99) {
		errMsg ("Lexeme size exceeds 100 characters");
		exit(0);
	}
}

char getChar() {
	char ch = infp.get();
	if (ch == '\n') {		
		line++;
		
	}
	return ch;
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
char getNonSpaceChar() {
	char ch = ' ';
	while (isspace(ch)) {
		ch = getChar();
	}
	return ch;
}

/*******************************************************************
LookupKeyword - a simple lookup code for keywords in the language: */
Tokens lookupKeywords (string lexeme) {
	// return keyword token
	Tokens token = UNKNOWN;
	if (lexeme == ("a")) return A;
	if (lexeme == "b") return B;
	if (lexeme == "c") return C;
	return UNKNOWN;
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic 
 expressions */
Tokens tokenizer() {
	lexeme = "";

	if (nextChar == EOF) {
		nextToken = ENDFILE;
		lexeme = "EOF";
		return nextToken;
	}

	if (isspace(nextChar)) nextChar = getNonSpaceChar();

	if (nextChar == 'a') {
		addChar(nextChar);
		nextToken = A;
		nextChar = getChar();
	}
	else if (nextChar == 'b') {
		addChar(nextChar);
		nextToken = B;
		nextChar = getChar();
	}
	else if (nextChar == 'c') {
		addChar(nextChar);
		nextToken = C;
		nextChar = getChar();
	}
	else if (nextChar == EOF) {
		nextToken = ENDFILE;
		lexeme = "EOF";
	}
	else {
		nextToken = UNKNOWN;
		addChar(nextChar);
		nextChar = getChar();
	}
  cout << "Token read:\t"; 
  prt(nextToken); 
  cout << " Lexeme: " << lexeme << endl;
  
  return nextToken;
}

/*************************************************/
/* <C> -> c
*/
Tokens CParser () {
	if (nextToken == C) {
		nextToken = tokenizer();
	} else {
		errMsg("Expecting c");
	}
	return nextToken;
}

/*************************************************/
/* <B> -> b<B> | b
*/
Tokens BParser () {
	if (nextToken == B) {
		nextToken = tokenizer();
		while (nextToken == B) {
			nextToken = tokenizer();
		}
	} else {
		errMsg("Expecting b");
	}
	return nextToken;
}

/***************************************************/
/* <A> -> a<A> | a
*/
Tokens AParser () {
	if (nextToken == A) {
		nextToken = tokenizer();
		while (nextToken == A) {
			nextToken = tokenizer();
		}
	} else {
		errMsg("Expecting a");
	}
	return nextToken;
}

/********************************************/
/* stmt - statement parser by the rule:
   <stmt> -> <A><C><B> | <A>
*/
Tokens S () {
	nextToken = AParser();
	if (nextToken == C) {
		nextToken = CParser();
	}
	nextToken = BParser();
	return nextToken;

}

/******************************************* End of Syntax Analyzer (parser) **************************************************************************/

/******************************************************/
/* main driver */
int main() {
	infp.open(".\\prg3.in");
	if (!infp) {
		cout << "ERROR - cannot open file \n";
		errors++;
	}
	else {
		nextChar = getChar();
		nextToken = tokenizer();
		do {
			nextToken = S();
			if (errors > 10) break;
		} while (nextToken != ENDFILE);
	}
	cout << "Total number of errors: " << errors << endl;
	infp.close();
	return 0;
}
