// Usama Shoora -- 1200796
// Section 2 - Dr. Radi Jarrar
// Project 1 submission

#include "../headers/local.h"

void mainMenu(struct TEAM *TEAM);

int main()
{
    // initialize teams list
    struct TEAM *TEAM;
    TEAM = MakeEmptyTeam(NULL);

    mainMenu(TEAM);
    return 0;
}

void mainMenu(struct TEAM *TEAM)
{
    int n;
    Menu(); // display Main Menu
    scanf("%d", &n);

    while (n != 0)
    {
        switch (n)
        {
        case 1:
            TEAM = MakeEmptyTeam(NULL);
            ReadTeam(TEAM);
            printf("\n\t\t\t\t\t--Teams' list read successfully.--");
            break;
        case 2:
            IsNoList(TEAM);
            PrintAllTeams(TEAM);
            break;
        case 3:
            IsNoList(TEAM);
            printf("\n\t\t\t\t\t\tEnter team's name: ");
            char name[MaxName];
            scanf("%s", name);
            PrintTeam(TEAM, name);
            break;
        case 4:
            IsNoList(TEAM);
            Add(TEAM);
            printf("\n\t\t\t\t\t--Team added successfully.--");
            break;
        case 5:
            IsNoList(TEAM);
            printf("\n\t\t\t\t\t   Enter team's name to Modify: ");
            char nameMod[MaxName];
            scanf("%s", nameMod);
            Modify(nameMod, TEAM);
            printf("\n\t\t\t\t--Team modified successfully.--");
            break;
        case 6:
            IsNoList(TEAM);
            printf("\n\t\t\t\t\t   Enter team's name to delete: ");
            char nameDel[MaxName];
            scanf("%s", nameDel);
            DeleteTeam(nameDel, TEAM);
            printf("\n\t\t\t\t\t\t--Team deleted successfully.--");
            break;
        case 7:
            IsNoList(TEAM);
            SortTeams(&TEAM, sizeTeam(TEAM));
            printf("\n\t\t\t\t\t--Teams' information sorted successfully.--");
            break;
        case 8:
            IsNoList(TEAM);
            SaveTeams(TEAM);
            printf("\n\t\t\t\t--Teams' information saved to teamsInfo.txt successfully.--");
            break;
        case 9:
            IsNoList(TEAM);
            CreateMatch(TEAM);
            break;
        case 10:
            IsNoList(TEAM);
            ReadPlayers(TEAM);
            printf("\n\t\t\t\t\t--Players list read successfully.--");
            break;
        case 11:
            IsNoList(TEAM);
            PrintAllPlayers(TEAM);
            break;
        case 12:
            IsNoList(TEAM);
            printf("\t\t\t\t\tEnter team's name: ");
            char TName[MaxName];
            scanf("%s", TName);
            PrintTeamPlayers(FindTeamName(TName, TEAM));
            break;
        case 13:
            IsNoList(TEAM);
            SavePlayers(TEAM);
            printf("\n\t\t\t\t--Players' information saved to playersInfo.txt successfully.--");
            break;
        default:
            printf("\n\t\t\t\t!!Option invalid!! Please enter one of the options above\n\n");
        }
        Menu();
        scanf("%d", &n);
    }
}

// function for initializing teams list
struct TEAM *MakeEmptyTeam(struct TEAM *L)
{
    if (L != NULL)
        DeleteTeamList(L);
    L = (struct TEAM *)malloc(sizeof(struct TEAM));

    if (L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    return L;
}

// function for initializing players list
struct Players *MakeEmptyPlayer(struct Players *L)
{
    if (L != NULL)
        DeletePLayerList(L);
    L = (struct Players *)malloc(sizeof(struct Players));

    if (L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    return L;
}

// function for initializing spare players queue
struct SpareQ *CreateQueue(int MaxElements)
{
    struct SpareQ *Q;

    Q = (struct SpareQ *)malloc(sizeof(struct SpareQ));
    if (Q == NULL)
        printf("Out of space");

