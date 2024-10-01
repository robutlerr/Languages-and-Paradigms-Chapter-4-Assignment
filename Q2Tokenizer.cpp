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
	// Type your code here
	switch (nt) {
		case A: cout << "<A>";
		case B: cout << "<B>";
		case C: cout << "<C>";
		case ENDFILE cout << "<ENDFILE>" << endl;
		case UNKNOWN cout << "<UNKNOWN>" << endl;
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
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic 
 expressions */
Tokens tokenizer() {
	Tokens nextToken = ENDFILE;
	lexeme = "";
	if (isspace(nextChar)) nextChar = getNonSpaceChar();
	if (nextChar == 'a') {
		nextToken = A;
		lexeme = nextChar;
		nextChar = getChar();
	}
	else if (nextChar == 'b') {
		nextToken = B;
		lexeme = nextChar;
		nextChar = getChar();
	}
	else if (nextChar == 'c') {
		nextToken = C;
		lexeme = nextChar;
		nextChar = getChar();
	}
	else if (nextChar == EOF) {
		nextToken = ENDFILE;
		lexeme = "EOF";

	}
	else nextToken = UNKNOWN;
  cout << "Token read:\t"; prt(nextToken); 
  cout << " Lexeme: " << lexeme << endl;
  
  return nextToken;
}

/******************************************************/
/* main driver */
int main() {
	infp.open(".\\prg3.in");
	if (!infp) {
		cout << "ERROR - cannot open file \n";
		errors++;
	}
	else {
		nextChar = ' ';
		do {
			nextToken = tokenizer();
		} while (nextToken != ENDFILE);
	}
	cout << "Total number of errors: " << errors << endl;
	return 0;
}
