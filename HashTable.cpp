//816044402 
//DILLON GANPAT 
//COMP 2611- DATA STRUCTURES 
//ASSIGNMENT #3


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Data.h"
#include "HashTable.h"
using namespace std;


HashTable * initHashTable(int sizeTable) {
    HashTable *ht = new HashTable;
    
    ht->sizeTable = sizeTable;
    
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        ht->elements[i] = NULL;
    }
    
    return ht;
}


HashTable * initHashTableFromFile(int sizeTable, char fileName[]) {
    ifstream inputFile;
    City city;
    int numCities;
    int storedCities = 0;
    
    HashTable *ht = initHashTable(sizeTable);    
    
    inputFile.open(fileName);
    
    if (!inputFile.is_open()) {
        cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
        exit(1);
    }

    numCities = 0;
    inputFile >> city.name;
    
    while (!inputFile.eof()) {
        inputFile >> city.latitude >> city.longitude;
        inputFile >> city.country >> city.country_iso2;
        inputFile >> city.population;
    
        numCities++;

        int locationHT = containsHT(ht, city.name);
        if (locationHT >= 0) {
            cout << "--> " << city.name << " is already in the hash table." << endl;  
        }
        else {
            insertHT(ht, city);
            storedCities++;
        }            
                
        inputFile >> city.name;
    }

    inputFile.close();
    
    cout<<endl; 
    cout << numCities << " cities read from " << fileName << " and " << storedCities << " stored in hash table." << endl;

	cout << endl; 
	
    return ht;
}




int hashFunction(string key, int tableSize) {
    int hash = 0;
for (int i = 0; i < key.length(); i++) {
    hash = hash + key[i] * (i + 1);  
}
int index = (hash % tableSize) + 1;  
}



int containsHT(HashTable *ht, string key) {
    if (ht == NULL) return -1;
    
    int i = 0;
    int hash = 0;
    while (i < key.length()) {
        hash = hash + key[i] * i;
        i++;
    }
    int index = (hash % ht->sizeTable) + 1;
    
    LLNode *current = ht->elements[index];
    
    while (current != NULL) {
        if (current->data.name == key) {
            return index;
        }
        current = current->next;
    }
    
    return -1;
}


void displayCity(City city) {
    cout << "NAME:         " << city.name << endl;
    cout << "LATITUDE:     " << city.latitude << endl;
    cout << "LONGITUDE:    " << city.longitude << endl;
    cout << "COUNTRY:      " << city.country << endl;
    cout << "COUNTRY CODE: " << city.country_iso2 << endl;
    cout << "POPULATION:   " << city.population << endl;
}




void displayCityHT(HashTable *ht, string key) {
    if (ht == NULL) return;
    
    int i = 0;
    int hash = 0;
    while (i < key.length()) {
        hash = hash + key[i] * i;
        i++;
    }
    int index = (hash % ht->sizeTable) + 1;
    
    LLNode *current = ht->elements[index];
    
    while (current != NULL) {
        if (current->data.name == key) {
            displayCity(current->data);
            return;
        }
        current = current->next;
    }
}



int lengthChain(HashTable *ht, int location) {
    if (ht == NULL || location < 1 || location > ht->sizeTable) {
        return 0;
    }
    
    int length = 0;
    LLNode *current = ht->elements[location];
    
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    return length;
}





LLNode * createNode(City city) {
    LLNode *newNode;
    newNode = new LLNode;
    newNode->data = city;
    newNode->next = NULL;
    return newNode;
}


void insertHT(HashTable *ht, City city) {
    if (ht == NULL) return;
    
    if (containsHT(ht, city.name) >= 0) {
        return;
    }
    
    int i = 0;
    int hash = 0;
    while (i < city.name.length()) {
        hash = hash + city.name[i] * i;
        i++;
    }
    int index = (hash % ht->sizeTable) + 1;
    
    LLNode *newNode = createNode(city);
    newNode->next = ht->elements[index];
    ht->elements[index] = newNode;
}




void statisticsHT(HashTable *ht) {
    if (ht == NULL) return;
    
    int numElements = 0;
    int filledLocations = 0;
    int emptyLocations = 0;
    int longestChain = 0;
    
    // Loop from 1 to sizeTable because of 1-based indexing
    for (int i = 1; i <= ht->sizeTable; i++) {
        int chainLength = lengthChain(ht, i);
        numElements += chainLength;
        
        if (chainLength > 0) {
            filledLocations++;
            if (chainLength > longestChain) {
                longestChain = chainLength;
            }
        }
        else {
            emptyLocations++;
        }
    }
    
    cout << "Statistics on the hash table:" << endl;
    cout << endl;
    cout << "There are " << numElements << " elements in the hash table." << endl;
    cout << "The hash table has " << filledLocations << " filled locations." << endl;
    cout << "The hash table has  " << emptyLocations << " empty locations." << endl;
    cout << "The length of the longest chain is: " << longestChain << endl;
}





void deleteHT(HashTable *ht, string key) {
    if (ht == NULL) return;
    
    int i = 0;
    int hash = 0;
    while (i < key.length()) {
        hash = hash + key[i] * i;
        i++;
    }
    int index = (hash % ht->sizeTable) + 1;
    
    LLNode *current = ht->elements[index];
    LLNode *prev = NULL;
    
    while (current != NULL) {
        if (current->data.name == key) {
            if (prev == NULL) {
                ht->elements[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            cout << "--> " << key << " deleted from the hash table." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    cout << "--> " << key << " is NOT in the hash table." << endl;
}




void clearHT(HashTable *ht) {
    if (ht == NULL) return;
    
    for (int i = 0; i < ht->sizeTable; i++) {
        LLNode *current = ht->elements[i];
        while (current != NULL) {
            LLNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    delete ht;
}
