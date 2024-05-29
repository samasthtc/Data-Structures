/*
    Usama Shoora -- 1200796
    Section 2 - Dr. Radi Jarrar
    Project 2 submission
*/

#include "../headers/local.h"

int main()
{
    MEDICINE MedicineTree;
    DELETED = (CELL)malloc((sizeof(struct HashEntry))); // assigning the DELETED (TOMBSTONE) marker
    MedicineTree = NULL;
    MakeEmpty(MedicineTree); // initalizing the BST of medicines

    int n;
    MainMenu();
    scanf("%d", &n);

    while (n != 0) // if user inputs 0, then exit program
    {
        switch (n)
        {
        case 1: // Read Meds File and add data to the medicines BST
            MedicineTree = ReadMedicine(MedicineTree);
            break;
        case 2: // Add a new medicine to the BST
            MedicineTree = AddMedicine(MedicineTree);
            break;
        case 3: // Print the nodes in alphabetical order
            printf("\nPrinting in alphabetical order:\n");
            PrintHeader();
            PrintInAlphaOrder(MedicineTree);
            break;
        case 4: // List medicines of same category
            ListSameCategory(MedicineTree);
            break;
        case 5: // List medicines that treat the same disease/symptom
            ListSameSymptom(MedicineTree);
            break;
        case 6: // Search for specific medicine and give the user the option to modify its info
            SearchModify(MedicineTree);
            break;
        case 7: // Update the quantity of a certain medicine
            UpdateQuantity(MedicineTree);
            break;
        case 8:                                          // Delete a medicine from the BST
            MedicineTree = DeleteFromList(MedicineTree); // function call to delete
            break;
        case 9: // Delete all medicines from the same company form the BST
            DeleteSameCompany(MedicineTree);
            break;
        case 10: // Store the BST in the Pharmacy File alphabetically
            StoreFile(MedicineTree);
            break;
        case 11: // Create Hash Table from the data in Pharmacy File
            Hashing();
            break;
        default: // In case the user inputs an invalid option
            printf("\n\t\t\t\t!!Option invalid!! Please enter one of the options above\n\n");
        }
        MainMenu();
        scanf("%d", &n);
    }
    MakeEmpty(MedicineTree);
    free(Table);
    return 0;
}

/* Function to print a header for the info */
void PrintHeader()
{
    printf("\e[1m=> %s\t%33s  %15s  %36s  %8s  %3s  %s\n\e[m", "NAME", "ACTIVE INGREDIENT", "CATEGORY", "INDICATIONS", "EXPIRATION", "QUANTITY", "COMPANY");
    printf("\e[1m %s\t%33s  %15s  %36s  %7s  %3s  %s\n\e[m", " ", " ", " ", " ", "DATE", " ", " ");
}

/* Function to print main menu */
void MainMenu()
{
    printf("\n\n\n\t\t\t\t      Please select from the following options:\n");
    printf("\n\t\t\t\t0. Exit program.");
    printf("\n\t\t\t\t1. Read medicines information from Meds.txt.\n\t\t\t\t2. Add a medicine.");
    printf("\n\t\t\t\t3. List medicines in alphabetical order with their information.\n\t\t\t\t4. List all medicines of certain category.");
    printf("\n\t\t\t\t5. List all medicines that treat a certain disease.\n\t\t\t\t6. Search for medicine.");
    printf("\n\t\t\t\t7. Update quantity of certain medicine.\n\t\t\t\t8. Delete medicine.");
    printf("\n\t\t\t\t9. Delete all medicines from the same company.\n\t\t\t\t10. Save list information to file Pharmacy.txt.");
    printf("\n\t\t\t\t11. Create hash table from data in Pharamcy.txt.");
    printf("\n\t\t\t\t\t\tEnter selection: ");
}

/* Function to print hash menu */
void HashMenu()
{
    printf("\n\n\n\t\t\t\t      Please select from the following options:\n");
    printf("\n\t\t\t\t1. Print hashed table and its size.\t2. Print the used hash function.");
    printf("\n\t\t\t\t3. Search for medicine.\t\t\t4. Insert new record (medicine).");
    printf("\n\t\t\t\t5. Delete a record (medicine).\t\t6. Save data to Pharamcy.txt.");
    printf("\n\t\t\t\t0. Back to Main Menu.");
    printf("\n\t\t\t\t\t\tEnter selection: ");
}

/* Function to make the BST empty */
void MakeEmpty(MEDICINE T)
{
    if (T == NULL)
        return;

    MakeEmpty(T->Left);
    MakeEmpty(T->Right);
    free(T);
}

