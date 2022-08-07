#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
// #include <termios.h>
#include <unistd.h>

//return 0-9 as 48-57 
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
}contact;
typedef struct customers
{
    char name[50];
    char email[41];
    char password[13];
    int n;
    struct contact *directory;
}customer;

void gotoxy(int x, int y);
void titleScreen();
void defaultInput(customer *c,int add);
customer *loginAuthentication(customer c[]);
void mainMenu();
void showContacts(customer *c);
void searchContact(customer *c);
void addContact(customer *c);
void editContact(customer *c,int choose);

int main()
{
    customer c[3];
    defaultInput(c,0);
    /*
    Demo of how to access the input.

    printf("%s  ", (c->directory)->name); Accessing the name of first contact of first customer.
    printf("%s  ", (c->directory)->number); Accessing the number of first contact of first customer.
    printf("%s  ", (c->directory)->email); Accessing the email of first contact of first customer.
    printf("\n\n");

    printf("%s  ", ((c->directory)+1)->name); Accessing the name of second contact of first customer.
    printf("%s  ", ((c->directory)+1)->number);
    printf("%s  ", ((c->directory)+1)->email);
    printf("\n\n");

    printf("%s  ", ((c+1)->directory)->name); Accessing the name of first contact of second customer.
    printf("%s  ", ((c+1)->directory)->number);
    printf("%s  ", ((c+1)->directory)->email);
    printf("\n\n");

    */

    titleScreen();

    // customer *c = loginAuthentication(c);

    mainMenu(c);

}

void mainMenu(customer *c){


    system("clear");
    system("cls");
    printf("\n\nentered main menu\n\n");
    
    // implement logic to call 
    // 1 showContacts()
    // 2 searchContact()
    // 3 addContact()

    printf("enter a number from below\n");
    printf("1 Show Contacts\n2 search contacts\n3 add contacts\n0 exit\n");
    int ch = getch() - 48;

    if(ch == 1)
        showContacts(c);
    else if ( ch ==2)
        searchContact(c);
    else if (ch == 3)
        addContact(c);
    else if ( ch ==  0){
        system("cls");
        system("clear");
        gotoxy(80,25);
        printf("THANK YOU FOR USING OUR SYSTEM.");
        gotoxy(83,28);
        printf("made with love from grp 2\n\n\n");
        gotoxy(0,50);
        exit(0);
    }
    else {
        printf("wrong no. try again");
        getch();
        mainMenu(c);
    }

}

void showContacts(customer *c){

    system("clear");
    system("cls");
    printf("\nS.No \t CONTACT LIST :-\n\n");
    int numberOfContacts = c->n;
    for(int i=0;i<numberOfContacts;i++){
        printf("%d\t %s \n",i+1, ((c->directory)+i)->name);
    }

    printf("\n\n1 choose a contact \t\t0 exit to menu\n");
    int choose = chooseBetweenTwo(0,1);
    if(choose == 1){
        printf("\nchoose a contact to show details :");
        int choose;
        scanf("%d",&choose);
        contactDetails(c, choose);

    }
    else 
        mainMenu(c);
}

void contactDetails( customer *c, int choose){

    system("clear");
    system("cls");
    printf("\nCONTACT DETAILS :- \n\n");
    printf("Name - %s\nNumber - %s\nEmail - %s\n\n\n",((c->directory)+(choose-1))->name,((c->directory)+(choose-1))->number,((c->directory)+(choose-1))->email);
    printf("1 edit contact\t0 return\n\n");
    int ch = chooseBetweenTwo(0,1);
    if(ch ==1)
        editContact(c,choose-1);
    else
        showContacts(c);
}

