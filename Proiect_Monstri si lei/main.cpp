#include <iostream>
#include <fstream>
#include "cost.cpp"
#include "translate.cpp"

using namespace std;

template <class T>
long long int dolarConvert(T c)
{
    // 1 ron = 0.22 $
    return c * 0.22;
}

void build_costs()
{
    ofstream file;
    file.open("csv/costs.csv");
    cost obj(30), obj2(45), obj3(60), obj4(100);
    file << "Days , Rent , (dollars) , Accommodation , (dollars) , Transport , (dollars) , Makeup , (dollars) , Foods & Drinks , (dollars)" << endl;
    file << 30
         << " , " << obj.rent()           << " , " << dolarConvert<int>(obj.rent())
         << " , " << obj.accommodation()  << " , " << dolarConvert<long int>(obj.accommodation())
         << " , " << obj.transport()      << " , " << dolarConvert<int>(obj.transport())
         << " , " << obj.makeup()         << " , " << dolarConvert<int>(obj.makeup()) 
         << " , " << (long int)(obj.menu() + obj.liquids()) << " , " << dolarConvert<long int>(obj.menu() + obj.liquids())<< endl;

    file << 45
         << " , " << obj2.rent()          << " , " << dolarConvert<int>(obj2.rent())
         << " , " << obj2.accommodation() << " , " << dolarConvert<long int>(obj2.accommodation())
         << " , " << obj2.transport()     << " , " << dolarConvert<int>(obj2.transport())
         << " , " << obj2.makeup()        << " , " << dolarConvert<int>(obj2.makeup())
         << " , " << (long int)(obj2.menu() + obj2.liquids()) << " , " << dolarConvert<long int>(obj2.menu() + obj2.liquids()) << " , " << endl;
    file << 60
         << " , " << obj3.rent()          << " , " << dolarConvert<int>(obj3.rent())
         << " , " << obj3.accommodation() << " , " << dolarConvert<long int>(obj2.accommodation())
         << " , " << obj3.transport()     << " , " << dolarConvert<int>(obj2.transport())
         << " , " << obj3.makeup()        << " , " << dolarConvert<int>(obj2.makeup()) 
         << " , " << (long int)(obj3.menu() + obj3.liquids()) << " , " << dolarConvert<long int>(obj2.menu() + obj2.liquids())<< " , " << endl;
    file << 100
         << " , " << obj4.rent()          << " , " << dolarConvert<int>(obj4.rent())
         << " , " << obj4.accommodation() << " , " << dolarConvert<long int>(obj2.accommodation())
         << " , " << obj4.transport()     << " , " << dolarConvert<int>(obj2.transport())
         << " , " << obj4.makeup()        << " , " << dolarConvert<int>(obj2.makeup()) 
         << " , " << (long int)(obj4.menu() + obj4.liquids()) << " , " << dolarConvert<long int>(obj2.menu() + obj2.liquids())<< " , " << endl;
    file.close();

}

int main()
{
     build_costs();
     translate trl;
     trl.translate_csv("csv/costs.csv",1);
}
