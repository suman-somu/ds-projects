#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
// #include <termios.h>

// return 0-9 as 48-57
/*int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
*/
typedef struct contact
{
    char name[50];
    char email[41];
    char number[11];
} contact;

typedef struct customers
{
    char name[50];
    char email[41];
    char password[13];
    int n;
    struct contact *directory;
} customer;

void gotoxy(int x, int y);
void titleScreen();
void screenHeading();
void defaultInput(customer *c);
int chooseBetweenTwo(int a, int b, int c);

customer *loginAuthentication(customer c[]);
customer *checkEmail(customer *c);
bool checkPassword(customer *c);

void mainMenu(customer *c);

void showContacts(customer *c);

void searchContact(customer *c);

void addContact(customer *c);

void editContact(customer *c, int choose, int fn);

void deleteContact(customer *c, int choose);

int chooseBetweenTwo(int a, int b, int c);

void contactDetails(customer *c, int choose, int fn);

bool checkNameValid(char *name);
bool checkNumberValid(char *number);
bool checkEmailValid(char *email);

int main()
{
    customer c[3];
    defaultInput(c);
    // titleScreen();

    // customer *current = loginAuthentication(c);

    mainMenu(c);
}

void mainMenu(customer *c)
{

    screenHeading();
    gotoxy(60, 10);
    printf("MAIN MENU");
    gotoxy(60, 13);
    printf("Enter a function to perform");
    gotoxy(60, 15);
    printf("1\t Show Contacts");
    gotoxy(60, 16);
    printf("2\t Search Contacts");
    gotoxy(60, 17);
    printf("3\t Add contacts");
    gotoxy(60, 18);
    printf("0\t Exit");

    int ch = getch() - 48;

    if (ch == 1)
        showContacts(c);
    else if (ch == 2)
        searchContact(c);
    else if (ch == 3)
        addContact(c);
    else if (ch == 0)
    {
        system("clear");
        system("cls");
        gotoxy(80, 25);
        printf("THANK YOU FOR USING OUR SYSTEM.");
        gotoxy(83, 28);
        printf("made with love from grp 2\n\n\n");
        gotoxy(0, 50);
        exit(0);
    }
    else
    {
        gotoxy(60, 21);
        printf("wrong no. try again");
        getch();
        mainMenu(c);
    }
}

void showContacts(customer *c)
{
    screenHeading();

    gotoxy(78, 10);
    printf("Sort Contacts:-");

    gotoxy(81, 11);
    printf("1. By Name.");
    gotoxy(81, 12);
    printf("2. By Number.");
    gotoxy(81, 13);
    printf("0. Go Back.");
    gotoxy(78, 15);
    printf(">>");

    int ch = chooseBetweenTwo(1, 2, 0);

    switch(ch){
        case 1: {
            // sortByName(c->directory);
            // break;
            sort(c->directory, 0, (c->n)-1, 1);
            break;
        }
        case 2:{
            sort(c->directory, 0, (c->n)-1, 2);
            break;
        }
        default:{
            mainMenu(c);
            break;
        }
    }

    screenHeading();

    int m = 26; // side margins
    int d = 18; // distance between columns
    /*
    2*m + 2*d + 52(name) + 21(number) + 8(s. no.) = 169.
    */
    gotoxy(m + 1, 10);
    printf("All Contacts:-");

    gotoxy(m + 1, 12);
    for (int i = 0; i < 8; i++)
        printf("_");
    gotoxy(m + d + 8, 12);
    for (int i = 0; i < 52; i++)
        printf("_");
    gotoxy(m + 2 * d + 60, 12);
    for (int i = 0; i < 21; i++)
        printf("_");

    gotoxy(m + 2, 14);
    printf("S. No.");
    gotoxy(m + d + 26, 14);
    printf("Recipient's Name");
    gotoxy(m + 2 * d + 61, 14);
    printf("Contact Information");

    gotoxy(m + 1, 15);
    for (int i = 0; i < 8; i++)
        printf("_");
    gotoxy(m + d + 8, 15);
    for (int i = 0; i < 52; i++)
        printf("_");
    gotoxy(m + 2 * d + 60, 15);
    for (int i = 0; i < 21; i++)
        printf("_");

    int i;
    for (i = 0; i < c->n; i++)
    {
        gotoxy(m+3, 17+2*i);
        printf("%d.", i+1);

        gotoxy(m+d+9, 17+2*i);
        printCamelString(((c->directory)+i)->name);
        // printf("%s", ((c->directory)+i)->name);

        gotoxy(m+2*d+63, 17+2*i);
        printf("+91-%s", ((c->directory)+i)->number);
    }

    gotoxy(m + 1, 17+2*i+3);
    printf("Press:");
    gotoxy(m+4, 17+2*i+4);
    printf("1. Choose a particular contact from the above list.");
    gotoxy(m+4, 17+2*i+5);
    printf("0. Go back.");
    gotoxy(m+1, 17+2*i+7);
    printf(">>");

    int choose = chooseBetweenTwo(1, 0, 0);
    switch(choose){
        case 1: {
            gotoxy(m+1, 17+2*i+9);
            printf("Enter the desired serial number: ");
            int choice;
            scanf("%d", &choice);
            getchar();
            if(choice>=1 && choice<=c->n){
                contactDetails(c,choice-1,1);
            }
            else {
                gotoxy(m+1, 17+2*i+11);
                printf("NO CONTACT");
                getch();
                showContacts(c);
            }
            break;
        }
        case 0: 
            showContacts(c);
            break;
    }
}


