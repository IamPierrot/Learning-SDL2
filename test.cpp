#include <iostream>

struct HauMilf
{
     HauMilf(int t, std::string n) : age(t), name(n)
     {
     }

     HauMilf(const HauMilf &person)
     {
          name = person.name + "(ban sao)";
     }
     int age;
     std::string name;
     bool con_zin = true;
};

void pha_zin(HauMilf person)
{
     std::cout << "thuc hien lmao voi " << person.name << std::endl;
     person.con_zin = false;
}

int main()
{
     HauMilf hauthu2(16, "milk");
     std::cout << "Truoc khi thay doi: " << (hauthu2.con_zin ? "Ngol" : "Chim cook") << std::endl;

     pha_zin(hauthu2);

     std::cout << "Sau khi thay doi: " << (hauthu2.con_zin ? "Ngol" : "Chim cook") << std::endl;

     return 0;
}