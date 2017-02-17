#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T",      // 0
				"NUM_TOKENS", // 1
				"CONS_T = 2", // 2
				"IF_T",       // 3
				"WHILE_T",    // 4
				"AND_T",      // 5
				"OR_T",       // 6
				"NOT_T",      // 7
				"DEFINE_T",   // 8
				"LISTOP_T",   // 9
				"NUMBERP_T",  // 10
				"SYMBOLP_T",  // 11
				"LISTP_T",    // 12
				"ZEROP_T",    // 13
				"NULLP_T",    // 14
				"CHARP_T",    // 15
				"STRINGP_T",  // 16
				"PLUS_T",     // 17
				"MINUS_T",    // 18
				"DIV_T",      // 19
				"MULT_T",     // 20
				"EQUALTO_T",  // 21
				"GT_T",       // 22
				"LT_T",       // 23
				"GTE_T",      // 24
				"LTE_T",      // 25
				"LPAREN_T",   // 26
				"RPAREN_T",   // 27
				"QUOTE_T",    // 28
				"IDENT_T",    // 29
				"NUMLIT_T"};  // 30

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // This function will initialize the lexical analyzer class
  input.open(filename);
  file_error = FILE_ERR;
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
  // This function will find the next lexeme int the input file and return
  // the token_type value associated with that lexeme
  
  
  string temp;
  if(!input.is_open()) {return file_error;}
  
  while (! input.eof()) {
    int startState = 0;  
    bool isLex = false;
    getline(input,line);
    
    while(!isLex){
      temp = line[pos];
      int tableColumn = charToInt[temp];
      startState = stateTable[startState][tableColumn];

      if(startState - 500 >= 0 && startState - 500 <= 30){
	lexeme += temp;
	pos++;
	return startState - 500;
      }
      else{
	pos++;
	lexeme += temp;
      }
    }
  }
  input.close();
  
  
  token_type test = EOF_T;

  return test;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return token_names[t];
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}
