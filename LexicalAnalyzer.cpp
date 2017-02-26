#include <cstdlib>
#include <iomanip>
#include "LexicalAnalyzer.h"
#include <fstream>
using namespace std;

/****************************************************
 * this is the array of names we can use to look up *
 * the sting name of our enumerated values.         *
 * toekn_names[NUMBERP_T] would take us to index 10 *
 * and return the appropriate names                 *
 ***************************************************/
static string token_names[] = {	"EOF_T",      // 0
				"NUM_TOKENS", // 1
				"CONS_T",     // 2
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
				"NUMLIT_T",   // 30
				"ERROR_T"};   // 31

 /*******************************************************
 *This State table will help our code quickly transition *
 *between error states and accepting states.             *
 *******************************************************/
int stateTable[][22] =
   {{0,528,526,527,520,8,11,519,9,10,3,521,4,-4,6,1,6,6,6,6,-4, -4},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,2,6,5,6,6,6,6, -4},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,5,509,6,6,6, -4},
    {522,522,522,522,522,522,522,522,522,522,522,524,522,522,522,522,522,522,522,522,522, -4},
    {523,523,523,523,523,523,523,523,523,523,523,525,523,523,523,523,523,523,523,523,523, -4},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,5,509,6,6,529, -4},
    {529,529,529,529,529,529,529,529,529,6,529,529,529,529,6,6,6,6,6,6,6, -4},
    {530,530,530,530,530,530,530,530,12,7,530,530,530,530,530,530,530,530,530,530,530, -4},
    {517,517,517,517,517,517,517,517,14,7,517,517,517,517,517,517,517,517,517,517,517, -4},
    {-3,-3,-3,-3,-3,-3,-3,-3,-3,12,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3, -4},
    {530,530,530,530,530,530,530,530,12,10,530,530,530,530,530,530,530,530,530,530,530, -4},
    {518,518,518,518,518,518,518,518,14,7,518,518,518,518,518,518,518,518,518,518,518, -4},
    {530,530,530,530,530,530,530,530,530,12,530,530,530,530,530,530,530,530,530,530,530, -4}};

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  /**************************************************************
 *These variables will be used for important infomation         *
 *regaurding our .lst, .dbg, and .P1 files. The .open functions *
 *beneath this are to open the files and get the ostream ready  *
 *to write to those files.                                      *
 ***************************************************************/
  input.open(filename);
  file_error = FILE_ERR;
  pos = 0;
  errors = 0;
  linenum = 0;
  line = "";

  listing.open("TeamH.lst", ios::trunc);
  if(!listing.is_open()) {
    cout << "error: .lst file did not open!" << endl;
    exit(1);
    }

  test1.open("test1.P1", ios::trunc);
  if(!listing.is_open()) {
    cout << "error: .p1 file did not open!" << endl;
    exit(1);
    }
 
  debug.open("TeamH.dbg", ios::trunc);
  if(!debug.is_open()) {
    cout << "error: .dbg file did not open!" << endl;
    exit(1);
  }

  /**********************************************************************
   *  ChartoInt is a map that we made to change any characters          *
   * to an integer value, that we can then use in our table 'stateTable'*
   *********************************************************************/
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
  charToInt["d"] = 16;
  charToInt["e"] = 18;
  charToInt["f"] = 18;
  charToInt["g"] = 18;
  charToInt["h"] = 18;
  charToInt["i"] = 18;
  charToInt["j"] = 18;
  charToInt["k"] = 18;
  charToInt["l"] = 18;
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
  charToInt["\\"] = 21;
  charToInt["{"] = 21;
  charToInt["}"] = 21;
  charToInt[";"] = 21;
  charToInt[":"] = 21;
  charToInt["!"] = 21;
  charToInt["@"] = 21;
  charToInt["["] = 21;
  charToInt["]"] = 21;
  



  /*********************************************************************
   * This Map is used that if the current lexeme has a question mark   *
   * We can quckily check this map to see if it is a predicate or not. *
   * If it is not. then the question mark is an error                  *
  *********************************************************************/
  predMap["number?"] = NUMBERP_T;
  predMap["symbol?"] = SYMBOLP_T;
  predMap["list?"] = LISTP_T;
  predMap["zero?"] = ZEROP_T;
  predMap["null?"] = NULLP_T;
  predMap["char?"] = CHARP_T;
  predMap["string?"] = STRINGP_T;

}

LexicalAnalyzer::~LexicalAnalyzer ()
{
  // We close the ostream file that we open.
  listing.close();
  test1.close();
  debug.close();
}

