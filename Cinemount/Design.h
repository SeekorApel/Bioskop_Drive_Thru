void fullscreen();
void gotoxy(int x,int y);

int x,y,i;

void PrintFile(char file[], int x, int y);

void gotoxy(int x,int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X=x;
	dwCursorPosition.Y=y;
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void DesainLogin()
{
	system ("color 8e");
	PrintFile("Source/Welcome.txt",54,6);
	PrintFile("Source/Cam.txt",11,11);
	//PrintFile("Source/SUS.txt",54,9);

	/* Kotak */
	for(x=2;x<=169;x++){
		gotoxy(x,1);printf("%c",219);
		gotoxy(x,43);printf("%c",219);
	}
	for(y=1;y<=42;y++){
		gotoxy(2,y);printf("%c",219);
		gotoxy(169,y);printf("%c",219);
	}

	/* Desain Menu Login */
	for(y=28;y<=38;y++){
		gotoxy(60,y);printf("%c",176);
		gotoxy(61,y);printf("%c",176);
		gotoxy(62,y);printf("%c",176);
		gotoxy(63,y);printf("%c",176);
		gotoxy(64,y);printf("%c",176);
		gotoxy(111,y);printf("%c",176);
		gotoxy(112,y);printf("%c",176);
		gotoxy(113,y);printf("%c",176);
		gotoxy(114,y);printf("%c",176);
		gotoxy(115,y);printf("%c",176);
	}

	/* Desain Input Login */
	for(x=64; x<=114; x++)
	{
		gotoxy(x,28); printf("%c",176);
		gotoxy(x,38); printf("%c",176);
	}

/* Design username*/
	gotoxy(73,31); printf(" USERNAME : ");
	gotoxy(71,30); printf("\xc9"); //  atas kiri
	gotoxy(104,30); printf("\xbb"); //atas kanan
	for (x=72; x<=103; x++)
	{
		gotoxy(x,30); printf("%c",205);
		gotoxy(x,32); printf("%c",205);
	}
	gotoxy(104,32); printf("\xbc"); // bawah kanan
	gotoxy(71,32); printf("\xc8"); // bawah kiri
	for (y=31; y<=31; y++)
	{
		gotoxy(71,y); printf("%c",186);
		gotoxy(104,y); printf("%c",186);
	}

	/* Design password*/
	gotoxy(73,35); printf(" PASSWORD : ");
	gotoxy(71,34); printf("\xc9");
	gotoxy(104,34); printf("\xbb");
	for (x=72; x<=103; x++)
	{
		gotoxy(x,34); printf("%c",205);
		gotoxy(x,36); printf("%c",205);
	}
	gotoxy(104,36); printf("\xbc");
	gotoxy(71,36); printf("\xc8");
	for (y=35; y<=35; y++)
	{
		gotoxy(71,y); printf("%c",186);
		gotoxy(104,y); printf("%c",186);
	}
}

void Tanggal()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *wday[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

    gotoxy(144, 7); printf("%s,", wday[tm.tm_wday]);
	gotoxy(144, 8);	printf("%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
}

void PrintFile(char file[], int x, int y)
{
	FILE *Text;
	char Data[100];
	if((Text=fopen(file, "r")) == NULL)
	{
		system("cls");
	}
	while(fgets(Data, 100, Text))
	{
		gotoxy(x, y);
		printf("%s", Data);
		y++;
	}
	fclose(Text);
}

void DesainAdmin()
{
	Tanggal();
	system("color 8e");
	PrintFile("Source/RDF.txt",55,4);
	//Tanggal1();
	/* Horizontal */
	for(x=7; x<=169; x++)
	{
		gotoxy(x,2); printf("%c",219);
		gotoxy(x,12); printf("%c",219);
		gotoxy(x,46); printf("%c",219);
	}

	/* vertical */
	for(y=3; y<=45; y++)
	{
		gotoxy(7,y); printf("%c",219);
		gotoxy(169,y); printf("%c",219);
	}

	/* vertical Menu */
	for(y=13; y<=45; y++)
	{
		gotoxy(35,y); printf("%c",219);
		gotoxy(132,y); printf("%c",219);
		gotoxy(34,y); printf("%c",176);
		gotoxy(33,y); printf("%c",176);
		gotoxy(9,y); printf("%c",176);
		gotoxy(8,y); printf("%c",176);
	}

	/* Horizontal Menu */
	for(x=10; x<=32; x++)
	{
		gotoxy(x,20); printf("%c",254);
		gotoxy(x,23); printf("%c",205);
		gotoxy(x,36); printf("%c",205);
		gotoxy(x,38); printf("%c",254);
		gotoxy(x,13); printf("%c",176);
		gotoxy(x,14); printf("%c",176);
		gotoxy(x,15); printf("%c",176);
		gotoxy(x,16); printf("%c",176);
		gotoxy(x,17); printf("%c",176);
		gotoxy(x,18); printf("%c",176);
		gotoxy(x,19); printf("%c",176);
		gotoxy(x,39); printf("%c",176);
		gotoxy(x,40); printf("%c",176);
		gotoxy(x,41); printf("%c",176);
		gotoxy(x,42); printf("%c",176);
		gotoxy(x,43); printf("%c",176);
		gotoxy(x,44); printf("%c",176);
		gotoxy(x,45); printf("%c",176);
	}

	/* vertical menu */
	for(y=21; y<=37; y++)
	{
		gotoxy(12,y); printf("%c",186);
		gotoxy(30,y); printf("%c",186);
		gotoxy(31,y); printf("%c",176);
		gotoxy(32,y); printf("%c",176);
		gotoxy(11,y); printf("%c",176);
		gotoxy(10,y); printf("%c",176);
	}
}

void CleanKiri()
{
	x=13; y=24;
	gotoxy(13,22); printf("                 ");
	gotoxy(13,21); printf("                 ");
	for (i=1; i<=12; i++)
	{
		gotoxy(x,y); printf("                 ");
		y++;
	}
	gotoxy(13,37); printf("                 ");
}

void CleanTengah()
{
	x=36,y=13;

	for (i=1; i<=32; i++)
	{
		gotoxy(x,y); printf("                                                                                                ");
		y++;
	}
}

void CleanKanan()
{
	x=133; y=15;
	for (i=1; i<=30; i++)
	{
		gotoxy(x,y); printf("                                   ");
		y++;
	}
}

void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

void DesainUbahData()
{
	system("color 8e");
	for (x=56; x<=111; x++)
	{
		gotoxy(x,18); printf("%c",219);
		gotoxy(x,23); printf("%c",205);
		gotoxy(x,38); printf("%c",219);
	}
		for (y=19; y<=37; y++)
	{
		gotoxy(56,y); printf("%c",186);
		gotoxy(111,y); printf("%c",186);
	}
}
