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

    cout << "Running lexical analyzer on: " << argv[1] << endl;    

  SetLimits ();
  SyntacticalAnalyzer parser (argv[1]);

	return 0;
}
