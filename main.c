#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact
{
    char name[50];
    char gmail[41];
    char mobile[11];
};
typedef struct customers
{
    char name[50];
    char gmail[41];
    char password[13];
    int n;
    struct contact *directory;
}customer;

void gotoxy(int x, int y);
void titleScreen();
void defaultInput(struct customers *c);
struct customers *loginAuthentication(struct customers c[]);
void mainMenu();
void showContacts();
void searchContact();
void addContact();

int main()
{
    customer c[3];
    defaultInput(c);
    /*
    Demo of how to access the input.

    printf("%s  ", (c->directory)->name); Accessing the name of first contact of first customer.
    printf("%s  ", (c->directory)->mobile); Accessing the mobile of first contact of first customer.
    printf("%s  ", (c->directory)->gmail); Accessing the gmail of first contact of first customer.
    printf("\n\n");

    printf("%s  ", ((c->directory)+1)->name); Accessing the name of second contact of first customer.
    printf("%s  ", ((c->directory)+1)->mobile);
    printf("%s  ", ((c->directory)+1)->gmail);
    printf("\n\n");

    printf("%s  ", ((c+1)->directory)->name); Accessing the name of first contact of second customer.
    printf("%s  ", ((c+1)->directory)->mobile);
    printf("%s  ", ((c+1)->directory)->gmail);
    printf("\n\n");

    */

    titleScreen();

    loginAuthentication(c);

    mainMenu();

}

void mainMenu(){

    printf("\n\nentered main menu");

    // implement logic to call 
    // 1 showContacts()
    // 2 searchContact()
    // 3 addContact()

}

void showContacts(){

}

void searchContact(){

}

void addContact(){

}

struct customers *loginAuthentication(struct customers c[])
{
    printf("Printing from login authentication function.");
}

