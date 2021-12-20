#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 
#include <thread>        
#include <chrono> 
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;


void search(int classNum, vector< vector<string> > fullClasses, int sectionNum, 
                set<string, string> &currentClasses, int** bookedSlots, int totalClasses);
void printSolution(map<int, int> &cal, int timeSlots);
bool updateClass(string str, int** &bookedSlots, string type);
void setBackSchedule(string str, int** &bookedSlots); 

int main(int arc,char* argv[]){
    string file = argv[1];

    ifstream infile(file.c_str());

    int totalClasses;
    infile >> totalClasses;

    vector< vector<string> > fullClasses;

    //gets vector of vectors that hold each class's time sections
    for(int i = 0; i < totalClasses; i++){
        string className;
        infile >> className;
        string classSchedule;
        getline(infile, classSchedule);
        vector<string> classes;
        classes.push_back(className);
        string result = "";
        for(long unsigned int i = 0; i <= classSchedule.length(); i++){
            if((classSchedule[i] == ',') || (i == classSchedule.length() && result != "")){
                classes.push_back(result);
                result = "";
            }
            else{
                result += classSchedule[i];
            }
        }
        fullClasses.push_back(classes);
    }

    set<string,string> currentClasses;
    int* bookedSlots[5];
    for(int i = 0; i < 5; i++){
        int temp[28];
        for(int j = 0; j < 28; j++){
            temp[j] = 0;
        }
        bookedSlots[i] = temp;
    }

    search(0, fullClasses, 0, currentClasses, bookedSlots, totalClasses);

}



void search(int classNum, vector< vector<string> > fullClasses, int sectionNum, 
                set<string,string> &currentClasses, int** &bookedSlots, int totalClasses){
    
    if(classNum == totalClasses){
        //DONE, PRINT SOLUTION
    }
    else{   
        for(unsigned long int i = 1; i < fullClasses[classNum].size(); i++){
            if(updateClass(fullClasses[classNum][sectionNum], bookedSlots, "add")){
                currentClasses.insert(fullClasses[classNum][0], fullClasses[classNum][sectionNum]);
                search(classNum+1, fullClasses, 1, currentClasses, bookedSlots, totalClasses);
                updateClass(fullClasses[classNum][sectionNum], bookedSlots, "remove");
            }
        }
    }
}

bool updateClass(string str, int** &bookedSlots, string type){
    map<char, int> dayConversion;
    dayConversion.insert(make_pair('M', 0));
    dayConversion.insert(make_pair('T', 1));
    dayConversion.insert(make_pair('W', 2));
    dayConversion.insert(make_pair('R', 3));
    dayConversion.insert(make_pair('F', 4));

    int i = 0;

    //gets the days the class is taken
    string days = "";
    while(str[i] != ' '){
        days += str[i];
        i++;
    }

    //gets the times of the classes
    i++;
    int twoTimes[2];
    for(int k = 0; k < 2; k++){
        string numStr = "";
        while(str[i] != 'p' && str[i] != 'a'){
            numStr += str[i];
            i++;
        }
        int num = stoi(numStr);
        if(str[i] == 'a' || (str[i-4] == '1' && str[i-3] == '2')){
            twoTimes[k] = (num - 800 +20)/50;
        }
        else{
            twoTimes[k] = (num + 400 +20)/50;
        }
        i += 3;
    }
    
    if(type == "add"){
        //checks if the class fits in the current schedule
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                if(bookedSlots[dayConversion[days[i]]][j] != 0){
                    return false;
                }
            }
        }

        //it works, so update the booked timeslots
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                bookedSlots[dayConversion[days[i]]][j] = 1;
            }
        }
        return true;
    }
    else{ //type == "remove"
        for(int i = 0; i < days.length(); i++){
            for(int j = twoTimes[0]; j <= twoTimes[1]; j++){
                bookedSlots[dayConversion[days[i]]][j] = 0;
            }
        }
        return true;
    }
}
//MF 230pm-430pm 
//MWF 1230pm-330pm












// void printSolution(map<int, int> &cal, int timeSlots){
//     vector< vector<int> > classHolder;
//     for(int i = 0; i < timeSlots; i++){
//         vector<int> slot;
//         slot.push_back(0);
//         classHolder.push_back(slot);
//     }

//     map<int, int>::iterator it;
//     for(it = cal.begin(); it != cal.end(); ++it){   
//         classHolder[it -> second].push_back((int)it->first);
//     }
    
//     for(int i = 0; i < timeSlots; i++){
//         if(classHolder[i].size() >= 2){
//             cout << "Section " << i+1 << ": ";
//             for(int j = 1; j < classHolder[i].size()-1; j++){
//                 cout << classHolder[i][j] << ", ";
//             }
//             cout << classHolder[i][classHolder[i].size()-1];
//         }
//         cout << endl;
//     }
// }