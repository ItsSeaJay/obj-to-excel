
/*
  OBJ to Excel by Callum John v0.0.3
  Released under the MIT License
  See LICENSE.txt or https://opensource.org/licenses/MIT for more information.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Vertex
{
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  double w = 1.0;
};

int const MAX_FACE_VERTICIES = 4;

struct Face
{
    Vertex verticies[MAX_FACE_VERTICIES];
};

int main(int argc, char const *argv[])
{
  struct Program
  {
    std::string name = "OBJ to Excel";
    std::string version = "v0.0.3";
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
  std::vector<Vertex> verticies;
  std::vector<Face> faces;
  std::ifstream objectFile(path);

  void pushVertex(
    std::string const currentLine,
    std::vector<Vertex>& verticies
  );

  void pushFace(
    std::string const currentLine,
    std::vector<Vertex> const verticies,
    std::vector<Face>& faces
  );

  int getFaceCount(std::string const currentLine);

  void outputVerticies(std::vector<Vertex> const verticies);
  void outputFaces(std::vector<Face> const faces);
  void horizontalRule(int const length);
  void outputCSV(std::string const path, std::vector<Face> const faces);

  if (objectFile.is_open())
  {
    std::string currentLine;

    while (std::getline(objectFile, currentLine))
    {
      std::istringstream verificationBuffer(currentLine);
      std::string token, marker;

      if (currentLine.find("v ") != std::string::npos)
      {
        pushVertex(currentLine, verticies);
      }

      if (currentLine.find("f ") != std::string::npos)
      {
        int tokenCount = 0;
        const int QUAD_TOKENS = 5;

        tokenCount = getFaceCount(currentLine);

        if (tokenCount == QUAD_TOKENS)
        {
          pushFace(currentLine, verticies, faces);
        }
        else
        {
          std::cout << "Error: invalid file - all object faces must be quads.";
          return;
        }
      }
    }

    std::cout << '\n' << "Found the following verticies: " << '\n';
    horizontalRule(80);
    outputVerticies(verticies);
    horizontalRule(80);
    outputFaces(faces);
    horizontalRule(80);
    outputCSV(path, faces);
  }
  else
  {
    std::cout << "Error: " << path << " is an invalid file path";
  }

  objectFile.close();
}

void pushVertex(std::string const currentLine, std::vector<Vertex>& verticies)
{
  std::istringstream buffer(currentLine);
  std::string marker;
  double x, y, z;
  double w = 1.0;

  buffer >> marker >> x >> y >> z;

  verticies.push_back({x, y, z, w});
}

void pushFace(
  std::string const currentLine,
  std::vector<Vertex> const verticies,
  std::vector<Face>& faces
)
{
  std::istringstream buffer(currentLine);
  std::string marker;
  int const MAX_INDICIES = 4;
  int faceIndicies[MAX_INDICIES] =
  {
    0,
    0,
    0,
    0
  };

  buffer >> marker;
  buffer >> faceIndicies[0];
  buffer >> faceIndicies[1];
  buffer >> faceIndicies[2];
  buffer >> faceIndicies[3];

  for (int i = 0; i < MAX_INDICIES; i++)
  {
    faceIndicies[i] -= 1;
  }

  faces.push_back({
    {
      verticies[faceIndicies[0]],
      verticies[faceIndicies[1]],
      verticies[faceIndicies[2]],
      verticies[faceIndicies[3]]
    }
  });
}

int getFaceCount(std::string currentLine)
{
  int faceCount = 0;
  std::istringstream buffer(currentLine);
  std::string token;

  while (buffer >> token)
  {
    ++faceCount;
  }

  return faceCount;
}

void outputVerticies(std::vector<Vertex> const verticies)
{
  std::cout << "Verticies size: " << verticies.size() << '\n';

  for(std::vector<int>::size_type i = 0; i != verticies.size(); i++)
  {
    std::cout << verticies[i].x << '\0';
    std::cout << verticies[i].y << '\0';
    std::cout << verticies[i].z << '\0';
    std::cout << verticies[i].w << '\n';
  }
}

void outputFaces(std::vector<Face> const faces)
{
  std::cout << "Faces size: " << faces.size() << '\n';

  for(std::vector<int>::size_type i = 0; i < faces.size(); i++)
  {
    for (int j = 0; j < MAX_FACE_VERTICIES; ++j)
    {
      std::cout << faces[i].verticies[j].x << '\0';
      std::cout << faces[i].verticies[j].y << '\0';
      std::cout << faces[i].verticies[j].z << '\0';
      std::cout << faces[i].verticies[j].w << '\n';
    }
  }
}

void horizontalRule(int const length)
{
  for (int i = 0; i < length; ++i)
  {
    std::cout << '~';
  }
  std::cout << '\n';
}

void outputCSV(std::string const path, std::vector<Face> const faces)
{
  std::ofstream CSVFile(path + ".csv");

  if (CSVFile.is_open())
  {
    for(std::vector<int>::size_type i = 0; i < faces.size(); i++)
    {
      for (int j = 0; j < MAX_FACE_VERTICIES; ++j)
      {
        CSVFile << faces[i].verticies[j].x << ',\0';
        CSVFile << faces[i].verticies[j].y << ',\0';
        CSVFile << faces[i].verticies[j].z << ',\0';
        CSVFile << faces[i].verticies[j].w << '\n';
      }
    }
    std::cout << "Wrote face values to: " << path + ".csv";
  }
  else
  {
    std::cout << "Error: " << path << " unable to write CSV file";
  }

  CSVFile.close();
}
