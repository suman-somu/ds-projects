#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


void gotoxy(int x, int y);

void Title_Screen();

int main(){
    Title_Screen();
}

void Title_Screen(){
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

}

void gotoxy(int x, int y)
{
    /*
    The gotoxy() function places the cursor at the desired location on the screen.
    SetConsoleCursorPosition is present in windows.h header file.
    */
    COORD c;
    c.X = x;
    c.Y = y;
 
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}