void contactDetails(customer *c, int choose, int fn)
{

    screenHeading();

    if (choose < c->n)
    {
        gotoxy(50, 10);
        printf("CONTACT DETAILS:-");

        gotoxy(50, 12);
        printCamelString(((c->directory) + (choose))->name);

        gotoxy(50, 14);
        printf("Contact Number : +91-%s.", ((c->directory) + (choose))->number);

        gotoxy(50, 16);
        printf("E-Mail ID : %s.", ((c->directory) + (choose))->email);

        gotoxy(50, 20);
        printf("Press:");
        gotoxy(53, 21);
        printf("1. Edit Contact.");
        gotoxy(53, 22);
        printf("2. Delete Contact.");
        gotoxy(53, 23);
        printf("0. Go back.");
        gotoxy(50, 25);
        printf(">>");

        int ch = chooseBetweenTwo(1, 2, 0);
        switch (ch)
        {
        case 1:
        {
            editContact(c, choose, fn);
            break;
        }
        case 2:
        {
            screenHeading();
            deleteContact(c, choose + 1);
            mainMenu(c);
            break;
        }
        default:
        {
            if (fn == 1)
            {
                showContacts(c);
            }
            else if (fn == 2)
            {
                searchContact(c);
            }
            break;
        }
        }
    }
    else
    {
        printf("\n\nthere is no contact of that number.");
        printf("\ntry again once more\n\n");
        showContacts(c);
    }
}

void editContact(customer *c, int choose, int fn)
{

    char tempName[50], tempNumber[11], tempEmail[41];

    printf("\t\t\t\t\t\n\nEdit Contact");
    printf("\n 1.Name\n 2.Number\n 3.Email\n 4.Cancel\n\n");
    int ch = getch() - 48;

    if (ch == 1)
    {
    Name:
        printf("\nEnter Name : ");
        gets(tempName);
        if(checkNameValid(tempName)){
            lowerString(tempName);
            strcpy(((c->directory) + c->n-1)->name,tempName);
        }
        else
        {
            printf("\nInvalid Name");
            goto Name;
        }
        printf("Your name has been edited\n");
    }
    else if (ch == 2)
    {
    Number:
        printf("\nEnter Number : ");
        gets(tempNumber);
        if (checkNumberValid(tempNumber))
        {
            strcpy(((c->directory) + choose)->number, tempNumber);
        }
        else
        {
            printf("\nInvalid Number");
            goto Number;
        }
        printf("Your number has been edited\n");
    }
    else if (ch == 3)
    {
    Email:
        printf("\nEnter Email : ");
        gets(tempEmail);
        if (checkEmailValid(tempEmail))
        {
            strcpy(((c->directory) + choose)->email, tempEmail);
        }
        else
        {

            printf("\nInvalid Email");
            goto Email;
        }
        printf("Your email has been edited\n");
    }
    else if (ch == 4)
    {
        system("clear");
        system("cls");
        printf("\nYour contact has not been edited\n");
        contactDetails(c, choose + 1, fn);
    }
    else
    {
        printf("wrong option\n");
        getch();
        contactDetails(c, choose + 1, fn);
    }
    showContacts(c);
}