void editContact(customer *c, int choose){
   
    char name[20], number[11], email[30];

    printf("\t\t\t\t\t\n\nEdit Contact");
    printf("\n 1.Name\n 2.Number\n 3.Email\n 4.Cancel\n\n");
    int ch = getch() - 48;

    if(ch == 1){
    printf("\nEnter Name : ");
     getchar();
        gets(name);
        strcpy(((c->directory) + choose)->name,name);
        printf("Your name has been edited\n");
    }
    else if( ch ==2){
    printf("\nEnter Number : ");
        getchar();
        gets(number);
        strcpy(((c->directory) + choose)->number,number);
        printf("Your number has been edited\n");
    }
    else if(ch == 3){
    printf("\nEnter Email : ");
        getchar();
        gets(email);
        strcpy(((c->directory) + choose)->email,email);
        printf("Your email has been edited\n");
    }
    else if(ch==4){
        system("cls");
        printf("\nYour contact has not been edited\n");
     showContacts(c);
    }
    printf("\nPress any Key to go back to main menu");
    getch();
        mainMenu(c);

    }

void searchContact(customer *c){
    //search by name or by number

    system("cls");
    system("clear");
    printf("SEARCH CONTACTS:\n\n\n");
    printf("1\tby name\n2\tby number\n");
    printf("\n\n0\treturn to menu");
    int ch = getch()-48;

    switch(ch){
        case 1:
            printf("\n\nbuilding just wait \n\n");
            getch();
            searchContact(c);
        case 2:
            printf("\n\nbuilding just wait \n\n");
            getch();
            searchContact(c);
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

void addContact(customer *c){
   
     defaultInput(c,1);

    char name[20], number[11], email[30];
    printf("\t\t\t\t\tAdd Contact");
    printf("\nName : ");
    gets(name);
    printf("\nNumber : ");
    gets(number);
    printf("\nEmail : ");
    gets(email);

        strcpy(((c->directory) + 4 + 1)->name,name);
        strcpy(((c->directory) + 4 + 1)->email,email);
        strcpy(((c->directory) + 4 + 1)->number,number);

        mainMenu(c);
}

customer *loginAuthentication(customer c[])
{
    printf("\nPrinting from login authentication function.\n");
}

void defaultInput(customer *c,int add)
{

    /*
    This function enters the default input into the program.
    */

    {
        // Entering data for 1st customer.
        strcpy(c->name, "Baibhav Kumar");
        strcpy(c->email, "baibhav.kumar@email.com");
        strcpy(c->password, "Baibhav@123");
        c->n = 5+add;
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

        strcpy((((c + 1)->directory) + 5)->name, "Ritesh Kumar");
        strcpy((((c + 1)->directory) + 5)->email, "ritesh.kumar@email.com");
        strcpy((((c + 1)->directory) + 5)->number, "8239084216");
    }

    {
        // Entering data for 3rd customer.
        strcpy((c + 2)->name, "Suman Sahoo");
        strcpy((c + 2)->email, "suman.sahoo@email.com");
        strcpy((c + 2)->password, "Suman@123");
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

        strcpy((((c + 2)->directory) + 5)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 5)->email, "ritesh.kumar@email.com");
        strcpy((((c + 2)->directory) + 5)->number, "8239084216");

        strcpy((((c + 2)->directory) + 6)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 6)->email, "ritesh.kumar@email.com");
        strcpy((((c + 2)->directory) + 6)->number, "8239084216");
    }
}

void titleScreen()
{
    /*
    This function presents the first screen before the audience. It mentions the project name and developers name.
    */
    system("clear");
    system("cls");
    gotoxy(76, 16);
    printf("Project Phone Book");
    gotoxy(76, 20);
    printf("Developed by:");
    gotoxy(76, 23);
    printf("Baibhav Kumar, ID: B421016.");
    gotoxy(76, 25);
    printf("Hemant Sah, ID: B421025");
    gotoxy(76, 27);
    printf("Suman Sahoo, ID: B421056");
    gotoxy(00, 29);
    getch();
}

void gotoxy(int x, int y)
{
    /*
    The gotoxy() function places the cursor at the desired location on the screen.
    SetConsoleCursorPosition is present in windows.h header file.
    */
    printf("%c[%d;%df", 0x1B, y, x);
}

int chooseBetweenTwo(int a, int b){

    int ch = getch()-48;
    if(ch==a || ch==b)
        return ch;
    else {
        if(ch < 0){
            chooseBetweenTwo(a,b);
        }
        else {
            printf("wrong input try once more\n");
            chooseBetweenTwo(a,b);
        }
    }
}





// NOTE
// remove system(cls) or system(clear) expression in the title function in your system while presentation 