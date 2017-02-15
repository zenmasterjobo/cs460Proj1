#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"
#include "LexicalAnalyzer.h"
int main (int argc, char * argv[])
{
  
  if (argc < 2){
    printf ("format: proj1 <filename>\n");
    exit (1);
  }
  
  LexicalAnalyzer *lex = new LexicalAnalyzer(argv[1]);
  token_type test = lex->GetToken();
  cout << lex->GetTokenName(test) << endl;
  
  
//SetLimits ();
//SyntacticalAnalyzer parser (argv[1]);
//
	return 0;
}
