#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
  struct Program
  {
    std::string name = "OBJ to Excel";
    std::string version = "v0.0.1";
  };

  struct Vertex
  {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };

  struct Face
  {
    Vertex a;
    Vertex b;
    Vertex c;
  };

  Program program;

  if (argc > 1)
  {
    for (int i = 0; i < argc; ++i)
    {
      std::cout << argv[i];
    }
  }
  else
  {
    std::cout << program.name << '\0' << program.version;
  }

  return 0;
}
