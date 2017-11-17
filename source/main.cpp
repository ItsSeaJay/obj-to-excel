#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{


  if (argc > 1)
  {
    for (int i = 0; i < argc; ++i)
    {
      std::cout << argv[i];
    }
  }
  else
  {
    std::cout << "Bar";
  }

  return 0;
}
