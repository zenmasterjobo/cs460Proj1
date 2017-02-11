#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include <map>

using namespace std;

map<string, string> lexMap;
static string token_names[] = {	"EOF_T" }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
    lexMap.insert(pair<string, string>("cons", "CONS_T"));
    lexMap.insert(pair<string, string>("if", "IF_T"));
    lexMap.insert(pair<string, string>("while", "WHILE_T"));
    lexMap.insert(pair<string, string>("and", "AND_T"));
    lexMap.insert(pair<string, string>("or", "OR_T"));
    lexMap.insert(pair<string, string>("not", "NOT_T"));
    lexMap.insert(pair<string, string>("define", "DEFINE_T"));
    //NEED LISTOF_T

    lexMap.insert(pair<string, string>("number?", "NUMBERP_T"));
    lexMap.insert(pair<string, string>("symbol?", "SYMBOLP_T"));
    lexMap.insert(pair<string, string>("list?", "LISTP_T"));
    lexMap.insert(pair<string, string>("zero?", "ZEROP_T"));
    lexMap.insert(pair<string, string>("null?", "NULLP_T"));
    lexMap.insert(pair<string, string>("char?", "CHARP_T"));
    lexMap.insert(pair<string, string>("string?", "STRINGP_T"));

    lexMap.insert(pair<string, string>("+", "PLUS_T"));
    lexMap.insert(pair<string, string>("-", "MINUS_T"));
    lexMap.insert(pair<string, string>("/", "DIV_T"));
    lexMap.insert(pair<string, string>("*", "MULT_T"));

    lexMap.insert(pair<string, string>("=", "EQUALTO_T"));
    lexMap.insert(pair<string, string>(">", "GT_T"));
    lexMap.insert(pair<string, string>("<", "LT_T"));
    lexMap.insert(pair<string, string>(">=", "GTE_T"));
    lexMap.insert(pair<string, string>("<=", "LTE_T"));

    lexMap.insert(pair<string, string>("(", "LPAREN_T"));
    lexMap.insert(pair<string, string>(")", "RPAREN_T"));
    lexMap.insert(pair<string, string>("'", "QUOTE_T"));

    lexMap.insert(pair<string, string>("", "EOF_T"));
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return "";
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
