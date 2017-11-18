
/*
  OBJ to Excel by Callum J. Cummings v0.0.2
  Released under the MIT License
  See LICENSE.txt or https://opensource.org/licenses/MIT for more information.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };

  std::vector<Vertex> verticies;

  struct Index
  {
    Vertex a;
    Vertex b;
    Vertex c;
    Vertex d;
  };

  std::vector<Index> indicies;
  std::ifstream objectFile;

  objectFile.open(path, std::ios::in);

  if (!objectFile.fail())
  {
    std::string line;

    while (std::getline(objectFile, line))
    {
      std::istringstream buffer(line);
      std::string token, marker;

      // Find lines containing verticies
      if (line.find("v ") != std::string::npos)
      {
        double x, y, z;

        buffer >> marker >> x >> y >> z;
        std::cout << marker<< '\0' << x << '\0' << y << '\0' << z << '\n';

        verticies.push_back({x, y, z});
      }

      // Find the faces
      if (line.find("f ") != std::string::npos)
      {
        // Obtain the indicies
        // std::cout << line << '\n';
      }
    }
  }
  else
  {
    std::cout << "Error: " << path << " is an invalid file path";
  }

  objectFile.close();
}
