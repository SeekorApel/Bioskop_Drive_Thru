FILE *usr;

void MenuKasir();
void MenuAdmin();
void MenuManager();

void Login()
{
	int ROLES;
	DesainLogin();

    //username
    fflush(stdin);
    gotoxy(86,31);	scanf("%s", &usn);
    if(strcmp("0",usn) == 0)
	{
		exit(0);
	}
    //password
    fflush(stdin);
    gotoxy(86,35);	takePassword(psw);

    usr = fopen("dat/User.dat", "rb+");
    fread(&U,sizeof(U),1,usr);

    while(!feof(usr)){
        if ((strcmp(U.Username,usn)==0) && (strcmp(U.Password,psw)==0)){
            switch(U.Role){
                case 1 :
                	MessageBoxA(NULL,"Welcome To Kasir!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                    ROLES = 1;
                    system("cls");
                    gotoxy(15,8);	puts(U.Nama);
                    MenuKasir();
					break;
                case 2 :
                	ROLES = 2;
                	system("cls");
                	gotoxy(15,8);	puts(U.Nama);
                	MessageBoxA(NULL,"Welcome To Menu Admin!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                	MenuAdmin();
                    break;
                case 3 :
                	ROLES = 3;
                	system("cls");
                	gotoxy(15,8);	puts(U.Nama);
                	MessageBoxA(NULL,"Welcome Manager!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                	MenuManager();
                    break;
            }
        }
        fread(&U,sizeof(U),1,usr);
    }

    if (ROLES != 1 || ROLES != 2 || ROLES != 3){
        MessageBoxA(NULL,"Username Atau Password Tidak Sesuai!","NOTIFICATION",MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
		gotoxy(86,31); printf("                      ");
		gotoxy(86,35); printf("                      ");
		Login();
    }
}

void MenuKasir()
{
    // Declaration
    int choose;
    CleanKiri();

    DesainAdmin();
    gotoxy(16,22);	printf("MENU KASIR");
    gotoxy(14,25);	printf("[1] Makanan");
    gotoxy(14,26);	printf("[2] Beli Makan");
    gotoxy(14,27);	printf("[3] Beli Tiket");
    gotoxy(14,28);	printf("[4] Log Out");
    gotoxy(22,30);	printf(" ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &choose);

    switch(choose){
        case 1 :
        	CleanKiri();
           	MenuMakanan();
            break;
        case 2 :
        	CleanKiri();
            TransaksiMakanan();
            break;
        case 3 :
        	CleanKiri();
            TTiket();
            break;
        case 4 :
        	MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        	system("cls");
            Login();
        default : MenuKasir(); break;
    }
}

void MenuAdmin()
{
    int choose;

    DesainAdmin();

    gotoxy(16,22);	printf("MENU ADMIN");

    gotoxy(14,25);	printf("[1] Pegawai");
    gotoxy(14,26);	printf("[2] Jadwal Event");
    gotoxy(14,27);	printf("[3] Film");
    gotoxy(14,28);	printf("[4] Produser");
    gotoxy(14,29);	printf("[5] Beli Film");
    gotoxy(14,30);	printf("[6] Log Out");

	gotoxy(22,31);	printf(" ");
    gotoxy(14,31);	printf("Pilih : ");
    gotoxy(22,31);	scanf("%d", &choose);

    switch(choose){
        case 1 :
        	CleanKiri();
            MenuMasterPegawai();
            break;
        case 2 :
        	CleanKiri();
            MenuJadwal();
            break;
        case 3 :
        	CleanKiri();
            MenuFilm();
            break;
        case 4 :
        	CleanKiri();
            MenuProduser();
            break;
        case 5 :
        	CleanKiri();
            SewaFilm();
            break;
        case 6 :
        	MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        	system("cls");
            Login();
            break;
        default : MenuAdmin(); break;
    }
}

void MenuManager()
{
	int choose;
	DesainAdmin();

    gotoxy(14,22);	printf("WELCOME MANAGER");
    gotoxy(14,25);	printf("[1] Pegawai");
    gotoxy(14,26);	printf("[2] Pemasukan");
    gotoxy(14,27);	printf("[3] Pengeluaran");
    gotoxy(14,28);	printf("[4] Log Out");

    gotoxy(22,29);	printf(" ");
    gotoxy(14,29);	printf("Pilih : ");
    gotoxy(22,29);	scanf("%d", &choose);

    switch(choose){
        case 1 :
            Lihatdata();
            getch();
            CleanKiri();
            CleanTengah();
            MenuManager();
            break;
        case 2 :
            Pemasukan();
            break;
        case 3 :
            LaporanFilm();
            getch();
        	CleanKiri();
            CleanTengah();
            CleanKanan();
            MenuManager();
            break;
        case 4 :
        	MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        	system("cls");
            Login();
            break;
        default : MenuManager(); break;
    }
}

void Pemasukan()
{
    int choose;

    CleanKiri();
    gotoxy(14,25); printf("[1] Makanan\n");
    gotoxy(14,26); printf("[2] Tiket\n");
    gotoxy(14,27); printf("[0] Keluar\n");
    gotoxy(14,29); printf("Pilih : ");
    scanf("%d", &choose);

    switch(choose){
        case 1 :
            LaporanMakanan();
            getch();
            CleanTengah();
            CleanKiri();
            CleanKanan();
            MenuManager();
            break;
        case 2 :
            LaporanTiket();
            getch();
            CleanTengah();
            CleanKiri();
            CleanKanan();
            MenuManager();
            break;
        case 0 :
            CleanKiri();
            CleanTengah();
            CleanKanan();
            MenuManager();
            break;
        default : Pemasukan(); break;
    }
}

void takePassword(char pwds[50])
{
    int is;
    char chs;
    while(1)
    {
        chs = getch();
        if(chs == ENTER || chs == TAB)
        {
            pwds[is]='\0';
            break;
        }
        else if(chs == BCKSPC)
        {
            if(is > 0)
            {
                is--;
                printf("\b \b");
            }
        }
        else
        {
            pwds[is++] = chs;
            printf("* \b");
        }
    }
}
