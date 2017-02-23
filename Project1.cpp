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
//  token_type result;
//  LexicalAnalyzer *lex = new LexicalAnalyzer(argv[1]);
//  do{
//    result = lex->GetToken();
//    if(result >= 0)
//      cout << lex->GetTokenName(result) << endl;
//    cout << endl;
//  } while(result > 0);
  
  SetLimits ();
  SyntacticalAnalyzer parser (argv[1]);

	return 0;
}