/* Function to open the Meds File, and store its data into the BST */
MEDICINE ReadMedicine(MEDICINE Medicine)
{
    MakeEmpty(Medicine);
    Medicine = NULL;

    FILE *in = fopen(MedsFile, "r");

    char *name, *expDate, *indication, *ingredient, *category, *company;
    int quantity;
    String line;

    while (fgets(line, 500, in)) // As long as EOF isn't met, scan and store teams information.
    {
        name = strtok(line, ":");
        name[0] = toupper(name[0]);
        ingredient = strtok(NULL, ":");
        category = strtok(NULL, ":");
        indication = strtok(NULL, ":");
        expDate = strtok(NULL, ":");
        quantity = atoi(strtok(NULL, ":"));
        company = strtok(NULL, "\n");
        Medicine = Insert(name, ingredient, category, indication, expDate, quantity, company, Medicine);
        MEDICINE temp = FindByName(name, Medicine);
    }

    printf("\n\t\t\t\t\t--Medicines' list read successfully.--");
    fclose(in);
    return Medicine;
}

/* Function to add a new medicine to the BST */
MEDICINE AddMedicine(MEDICINE Medicine)
{
    String name, ingredient, category, expDate, ind, company;
    int quantity;

    printf("\n\t\t\t\t\t\tEnter name of medicine: ");
    scanf(" %[^\n]s", name);
    name[0] = toupper(name[0]);
    MEDICINE status = FindByName(name, Medicine);
    /* Checking if the medicicne already exists, if yes: the user is given the option to update its quantity */
    /*                                           if not: the user is asked to enter the rest of the info */
    if (status != NULL)
    {
        printf("\n\t\t\t\t\t\tMedicine %s already exists in the tree.\n\t\t\t\t\t\tDo you want to update its available quantity?(yes/no): ", name);
        char answer[3];
        scanf("%s", answer);

        if (strcasecmp(answer, "no") == 0)
            return Medicine;

        printf("\n\t\t\t\t\t\tEnter the quantity you want to update instead of the existing available quantity of (%d): ", status->Quantity);
        scanf("%d", &quantity);
        status->Quantity = quantity;
        if (status->Quantity == quantity)
            printf("\n\t\t\t\t\t\tThe new updated quantity is: (%d)", status->Quantity);
        else
            printf("!!Updating Quantity failed!!");

        return Medicine;
    }
    else // If medicine doesn't already exist
    {
        char buffer[10000];
        printf("\n\t\t\t\t\t\tEnter the active ingredient in the medicine: ");
        fgets(buffer, sizeof(buffer), stdin);
        fgets(ingredient, sizeof(ingredient), stdin);
        ingredient[strcspn(ingredient, "\n")] = 0;
        printf("\n\t\t\t\t\tEnter the category of the medicine: ");
        fgets(category, sizeof(category), stdin);
        category[strcspn(category, "\n")] = 0;
        printf("\n\t\t\t\t\tEnter the indications/symptoms this medicine is used for (indication1,indication2,...): ");
        fgets(ind, sizeof(ind), stdin);
        ind[strcspn(ind, "\n")] = 0;
        printf("\n\t\t\t\t\tEnter the expiry date for this medicine (MM,YYYY): ");
        scanf("%s", expDate);
        printf("\n\t\t\t\t\tEnter the available quantity of this medicine: ");
        scanf("%d", &quantity);
        printf("\n\t\t\t\t\tEnter the manufacturing company of this medicine: ");
        fgets(company, sizeof(company), stdin);
        fgets(company, sizeof(company), stdin);
        company[strcspn(company, "\n")] = 0;
        // scanf("%s", company);

        // Add new medicine to the BST
        Medicine = Insert(name, ingredient, category, ind, expDate, quantity, company, Medicine);

        printf("%s,  %s,  %s,  %s,  %s,  %d,  %s\n", name, ingredient, category, ind, expDate, quantity, company);

        /** Extra code for automatically adding the new medicine to the Meds File **/
        // FILE *out = fopen(MedsFile, "a"); // open file for appending new team
        // fprintf(out, "\n%s:%s:%s:%s:%s:%d:%s", name, ingredient, category, ind, expDate, quantity, company);
        // fclose(out); // close file

        return Medicine;
    }
}

/* Funciton to search for a medicine in the BST by name */
MEDICINE FindByName(char *name, MEDICINE T)
{

    if (T == NULL)
        return NULL;
    else
    {
        int comparison = strcasecmp(name, T->Name);
        if (comparison == 0)
            return T;
        if (comparison < 0)
            return FindByName(name, T->Left);
        else if (comparison > 0)
            return FindByName(name, T->Right);
        return NULL;
    }
}

/* Funciton to search for a medicine in the BST by indications/symptoms */
MEDICINE FindBySymptom(char *symptom, MEDICINE T)
{

    if (T == NULL)
        return NULL;

    if (strstr(T->Indications, symptom) != NULL)
        return T;

    if (T->Left != NULL)
        T = FindBySymptom(symptom, T->Left);
    if (T->Right != NULL)
        T = FindBySymptom(symptom, T->Right);

    return T;
}

