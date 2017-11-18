
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

  Program program;

  void parseObjectFile(std::string const filePath);

  if (argc > 1)
  {
    parseObjectFile(argv[1]);
  }
  else
  {
    std::cout << program.name << '\0' << program.version;
  }

  return 0;
}

void parseObjectFile(std::string const path)
{
  struct Vertex
  {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
  };

  struct Face
  {
    Vertex a;
    Vertex b;
    Vertex c;
  };

  std::ifstream objectFile;

  objectFile.open(path, std::ios::in);

  if (!objectFile.fail())
  {
    std::string line;

    while (std::getline(objectFile, line))
    {
      // Find the verticies
      if (line.find("v ") != std::string::npos)
      {
        float x, y, z;

        std::cout << line << '\n';
      }
    }
  }
  else
  {
    std::cout << "Error: " << path << " is an invalid file path";
  }

  objectFile.close();
}
