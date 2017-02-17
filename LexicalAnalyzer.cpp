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

    charToInt[" "] = 1;
    charToInt["'"] = 2;
    charToInt["("] = 3;
    charToInt[")"] = 4;
    charToInt["*"] = 5;
    charToInt["+"] = 6;
    charToInt["-"] = 7;
    charToInt["/"] = 8;
    charToInt["."] = 9;
    charToInt["0"] = 10;
    charToInt["1"] = 10;
    charToInt["2"] = 10;
    charToInt["3"] = 10;
    charToInt["4"] = 10;
    charToInt["5"] = 10;
    charToInt["6"] = 10;
    charToInt["7"] = 10;
    charToInt["8"] = 10;
    charToInt["9"] = 10;
    charToInt["<"] = 11;
    charToInt["="] = 12;
    charToInt[">"] = 13;
    charToInt["?"] = 14;
    charToInt["a"] = 15;
    charToInt["b"] = 19;
    charToInt["c"] = 16;
    charToInt["d"] = 17;
    charToInt["e"] = 19;
    charToInt["f"] = 19;
    charToInt["g"] = 19;
    charToInt["h"] = 19;
    charToInt["i"] = 19;
    charToInt["j"] = 19;
    charToInt["k"] = 19;
    charToInt["m"] = 19;
    charToInt["n"] = 19;
    charToInt["o"] = 19;
    charToInt["p"] = 19;
    charToInt["q"] = 19;
    charToInt["r"] = 18;
    charToInt["s"] = 19;
    charToInt["t"] = 19;
    charToInt["u"] = 19;
    charToInt["v"] = 19;
    charToInt["w"] = 19;
    charToInt["x"] = 19;
    charToInt["y"] = 19;
    charToInt["z"] = 19;
    charToInt["A"] = 20;
    charToInt["B"] = 20;
    charToInt["C"] = 20;
    charToInt["D"] = 20;
    charToInt["E"] = 20;
    charToInt["F"] = 20;
    charToInt["G"] = 20;
    charToInt["H"] = 20;
    charToInt["I"] = 20;
    charToInt["J"] = 20;
    charToInt["K"] = 20;
    charToInt["M"] = 20;
    charToInt["N"] = 20;
    charToInt["O"] = 20;
    charToInt["P"] = 20;
    charToInt["Q"] = 20;
    charToInt["R"] = 20;
    charToInt["S"] = 20;
    charToInt["T"] = 20;
    charToInt["U"] = 20;
    charToInt["V"] = 20;
    charToInt["W"] = 20;
    charToInt["X"] = 20;
    charToInt["Y"] = 20;
    charToInt["Z"] = 20;
    charToInt["_"] = 21;
    charToInt["$"] = 22;
    charToInt["#"] = 22;
    charToInt["%"] = 22;
    charToInt["^"] = 22;
    charToInt["&"] = 22;
    charToInt["~"] = 22;
    charToInt["|"] = 22;

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
