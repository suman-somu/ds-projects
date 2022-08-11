#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>
#include <stdbool.h>
// #include <conio.h>
#include <termios.h>
#include <unistd.h>

// return 0-9 as 48-57
int getch(void)
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
void defaultInput(customer *c, int add);
int chooseBetweenTwo(int a, int b);

customer *loginAuthentication(customer c[]);
customer *checkEmail(customer *c);
bool checkPassword(customer *c);

void mainMenu();

void showContacts(customer *c);

void searchContact(customer *c);

void addContact(customer *c);

void editContact(customer *c, int choose, int fn);

int chooseBetweenTwo(int a, int b);

void contactDetails(customer *c, int choose, int fn);

int main()
{
    customer c[3];
    defaultInput(c, 0);

    titleScreen();

    // customer *current = loginAuthentication(c);

    // mainMenu(c);

}

void mainMenu(customer *c)
{

    system("cls");
    system("clear");
    printf("\n\nentered main menu\n\n");

    printf("enter a number from below\n");
    printf("1 Show Contacts\n2 search contacts\n3 add contacts\n0 exit\n");

    int ch = getch() - 48;

    if (ch == 1)
        showContacts(c);
    else if (ch == 2)
        searchContact(c);
    else if (ch == 3)
        addContact(c);
    else if (ch == 0)
    {
        system("cls");
        system("clear");
        gotoxy(80, 25);
        printf("THANK YOU FOR USING OUR SYSTEM.");
        gotoxy(83, 28);
        printf("made with love from grp 2\n\n\n");
        gotoxy(0, 50);
        exit(0);
    }
    else
    {
        printf("wrong no. try again");
        getch();
        mainMenu(c);
    }
}

void showContacts(customer *c)
{

    system("cls");
    system("clear");
    printf("\nS.No \t CONTACT LIST \t\t Phone No. :-\n\n");
    int numberOfContacts = c->n;
    for (int i = 0; i < numberOfContacts; i++)
    {
        printf("%d\t %s \t %s \n", i + 1, ((c->directory) + i)->name,((c->directory)+i)->number);
    }

    printf("\n\n1 choose a contact \t\t0 exit to menu\n");
    int choose = chooseBetweenTwo(0, 1);
    if (choose == 1)
    {
        printf("\nchoose a contact to show details :");
        int choose;
        scanf("%d", &choose);
        contactDetails(c, choose,1);
    }
    else
        mainMenu(c);
}

void contactDetails(customer *c, int choose, int fn)
{

    if (choose <= c->n)
    {
        system("cls");
        system("clear");
        printf("\nCONTACT DETAILS :- \n\n");
        printf("Name - %s\nNumber - %s\nEmail - %s\n\n\n", ((c->directory) + (choose - 1))->name, ((c->directory) + (choose - 1))->number, ((c->directory) + (choose - 1))->email);
        printf("1 edit contact\t0 return\n\n");
        int ch = chooseBetweenTwo(0, 1);
        if (ch == 1)
            editContact(c, choose-1,fn);
        else{
            if(fn==1){
                showContacts(c);
            }
            else if(fn==2){
                searchContact(c);
            }
        }
            
    }
    else
    {
        printf("\n\nthere is no contact of that number.");
        printf("\ntry again once more\n\n");
        sleep(2);
        showContacts(c);
    }
}

void editContact(customer *c, int choose, int fn)
{

    char name[50], number[11], email[41];

    printf("\t\t\t\t\t\n\nEdit Contact");
    printf("\n 1.Name\n 2.Number\n 3.Email\n 4.Cancel\n\n");
    int ch = getch() - 48;

    if (ch == 1)
    {
        printf("\nEnter Name : ");
        getchar();
        gets(name);
        strcpy(((c->directory) + choose)->name, name);
        printf("Your name has been edited\n");
    }
    else if (ch == 2)
    {
        printf("\nEnter Number : ");
        getchar();
        gets(number);
        strcpy(((c->directory) + choose)->number, number);
        printf("Your number has been edited\n");
    }
    else if (ch == 3)
    {
        printf("\nEnter Email : ");
        getchar();
        gets(email);
        strcpy(((c->directory) + choose)->email, email);
        printf("Your email has been edited\n");
    }
    else if (ch == 4)
    {
        system("cls");
        system("clear")
        printf("\nYour contact has not been edited\n");
        contactDetails(c,choose,fn);
    }
    printf("\nPress any Key to go back to main menu");
    getch();
    mainMenu(c);
}

void searchContact(customer *c)
{
    // search by name or by number

    system("cls");
    system("clear");
    printf("SEARCH CONTACTS:\n\n\n");
    printf("1\tby name\n2\tby number\n");
    printf("\n\n0\treturn to menu");
    int ch = getch() - 48;

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
    case 0:
        mainMenu(c);
        break;
    default:
        printf("\n\nwrong choice");
        getch();
        searchContact(c);
        break;
    }
}

