#include<iostream>
int yyparse();
int main(int argc, char **argv)
{
  if ((argc > 1) && (std::freopen(argv[1], "r", stdin) == nullptr))
  {
    std::cerr << argv[0] << ": File " << argv[1] << " cannot be opened.\n";
    return 1;
  }
  
  yyparse();

  return 0;
}
