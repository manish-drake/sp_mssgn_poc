#include <iostream>
#include "csvlist.h"

using namespace std;
#define UNUSED(x) (void)(x)
int main(int argc, char* argv[]){
    UNUSED(argc);
    UNUSED(argv);
    
    CSVList csv("name,age,class");
    csv.Add("student1,16,IX");
    csv.Add("student2,17,IX");
    csv.Add("student3,15,IX");
    csv.Add("student4,16,IX");
    for(const auto &row: csv)
    {
        if(row["name1"])
        {
            auto p = *row["name1"];
        }
        std::cout << row[0] << std::endl;
    }  
    csv.Save("test1.csv");
    CSVList csv_read;
    csv_read.Open("test1.csv");
    csv_read.Save("temp.txt");
  
   
    cin.ignore();
    return 0;
}
