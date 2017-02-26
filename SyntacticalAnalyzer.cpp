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

	while ((t = lex->GetToken()) != EOF_T)
	{
	  // This will run the Lexical Analyzer GetToken()
	  // until there are no more lines left in the input file.
	  // GetToken handles all ostream file output, along with
	  // the finding of lexemes 
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
