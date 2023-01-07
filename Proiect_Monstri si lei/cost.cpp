#include <iostream>
#include <fstream>
#include "actors.cpp"

using namespace std;

// clasa cost pastreaza toate numerele de persoane

class cost
{
public:
    int days;
    int noActors;
    int mainActors;
    int figuranti;
    int maxFig;

    int priceMakeup[5];

    actors num;
    cost(int x);
    ~cost();

    int rent();
    int transport();
    long int accommodation();
    double liquids();
    int menu();
    int makeup();
};

cost::cost(int d)
{
    days = d;
    mainActors = 735;
    figuranti = 132;
    noActors = mainActors + figuranti;
    num.add_fig(figuranti);
    priceMakeup[0] = 230; // vampires
    priceMakeup[1] = 555; // werewolves
    priceMakeup[2] = 157; // seers
    priceMakeup[3] = 345; // mermaids
    priceMakeup[4] = 55;  // human
}

cost::~cost()
{
    // cout << endl;
}

// calculul chiriei pentru numarul de zile ales
int cost::rent()
{
    double rent;
    int z;
    try
    {
        z = days % 10;
        if (z == 0)
            rent = days * 10000 - days * 100 * 2;
        throw(z);
    }
    catch (int z)
    {
        // cout << days % 10 << "Zile in plus" << endl;
        rent = (days - days % 10) * 10000 - (days - days % 10) * 100 * 2 + (days % 10) * 10000;
    }
    return rent;
}

// calculul numarului de autocare folosite pentru transport dus-intors
int cost::transport()
{
    if (noActors % 50 != 0)
        return (noActors / 50 + 1) * 5680 * 2;
    else
        return (noActors / 50) * 5680 * 2;
}

// calculul cazarii la hotel=> posibil sa pot include exceptii
long int cost::accommodation()
{
    long int doubleRooms, tripleRooms;
    try
    {
        doubleRooms = mainActors / 2 * 350;
        tripleRooms = (figuranti / 3) * 420;
        int r = mainActors % 2 + figuranti % 3;
        throw r;
    }
    catch (int r)
    {
        if (r <= 2)
            doubleRooms++;
        if (r == 3)
            tripleRooms++;
    }
    // cout << tripleRooms << " " << doubleRooms << " " << days << endl;
    long int acpr = tripleRooms * doubleRooms * days;
    // cout << acpr << endl;
    return acpr;
}

// calculul costului machiajului
int cost::makeup()
{
    string file_name = "csv/wednesdayCast.csv";
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name = file_name.erase(0, 4);
    file_name = file_name + to_string(days);
    file_name = "csv/" + file_name + ".csv";

    num.add_monsterClass(file_name);
    int oneDay = num.vampires * priceMakeup[0] + num.werewolves * priceMakeup[1] + num.seers * priceMakeup[2] + num.mermaids * priceMakeup[3] + num.humans * priceMakeup[4];
    int allDays = oneDay * days;
    return allDays;
}

// calcul cost mancare si apa
double cost::liquids()
{
    int water = 2 * noActors * 6;
    int coffee = 2 * noActors * 30;
    double soda = noActors * 2 * 0.8 * 8;

    return (water + coffee + soda) * days;
}

int cost::menu()
{
    string file_name = "csv/wednesdayCast.csv";
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name.pop_back();
    file_name = file_name.erase(0, 4);
    file_name = file_name + to_string(days);
    file_name = "csv/" + file_name + ".csv";

    num.add_diet(file_name);
    // atribuirea unui numar aleator de oameni pentru fiecare meniu, gandit ca 10% pot fi flexitarieni, 30% pot fi vegetarienii si restul orice
    int vegetarian, flexitarian, anything;
    int no = days;
    long int s = 0;
    ofstream data;
    data.open("csv/menu.csv", std::ios_base::app);
    if (!data)
    {
        cerr << "Error: file could not be opened" << endl;
    }

    // calularea pretului pentru intreaga sedere daca in fiecare zi se schimba numarul de meniuri de un tip
    while (no != 0)
    {

        // numar random de oameni pentru o zi
        vegetarian = rand() % num.veg;
        flexitarian = rand() % num.flex;
        anything = noActors - vegetarian - flexitarian;

        long int menu_day = vegetarian * 33 + flexitarian * 46 + anything * 40;
        s = s + menu_day;

        // adaugarea in menu.csv
        string menu_choice = random<string>("csv/menu_choice.csv");

        data << menu_choice << "Numar flexitarieni vegetarieni orice: " << flexitarian << " " << vegetarian << " " << anything << "," << endl;
        // cout << menu_choice << endl;

        no--;
    }
    data << "Cost total " << s << endl;
    data.close();
    return s;
}

// int main()
// {
//     cost imi(30);
//     // cout << imi.menu()<<endl;
// }