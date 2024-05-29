#ifndef LOCAL_H
#define LOCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxName 30 // Maximum characters for team/player names
#define MaxCode 4  // Maximum characters for teams codes

// struct for players list
struct Players
{
  char PlayerName[MaxName];
  struct Players *Next;
};

// struct for spare players queue, implemented on the players linked list directly
struct SpareQ
{
  struct Players *Front;
  struct Players *Rear;
};

// struct for teams list
struct TEAM
{
  char TeamName[MaxName];
  char TeamCode[MaxCode];
  int Wins;
  int Draws;
  int Losses;
  int GoalDiff;
  int Points;
  int Count;
  struct Players *Players;
  struct SpareQ *Spare;
  struct TEAM *Next;
};

struct TEAM *FindTeamName(char[MaxName], struct TEAM *);
struct Players *FindPlayerName(char[MaxName], struct Players *);
struct TEAM *FindTeamCode(char[MaxName], struct TEAM *);
struct TEAM *FindPreviousTeam(char[MaxName], struct TEAM *);
struct Players *FindPreviousPlayer(char[MaxName], struct Players *);
struct Players *Front(struct SpareQ *);
struct Players *FrontAndDequeue(struct Players *, struct SpareQ *);
struct TEAM *swap(struct TEAM *, struct TEAM *);
struct TEAM *MakeEmptyTeam(struct TEAM *L);
struct Players *MakeEmptyPlayer(struct Players *L);
struct SpareQ *CreateQueue(int);

void InsertLastTeam(char[MaxName], char[MaxCode], int, int, int, int, int, struct TEAM *);
int IsEmptyTeam(struct TEAM *);
int IsEmptyPlayer(struct Players *);
int IsLastTeam(struct TEAM *, struct TEAM *);
int IsLastPlayer(struct Players *, struct Players *);
void InsertLastPlayer(char[MaxName], struct TEAM *);
void DeleteTeam(char[MaxName], struct TEAM *);
void DeletePlayer(char[MaxName], struct Players *);
void ModifyTeam(char[MaxName], char[MaxCode], int, int, int, int, int, struct TEAM *);
void PrintAllPlayers(struct TEAM *);
void PrintTeamPlayers(struct TEAM *);
void PrintAllTeams(struct TEAM *);
void PrintTeam(struct TEAM *, char[MaxName]);
void DeleteTeamList(struct TEAM *);
void DeletePLayerList(struct Players *);
int sizeTeam(struct TEAM *);
int sizePlayers(struct Players *);
int IsEmptyQueue(struct SpareQ *);
void DisposeQueue(struct SpareQ *);
void Enqueue(char[MaxName], struct TEAM *);
void Dequeue(struct SpareQ *);
void Menu(void);
void MatchMenu(void);
void CreateMatch(struct TEAM *);
void Modify(char[MaxName], struct TEAM *);
void ReadTeam(struct TEAM *);
void ReadPlayers(struct TEAM *);
void SaveTeams(struct TEAM *);
void Add(struct TEAM *);
void ElementarySpareSwap(struct TEAM *, char[MaxName]);
void RedCard(struct TEAM *, char[MaxName]);
void SavePlayers(struct TEAM *);
void IsNoList(struct TEAM *);
void RadixSort(struct TEAM **);
void SortTeams(struct TEAM **, int);

#endif // LOCAL_H
