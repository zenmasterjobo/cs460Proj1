#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"
#include <cstdlib>

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	fstream output, debug;

	output.open("lex.lst", ios::out | ios::trunc);
	if(!output.is_open()) {
		cout << "error: .lst file did not open!" << endl;
		exit(1);
	}

	debug.open("lex.dbg", ios::out | ios::trunc);
	if(!debug.is_open()) {
		cout << "error: .dbg file did not open!" << endl;
		exit(2);
	}

	while ((t = lex->GetToken()) != EOF_T)
	{
		cout << lex->GetTokenName(t) << endl;
		cout << endl;
		// get a token
		// write its name to the debug file
		// write the corresponding lexeme to the debug file
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
