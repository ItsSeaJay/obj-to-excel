
/*
  OBJ to Excel by Callum J. Cummings v0.0.2
  Released under the MIT License
  See LICENSE.txt or https://opensource.org/licenses/MIT for more information.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char const *argv[])
{
  struct Program
  {
    std::string name = "OBJ to Excel";
    std::string version = "v0.0.2";
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
  std::ifstream objectFile(argv[1]);
  std::string line;

  if (argc > 1)
  {
    if (objectFile.is_open())
    {
      while (getline(objectFile, line))
      {
        std::cout << line;
      }

      objectFile.close();
    }
    else
    {
      std::cout << "Error: invalid file path";
    }
  }
  else
  {
    std::cout << program.name << '\0' << program.version;
  }

  return 0;
}
