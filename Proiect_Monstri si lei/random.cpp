#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

// pentru alegerea meniului se va pune total lines =1; el va fi folosit pentru alegerea unui meniu pentru fiecare zi
// alege random o linie din csv si o returneaza
// paramentrul total_lines este initializat cu prima line de unde citeste~deobicei 0
template <class A>
A random(string myFile)
{
  string line;
  vector<A> lines;
  int total_lines = 0;

  ifstream file(myFile);

  while (getline( file,line))
  {
    line.pop_back();
    total_lines++;
    lines.push_back(line);
  }

  int random_number = rand() % total_lines;

  return lines[random_number];
}

vector<vector<string>> read(string file_name)
{
  vector<vector<string>> content;             // 2-D vector de stringuri
  vector<string> row;
  string line, word;
  fstream file(file_name, ios::in);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      row.clear();

      stringstream str(line);
      int i = 0;
      while (getline(str, word, ','))
      {
        // pentru a scapa de /n in plus
        if (i == 1)
          word.pop_back();

        row.push_back(word); // pune pe linie cate un cuvant
        i++;
      }
      content.push_back(row); // pune in content cate o linie
    }
  }
  else
    cerr << "Could not open the file\n";
  return content;
  content.clear();
}

void write(string file_name, vector<vector<string>> content)
{
  ofstream data;

  data.open(file_name);
  if (!data)
  {
    cerr << "Error: file could not be opened" << endl;
  }

  for (int i = 0; i < content.size(); i++)
  {
    for (int j = 0; j < content[i].size(); j++)
    {
      data << content[i][j] << ",";
    }
    data << "\n";
  }

  data.close();
  content.clear();
}
