#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

#include "MasterPegawai.h"

char usn[25];
char psw[25];

FILE *usr;

int main()
{
	system("cls");
    printf("--- LOGIN PAGE ---\n\n");
    printf("username : ");
    fflush(stdin);
    scanf("%s", &usn);
    printf("password : ");
    fflush(stdin);
    takePassword(psw);

    usr = fopen("User.dat", "rb");
    fread(&U,sizeof(U),1,usr);

    while(!feof(usr)){
        if ((strcmp(U.Username,usn)==0) && (strcmp(U.Password,psw))==0){
            switch(U.Role){
                case 1 :
                    MenuKasir(); break;
                case 2 :
                    MenuAdmin(); break;
                case 3 :
                    MenuManager(); break;
            }
        }
        fread(&U,sizeof(U),1,usr);
    }
}

void MenuKasir()
{
    system("cls");
    printf("WELCOME KASIR");
    getch();
}

void MenuAdmin()
{
    int choose;

    system("cls");
    MessageBoxA(NULL,"Welcome To Menu Admin!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
    printf("MENU ADMIN\n\n");

    printf("[1] Pegawai\n");
    printf("[2] Jadwal Event\n");
    printf("[3] Film\n");
    printf("[4] Produser\n");
    printf("[5] Log Out\n");

    printf("Pilih : ");
    scanf("%d", &choose);

    switch(choose){
        case 1 :
            MenuMasterPegawai();
            break;
        /*case 2 :
            MenuMasterJadwal();
            break;
        case 3 :
            MenuMasterFilm();
            break;
        case 4 :
            MenuMasterProduser();
            break;*/
        case 5 :
            main();
            break;
    }
}

void MenuManager()
{
    printf("WELCOME MANAGER");
    getch();
}