/* Funciton to search for a medicine in the BST by company */
MEDICINE FindByCompany(char *company, MEDICINE T)
{

    if (T == NULL)
        return NULL;
    if (strcasecmp(T->Company, company) == 0)
        return T;

    MEDICINE found = FindByCompany(company, T->Left);
    if (found != NULL)
        return found;
    found = FindByCompany(company, T->Right);
    if (found != NULL)
        return found;
}

/* Funciton to search for a medicine in the BST by category */
MEDICINE FindByCategory(char *category, MEDICINE T)
{

    if (T == NULL)
        return NULL;
    if (strcasecmp(T->Category, category) == 0)
        return T;

    MEDICINE found = FindByCategory(category, T->Left);
    if (found != NULL)
        return found;
    found = FindByCategory(category, T->Right);
    if (found != NULL)
        return found;
}

/* Function to find the left-most node (the smallest based on key) in the BST (or sub-BST) */
MEDICINE FindMin(MEDICINE T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

/* Funciton to insert medicine (node) into BST and sorting based on the Name field */
MEDICINE Insert(String name, String ingredient, String category, String indications, String expDate, int quantity, String company, MEDICINE T)
{

    if (T == NULL) // If root (node) is empty then create node and assign the values to it
    {
        T = (struct Node *)malloc(sizeof(struct Node));
        if (T == NULL)
            printf("Out of space");
        else
        {
            strcpy(T->Name, name);
            strcpy(T->ActiveIngredient, ingredient);
            strcpy(T->Category, category);
            strcpy(T->Indications, indications);
            strcpy(T->ExpirationDate, expDate);
            T->Quantity = quantity;
            strcpy(T->Company, company);

            T->Left = T->Right = NULL;
        }
    }
    else if (strcmp(name, T->Name) < 0) // If new name is lexicographically less than the current node, insert at left subtree
    {
        T->Left = Insert(name, ingredient, category, indications, expDate, quantity, company, T->Left);
    }
    else if (strcmp(name, T->Name) > 0) // If new name is lexicographically greater than the current node, insert at right subtree
    {
        T->Right = Insert(name, ingredient, category, indications, expDate, quantity, company, T->Right);
    }
    else // else, the medicine is in the tree already, increment its quantity by one
        T->Quantity++;
    return T;
}

/* Delete Medicine from tree based on name */
MEDICINE DeleteByName(MEDICINE root, char *name)
{
    if (root == NULL)
        return root;

    int cmp = strcasecmp(name, root->Name);
    if (cmp < 0) // If name is lexicographically less than the current node, delete at left subtree
        root->Left = DeleteByName(root->Left, name);
    else if (cmp > 0) // If name is lexicographically less than the current node, delete at right subtree
        root->Right = DeleteByName(root->Right, name);
    else // If node is found
    {
        if (root->Left == NULL) // If it only has a right child, make it the new root of the (sub)tree
        {
            MEDICINE temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL) // If it only has a left child, make it the new root of the (sub)tree
        {
            MEDICINE temp = root->Left;
            free(root);
            return temp;
        }
        /* If it has both left and right children, make the left-most (lexicographically smallest) node in the right subtree the new root */
        MEDICINE temp = FindMin(root->Right);
        strcpy(root->Name, temp->Name);
        strcpy(root->ActiveIngredient, temp->ActiveIngredient);
        strcpy(root->Category, temp->Category);
        strcpy(root->Indications, temp->Indications);
        strcpy(root->ExpirationDate, temp->ExpirationDate);
        root->Quantity = temp->Quantity;
        strcpy(root->Company, temp->Company);
        root->Right = DeleteByName(root->Right, temp->Name);
        return root;
    }
    return root;
}

/* Function to delete a medicine based on company name */
MEDICINE DeleteByCompany(MEDICINE root, char *company)
{ // Functions similarly to DeleteByName()
    if (root == NULL)
        return NULL;

    root->Left = DeleteByCompany(root->Left, company);
    root->Right = DeleteByCompany(root->Right, company);

    if (strcmp(root->Company, company) == 0)
    {
        if (root->Left == NULL)
        {
            MEDICINE temp = root->Right;
            free(root);
            return temp;
        }
        else if (root->Right == NULL)
        {
            MEDICINE temp = root->Left;
            free(root);
            return temp;
        }

        MEDICINE temp = FindMin(root->Right);
        strcpy(root->Name, temp->Name);
        strcpy(root->ActiveIngredient, temp->ActiveIngredient);
        strcpy(root->Category, temp->Category);
        strcpy(root->Indications, temp->Indications);
        strcpy(root->ExpirationDate, temp->ExpirationDate);
        root->Quantity = temp->Quantity;
        strcpy(root->Company, temp->Company);
        root->Right = DeleteByName(root->Right, temp->Name);
        return root;
    }

    return root;
}

/* Function to delete a medicine from the tree */
MEDICINE DeleteFromList(MEDICINE root)
{
    String buffer, name;
    printf("\n\t\t\t\t\t   Enter medicine's name to delete: ");
    fgets(buffer, sizeof(buffer), stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    name[0] = toupper(name[0]);

    root = DeleteByName(root, name);
    if (FindByName(name, root) == NULL)
        printf("Medicine %s has been successfully deleted!\n", name);
    else
        printf("!!Deleting Medicine %s has failed!!\n", name);
    return root;
}

/* Function to search for a medicine in the BST and give the user the option to modify its info */
void SearchModify(MEDICINE T)
{
    String buffer, name;
    printf("Please enter the medicine's name: ");
    fgets(buffer, sizeof(buffer), stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    MEDICINE P = FindByName(name, T);
    int option; // Input from user
    if (P != NULL && strcasecmp(P->Name, name) == 0)
    {
        printf("Medicine (%s) found!\n", P->Name);
        PrintHeader();
        printf("=> %s\t%25s  %15s  %36s  %8s  %6d\t%s\n", P->Name, P->ActiveIngredient, P->Category, P->Indications, P->ExpirationDate, P->Quantity, P->Company);
        printf(" Do you want to modify its information? (y/n)\n", P->Name);
        char answer;
        scanf("%c", &answer);
        switch (answer)
        {
        case 'n':
            break;
        case 'y':

            option = -1;
            MEDICINE temp = P;

            while (option != 0)
            {
                printf("\nChoose from the following options to modify:\n");
                printf("1. Name\t\t\t2. Active Ingredient\n3. Category\t\t4. Indications\n");
                printf("5. Expiration Date\t6. Quantity\n7. Company\t\t0. Done\n");
                scanf("%d", &option);
                switch (option)
                {
                case 1: // Update name, by copying the info of the medicine to a temp node,
                        // then deleting the medicine, then inserting the temp node back to the tree with the new name,
                    printf("Enter the new name you wish to update. (Current name: %s)\n", P->Name);
                    String newName;
                    fgets(newName, sizeof(newName), stdin);
                    fgets(newName, sizeof(newName), stdin);
                    newName[strcspn(newName, "\n")] = 0;
                    int tempQuantity = P->Quantity;
                    T = DeleteByName(T, P->Name);
                    T = Insert(newName, temp->ActiveIngredient, temp->Category, temp->Indications, temp->ExpirationDate, tempQuantity, temp->Company, T);
                    P = FindByName(newName, T);
                    if (strcasecmp(P->Name, newName) == 0)
                    {
                        printf("Name updated to %s successfully.\n", P->Name);
                    }
                    else
                        printf("!!Updating name has failed!!");
                    break;
                case 2: // Update active ingredient
                    printf("Enter the new active ingredient you wish to update. (Current ingredient: %s)\n", P->ActiveIngredient);
                    String newIngredient;
                    scanf("%s", newIngredient);
                    strcpy(P->ActiveIngredient, newIngredient);
                    if (strcasecmp(P->ActiveIngredient, newIngredient) == 0)
                        printf("Ingredient updated to %s successfully.\n", P->ActiveIngredient);
                    else
                        printf("!!Updating ingredient has failed!!");
                    break;
                case 3: // Update category
                    printf("Enter the new category you wish to update. (Current category: %s)\n", P->Category);
                    String newCategory;
                    fgets(newCategory, sizeof(newCategory), stdin);
                    fgets(newCategory, sizeof(newCategory), stdin);
                    newCategory[strcspn(newCategory, "\n")] = 0;
                    strcpy(P->Category, newCategory);
                    if (strcasecmp(P->Category, newCategory) == 0)
                        printf("Category updated to %s successfully.\n", P->Category);
                    else
                        printf("!!Updating category has failed!!");
                    break;
                case 4: // Update indications, give the user options to delete or add indications REMEMBER TO MODIFY
                    printf("\nCurrent indications: %s\nDo you want to (a) Add an indication. (b) Delete an indication. (c) Go back.\n", P->Indications);
                    char c;
                    scanf("%c", &c);
                    scanf("%c", &c);
                    String addIndication, deleteIndication;
                    while (c != 'c')
                    {
                        switch (c)
                        {
                        case 'a': // Add new indication
                            printf("Enter new indication: ");
                            scanf("%s", addIndication);
                            String cat;
                            sprintf(cat, ",%s", addIndication);
                            strcat(P->Indications, cat);
                            if (strstr(P->Indications, addIndication) != NULL)
                                printf("New indication %s added successfully!\n", addIndication);
                            else
                                printf("!!Adding new indication has failed!!\n");
                            break;
                        case 'b': // Delete existing indication
                            printf("Enter indication you want to delete: ");
                            scanf("%s", deleteIndication);

                            // Pointer to the start of the indication
                            char *ptr = strstr(P->Indications, deleteIndication);
                            // If the indication to be deleted is the last indication, delete it along with the comma preceding it
                            if (ptr[strlen(ptr) - 1] == P->Indications[strlen(P->Indications) - 1])
                            {
                                strncpy(ptr - 1, ptr + strlen(deleteIndication), strlen(ptr));
                            }
                            else if (ptr != NULL)
                                // Delete the indication with the comma after it
                                strncpy(ptr, ptr + strlen(deleteIndication) + 1, strlen(ptr));

                            // Check if indication has been deleted
                            if (strstr(P->Indications, deleteIndication) == NULL)
                                printf("Indication %s deleted successfully!\n", deleteIndication);
                            else
                                printf("!!Deleting new indication has failed!!\n");
                            break;
                        case 'c': // Go back
                            break;
                        default:
                            printf("!!Invalid option. Please enter one of the options above!!\n");
                            break;
                        }
                        printf("\nCurrent indications: %s\nDo you want to (a) Add an indication. (b) Delete an indication. (c) Go back.\n", P->Indications);
                        scanf("%c", &c);
                        scanf("%c", &c);
                    }
                    break;
                case 5: // Update expiry date
                    printf("Enter the new expiration date you wish to update. (Current expiration date: %s)\n", P->ExpirationDate);
                    String newExpDate;
                    scanf("%s", newExpDate);
                    strcpy(P->ExpirationDate, newExpDate);
                    if (strcasecmp(P->ExpirationDate, newExpDate) == 0)
                        printf("Expiration date updated to %s successfully.\n", P->ExpirationDate);
                    else
                        printf("!!Updating expiration date has failed!!");
                    break;
                case 6: // Update quantity
                    printf("Enter the new quantity you wish to update. (Current quantity: %d)\n", P->Quantity);
                    int newQuantity;
                    scanf("%d", &newQuantity);
                    P->Quantity = newQuantity;
                    if (P->Quantity == newQuantity)
                        printf("Quantity updated to %d successfully.\n", P->Quantity);
                    else
                        printf("!!Updating quantity has failed!!");
                    break;
                case 7: // Update company
                    printf("Enter the new company you wish to update. (Current company: %s)\n", P->Company);
                    String newCompany;
                    fgets(newCompany, sizeof(newCompany), stdin);
                    fgets(newCompany, sizeof(newCompany), stdin);
                    newCompany[strcspn(newCompany, "\n")] = 0;
                    strcpy(P->Company, newCompany);
                    if (strcasecmp(P->Company, newCompany) == 0)
                        printf("Company updated to %s successfully.\n", P->Company);
                    else
                        printf("!!Updating company has failed!!");
                    break;
                case 0:
                    break;
                default:
                    printf("!!Option invalid. Please enter one of the options above!!");
                    break;
                }
            }
            break;
        }
    }
    else
        printf("!!Medicine Not Found!!\n");
}

/* Function to delete all medicines with the same company name */
void DeleteSameCompany(MEDICINE root)
{
    String buffer, company;
    printf("\n\t\t\t\t\t   Enter company's name to delete all medicines of: ");
    fgets(buffer, sizeof(buffer), stdin);
    fgets(company, sizeof(company), stdin);
    company[strcspn(company, "\n")] = 0;

    root = DeleteByCompany(root, company);
    if (FindByCompany(company, root) == NULL)
        printf("All medicines with company %s have been deleted successfully!\n", company);
    else
        printf("!!Deleting all medicines with company %s has failed!!\n", company);
}

/* Function to print all medicines that treat a specific disease/symptom */
void PrintSameSymptom(char *symptom, MEDICINE t)
{
    if (t == NULL)
        return;

    PrintSameSymptom(symptom, t->Left);
    if (strstr(t->Indications, symptom) != NULL)
        printf("=> %s\t%25s  %15s  %36s  %8s  %6d\t%s\n", t->Name, t->ActiveIngredient, t->Category, t->Indications, t->ExpirationDate, t->Quantity, t->Company);
    PrintSameSymptom(symptom, t->Right);
}

/* Function to format the output of PrintSameSymptom() */
void ListSameSymptom(MEDICINE MedicineTree)
{
    String buffer, symptom;
    printf("Please enter the symptom/disease: ");
    fgets(buffer, sizeof(buffer), stdin);
    fgets(symptom, sizeof(symptom), stdin);
    symptom[strcspn(symptom, "\n")] = 0;

    if (FindBySymptom(symptom, MedicineTree) != NULL)
    {
        printf("Medicine(s) available:\n");
        PrintHeader();
        PrintSameSymptom(symptom, MedicineTree);
    }
    else
        printf("No medicines for %s available!\n", symptom);
}

/* Function to print all medicines that are under the same category */
void PrintSameCategory(char *category, MEDICINE t)
{
    if (t == NULL)
        return;

    PrintSameCategory(category, t->Left);
    if (strcasecmp(category, t->Category) == 0)
        printf("=> %s\t%25s  %15s  %36s  %8s  %6d\t%s\n", t->Name, t->ActiveIngredient, t->Category, t->Indications, t->ExpirationDate, t->Quantity, t->Company);
    PrintSameCategory(category, t->Right);
}

/* Function to format the output of PrintSameCategory() */
void ListSameCategory(MEDICINE MedicineTree)
{
    String buffer, category;
    printf("Please enter the category: ");
    fgets(buffer, sizeof(buffer), stdin);
    fgets(category, sizeof(category), stdin);
    category[strcspn(category, "\n")] = 0;

    if (FindByCategory(category, MedicineTree) != NULL)
    {
        printf("Medicine(s) available:\n");
        PrintHeader();
        PrintSameCategory(category, MedicineTree);
    }
    else
        printf("No %s medicines available!\n", category);
}
/* Function to print medicines in alphabetical order */
void PrintInAlphaOrder(MEDICINE t)
{

    if (t == NULL)
        return;

    PrintInAlphaOrder(t->Left);
    printf("=> %s\t%25s  %15s  %36s  %8s  %6d\t%s\n", t->Name, t->ActiveIngredient, t->Category, t->Indications, t->ExpirationDate, t->Quantity, t->Company);
    PrintInAlphaOrder(t->Right);
}

/* Storing medicines in Pharmacy File alphabetically ascending */
void StoreMedicines(MEDICINE T)
{
    FILE *out = fopen(PharmacyFile, "a");
    if (T != NULL)
    {
        StoreMedicines(T->Left);
        fprintf(out, "%s:%s:%s:%s:%s:%d:%s\n", T->Name, T->ActiveIngredient, T->Category, T->Indications, T->ExpirationDate, T->Quantity, T->Company);
        fclose(out);
        StoreMedicines(T->Right);
    }
    fclose(out);
}

/* Open the Pharmacy File for writing. */
void StoreFile(MEDICINE T)
{
    FILE *out = fopen(PharmacyFile, "w");
    StoreMedicines(T);
    fclose(out);
    printf("\n\t\t\t\t--Medicines' information has been saved to %s successfully.--", PharmacyFile);
}

/* Function to update the quantity of a certain medicine */
void UpdateQuantity(MEDICINE M)
{
    String name;
    printf("Enter medicine's name to update quantity: ");
    fgets(name, sizeof(name), stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    MEDICINE P = FindByName(name, M);
    if (P != NULL && strcasecmp(P->Name, name) == 0)
    {
        printf("\nMedicine %s is found with quantity (%d)! Enter the new quantity: ", P->Name, P->Quantity);
        int newQuantity;
        scanf("%d", &newQuantity);
        P->Quantity = newQuantity;
        if (P->Quantity == newQuantity)
            printf("Quantity updated to %d successfully.\n", newQuantity);
        else
            printf("!!Updating Quantity has failed!!");
    }
    else
        printf("\n!!Medicine not Found!\n");
}

/* Function to create a hash table from the data in Pharmacy File */
void Hashing()
{
    /* Resetting the values in case the Hashing function was called multiple times */
    TotalCollisions = 0;
    TableCollisions = 0;
    TableEntries = 0;
    TableSize = 13; // INITIAL SIZE
    SizeBefore = 0;
    Table = (CELL *)malloc((sizeof(CELL)) * TableSize);

    InitializeTable(); // Initialize table with empty slots
    LoadHash();        // Load data from Pharmacy File into the Hash table

    int n = 0;  // Input from user
    HashMenu(); // Print Hash Menu
    scanf("%d", &n);

    while (n != 0)
    {
        switch (n)
        {
        case 1: // Print hash table, including empty and deleted slots
            PrintHashTable();
            break;
        case 2: // Print the hash function used
            PrintHashFunction();
            break;
        case 3: // Search for a medicine from the table
            SearchEntry();
            break;
        case 4: // Insert new medicine into the table
            InsertNewRecord();
            break;
        case 5: // Delete a medicine from the table
            DeleteRecord();
            break;
        case 6: // Save the hash table in Pharmacy File
            SaveHashTable();
            break;
        default:
            printf("\n\t\t\t\t!!Option invalid!! Please enter one of the options above\n\n");
            break;
        }
        HashMenu();
        scanf("%d", &n);
    }
}

/* Function to initalize table with empty slots */
void InitializeTable()
{
    for (int i = 0; i < TableSize; i++)
        Table[i] = NULL;
}

/* Load data from Pharmacy File into the Hash table */
void LoadHash()
{
    FILE *in = fopen(PharmacyFile, "r");
    String temp, name;
    while (fgets(temp, 500, in))
    {
        CELL Medicine = (CELL)malloc(sizeof(struct HashEntry));
        strcpy(name, strtok(temp, ":"));
        name[0] = toupper(name[0]); // Make first letter upper case
        strcpy(Medicine->Name, name);
        strcpy(Medicine->ActiveIngredient, strtok(NULL, ":"));
        strcpy(Medicine->Category, strtok(NULL, ":"));
        strcpy(Medicine->Indications, strtok(NULL, ":"));
        strcpy(Medicine->ExpirationDate, strtok(NULL, ":"));
        Medicine->Quantity = atoi(strtok(NULL, ":"));
        strcpy(Medicine->Company, strtok(NULL, "\n"));
        TotalCollisions += InsertHashEntry(Table, Medicine); // Inserting into hash table and increment number of collisions
    }

    fclose(in);
}

/* Function to rehash the table if it gets more than 70% full */
void reHash()
{
    /* Resetting entries size, and keep track of the old size to traverse, and get the new size, then create a table with the new size*/
    TableEntries = 0;
    SizeBefore = TableSize;
    TableSize = NextPrime(SizeBefore * 2);
    CELL *tempTable = (CELL *)malloc((sizeof(CELL)) * TableSize);

    // Inititalize new table with empty slots
    for (int i = 0; i < TableSize; ++i)
        tempTable[i] = NULL;

    // Copy old table entries into the new one
    for (int i = 0; i < SizeBefore; ++i)
    {
        if (Table[i] != NULL && Table[i] != DELETED)
        {
            TotalCollisions += InsertHashEntry(tempTable, Table[i]);
        }
    }
    free(Table);       // Free old table
    Table = tempTable; // Assign table to new table
}

/* Function to aply hash function: sum += Key[Keysize -1 -i] * 32^i % tableSize */
int HashFunction(String Key, int tableSize)
{
    int sum = 0, i = 0;
    while (i < KeySize)
    {
        // sum += Key[Keysize -1 -i] * 32^i % tableSize
        sum += Key[KeySize - 1 - i] * (int)pow(32, i) % tableSize;
        i++;
    }
    return (sum % tableSize);
}

/* Function to determine whether an integer is prime or not */
int isPrime(int n)
{               // 0 = false, 1 = true
    if (n <= 1) // 0 or 1 are not prime
        return 0;
    if (n <= 3) // 2 and 3 are prime
        return 1;

    /* if the integer is divisible by any number from 2 up to (integer - 1) then it's not prime, else then it's prime */
    for (int j = 2; j < n; j++)
    {
        if (n % j == 0)
            return 0;
    }
    return 1;
}

/* Function to find the next prime number after integer n */
int NextPrime(int n)
{
    if (n <= 1)
        return 2;
    int prime = n;
    while (!isPrime(prime))
    {
        prime++;
    }
    return prime;
}

/* Function to insert entry into hash table */
int InsertHashEntry(CELL Table[], CELL Medicine)
{
    int NumOfCollision = 0; // Number of collisions for one entry
    int newIndex = 0;       // New index in case of collision
    if (Medicine == NULL)
        return 0;

    int index = HashFunction(Medicine->Name, TableSize);
    for (int i = 0; i < TableSize; i++)
    {
        newIndex = (i * i + index) % TableSize; // Resolving collision by using Quadratic Probing

        if (Table[newIndex] == NULL || Table[newIndex] == DELETED) // If the slot is either empty or has been deleted then insert in it
        {
            Table[newIndex] = Medicine;
            Table[newIndex]->index = newIndex;
            TableEntries += 1;
            if (((float)TableEntries / TableSize) > 0.7) // Using the threshold 0.7 ensures that rehashing is done when more than half, but just enough, of the table is full
            {
                TableCollisions = 0;
                printf("\n!! Rehashing occured !!\n");
                reHash();
            }
            return NumOfCollision;
        }
        NumOfCollision++;  // Increment total collisions
        TableCollisions++; // Increment table's collisions
    }
    printf("!!Insertion Failed\n"); // If insertion failed
    return NumOfCollision;
}

/* Function to save the table to Pharmacy File */
void SaveHashTable()
{
    FILE *out = fopen(PharmacyFile, "w");
    for (int i = 0; i < TableSize; i++)
        if (Table[i] != NULL && Table[i] != DELETED) // Only print the occupied slots
            fprintf(out, "%s:%s:%s:%s:%s:%d:%s\n", Table[i]->Name, Table[i]->ActiveIngredient, Table[i]->Category, Table[i]->Indications, Table[i]->ExpirationDate, Table[i]->Quantity, Table[i]->Company);
    fclose(out);
}

/* Function to insert a new medicine into the table */
void InsertNewRecord()
{
    /* Read medicine info */
    CELL Medicine = malloc(sizeof(struct HashEntry));
    String name;
    printf("Enter name: ");
    scanf(" %[^\n]", name);
    name[0] = toupper(name[0]); // Make first letter uppercase
    strcpy(Medicine->Name, name);
    printf("Enter active ingredient: ");
    scanf(" %[^\n]", Medicine->ActiveIngredient);
    printf("Enter category: ");
    scanf(" %[^\n]", Medicine->Category);
    printf("Enter indications: ");
    scanf(" %[^\n]", Medicine->Indications);
    printf("Enter expiraton date: ");
    scanf(" %[^\n]", Medicine->ExpirationDate);
    printf("Enter quantity: ");
    scanf("%d", &Medicine->Quantity);
    printf("Enter company: ");
    scanf(" %[^\n]", Medicine->Company);
    TotalCollisions += InsertHashEntry(Table, Medicine); // Inserting new medicine

    /* Check if the medicine has been added or not */
    if (SearchHash(Medicine->Name) != NULL)
        printf("Hash entry successfully added at index (%d)!\n", SearchHash(Medicine->Name)->index);
    else
        printf("!!Adding new hash entry has failed!!\n");
}

/* Function to print the table including the empty slots */
void PrintHashTable()
{
    printf("\n\n\n\e[1mHASH TABLE ENTRIES\n\e[m");
    int i;
    for (i = 0; i < TableSize; ++i)
    {
        if (Table[i] == NULL)
            printf("%d\t%s\n", i, "-< EMPTY >-");
        else if (Table[i] == DELETED)
            printf("%d\t%s\n", i, "-< DELETED >-");
        else
            printf("%d\t%s\n", i, Table[i]->Name);
    }
    printf("\e[1mSize: %d\tOccupied Cells: %d/%d\n\e[m", TableSize, TableEntries, TableSize);
    printf("\e[1mTotal Collisions: %d\t This Table's Collisions: %d\n\n\e[m", TotalCollisions, TableCollisions);
}

/* Function to print the used hash function */
void PrintHashFunction()
{
    printf("Hash function used is:\n");
    printf("\e[1mSUM[i](0 -> KeySize-1)  [ Key[KeySize - i - 1] * 32^i % TableSize ]\n\e[m");
    printf("Collision is resolved using \e[1mQuadratic Probing\e[m\n");
}

/* Function to search for medicine in the table */
void SearchEntry()
{
    String name;
    printf("Enter name of medicine: ");
    scanf(" %[^\n]", name);
    name[0] = toupper(name[0]);
    printf("\n");
    CELL result = SearchHash(name);
    if (result != NULL)
    {
        printf("\nMedicine %s found at index (%d).\t Number of collisions: %d\n", result->Name, result->index, SearchColissions);
        PrintHeader();
        printf("=> %s\t%25s  %15s  %36s  %8s  %6d\t%s\n", result->Name, result->ActiveIngredient, result->Category, result->Indications, result->ExpirationDate, result->Quantity, result->Company);
    }
}

/* Function to delete a medicine from the table */
void DeleteRecord()
{
    String name;
    printf("Enter name of the medicine you want to delete: ");
    scanf(" %[^\n]", name);
    name[0] = toupper(name[0]); // Make first letter uppercase

    if (DeleteHashEntry(name) != NULL)
        printf("DELETED SUCCESSFULLY FROM TABLE\n");
    else
        printf("NODE NOT FOUND IN TABLE\n");
}

/* Function to delete an entry from the hash table */
CELL DeleteHashEntry(String name)
{
    int index = HashFunction(name, TableSize); // Get index of entry
    for (int i = 0; i < TableSize; ++i)
    {
        int newIndex = (index + i * i) % TableSize; // Resolve collision

        if (Table[newIndex] == NULL) // If slot is empty, return null
            return NULL;
        if (Table[newIndex] == DELETED) // If slot is already deleted, skip current iteration and start the new one
            continue;
        if (strcasecmp(name, Table[newIndex]->Name) == 0) // Entry is found
        {
            /* Set the entry slot to the DELETED marker, and decrement the number of Table Entries */
            CELL temp = Table[newIndex];
            Table[newIndex] = DELETED;
            TableEntries--;
            return temp;
        }
    }
    return NULL;
}

/* Function to search for an entry in the hash table */
CELL SearchHash(String name)
{
    /* Get the index where the entry is supposed to be, then check if the entry at that index
       has the same name we're looking for
    */
    SearchColissions = 0;
    int index = HashFunction(name, TableSize);

    for (int i = 0; i < TableSize; ++i)
    {
        int newIndex = (index + i * i) % TableSize;
        if (Table[newIndex] == NULL)
        {
            printf("!!Medicine %s is not found!!", name);
            return NULL;
        }
        if (Table[newIndex] == DELETED)
            continue;
        if (strcasecmp(name, Table[newIndex]->Name) == 0)
        {

            return Table[newIndex];
        }
        SearchColissions++;
    }
}

/* Extra function to find the right-most node of the tree (or subtree) */
// MEDICINE FindMax(MEDICINE T)
// {
//     if (T == NULL)
//         return NULL;
//     else if (T->Right == NULL)
//         return T;
//     else
//         return FindMax(T->Right);
// }