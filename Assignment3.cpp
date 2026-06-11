
//816044402 
//DILLON GANPAT 
//COMP 2611- DATA STRUCTURES 
//ASSIGNMENT #3

#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "Data.h"
using namespace std;

#define QUIT 99

int main() {
    char fileName[25] = "WorldCities.txt";
    char commandsFile[25] = "Commands.txt";
    ifstream inputFile;
    int command;
    City city;

    cout << "--> Creating hash table ..." << endl;
    cout << endl; 
        
    HashTable *ht = initHashTableFromFile(701, fileName);
        
    cout << endl;

    cout << "--> Processing commands from Commands file ..." << endl << endl;
        
    inputFile.open(commandsFile);
    
    if (!inputFile.is_open()) {
        cout << "--> Commands file could not be opened. Aborting ..." << endl;
        exit(1);
    }

    inputFile >> command;

    while (command != QUIT) {

        cout << "COMMAND " << command << ":" << endl;
        


//if statements

		
		//create city struct
        if (command == 10) {
    inputFile >> city.name >> city.latitude >> city.longitude;
    inputFile >> city.country >> city.country_iso2 >> city.population;
    
    int location = containsHT(ht, city.name);
    
    if (location >= 0) {
        cout << "--> " << city.name << " is already in the hash table." << endl;
    } else {
        insertHT(ht, city);
        cout << "--> " << city.name << " inserted in the hash table." << endl;
    }
    
}
        
        
        //contains 
        else if (command == 11) {
            inputFile >> city.name;
            int location = containsHT(ht, city.name);
            
            if (location >= 0) {
               cout << "--> " << city.name << " is in the hash table." << endl;
               cout << endl; 
               
                displayCityHT(ht, city.name);
                
                cout << endl; 
                cout << "--> The length of the chain is " << lengthChain(ht, location) << endl;
            } else {
                cout << "--> " << city.name << " is NOT in the hash table." << endl;
            }
        }
            
        
        

        //delete 
        else if (command == 12) {
            inputFile >> city.name;
            deleteHT(ht, city.name);
            
        }
        
        //Statistics 
        else if (command == 13) {
            statisticsHT(ht);
        }
        
        cout << endl;
        inputFile >> command;
    }

    clearHT(ht);
    inputFile.close();

    return 0;
}
