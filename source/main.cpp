
/*
  OBJ to Excel by Callum J. Cummings v0.0.2
  Released under the MIT License
  See LICENSE.txt or https://opensource.org/licenses/MIT for more information.
*/

#include <algorithm>
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

  int const MAX_FACE_VERTICIES = 4;

  struct Face
  {
      Vertex verticies[MAX_FACE_VERTICIES];
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
      std::string token, marker;

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
        int faceIndicies[MAX_INDICIES] =
        {
          0,
          0,
          0,
          0
        };
        int const MAX_NORMALS = 4;
        int faceNormals[MAX_NORMALS] =
        {
          0,
          0,
          0,
          0
        };
        int tokenCount = 0;
        const int QUAD_TOKENS = 5;

        // Find out whether the face is a tri or a quad
        // TODO: Make this a function
        while (verificationBuffer >> token)
        {
          ++tokenCount;
        }

        if (tokenCount == QUAD_TOKENS)
        {
          std::replace(line.begin(), line.end(), '/', '\0');
          std::cout << line << '\n';

          inputBuffer >> marker >> faceIndicies[0] >> faceNormals[0];
          inputBuffer >> faceIndicies[1] >> faceNormals[1];
          inputBuffer >> faceIndicies[2] >> faceNormals[2];
          inputBuffer >> faceIndicies[3] >> faceNormals[3];

          faces.push_back({
            {
              verticies[faceIndicies[0]],
              verticies[faceIndicies[1]],
              verticies[faceIndicies[2]],
              verticies[faceIndicies[3]]
            }
          });
        }
        else
        {
          std::cout << "Error: all object faces must be quads.";
        }
      }
    }

    // Check that the verticies have been stored correctly
    for (std::vector<int>::size_type i = 0; i != verticies.size(); ++i)
    {
      std::cout << verticies[i].x;
      std::cout << '\0';
      std::cout << verticies[i].y;
      std::cout << '\0';
      std::cout << verticies[i].z;
      std::cout << '\n';
    }

    // Check that the face verticies have also been stored correctly
    // for(std::vector<int>::size_type i = 0; i != faces.size(); ++i)
    // {
    //     for (int j = 0; j < MAX_FACE_VERTICIES; ++j)
    //     {
    //       std::cout << faces[i].verticies[j].x;
    //       std::cout << '\0';
    //       std::cout << faces[i].verticies[j].y;
    //       std::cout << '\0';
    //       std::cout << faces[i].verticies[j].z;
    //       std::cout << '\n';
    //     }
    // }
  }
  else
  {
    std::cout << "Error: " << path << " is an invalid file path";
  }

  objectFile.close();
}
