#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>

using namespace std;

class translate
{
public:
    vector<string> row;
    vector<vector<string>> vocabulary;

    translate(/* args */);
    ~translate();

    void add_word(string romana, string english);
    void translate_csv(string file_name, int c);
    string translate_word(string word, int c);
    void build_dictionary();
};

translate::translate()
{
}

translate::~translate()
{
}

void translate ::add_word(string romana, string english)
{
    // row este un vector cu 2 elemente : ro-en
    row.clear();
    row.push_back(romana);
    row.push_back(english);
    vocabulary.push_back(row);
    row.clear();
}

string translate::translate_word(string word, int c)
{
    int d;
    if (c == 0)
        d = 1;
    else
        d = 0;
    for (int k = 0; k < vocabulary.size(); k++)
        if (word == vocabulary[k][c])
            word = vocabulary[k][d];
    return word;
}

void translate::build_dictionary()
{
    add_word("Chirie"   , "Rent");
    add_word("Meniu"    , "Menu");
    add_word("Cazare"   , "Accommodation");
    add_word("Machiaj"  , "Makeup");
    add_word("Mancare"  , "Foods");
    add_word("Bauturi"  , "Drinks");
    add_word("Zile"     , "Days");
    add_word("costuri"  , "costs");
    add_word("meniu"    , "menu");
    add_word("nume"     , "names");
    add_word("prenume"  , "surname");
}

// c =0 ro2en c =1 en2ro
void translate::translate_csv(string file_name, int c)
{
    build_dictionary();
    vector<vector<string>> content; 
    vector<string> row;
    string line, word;

    fstream file;
    file.open(file_name, ios::in);

    while (getline(file, line))
    {
        row.clear();
        stringstream str(line);
        int i = 0;

        while (getline(str, word, ' '))
        {

            word = translate_word(word, c);

            row.push_back(word); // pune pe linie cate un cuvant

            i++;
        }
        content.push_back(row); // pune in content cate o linie
    }

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
            data << content[i][j] << " ";
            // cout << content[i][j] << " ";
        }
        data << "\n";
        // cout << "\n";
    }
    data.close();
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name = file_name.erase(0, 4);
    cout << file_name << endl;
    string translatedWord = translate_word(file_name, c);
    rename(("csv/" + file_name + ".csv").c_str(), ("csv/" + translatedWord + ".csv").c_str());
}
