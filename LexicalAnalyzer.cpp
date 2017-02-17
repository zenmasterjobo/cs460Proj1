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

int stateTable[][21] =
   {{0,528,526,527,520,8,11,519,9,10,3,521,4,-50,6,1,6,6,6,6,-50},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,2,6,5,6,6,6,6},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,5,509,6,6,6},
    {522,522,522,522,522,522,522,522,522,522,522,524,522,522,522,522,522,522,522,522,522},
    {523,523,523,523,523,523,523,523,523,523,523,525,523,523,523,523,523,523,523,523,523},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,5,509,6,6,529},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,6,6,6,6,6},
    {530,530,530,530,530,530,530,530,12,7,530,530,530,530,530,530,530,530,530,530,530},
    {517,517,517,517,517,517,517,517,14,7,517,517,517,517,517,517,517,517,517,517,517},
    {-50,-50,-50,-50,-50,-50,-50,-50,-50,12,-50,-50,-50,-50,-50,-50,-50,-50,-50,-50,-50},
    {530,530,530,530,530,530,530,530,12,10,530,530,530,530,530,530,530,530,530,530,530},
    {518,518,518,518,518,518,518,518,14,7,518,518,518,518,518,518,518,518,518,518,518},
    {530,530,530,530,530,530,530,530,530,12,530,530,530,530,530,530,530,530,530,530,530}}; 


LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // This function will initialize the lexical analyzer class
  input.open(filename);
  file_error = FILE_ERR;


    charToInt[" "] = 0;
    charToInt["'"] = 1;
    charToInt["("] = 2;
    charToInt[")"] = 3;
    charToInt["*"] = 4;
    charToInt["+"] = 5;
    charToInt["-"] = 6;
    charToInt["/"] = 7;
    charToInt["."] = 8;
    charToInt["0"] = 9;
    charToInt["1"] = 9;
    charToInt["2"] = 9;
    charToInt["3"] = 9;
    charToInt["4"] = 9;
    charToInt["5"] = 9;
    charToInt["6"] = 9;
    charToInt["7"] = 9;
    charToInt["8"] = 9;
    charToInt["9"] = 9;
    charToInt["<"] = 10;
    charToInt["="] = 11;
    charToInt[">"] = 12;
    charToInt["?"] = 13;
    charToInt["a"] = 14;
    charToInt["b"] = 18;
    charToInt["c"] = 15;
    charToInt["d"] = 15;
    charToInt["e"] = 18;
    charToInt["f"] = 18;
    charToInt["g"] = 18;
    charToInt["h"] = 18;
    charToInt["i"] = 18;
    charToInt["j"] = 18;
    charToInt["k"] = 18;
    charToInt["m"] = 18;
    charToInt["n"] = 18;
    charToInt["o"] = 18;
    charToInt["p"] = 18;
    charToInt["q"] = 18;
    charToInt["r"] = 17;
    charToInt["s"] = 18;
    charToInt["t"] = 18;
    charToInt["u"] = 18;
    charToInt["v"] = 18;
    charToInt["w"] = 18;
    charToInt["x"] = 18;
    charToInt["y"] = 18;
    charToInt["z"] = 18;
    charToInt["A"] = 19;
    charToInt["B"] = 19;
    charToInt["C"] = 19;
    charToInt["D"] = 19;
    charToInt["E"] = 19;
    charToInt["F"] = 19;
    charToInt["G"] = 19;
    charToInt["H"] = 19;
    charToInt["I"] = 19;
    charToInt["J"] = 19;
    charToInt["K"] = 19;
    charToInt["M"] = 19;
    charToInt["N"] = 19;
    charToInt["O"] = 19;
    charToInt["P"] = 19;
    charToInt["Q"] = 19;
    charToInt["R"] = 19;
    charToInt["S"] = 19;
    charToInt["T"] = 19;
    charToInt["U"] = 19;
    charToInt["V"] = 19;
    charToInt["W"] = 19;
    charToInt["X"] = 19;
    charToInt["Y"] = 19;
    charToInt["Z"] = 19;
    charToInt["_"] = 20;
    charToInt["$"] = 21;
    charToInt["#"] = 21;
    charToInt["%"] = 21;
    charToInt["^"] = 21;
    charToInt["&"] = 21;
    charToInt["~"] = 21;
    charToInt["|"] = 21;

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
    lexeme = " ";
    getline(input,line);
    
    while(!isLex){
      temp = line[pos];
      //cout << "TEMP:" << temp << endl; 
      int tableColumn = charToInt[temp];
      //cout << "TABLE COL: "<< tableColumn << endl; 
      startState = stateTable[startState][tableColumn];
      
      if(startState - 500 >= 0 && startState - 500 <= 30){
	lexeme += temp;
	pos++;
	token_type lex = token_type(startState - 500);
	//cout << "START STATE: " << startState << endl;
	//cout << "OUR LEX: "<< lex << endl;
	return lex;
      }
      else{
	pos++;
	lexeme += temp;
	cout << "LEXEME: " << lexeme << endl;
      }
    }
  }
  input.close();
  
  
return token_type(EOF_T);
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