void searchContact(customer *c)
{
    // search by name or by number

    system("clear");
    screenHeading();
    gotoxy(70, 10);
    printf("SEARCH CONTACTS:");
    gotoxy(60, 13);
    printf("1\tBy name");
    gotoxy(60, 15);
    printf("2\tBy number");
    gotoxy(60, 18);
    printf("0\treturn to menu");
    int ch = chooseBetweenTwo(1, 2, 0);

    switch (ch)
    {
    case 1:
        searchByName(c);
        searchContact(c);
        break;
    case 2:
        searchByNumber(c);
        searchContact(c);
        break;
    default:
        mainMenu(c);
        break;
        // default:
        //     printf("\n\nwrong choice");
        //     getch();
        //     searchContact(c);
        //     break;
    }
}

void addContact(customer *c)
{
    screenHeading();
    c->n = c->n + 1;
    c->directory = (struct contact *)realloc(c->directory, c->n * sizeof(struct contact));

    gotoxy(20, 10);
    printf("ADD CONTACT :-\n\n");

    char tempName[50], tempNumber[11], tempEmail[41];

Name:
    printf("\nEnter Name : ");
    gets(tempName);
    if (checkNameValid(tempName))
    {
        lowerString(tempName);
        strcpy(((c->directory) + c->n-1)->name, tempName);
    }
    else
    {
        printf("\nInvalid Name");
        goto Name;
    }

Number:
    printf("\nEnter Number : ");
    gets(tempNumber);
    if (checkNumberValid(tempNumber))
    {
        strcpy(((c->directory) + c->n - 1)->number, tempNumber);
    }
    else
    {
        printf("\nInvalid Number");
        goto Number;
    }

Email:
    printf("\nEnter Email : ");
    gets(tempEmail);
    if (checkEmailValid(tempEmail))
    {
        strcpy(((c->directory) + c->n - 1)->email, tempEmail);
    }
    else
    {
        printf("\nInvalid Email");
        goto Email;
    }

    printf("\n\n\nYour Contact has been save\n");
    printf("Press Any Key To go Back To Main Menu\n");
    getch();
    mainMenu(c);
}

bool checkNameValid(char *name)
{

    if (!((*name <= 90 && *name >= 65) || (*name <= 122 && *name >= 97) || (*name == '_')))
        return false;

    if (strlen(name) == 0)
        return false;
}

bool checkNumberValid(char *number)
{
    if (!(strlen(number) == 10 && number[0] >= 54 && number[0] <= 57))
    {
        return false;
    }

    int i = 0;
    while (number[i] != '\0')
    {
        if (!(number[i] <= 57 || number[i] >= 48))
            return false;
        i++;
    }

    return true;
}

bool checkEmailValid(char *email)
{
    int len = strlen(email);

    char *last_10 = &email[len - 10];
    if ((strcmp(last_10, "@email.com") == 0) || (strcmp(last_10, "@gmail.com") == 0) || (strcmp(last_10, "@yahoo.com") == 0))
    {
        return true;
    }
    return false;
}

void printCamelString(char *str){
    int i=0;
    while(str[i]!='\0'){
        if((i==0 && (str[i]<=122 && str[i]>=97)) || (str[i-1]==' ' && (str[i]<=122 && str[i]>=97)))
            printf("%c", str[i]-32);
        else
            printf("%c", str[i]);
        
        i++;
    }
}

void lowerString(char *str){
    int i=0;
    while(str[i]!='\0'){
        if(str[i]>=65 && str[i]<=90)
            str[i] = (str[i]+32);
        
        i++;
    }
}

void deleteContact(customer *c, int choose)
{

    char del;
    printf("Are you sure y/n : ");
    scanf("%c", &del);
    if(del=='y'){
    int totalContact = c->n;
    for (int i = choose; i < totalContact; i++)
    {
        strcpy(((c->directory) + i - 1)->name, ((c->directory) + i)->name);
        strcpy(((c->directory) + i - 1)->number, ((c->directory) + i)->number);
        strcpy(((c->directory) + i - 1)->email, ((c->directory) + i)->email);
    }
    c->n--;

    printf("\nContact has been deleted");
    printf("\nPress any key to go back to main menu");
    getch();
    }
    else
    {
    showContacts(c);
    }
    
}

