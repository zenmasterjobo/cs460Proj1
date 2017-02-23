#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

enum token_type {NONE = -1,
		 EOF_T,      // 0
		 NUM_TOKENS, // 1
                 CONS_T = 2, // 2
		 IF_T,       // 3
		 WHILE_T,    // 4	
		 AND_T,      // 5		
		 OR_T,       // 6
		 NOT_T,      // 7
		 DEFINE_T,   // 8
		 LISTOP_T,   // 9
		 NUMBERP_T,  // 10
		 SYMBOLP_T,  // 11
		 LISTP_T,    // 12
		 ZEROP_T,    // 13
		 NULLP_T,    // 14
		 CHARP_T,    // 15
		 STRINGP_T,  // 16
		 PLUS_T,     // 17
		 MINUS_T,    // 18
		 DIV_T,      // 19
		 MULT_T,     // 20
		 EQUALTO_T,  // 21		
		 GT_T,       // 22
		 LT_T,       // 23
		 GTE_T,      // 24
		 LTE_T,      // 25
		 LPAREN_T,   // 26
		 RPAREN_T,   // 27
		 QUOTE_T,    // 28
		 IDENT_T,    // 29
		 NUMLIT_T,   // 30
		 ERROR_T,	// 31
		 FILE_ERR = -2,
		 NUM_ERR = -3,
         CURRCHAR_ERR = -4};


class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
    private:
	ifstream input;
	ofstream listing;
	ofstream debug;
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
	token_type file_error;
        map<string, int> charToInt;
	map<string, token_type > predMap;

};
	
#endif
