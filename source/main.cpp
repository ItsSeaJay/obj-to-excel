
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

  int const MAX_VERTICIES = 4;

  struct Face
  {
      Vertex verticies[MAX_VERTICIES];
  };

  std::vector<Face> faces;
  std::ifstream objectFile;

  objectFile.open(path, std::ios::in);

  if (!objectFile.fail())
  {
    std::string line;

    while (std::getline(objectFile, line))
    {
      std::istringstream verificationBuffer(line);
      std::istringstream inputBuffer(line);
      std::string token, marker, skip;

      // Find lines containing verticies
      if (line.find("v ") != std::string::npos)
      {
        double x, y, z;

        inputBuffer >> marker >> x >> y >> z;
        // std::cout << x << '\0' << y << '\0' << z << '\n';

        verticies.push_back({x, y, z});
      }

      // Find the faces
      if (line.find("f ") != std::string::npos)
      {
        int const MAX_INDICIES = 4;
        int faceIndicies[MAX_INDICIES] = {
          0,
          0,
          0,
          0
        };
        int const MAX_NORMALS = 4;
        int faceNormals[MAX_NORMALS] = {
          0,
          0,
          0,
          0
        };
        int tokenCount = 0;
        int quadTokens = 5;
        int triTokens = quadTokens - 1;

        // Find out whether the face is a tri or a quad
        // TODO: Make this a function
        while (verificationBuffer >> token)
        {
          ++tokenCount;
        }

        if (tokenCount == quadTokens)
        {
          inputBuffer >> marker >> faceIndicies[0] >> skip >> faceNormals[0];
          inputBuffer >> faceIndicies[1] >> skip >> faceNormals[1];
          inputBuffer >> faceIndicies[2] >> skip >> faceNormals[2];
          inputBuffer >> faceIndicies[3] >> skip >> faceNormals[3];

          faces.push_back({
            {
              verticies[faceIndicies[0]],
              verticies[faceIndicies[1]],
              verticies[faceIndicies[2]],
              verticies[faceIndicies[3]],
            }
          });
        }
        else if (tokenCount == triTokens)
        {
          /* code */
        }
        else
        {
          /* code */
        }
      }
    }

    // Check that the verticies have been stored correctly
    for(std::vector<int>::size_type i = 0; i != verticies.size(); ++i)
    {
        // std::cout << verticies[i].x << verticies[i].y << verticies[i].z << '\n';
    }

    // Check that the face verticies have also been stored correctly
    for(std::vector<int>::size_type i = 0; i != faces.size(); ++i)
    {
        for (int j = 0; j < MAX_VERTICIES; ++j)
        {
          std::cout << faces[i].verticies[j].x;
          std::cout << faces[i].verticies[j].y;
          std::cout << faces[i].verticies[j].z;
        }
    }
  }
  else
  {
    std::cout << "Error: " << path << " is an invalid file path";
  }

  objectFile.close();
}