void defaultInput(struct customers *c)
{

    /*
    This function enters the default input into the program.
    */

    {
        // Entering data for 1st customer.
        strcpy(c->name, "Baibhav Kumar");
        strcpy(c->gmail, "baibhav.kumar@gmail.com");
        strcpy(c->password, "Baibhav@123");
        c->n = 5;
        c->directory = (struct contact *)malloc((c->n) * sizeof(struct contact));

        strcpy(((c->directory) + 0)->name, "Pratik Prakhar");
        strcpy(((c->directory) + 0)->gmail, "pratik.prakhar@gmail.com");
        strcpy(((c->directory) + 0)->mobile, "8249539257");

        strcpy(((c->directory) + 1)->name, "Yash Raj Singh");
        strcpy(((c->directory) + 1)->gmail, "yashraj.singh@gmail.com");
        strcpy(((c->directory) + 1)->mobile, "9693221160");

        strcpy(((c->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy(((c->directory) + 2)->gmail, "dibya.ranjan@gmail.com");
        strcpy(((c->directory) + 2)->mobile, "9348174331");

        strcpy(((c->directory) + 3)->name, "Shubhank Nagar");
        strcpy(((c->directory) + 3)->gmail, "shubhank.nagar@gmail.com");
        strcpy(((c->directory) + 3)->mobile, "9001332089");

        strcpy(((c->directory) + 4)->name, "Ritesh Kumar");
        strcpy(((c->directory) + 4)->gmail, "ritesh.kumar@gmail.com");
        strcpy(((c->directory) + 4)->mobile, "8239084216");
    }

    {
        // Entering data for 2nd customer.
        strcpy((c + 1)->name, "Hemant Sah");
        strcpy((c + 1)->gmail, "hemant.sah@gmail.com");
        strcpy((c + 1)->password, "Hemant@123");
        (c + 1)->n = 6;
        (c + 1)->directory = (struct contact *)malloc(((c + 1)->n) * sizeof(struct contact));

        strcpy((((c + 1)->directory) + 0)->name, "Pratik Prakhar");
        strcpy((((c + 1)->directory) + 0)->gmail, "pratik.prakhar@gmail.com");
        strcpy((((c + 1)->directory) + 0)->mobile, "8249539257");

        strcpy((((c + 1)->directory) + 1)->name, "Yash Raj Singh");
        strcpy((((c + 1)->directory) + 1)->gmail, "yashraj.singh@gmail.com");
        strcpy((((c + 1)->directory) + 1)->mobile, "9693221160");

        strcpy((((c + 1)->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy((((c + 1)->directory) + 2)->gmail, "dibya.ranjan@gmail.com");
        strcpy((((c + 1)->directory) + 2)->mobile, "9348174331");

        strcpy((((c + 1)->directory) + 3)->name, "Shubhank Nagar");
        strcpy((((c + 1)->directory) + 3)->gmail, "shubhank.nagar@gmail.com");
        strcpy((((c + 1)->directory) + 3)->mobile, "9001332089");

        strcpy((((c + 1)->directory) + 4)->name, "Ritesh Kumar");
        strcpy((((c + 1)->directory) + 4)->gmail, "ritesh.kumar@gmail.com");
        strcpy((((c + 1)->directory) + 4)->mobile, "8239084216");

        strcpy((((c + 1)->directory) + 5)->name, "Ritesh Kumar");
        strcpy((((c + 1)->directory) + 5)->gmail, "ritesh.kumar@gmail.com");
        strcpy((((c + 1)->directory) + 5)->mobile, "8239084216");
    }

    {
        // Entering data for 3rd customer.
        strcpy((c + 2)->name, "Suman Sahoo");
        strcpy((c + 2)->gmail, "suman.sahoo@gmail.com");
        strcpy((c + 2)->password, "Suman@123");
        (c + 2)->n = 7;
        (c + 2)->directory = (struct contact *)malloc(((c + 2)->n) * sizeof(struct contact));

        strcpy((((c + 2)->directory) + 0)->name, "Pratik Prakhar");
        strcpy((((c + 2)->directory) + 0)->gmail, "pratik.prakhar@gmail.com");
        strcpy((((c + 2)->directory) + 0)->mobile, "8249539257");

        strcpy((((c + 2)->directory) + 1)->name, "Yash Raj Singh");
        strcpy((((c + 2)->directory) + 1)->gmail, "yashraj.singh@gmail.com");
        strcpy((((c + 2)->directory) + 1)->mobile, "9693221160");

        strcpy((((c + 2)->directory) + 2)->name, "Dibya Ranjan Sahu");
        strcpy((((c + 2)->directory) + 2)->gmail, "dibya.ranjan@gmail.com");
        strcpy((((c + 2)->directory) + 2)->mobile, "9348174331");

        strcpy((((c + 2)->directory) + 3)->name, "Shubhank Nagar");
        strcpy((((c + 2)->directory) + 3)->gmail, "shubhank.nagar@gmail.com");
        strcpy((((c + 2)->directory) + 3)->mobile, "9001332089");

        strcpy((((c + 2)->directory) + 4)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 4)->gmail, "ritesh.kumar@gmail.com");
        strcpy((((c + 2)->directory) + 4)->mobile, "8239084216");

        strcpy((((c + 2)->directory) + 5)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 5)->gmail, "ritesh.kumar@gmail.com");
        strcpy((((c + 2)->directory) + 5)->mobile, "8239084216");

        strcpy((((c + 2)->directory) + 6)->name, "Ritesh Kumar");
        strcpy((((c + 2)->directory) + 6)->gmail, "ritesh.kumar@gmail.com");
        strcpy((((c + 2)->directory) + 6)->mobile, "8239084216");
    }
}

void titleScreen()
{
    /*
    This function presents the first screen before the audience. It mentions the project name and developers name.
    */
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
}

void gotoxy(int x, int y)
{
    /*
    The gotoxy() function places the cursor at the desired location on the screen.
    SetConsoleCursorPosition is present in windows.h header file.
    */
    printf("%c[%d;%df", 0x1B, y, x);
}
