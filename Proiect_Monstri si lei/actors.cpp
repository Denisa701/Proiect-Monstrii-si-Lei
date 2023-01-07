#include <iostream>
#include <string.h>
#include <fstream>

#include "random.cpp"

using namespace std;

class oneActor
{
public:
   string monster;
   string dieta;
   string name, surname, rol;
   int age;
   oneActor();
   oneActor(string name, string surname);
   oneActor(int age);
   virtual void add_diet()
   {
      string diet[3] = {"flexitarian", "vegetarian", "anything"};
      dieta = diet[rand() % 3];
   }

   virtual void add_monsterClass()
   {
      string monsterClass[5] = {"vampire", "werewolf", "seer", "mermaid", "human"};
      monster = monsterClass[rand() % 5];
   }
};

oneActor::oneActor()
{
}

oneActor::oneActor(string name, string surname)
{
   name = name;
   surname = surname;
}

oneActor::oneActor(int age)
{
   age = age;
}

class actors : public oneActor
{
public:
   int vampires, werewolves, seers, mermaids, humans;
   int veg, flex, any;

   actors();
   void add_fig(int n);
   void add_diet(string file_name);
   void add_monsterClass(string file_name);
};

actors::actors()
{
   vampires = 0;
   werewolves = 0;
   seers = 0;
   mermaids = 0;
   humans = 0;
   flex = 0;
   any = 0;
   veg = 0;
}

void actors::add_fig(int n)
{
   int i = 0;
   while (i < n)
   {

      string figName = random<string>("csv/names.csv");
      string figSurname = random<string>("csv/surnames.csv");

      ofstream file;
      file.open("csv/wednesdayCast.csv", std::ios_base::app);
      file << n << "." << figName << " " << figSurname << ",figurant," << endl;
      file.close();

      i++;
   }
}

void actors::add_diet( string file_name)
{
   string diet[3] = {"flexitarian", "vegetarian", "anything"};
   vector<vector<string>> content = read(file_name);

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
         try
         {
            if (j < 2)
               data << content[i][j] << " , ";
            else
               throw j;
         }
         catch (int j)
         {
            int z = rand() % 3;
            data << content[i][j] << " , " << diet[z]<< " , ";
            switch (z)
            {
            case 0:
               flex++;
               break;
            case 1:
               veg++;
               break;

            case 2:
               any++;
               break;
            }
         }
      }
      data << "\n";
   }

   data.close();
}

void actors::add_monsterClass(string file_name)
{
   string monsterClass[5] = {"vampire", "werewolf", "seer", "mermaid", "human"};
   vector<vector<string>> content = read("csv/wednesdayCast.csv");

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
         try
         {
            if (j == 0)
               data << content[i][j] << " , ";
            else
               throw j;
         }
         catch (int j)
         {
            int z = rand() % 5;
            data << content[i][j] << " , " << monsterClass[z];
            switch (z)
            {
            case 0:
               vampires++;
               break;
            case 1:
               werewolves++;
               break;
            case 2:
               seers++;
               break;
            case 3:
               mermaids++;
               break;
            case 4:
               humans++;
               break;
            }
         }
      }
      data << "\n";
   }

   data.close();
}

// int main()
// {
//    actors om;
//    om.add_menu();
//    cout << om.flex<< " "<< om.any<<" "<< om.veg<<endl;
//    om.add_monsterClass();
//    cout << om.flex+om.veg+om.any<<endl;
// }