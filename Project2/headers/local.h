#ifndef LOCAL_H
#define LOCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Definitions and Global variables */
typedef char String[400];
typedef struct Node *MEDICINE;
typedef struct HashEntry *CELL;
#define KeySize 3 // Key used for hashing => only the first 3 letters of the name
String MedsFile = "data/Meds.txt";
String PharmacyFile = "out/Pharmacy.txt";
int TableSize = 0;
int TableEntries = 0;
int SizeBefore = 0;
int TotalCollisions = 0;
int TableCollisions = 0;
int SearchColissions = 0;
CELL *Table = NULL;
CELL DELETED = NULL; // initalizing a special CELL to assign it to entries when they get deleted (the TOMBSTONE marker)

/* Node for the BST. This node contains the medicine's info. */
struct Node
{
  int Quantity;
  String Name, ActiveIngredient, Category, Indications, ExpirationDate, Company;
  struct Node *Left;
  struct Node *Right;
};
/* Node for the entries in the Hash table, every entry is a medicine. */
struct HashEntry
{
  int index;
  int Quantity;
  String Name, ActiveIngredient, Category, Indications, ExpirationDate, Company;
};

/* Functions' prototypes */
void PrintHeader();
void MainMenu();
void HashMenu();
void MakeEmpty(MEDICINE T);
MEDICINE ReadMedicine(MEDICINE Medicine);
MEDICINE AddMedicine(MEDICINE Medicine);
MEDICINE FindByName(char *name, MEDICINE T);
MEDICINE FindBySymptom(char *symptom, MEDICINE T);
MEDICINE FindByCompany(char *company, MEDICINE T);
MEDICINE FindByCategory(char *category, MEDICINE T);
MEDICINE FindMin(MEDICINE T);
MEDICINE Insert(String name, String ingredient, String category, String indications, String expDate, int quantity, String company, MEDICINE T);
MEDICINE DeleteByName(MEDICINE root, char *name);
MEDICINE DeleteByCompany(MEDICINE root, char *company);
MEDICINE DeleteFromList(MEDICINE root);
void SearchModify(MEDICINE T);
void DeleteSameCompany(MEDICINE root);
void PrintSameSymptom(char *symptom, MEDICINE t);
void ListSameSymptom(MEDICINE MedicineTree);
void PrintSameCategory(char *category, MEDICINE t);
void ListSameCategory(MEDICINE MedicineTree);
void PrintInAlphaOrder(MEDICINE t);
void StoreMedicines(MEDICINE T);
void StoreFile(MEDICINE T);
void UpdateQuantity(MEDICINE M);
void Hashing();
void InitializeTable();
void LoadHash();
void reHash();
int HashFunction(String Key, int tableSize);
int isPrime(int n);
int NextPrime(int n);
int InsertHashEntry(CELL Table[], CELL Medicine);
void SaveHashTable();
void InsertNewRecord();
void PrintHashTable();
void PrintHashFunction();
void SearchEntry();
void DeleteRecord();
CELL DeleteHashEntry(String name);
CELL SearchHash(String name);

#endif // LOCAL_H