void searchByName(customer *c)
{

    system("clear");
    system("cls");
    screenHeading();
    gotoxy(70, 10);
    printf("SEARCH CONTACT :\n\n\n");

    gotoxy(60, 13);
    printf("Enter the name: ");
    char name[50];
    // scanf("%s",&name);
    gets(name);

    int d = 0, i = 0;
    for (i = 0; i < c->n; i++)
    {
        if (strcmp(((c->directory) + i)->name, name) == 0)
        {
            d++;
            break;
        }
    }

    if (d == 1)
    {
        gotoxy(70, 17);
        printf("Contact Found");
        gotoxy(60, 19);
        printf("1. ");
        printCamelString(((c->directory) + i)->name);
        gotoxy(60, 23);
        printf("1 select contact\t\t0 go back");
        gotoxy(60, 25);
        printf(">>");
        int ch = chooseBetweenTwo(1, 0, 0);
        if (ch == 0)
        {
            mainMenu(c);
        }
        else
        {
            contactDetails(c, i + 1, 2);
        }
    }
    else
    {
        printf("not found");
        getch();
    }
}

void searchByNumber(customer *c)
{
    system("clear");
    system("cls");
    screenHeading();
    gotoxy(70, 10);
    printf("SEARCH CONTACT :\n\n\n");

    gotoxy(60, 13);
    printf("Enter the number: ");
    char number[11];
    // scanf("%s",&name);
    gets(number);

    int d = 0, i = 0;
    for (i = 0; i < c->n; i++)
    {
        if (strcmp(((c->directory) + i)->number, number) == 0)
        {
            d++;
            break;
        }
    }

    if (d == 1)
    {
        gotoxy(70, 17);
        printf("Contact Found");
        gotoxy(60, 19);
        printf(" 1\t%s", ((c->directory) + i)->name);
        gotoxy(60, 23);
        printf("1 select contact\t\t0 go back");
        gotoxy(60, 25);
        printf(">>");
        int ch = chooseBetweenTwo(1, 0, 0);
        if (ch == 0)
        {
            mainMenu(c);
        }
        else
        {
            contactDetails(c, i + 1, 2);
        }
    }
    else
    {
        printf("not found");
        getch();
    }
}

customer *loginAuthentication(customer c[])
{
    screenHeading();
    printf("\n\nLogin authentication...\n\n");
    printf("\n\nPress any key to login...");
    getch();

    customer *tempCustomer = checkEmail(c);
    getchar();
    if (checkPassword(tempCustomer))
        return (tempCustomer);
}

int partition (contact *co, int low, int high, int feature) 
{ 
    contact pivot = co[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    
    for (int j = low; j <= high - 1; j++) 
    { 
        if(feature == 1){
            if (strcmp((co+j)->name, pivot.name) < 0)
            { 
                i++;
                swapContacts((co+i), (co+j));
            }
        }
        else if (feature == 2){
            if (strcmp((co+j)->number, pivot.number) < 0)
            { 
                i++;
                swapContacts((co+i), (co+j));
            }
        }
    } 
    swapContacts((co+i+1), (co+high));
    return (i + 1); 
}

void sort(contact *co, int low, int high, int feature)
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(co, low, high, feature); 
  
        // Separately sort elements before 
        // partition and after partition 
        sort(co, low, pi - 1, feature); 
        sort(co, pi + 1, high, feature); 
    } 
}

void swapContacts(contact *co1, contact *co2){
    contact temp;
    strcpy(temp.name, co1->name);
    strcpy(temp.email, co1->email);
    strcpy(temp.number, co1->number);

    strcpy(co1->name, co2->name);
    strcpy(co1->email, co2->email);
    strcpy(co1->number, co2->number);

    strcpy(co2->name, temp.name);
    strcpy(co2->email, temp.email);
    strcpy(co2->number, temp.number);
}

customer *checkEmail(customer *c)
{

    screenHeading();

    printf("E-Mail Authentication:-");

    char tempEmail[41];

    printf("\n\nE-Mail ID: ");
    scanf("%s", tempEmail);
    // gets(tempEmail);

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(tempEmail, (c + i)->email) == 0)
            return (c + i);
    }

    // If E-mail not found
    gotoxy(70, 16);
    printf("OOPS! Email not found!");
    gotoxy(61, 18);
    printf("Press any key to enter email ID again...");
    getch();
    return (checkEmail(c));
}