    Q->Front = NULL;
    Q->Rear = NULL;

    return Q;
}

// function for inserting at the end of teams list
void InsertLastTeam(char Name[MaxName], char Code[MaxCode], int Wins, int Draws, int Losses,
                    int GoalDiff, int Points, struct TEAM *L)
{
    struct TEAM *temp, *P = L;
    struct Players *E;
    E = MakeEmptyPlayer(NULL);
    int j = 1;
    struct SpareQ *Q = CreateQueue(15); // create spare players queue with maximum 15 spare players
    temp = (struct TEAM *)malloc(sizeof(struct TEAM));
    Name[0] = toupper(Name[0]); // capitalize first letter of team's name
    strcpy(temp->TeamName, Name);
    strcpy(temp->TeamCode, strupr(Code)); // strupr() is used to capitalize team code
    temp->Wins = Wins;
    temp->Draws = Draws;
    temp->Losses = Losses;
    temp->GoalDiff = GoalDiff;
    temp->Points = Points;
    temp->Players = E;
    temp->Spare = Q;
    while (P->Next != NULL)
    {
        P = P->Next;
        j++;
    }
    temp->Count = j;
    P->Next = temp;
    temp->Next = NULL;
}
// function for checking if teams list is empty
int IsEmptyTeam(struct TEAM *L)
{
    return L->Next == NULL;
}
// function for checking if players list is empty
int IsEmptyPlayer(struct Players *L)
{
    return L->Next == NULL;
}
// function for checking if a team is the last in the list
int IsLastTeam(struct TEAM *P, struct TEAM *L)
{
    return P->Next == NULL;
}
// function for checking if a player is the last in the list
int IsLastPlayer(struct Players *P, struct Players *L)
{
    return P->Next == NULL;
}
// function for finding a team node based on given team name
struct TEAM *FindTeamName(char name[MaxName], struct TEAM *L)
{
    struct TEAM *P;
    P = L->Next;
    while (P != NULL && strcasecmp(P->TeamName, name) != 0)
        P = P->Next;
    return P;
}
// function for finding a player node based on given player name
struct Players *FindPlayerName(char name[MaxName], struct Players *L)
{
    struct Players *P;
    P = L->Next;
    while (P != NULL && strcasecmp(P->PlayerName, name) != 0)
        P = P->Next;
    return P;
}
// function for finding a team node based on given team code
struct TEAM *FindTeamCode(char code[MaxName], struct TEAM *L)
{
    struct TEAM *P;
    P = L->Next;
    while (P != NULL && strcasecmp(P->TeamCode, code) != 0)
        P = P->Next;
    return P;
}
// function for inserting at the end of players list
void InsertLastPlayer(char Name[MaxName], struct TEAM *L)
{
    struct Players *temp, *P;
    P = L->Players;
    temp = (struct Players *)malloc(sizeof(struct Players));
    strcpy(temp->PlayerName, Name);
    while (P->Next != NULL)
        P = P->Next;
    P->Next = temp;
    temp->Next = NULL;
}
// function for finding the previous team node of a team based on given team name
struct TEAM *FindPreviousTeam(char name[MaxName], struct TEAM *L)
{
    struct TEAM *P;
    P = L;
    while (P->Next != NULL && strcasecmp(P->Next->TeamName, name) != 0)
        P = P->Next;
    return P;
}
// function for finding the previous player node of a player based on given player name
struct Players *FindPreviousPlayer(char name[MaxName], struct Players *L)
{
    struct Players *P;
    P = L;
    while (P->Next != NULL && strcmp(P->Next->PlayerName, name) != 0)
        P = P->Next;
    return P;
}
// function for deleting team based on given team name
// then applying the change to original file by copying
// its contents to another file except for the deleted team
void DeleteTeam(char name[MaxName], struct TEAM *L)
{
    struct TEAM *P, *temp;
    P = FindPreviousTeam(name, L);
    FILE *f1, *f2; // initialize files to copy from and move data to
    char c;
    int deleteLine, currLine = 1;      // initialize variables to keep track of line to be deleted and current line
    deleteLine = P->Next->Count;       // line to be deleted is equal to the line of the team's data from teams.txt
    f1 = fopen("data/teams.txt", "r"); // open teams file in read mode
    rewind(f1);
    f2 = fopen("data/temp.txt", "w"); // open new temp file in write mode
    c = getc(f1);                     // get first character in teams.txt
    while (c != EOF)
    {
        if (c == '\n') // if character is line break, increment current line by 1
            currLine++;
        if (currLine != deleteLine) // copy all lines in file teams.txt except the line to be deleted to new temp file
            putc(c, f2);            // move lines character by character to temp file
        c = getc(f1);
    }
    // close both files.
    fclose(f1);
    fclose(f2);
    remove("data/teams.txt");                  // remove original file
    rename("data/temp.txt", "data/teams.txt"); // rename the file temp.txt to original name
    //  delete (free) team node, and re-link the pointers appropriately
    if (!IsLastTeam(P, L))
    {
        temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }
}
// function to delete a player
void DeletePlayer(char name[MaxName], struct Players *L)
{
    struct Players *P, *temp;
    P = FindPreviousPlayer(name, L);
    if (!IsLastPlayer(P, L))
    {
        temp = P->Next;
        P->Next = temp->Next; // bypass delete cell
        free(temp);
    }
}
// function to modify a team in the teams list
// then applying the change to original file by copying
// its contents to another file except for the modified team
// and inserting the modified team back into its correct line position
void ModifyTeam(char Name[MaxName], char Code[MaxCode], int Wins, int Draws, int Losses, int GoalDiff,
                int Points, struct TEAM *L)
{
    struct TEAM *P;
    P = FindTeamName(Name, L);
    strcpy(P->TeamCode, Code);
    P->Wins = Wins;
    P->Draws = Draws;
    P->Losses = Losses;
    P->GoalDiff = GoalDiff;
    P->Points = Points;
    FILE *f1, *f2;     // initialize files to copy from and move data to
    char str[50] = ""; // string to insert into teams.txt
    char c;
    int modifyLine, currLine = 1;      // initialize variables to keep track of line to be modified and current line
    modifyLine = P->Count;             // line to be deleted is equal to the line of the team's data from teams.txt
    f1 = fopen("data/teams.txt", "r"); // open teams file in read mode
    rewind(f1);
    sprintf(str, "\n%s,%s,%d,%d,%d,%d", P->TeamName, P->TeamCode, P->Wins, P->Draws, P->Losses, P->GoalDiff); // format string to insert text
    f2 = fopen("data/temp.txt", "w");                                                                         // open new file in write mode
    c = getc(f1);                                                                                             // get first character in teams.txt
    int i = 0;
    while (c != EOF)
    {
        if (c == '\n') // if character is line break, increment current line by 1
            currLine++;
        if (currLine == modifyLine) // only insert modified team to temp file
        {
            putc(str[i], f2); // move string of modified team to temp file
            i++;
        }
        else
            putc(c, f2); // move lines character by character to temp file
        c = getc(f1);
    }
    // close both the files.
    fclose(f1);
    fclose(f2);
    remove("data/teams.txt");                  // remove original file
    rename("data/temp.txt", "data/teams.txt"); // rename the file temp.txt to original name
}
// function to print elementary players of all teams
void PrintAllPlayers(struct TEAM *L)
{
    struct TEAM *P = L;
    if (IsEmptyTeam(L))
        printf("Empty list\n");
    else
        do
        {
            P = P->Next;
            PrintTeamPlayers(P);
        } while (!IsLastTeam(P, L));
    printf("\n");
}
// function to print elementary players of a specific team
void PrintTeamPlayers(struct TEAM *L)
{
    struct Players *El = L->Players;
    if (IsEmptyPlayer(El)) // if team has no players, print the following
        printf("\t\t\t\t\t!!No %s players!!\n", L->TeamName);
    else
    {
        struct Players *E = El;
        printf("\n\t\t\t\t---Printing %s elementary players:\n\n", L->TeamName);
        int j = 1;
        do
        {
            E = E->Next;
            if (j < 12)
            {
                printf("\t\t\t\t\t\t%d. %s\n", j, E->PlayerName);
                j++;
            }
        } while (!IsLastPlayer(E, El));
        printf("\n");
    }
}
// function to print information of all teams
void PrintAllTeams(struct TEAM *L)
{
    struct TEAM *P = L;
    if (IsEmptyTeam(L))
        printf("Empty list\n");
    else
        printf("\n\t\t\t\t-------Printing information for all teams:\n\n");
    int j = 1;
    do
    {
        P = P->Next;
        printf("\t\t%d. Team name: %s, Team Code: %s, %d Wins, %d Draws, %d Losses, ",
               j, P->TeamName, P->TeamCode, P->Wins, P->Draws, P->Losses);
        printf("Goals difference: %d, Points: %d\n", P->GoalDiff, P->Points);
        j++;
    } while (!IsLastTeam(P, L));
    printf("\n");
}
// function to print information of a specific team
void PrintTeam(struct TEAM *L, char name[MaxName])
{
    struct TEAM *P = L;
    if (IsEmptyTeam(L))
        printf("Empty list\n");
    else
        P = FindTeamName(name, L);
    if (P->TeamName != NULL)
    {
        printf("\n\t\t\t\t-------Printing information for team %s:\n\n", P->TeamName);
        printf("\t\tTeam name: %s, Team Code: %s, %d Wins, %d Draws, %d Losses, ",
               P->TeamName, P->TeamCode, P->Wins, P->Draws, P->Losses);
        printf("Goals difference: %d, Points: %d\n", P->GoalDiff, P->Points);
        printf("\n");
    }
    else
        printf("Team not found.\n");
}
// function to delete entire teams list
void DeleteTeamList(struct TEAM *L)
{
    struct TEAM *P, *temp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }
}
// function to delete entire players list
void DeletePLayerList(struct Players *L)
{
    struct Players *P, *temp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }
}
// function to return size of teams list
int sizeTeam(struct TEAM *L)
{
    struct TEAM *p = L->Next;
    int count = 0;
    while (p != NULL)
    {
        count += 1;
        p = p->Next;
    }
    return count;
}
// function to return size of players list
int sizePlayers(struct Players *L)
{
    struct Players *p = L->Next;
    int count = 0;
    while (p != NULL)
    {
        count += 1;
        p = p->Next;
    }
    return count;
}
// function to determine if spare queue is empty or not
int IsEmptyQueue(struct SpareQ *Q)
{
    return Q->Front == NULL;
}
// function do dispose of spare queue
void DisposeQueue(struct SpareQ *Q)
{
    if (Q != NULL)
    {
        free(Q);
    }
}
// function to return the first (front) player in spare queue
struct Players *Front(struct SpareQ *Q)
{
    if (!IsEmptyQueue(Q))
        return Q->Front;
    printf("Empty Queue!");
    return 0;
}
// function to return and delete the first (front) player in spare queue
struct Players *FrontAndDequeue(struct Players *L, struct SpareQ *Q)
{
    struct Players *P;
    if (IsEmptyQueue(Q))
        printf("Empty Queue!");
    else
    {
        P = Q->Front;
        Q->Front = Q->Front->Next;
        L = FindPreviousPlayer(P->PlayerName, L);
        L->Next = Q->Front;
    }
    return P;
}
// function to insert (enqueue) into the end of spare queue
void Enqueue(char name[MaxName], struct TEAM *L)
{
    struct SpareQ *Q = L->Spare;
    struct Players *P = L->Players;
    InsertLastPlayer(name, L);
    while (P->Next != NULL) // find last node
        P = P->Next;
    if (IsEmptyQueue(Q)) // If the queue is empty, set both the front and rear to the new node
    {
        Q->Front = P;
        Q->Rear = P;
    }
    else // If the queue is not empty, add the new node to the end of the queue and update the rear
    {
        Q->Rear->Next = P;
        Q->Rear = P;
    }
}
// function to delete (dequeue) the first node (front) in queue
void Dequeue(struct SpareQ *Q)
{
    if (IsEmptyQueue(Q))
        printf("Empty Queue!");
    else
    {
        Q->Front = Q->Front->Next;
    }
}
// function to display Main Menu selection
void Menu()
{
    printf("\n\n\n\t\t\t\t      Please select from the following options:\n");
    printf("\n\t\t\t\t0. Exit program.");
    printf("\n\t\t\t\t1. Read teams information from teams.txt.\n\t\t\t\t2. Print all teams information.");
    printf("\n\t\t\t\t3. Print a specific team's information.\n\t\t\t\t4. Add a team.");
    printf("\n\t\t\t\t5. Modify team list.\n\t\t\t\t6. Delete Team.");
    printf("\n\t\t\t\t7. Sort teams based on points from highest to lowest.\n\t\t\t\t8. Save teams information to file teamsInfo.txt.");
    printf("\n\t\t\t\t9. Create Match.\n\t\t\t\t10. Read players from players.txt.\n\t\t\t\t11. Print elementary players of all teams.");
    printf("\n\t\t\t\t12. Print elementary players of specific team\n\t\t\t\t13. Save players info to playersInfo.txt.");
    printf("\n\t\t\t\t\t\tEnter selection: ");
}
// function to display Match Menu selection
void MatchMenu()
{
    printf("\n\n\n\t\t\t\t      Please select from the following options:");
    printf("\n\t\t\t\t1. Swap specific elementary player with spare.\n\t\t\t\t2. Give red card to player.");
    printf("\n\t\t\t\t3. Save players info to playersInfo.txt.\n\t\t\t\t0. Back to Main menu.\n\t\t\t\t\t\tEnter selection: ");
}
// function to create match
void CreateMatch(struct TEAM *L)
{
    struct TEAM *F, *S; // first and second team
    char firstTeam[MaxName];
    char secondTeam[MaxName];
    printf("\n\t\t\t\t\t   Enter first team's code: ");
    scanf("%s", firstTeam);
    printf("\t\t\t\t\t   Enter second team's code: ");
    scanf("%s", secondTeam);
    // find both teams based on their codes, if one or both are not found,
    // an appropriate message is printed
    F = FindTeamCode(firstTeam, L);
    S = FindTeamCode(secondTeam, L);
    if (F == NULL && S == NULL)
    {
        printf("\n\t\tBoth teams not found.  You can add each of them to list by choosing option (4) from Main menu.\n");
        return;
    }
    else if (F == NULL)
    {
        printf("\n\t\tFirst team not found. You can add it to list by choosing option (4) from Main menu.\n");
        return;
    }
    else if (S == NULL)
    {
        printf("\n\t\tSecond team not found. You can add it to list by choosing option (4) from Main menu.\n");
        return;
    }
    else
        printf("\n\t\t\t\t\tFound both teams:  %s vs. %s\n", F->TeamName, S->TeamName);
    int n;
    MatchMenu(); // display match menu selections
    scanf("%d", &n);
    L->Players = MakeEmptyPlayer(NULL);
    ReadPlayers(L); // read players of teams from players.txt
    while (n != 0)
    {
        char TName[MaxName];
        char PName[MaxName];
        switch (n)
        {
        case 1: // swap elementary player with spare
            printf("\n\t\t\t\t\t   Enter team's name: ");
            scanf("%s", TName);
            printf("\t\t\t\t\t   Enter player's name: ");
            scanf("%s", PName);
            ElementarySpareSwap(FindTeamName(TName, L), PName); // function call to perform operation
            printf("\n\t\t\t\t\t--Players swapped successfully--");
            break;
        case 2: // give red card to player
            printf("\n\t\t\t\t\t   Enter team's name: ");
            scanf("%s", TName);
            printf("\t\t\t\t   Enter player's name to give red card: ");
            scanf("%s", PName);
            RedCard(FindTeamName(TName, L), PName); // function call to perform operation
            printf("\n\t\t\t\t\t--Red card given to %s successfully--", PName);
            break;
        case 3: // save players info to playersInfo.txt
            SavePlayers(L);
            printf("\n\t\t\t\t--Players' information saved to playersInfo.txt successfully--");
            break;
        case 0:
            exit(1);
        default:
            printf("\n\t\t\t\t!!Option invalid!! Please enter one of the options above\n\n");
        }
        MatchMenu(); // display match menu selections
        scanf("%d", &n);
    }
}
// function to modify a team in the teams list
void Modify(char name[MaxName], struct TEAM *L)
{
    char code[MaxCode];
    int wins, draws, losses, goalDiff, points;
    printf("\n\t\t\t\t\t\t\tEnter code: ");
    scanf("%s", code);
    printf("\n\t\t\t\t\t\t   Enter number of wins: ");
    scanf("%d", &wins);
    printf("\n\t\t\t\t\t\t   Enter number of draws: ");
    scanf("%d", &draws);
    printf("\n\t\t\t\t\t\t   Enter number of losses: ");
    scanf("%d", &losses);
    printf("\n\t\t\t\t\t\t   Enter goals difference: ");
    scanf("%d", &goalDiff);
    points = (3 * wins) + draws;
    // function call to perform modification
    ModifyTeam(name, code, wins, draws, losses, goalDiff, points, L);
}
// function to read and store teams' information into TEAM linked list
void ReadTeam(struct TEAM *TEAM)
{
    FILE *in = fopen("data/teams.txt", "r");
    char name[MaxName];
    char code[MaxCode];
    int wins, draws, losses, goalDiff, points;
    int status = fscanf(in, "%[^,]s", name); // Check if there's data in the file, while scanning and storing ID numbers.
    while (status != EOF)                    // As long as EOF isn't met, scan and store teams information.
    {
        fscanf(in, ",%[^,]s", code);
        fscanf(in, ",%d,%d,%d,%d", &wins, &draws, &losses, &goalDiff);
        points = (3 * wins) + draws;
        InsertLastTeam(name, code, wins, draws, losses, goalDiff, points, TEAM);
        status = fscanf(in, "\n%[^,]s", name);
    }
    fclose(in);
}
// function to read and store players' into Player linked list
void ReadPlayers(struct TEAM *Team)
{
    struct TEAM *T;
    FILE *in = fopen("data/players.txt", "r");
    char name[30];
    char code[10];
    int cnt;
    int status1 = fscanf(in, "%s", code); // Check if there's data in the file, while scanning and storing teams' codes.
    while (status1 != EOF)                // if EOF isn't reached
    {
        if (strncmp(code, "*", 1) == 0)
        {
            char *tok;
            tok = strtok(code, "*");
            strcpy(code, tok);
            T = FindTeamCode(code, Team);       // search for team based on its code
            T->Players = MakeEmptyPlayer(NULL); // initialize players list for team
            int status2 = fscanf(in, "%d-", &cnt);
            while (status2 != EOF) // As long as EOF isn't met, scan and store players names.
            {
                status1 = fscanf(in, "%s", name); // scan player name
                if (!strncmp(name, "*", 1))       // if name has (*) then break loop, (*) indicates new team
                    break;
                if (cnt <= 11) // elementary players
                    InsertLastPlayer(name, T);
                else // spare players
                    Enqueue(name, T);
                status2 = fscanf(in, "%d-", &cnt);
            }
            strcpy(code, name);
            if (status2 == EOF)
                status1 = EOF;
        }
    }
    fclose(in);
}
// function to save teams to teamsInfo.txt
void SaveTeams(struct TEAM *L)
{
    FILE *out = fopen("out/teamsInfo.txt", "w"); // open file for writing
    struct TEAM *P = L;
    if (IsEmptyTeam(L))
        printf("\t\t\t\t\tEmpty list\n");
    else
    {
        int j = 1;
        do
        {
            P = P->Next;
            fprintf(out, "%d. Team name: %s, Team Code: %s, %d Wins, %d Draws, %d Losses, ",
                    j, P->TeamName, P->TeamCode, P->Wins, P->Draws, P->Losses);
            fprintf(out, "Goals difference: %d, Points: %d\n", P->GoalDiff, P->Points);
            j++;
        } while (!IsLastTeam(P, L));
    }
    fclose(out);
}
// function to add a new team to teams list
// and append the new team to teams.txt
void Add(struct TEAM *TEAM)
{
    char name[MaxName];
    char code[MaxCode];
    int wins, draws, losses, goalDiff, points;
    printf("\n\t\t\t\t\t\tEnter name of team: ");
    scanf("%s", name);
    printf("\n\t\t\t\t\t\tEnter code of team: ");
    scanf("%s", code);
    printf("\n\t\t\t\t\tEnter number of wins for the team: ");
    scanf("%d", &wins);
    printf("\n\t\t\t\t\tEnter number of draws for the team: ");
    scanf("%d", &draws);
    printf("\n\t\t\t\t\tEnter number of losses for the team: ");
    scanf("%d", &losses);
    printf("\n\t\t\t\t\tEnter goals difference for the team: ");
    scanf("%d", &goalDiff);
    points = (3 * wins) + draws;
    // add new team to the end of teams linked list
    InsertLastTeam(name, code, wins, draws, losses, goalDiff, points, TEAM);
    FILE *f = fopen("data/teams.txt", "a"); // open file for appending new team
    fprintf(f, "\n%s,%s,%d,%d,%d,%d", name, code, wins, draws, losses, goalDiff);
    fclose(f); // close file
}
// function to swap elementary player with spare
void ElementarySpareSwap(struct TEAM *L, char player[MaxName])
{
    struct Players *temp, *temp2, *P = L->Players;
    temp = MakeEmptyPlayer(NULL);
    temp2 = MakeEmptyPlayer(NULL);
    struct SpareQ *Q;
    Q = L->Spare; // Q becomes the spare queue in team
    P = FindPlayerName(player, P);
    temp2 = Q->Front;
    strcpy(temp->PlayerName, P->PlayerName);                           // copy player name to temp
    strcpy(P->PlayerName, FrontAndDequeue(L->Players, Q)->PlayerName); // get spare player from queue
    Enqueue(temp->PlayerName, L);                                      // enqueue elementary player to end of spare queue
    // free both temp variables
    free(temp);
    free(temp2);
}
// function to give red card to player
void RedCard(struct TEAM *L, char player[MaxName])
{
    struct Players *R = L->Players;
    R = FindPlayerName(player, R);
    Enqueue(R->PlayerName, L);               // enqueue elementary player to spare queue
    DeletePlayer(R->PlayerName, L->Players); // delete player from elementary list
}
// save players to playersInfo.txt
void SavePlayers(struct TEAM *L)
{
    FILE *out = fopen("out/playersInfo.txt", "w"); // open file for writing
    struct TEAM *P = L;
    struct Players *D;
    int j;
    do
    {
        P = P->Next;
        fprintf(out, "*%s\n", P->TeamName); // prints team name, if team has no players it'll print the name regardless
        D = P->Players;
        if (!IsEmptyPlayer(D))
        {
            int s = 12;
            j = 1;
            fprintf(out, "--Elementary players:\n");
            do // print elementary players only
            {
                D = D->Next;
                fprintf(out, "\t%d. %s\n", j, D->PlayerName);
                j++;
            } while (!IsLastPlayer(D, L), j < s);
            if (!IsEmptyPlayer(D))
                fprintf(out, "--Spare players:\n");
            while (!IsEmptyPlayer(D)) // print spare players
            {
                D = D->Next;
                fprintf(out, "\t%d. %s\n", j, D->PlayerName);
                j++;
            }
        }
    } while (!IsLastTeam(P, L));
    fclose(out); // close file
}
// function to determine if teams list is created, if not then exit program
void IsNoList(struct TEAM *L)
{
    if (IsEmptyTeam(L))
    {
        printf("\n!!No list of teams available yet!!\n");
        exit(0);
    }
}
// function to perform Radix Sort on teams list based on Points value
void RadixSort(struct TEAM **L)
{
    struct TEAM *bucket[10]; // array of buckets
    bucket[10] = MakeEmptyTeam(NULL);
    struct TEAM *P; // pointer to the current node
    P = MakeEmptyTeam(NULL);
    struct TEAM *tail[10]; // array of tails for each bucket
    tail[10] = MakeEmptyTeam(NULL);
    int i, j, k;
    int factor;     // factor (factor of 10) to sort on
    int digits[10]; // array to store the digits of the Points
    // Initialize the buckets and tails
    for (i = 0; i < 10; i++)
    {
        bucket[i] = 0;
        tail[i] = 0;
    }
    // Find the maximum number of digits in the Points
    int maxDigits = 0;
    P = *L;
    while (P != NULL) // while team isn't null
    {
        int Points = P->Points;
        int numDigits = 0;
        while (Points > 0)
        {
            numDigits++;
            Points /= 10;
        }
        if (numDigits > maxDigits)
        {
            maxDigits = numDigits;
        }
        P = P->Next;
    }
    // Loop through each digit, starting with the least significant digit
    for (factor = 1; maxDigits > 0; factor *= 10, maxDigits--)
    {
        memset(digits, 0, sizeof(digits)); // reset digits
        memset(bucket, 0, sizeof(bucket)); // reset buckets
        P = *L;
        while (P != NULL) // while team isn't null
        {
            digits[P->Points / factor % 10]++;
            P = P->Next;
        }
        P = *L;
        while (P != NULL) // store Points values into buckets
        {
            int digit = P->Points / factor % 10;
            if (bucket[digit] == NULL)
            {
                bucket[digit] = P;
                tail[digit] = P;
            }
            else
            {
                tail[digit]->Next = P;
                tail[digit] = P;
            }
            P = P->Next;
        }
        *L = NULL;
        P = NULL; // track the current tail of the newly built list
        for (i = 9; i >= 0; i--)
        {
            if (bucket[i] != NULL && bucket[i]->TeamName != NULL)
            {
                if (*L == NULL)
                {
                    *L = bucket[i];
                }
                else
                {
                    P->Next = bucket[i]; // Append bucket after the current tail
                }
                P = tail[i]; // The tail is now at the end of this bucket
            }
        }
        P->Next = NULL; // Terminate the list
    }
}
// function to swap team nodes
struct TEAM *swap(struct TEAM *P1, struct TEAM *P2)
{
    struct TEAM *temp = P2->Next;
    P2->Next = P1;
    P1->Next = temp;
    return P2;
}
// function to apply Radix sort on teams list,
// then swap teams based on which of them has a higher goal difference
void SortTeams(struct TEAM **L, int count)
{
    RadixSort(&(*L)->Next); // perform radix sort on teams list
    struct TEAM **P;
    int i, j, swapped;
    for (i = 0; i <= count; i++) // iterate (traverse) on list based on its size
    {
        P = &(*L)->Next; // start at first team
        swapped = 0;
        for (j = 0; j < count - i - 1; j++)
        {
            struct TEAM *p1 = *P;
            struct TEAM *p2 = p1->Next;
            if (p1->Points == p2->Points) // if points of two teams are equal,
            {
                // swap them based on higher goals difference
                if (p1->GoalDiff < p2->GoalDiff)
                {
                    *P = swap(p1, p2);
                    swapped = 1;
                }
            }
            P = &(*P)->Next; // move on to next team
        }
        if (swapped == 0)
            continue;
    }
}