void addContact(customer *c)
{
    screenHeading();

    char name[20], number[11], email[30];
    printf("\t\t\t\t\tAdd Contact");
    printf("\nName : ");
    gets(name);
    printf("\nNumber : ");
    gets(number);
    printf("\nEmail : ");
    gets(email);

    strcpy(((c->directory) + 4 + 1)->name, name);
    strcpy(((c->directory) + 4 + 1)->email, email);
    strcpy(((c->directory) + 4 + 1)->number, number);

    mainMenu(c);
}

void searchByName(customer *c)
{

    system("cls");
    system("clear");
    printf("SEARCH CONTACT :\n\n\n");

    printf("enter the name:");
    char name[50];
    // scanf("%s",&name);
    gets(name);

    int d=0,i=0;
    for(i=0;i< c->n;i++){
        if(strcmp(((c->directory)+i)->name,name)==0){
            d++;
            break;
        }
    }

    if(d==1){
        printf("\n\nContact Found\n\n");
        printf(" 1\t%s\n\n",((c->directory)+i)->name);
        printf("\n\n1 select contact\t\t0 go back\n\n");
        int ch=getch()-48;
        if(ch<0){
            ch = getch() -48;
        }
        if(ch ==1){
            contactDetails(c,i+1,2);
        }
        else{
            mainMenu(c);
        }
    }
    else {
        printf("not found");
        getch();
    }
}

void searchByNumber(customer *c){
    system("cls");
    system("clear");
    printf("SEARCH CONTACT :\n\n\n");

    printf("enter the number:");
    char number[11];
    // scanf("%s",&name);
    gets(number);

    int d=0,i=0;
    for(i=0;i< c->n;i++){
        if(strcmp(((c->directory)+i)->number,number)==0){
            d++;
            break;
        }
    }

    if(d==1){
        printf("\n\ncontact found\n\n");
        printf(" 1\t%s\n\n",((c->directory)+i)->name);
        printf("1 select contact\t\t0 go back\n\n");
        int ch;
        scanf("%d",&ch);
        if(ch ==1){
            contactDetails(c,i+1,2);
        }
        else{
            mainMenu(c);
        }
    }
    else {
        printf("not found");
        getch();
    }
}

customer *loginAuthentication(customer c[])
{
    screenHeading();
    printf("Login authentication...\n\n");
    // sleep(2);
    printf("\n\nPress any key to login...");

    customer *tempCustomer = checkEmail(c);

    if (checkPassword(tempCustomer))
        return (tempCustomer);
}

customer *checkEmail(customer *c)
{

    screenHeading();

    printf("E-Mail Authentication:-");

    char tempEmail[41];

    printf("\n\nE-Mail ID: ");
    scanf("%s", tempEmail);

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
    do
    {
        tempPassword[p] = getch();
        if (tempPassword[p] != '\r')
        {
            printf("*");
        }
        p++;
    } while (tempPassword[p - 1] != '\r');
    tempPassword[p - 1] = '\0';

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

void defaultInput(customer *c, int add)
{

    /*
    This function enters the default input into the program.
    */

    {
        // Entering data for 1st customer.
        strcpy(c->name, "Baibhav Kumar");
        strcpy(c->email, "baibhav.kumar@email.com");
        strcpy(c->password, "Baibhav@123");
        c->n = 5 + add;
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
        strcpy((c + 2)->email, "suman@gmail.com");
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

    system("cls");
    system("clear");

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
    printf("Built with passion by Group-11:");

    gotoxy(72, 28);
    printf("1. Baibhav Kumar;");
    gotoxy(90, 28);
    printf("ID: B421016.");

    gotoxy(72, 30);
    printf("2. Hemant Sah;");
    gotoxy(90, 30);
    printf("ID: B421025.");

    gotoxy(72, 32);
    printf("3. Suman Sahoo;");
    gotoxy(90, 32);
    printf("ID: B421056.");

    gotoxy(10, 39);
    printf("Loading");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    // getch();
}

void screenHeading()
{

    // Thus function prints a heading on every screen.
    // Whenever you need to cls the screen, call this function.

    system("cls");
    system("clear");

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

int chooseBetweenTwo(int a, int b)
{

    int ch = getch() - 48;
    if (ch == a || ch == b)
        return ch;
    else
    {
        if (ch < 0)
        {
            chooseBetweenTwo(a, b);
        }
        else
        {
            printf("wrong input try once more\n");
            chooseBetweenTwo(a, b);
        }
    }
}



// NOTE
// remove system(cls) or system(clear) expression in the title function in your system while presentation

// functionality to check number and name before adding