bool checkPassword(customer *c)
{

    screenHeading();

    printf("Password Authentication:-");

    char tempPassword[13] = {};

    printf("\n\nPassword: ");
    int p = 0;

    char ch = getch();
    while (ch != 13 && ch != 10 && p < 12)
    {
        // printf("%d",ch);
        tempPassword[p++] = ch;
        printf("*");
        ch = getch();
    }

    if (strcmp(tempPassword, (c)->password) == 0)
        return true;

    // If password not found
    gotoxy(70, 16);
    printf("OOPS! Incorrect password!");
    gotoxy(61, 18);
    printf("Press any key to enter password again...");
    getch();
    return (checkPassword(c));
}

void defaultInput(customer *c)
{
    /*
    This function enters the default input into the program.
    */
    {
        // Entering data for 1st customer.
        strcpy(c->name, "Baibhav Kumar");
        strcpy(c->email, "baibhav.kumar@email.com");
        strcpy(c->password, "Baibhav@123");
        c->n = 5;
        c->directory = (struct contact *)malloc((c->n) * sizeof(struct contact));

        strcpy(((c->directory) + 0)->name, "Pratik Prakhar");
        strcpy(((c->directory) + 0)->email, "pratik.prakhar@email.com");
        strcpy(((c->directory) + 0)->number, "8249539257");

        strcpy(((c->directory) + 1)->name, "Yash Raj Singh");
        strcpy(((c->directory) + 1)->email, "yashraj.singh@email.com");
        strcpy(((c->directory) + 1)->number, "9693221160");

        strcpy(((c->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy(((c->directory) + 2)->email, "dibya.ranjan@email.com");
        strcpy(((c->directory) + 2)->number, "9348174331");

        strcpy(((c->directory) + 3)->name, "Shubhank Nagar");
        strcpy(((c->directory) + 3)->email, "shubhank.nagar@email.com");
        strcpy(((c->directory) + 3)->number, "9001332089");

        strcpy(((c->directory) + 4)->name, "Ritesh Kumar");
        strcpy(((c->directory) + 4)->email, "ritesh.kumar@email.com");
        strcpy(((c->directory) + 4)->number, "8239084216");
    }

    {
        // Entering data for 2nd customer.
        strcpy((c + 1)->name, "Hemant Sah");
        strcpy((c + 1)->email, "hemant.sah@email.com");
        strcpy((c + 1)->password, "Hemant@123");
        (c + 1)->n = 6;
        (c + 1)->directory = (struct contact *)malloc(((c + 1)->n) * sizeof(struct contact));

        strcpy((((c + 1)->directory) + 0)->name, "Pratik Prakhar");
        strcpy((((c + 1)->directory) + 0)->email, "pratik.prakhar@email.com");
        strcpy((((c + 1)->directory) + 0)->number, "8249539257");

        strcpy((((c + 1)->directory) + 1)->name, "Yash Raj Singh");
        strcpy((((c + 1)->directory) + 1)->email, "yashraj.singh@email.com");
        strcpy((((c + 1)->directory) + 1)->number, "9693221160");

        strcpy((((c + 1)->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy((((c + 1)->directory) + 2)->email, "dibya.ranjan@email.com");
        strcpy((((c + 1)->directory) + 2)->number, "9348174331");

        strcpy((((c + 1)->directory) + 3)->name, "Shubhank Nagar");
        strcpy((((c + 1)->directory) + 3)->email, "shubhank.nagar@email.com");
        strcpy((((c + 1)->directory) + 3)->number, "9001332089");

        strcpy((((c + 1)->directory) + 4)->name, "Ritesh Kumar");
        strcpy((((c + 1)->directory) + 4)->email, "ritesh.kumar@email.com");
        strcpy((((c + 1)->directory) + 4)->number, "8239084216");

        strcpy((((c + 1)->directory) + 5)->name, "aare maghia");
        strcpy((((c + 1)->directory) + 5)->email, "ritesh.kumar@email.com");
        strcpy((((c + 1)->directory) + 5)->number, "8239084216");
    }

    {
        // Entering data for 3rd customer.
        strcpy((c + 2)->name, "Suman Sahoo");
        strcpy((c + 2)->email, "suman");
        strcpy((c + 2)->password, "123");
        (c + 2)->n = 7;
        (c + 2)->directory = (struct contact *)malloc(((c + 2)->n) * sizeof(struct contact));

        strcpy((((c + 2)->directory) + 0)->name, "Pratik Prakhar");
        strcpy((((c + 2)->directory) + 0)->email, "pratik.prakhar@email.com");
        strcpy((((c + 2)->directory) + 0)->number, "8249539257");

        strcpy((((c + 2)->directory) + 1)->name, "Yash Raj Singh");
        strcpy((((c + 2)->directory) + 1)->email, "yashraj.singh@email.com");
        strcpy((((c + 2)->directory) + 1)->number, "9693221160");

        strcpy((((c + 2)->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy((((c + 2)->directory) + 2)->email, "dibya.ranjan@email.com");
        strcpy((((c + 2)->directory) + 2)->number, "9348174331");

        strcpy((((c + 2)->directory) + 3)->name, "Shubhank Nagar");
        strcpy((((c + 2)->directory) + 3)->email, "shubhank.nagar@email.com");
        strcpy((((c + 2)->directory) + 3)->number, "9001332089");

        strcpy((((c + 2)->directory) + 4)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 4)->email, "ritesh.kumar@email.com");
        strcpy((((c + 2)->directory) + 4)->number, "8239084216");

        strcpy((((c + 2)->directory) + 5)->name, "randua the randi sndflknsdflnsdlkfn");
        strcpy((((c + 2)->directory) + 5)->email, "ritesh.kumar@email.com");
        strcpy((((c + 2)->directory) + 5)->number, "8239084216");

        strcpy((((c + 2)->directory) + 6)->name, "bsdk");
        strcpy((((c + 2)->directory) + 6)->email, "ritesh.kumar@email.com");
        strcpy((((c + 2)->directory) + 6)->number, "8239084216");
    }
}

void titleScreen()
{

    // This function presents the first screen before the audience.
    // It mentions the project name and developers name.

    system("clear");
    system("cls");

    gotoxy(71, 5);
    printf("__________________________");
    gotoxy(71, 6);
    printf("__________________________");

    gotoxy(72, 8);
    printf("***Project Phone Book***");

    gotoxy(71, 9);
    printf("__________________________");
    gotoxy(71, 10);
    printf("__________________________");

    gotoxy(70, 25);
    printf("BUILT WITH PASSION BY GROUP-11:");

    gotoxy(70, 28);
    printf("1. Baibhav Kumar;");
    gotoxy(90, 28);
    printf("ID: B421016.");

    gotoxy(70, 30);
    printf("2. Hemant Sah;");
    gotoxy(90, 30);
    printf("ID: B421025.");

    gotoxy(70, 32);
    printf("3. Suman Sahoo;");
    gotoxy(90, 32);
    printf("ID: B421056.");

    gotoxy(10, 39);
    printf("Loading");
    printf(".");
    printf(".");
    printf(".");
    getch();
}

void screenHeading()
{

    // Thus function prints a heading on every screen.
    // Whenever you need to cls the screen, call this function.

    system("clear");
    system("cls");

    gotoxy(71, 1);
    printf("__________________________");

    gotoxy(72, 3);
    printf("***Project Phone Book***");

    gotoxy(71, 4);
    printf("__________________________");

    gotoxy(0, 10);
}

void gotoxy(int x, int y)
{
    /*
    The gotoxy() function places the cursor at the desired location on the screen.
    SetConsoleCursorPosition is present in windows.h header file.
    */
    printf("%c[%d;%df", 0x1B, y, x);
}

int chooseBetweenTwo(int a, int b, int c)
{

    int ch = getch() - 48;

    if (ch == -35 || ch == -38 || ch == 79)
    {
        chooseBetweenTwo(a, b, c);
    }
    else if (ch == a || ch == b || ch == c)
    {
        return ch;
    }
    else
    {
        printf("\n\n\n");
        for (int i = 0; i < 69; i++)
            printf(" ");
        printf("OOPS! Wrong Input!  %d\n\n", ch);
        // for(int i=0; i<60; i++)
        //     printf(" ");
        // printf("Press any key to enter the input again...");
        // getch();
        chooseBetweenTwo(a, b, c);
    }
}

// NOTE
// remove system(cls) or system(clear) expression in the title function in your system while presentation

// functionality to check number and name before adding