/*********************************************************************
This funcion will find legal tokens to pass to the Syntactical       *
analyzer. It does this by parsing each character of a line, and      *
changing that character to a number. That number is then passed      *
to the stateTable in which we update which 'state' we are in. The    *
state will return a valid identifier if the number can be subtracted *
by 500 and be >= 0 and <= 30                                         *
*********************************************************************/
token_type LexicalAnalyzer::GetToken ()
{
  string currChar;
  if(!input.is_open()) {
      ReportError("file failed to open!");
      return file_error;
  }

   /*******************************
   * Make Sure we have good input *
   ********************************/
  while (! input.eof()) {
    if(listing.fail()){
      cout << "Listing failed to write" << endl;
     }
    if(test1.fail()){
      cout << "Test1 failed to write" << endl;
    }

    /****************************************************************
     * Set our start state to 0, get the current line,              *
     * Increment the line number for .lst file, set our position    *
     * index to 0, for the .lst file. If our line has nothing in it *
     * we want to skip the rest of code and start this loop over    *
     ****************************************************************/
    int startState = 0;
    lexeme = "";
    if(pos == line.size()) {
        debug << "getline called" << endl;
        getline(input, line);
        linenum++;
	if(line != ""){
	  listing << linenum << ": " << line << endl;
	}
        pos = 0;
    }

  if(line.size() == 0) { continue; }

  /**********************************************************************
   * pos == line.size would mean that we reached the end of the line    *
   * we want to check and see if the lexeme is empty or not.            *
   * If it is not empty we will write the token name  of the lexeme to  *
   * our .P1 file. then break out of the while loop, and go back to the *
   * previous while loop, and get the next line                         *
   *********************************************************************/
    while(true){
        if(pos == line.size()) {
            if(lexeme != "")
            {
	      test1 << GetTokenName(token_type(stateTable[startState][0] - 500)) << " " << lexeme << endl; 
            }
            break;
        }
	/***************************************************************************
	* We are going to find the current Character, and then convert             *
        * that char into a number we can use inside of our stateTable.             *
        * We keep not of our previous state to handle not bombing out of           *
        * our previous lexeme in the chance that we get an error. See the          *
        * last else if statement. If our startState can be subtracted by 500 and   *
        * return a value between 0 and 30, we know that we have a _T key.          * 
        * we check if the lex is an IDENT key cause if it is, we need to check     *
        * our pred map, and if we add the current char to our lexeme (given that   *
        * it is a ?) we can find if our lexeme is P_T. We then put the values into *
        * our .P1 file.                                                            *
	****************************************************************************/
	currChar = line[pos];
	int tableColumn = charToInt[currChar];
	prevState = startState;
	startState = stateTable[startState][tableColumn];
	
	debug << "start state: " << prevState << " new state: " << startState << " table Column: " << tableColumn  << " cur token: " << currChar << endl;
	if(startState - 500 >= 0 && startState - 500 <= 30){
	  token_type lex = token_type(startState - 500);
	  if(lex != IDENT_T && lex != NUMLIT_T){
	    if(currChar != " ") { lexeme += currChar; }
	    pos++;
	  } else if(lex == IDENT_T) {
	    if(predMap.count(lexeme + currChar)) {
	      lexeme += currChar;
	      lex = predMap[lexeme];
	      pos++;
	    }
	  }
	  test1 << GetTokenName(lex) << ' ';
	  test1 << lexeme << endl;
	  return lex;

	  /*************************************************************************
	  * if our start state goes to -3 that means we were builing a numlit_t,   *
	  * and we got a value that we can't accept like '.a' or '-1.d'            *
          **************************************************************************/
	} else if(startState == -3) {                                             
	  ReportError( to_string(linenum) + ": unexpected '" + currChar + "' at position " + to_string(pos + 1));
	  pos++;
          errors++;
	  test1 << GetTokenName(token_type(ERROR_T)) << ' ';
	  test1 << currChar << endl;
          return token_type(ERROR_T);

	  /*********************************************************************************************
	   * A start state of -4 and an empty lexeme means we found an invalid character like '^'.     * 
	   * this meant that we foudn it on it's own and that we were not building up lexeme before it * 
	   * that might get bombed out.                                                                *
	  *********************************************************************************************/
	} else if(startState == -4 && lexeme == "") {
	  ReportError(to_string(linenum) + ": unexpected '" + currChar + "' at position " + to_string(pos + 1));
	  pos++;
	  errors++;
	  test1 << GetTokenName(token_type(ERROR_T)) << ' ';
	  test1 << currChar << endl;
	  return token_type(ERROR_T);
	  /*********************************************************************************************************
	   * This else if  handles if we have 'adsfsadsf?asdfadsf' or anything like that. we have two IDENT_T and  *
	   * and and ERROR_T in the middle. This stores and gets us the first IDENT_T and puts it in our           *
           * .P1 file, and then it will be able to handle the -4 on the next loop because the lexeme will be empty *
           * and we wont lose our IDENT_T before the error                                                         *
	   ********************************************************************************************************/
	} else if(startState == -4 && lexeme != "") {
	  test1 << GetTokenName(token_type(stateTable[prevState][0] - 500)) << " " << lexeme << endl; 
	  startState = 0;
	  lexeme = "";
	} else {
	  pos++;
	  if(currChar != " ") { lexeme += currChar; }
	}
    }
  }
  input.close();
  listing << errors << ' ' << "error(s) found" << endl;
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
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
  // This function will be called to write an error message to a file
  listing << "error on line " + msg << endl;
}
