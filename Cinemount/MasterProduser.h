void MenuProduser()
{
    remove("dat/Temp Data Produser.dat");

    int choose;

    CleanKiri();
	CleanTengah();
    gotoxy(14,22);	printf("MASTER PRODUSER");

    gotoxy(14,25);	printf("[1] Tambah Data");
    gotoxy(14,26);	printf("[2] Lihat Data");
    gotoxy(14,27);	printf("[3] Ubah Data");
    gotoxy(14,28);	printf("[4] Hapus Data");
    gotoxy(14,29);	printf("[5] Keluar");

    gotoxy(22,30);	printf(" ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahPrd();
        break;
    case 2 :
        LihatPrd();
        gotoxy(22,30);	getch();
        MenuProduser();
        break;
    case 3 :
        UbahPrd();
        break;
    case 4 :
        HapusPrd();
        break;
    case 5 :
        CleanKiri();
        MenuAdmin();
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuProduser();
        break;
    }
}

void TambahPrd()
{
    int id, i=0;
    char ans;

    gotoxy(74,44);	printf("                                ");
    gotoxy(138,44);	printf("Untuk kembali, ketik '0'\n");

	LihatPrd(); /* menampilkan data produser */

    arsprd = fopen("dat/Data Produser.dat", "ab+"); /* buka file untuk ditambah dan dibaca */
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        id = prd.id;
        i++;
    }
    if(i==0){
        prd.id = 1;
    }else{
        prd.id = id+1; /* id otomatis */
    }

    gotoxy(134,17);	printf("ID Produser = PRD%d", prd.id);

    gotoxy(134,18);	printf("Nama Perusahaan = ");
    fflush(stdin);
    gets(prd.nama);
    if(!strcmp(prd.nama,"0")){
    	CleanKanan();
        MenuProduser();
    }

    gotoxy(134,19);	printf("Alamat = ");
    fflush(stdin);
    gets(prd.alamat);
    if(!strcmp(prd.alamat,"0")){
    	CleanKanan();
        MenuProduser();
    }

    gotoxy(134,20);	printf("No Telepon = ");
    fflush(stdin);
    gets(prd.telp);
    if(!strcmp(prd.telp,"0")){
    	CleanKanan();
        MenuProduser();
    }

    gotoxy(134,21);	printf("E-mail = ");
    fflush(stdin);
    gets(prd.email);
    if(!strcmp(prd.email,"0")){
    	CleanKanan();
        MenuProduser();
    }

    fwrite(&prd,sizeof(prd),1,arsprd); /* menambahkan data kedalam file */
    fclose(arsprd);

    MessageBoxA(0,"Data Berhasil di Tambahkan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(160,23); printf("   ");
        gotoxy(134,23);	printf("Tambah data lagi? [Y/N] : ");
        gotoxy(160,23); scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanKanan();
            TambahPrd();
            break;
        case 'N':
            CleanKanan();
            MenuProduser();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void LihatPrd()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--");

    arsprd = fopen("dat/Data Produser.dat", "rb"); /* buka file untuk dibaca */
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
    fclose(arsprd);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("  ID\tPerusahaan\t         Alamat\t     	    Telepon\t      E-mail");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuProduser();
    }else{
        arsprd = fopen("dat/Data Produser.dat","rb"); /* buka file untuk dibaca */
        fread(&prd,sizeof(prd),1,arsprd);
        while(!feof(arsprd)){
        	Baris++; Next++;
        	if(Baris%2==0)
			{
				gotoxy(Kolom,Baris);
			}
			else
        	{
				gotoxy(Kolom,Baris);
			}
	   		for(i=1;i<=Kolom+54;i++)
			{
				printf(" ");
			}
            gotoxy(Kolom+1,Baris);	 printf("PRD%d", prd.id);
            gotoxy(Kolom+8,Baris);   printf("%s", prd.nama);
            gotoxy(Kolom+32,Baris);  printf("%s", prd.alamat);
            gotoxy(Kolom+54,Baris);	 printf("%s", prd.telp);
            gotoxy(Kolom+70,Baris);	 printf("%s", prd.email);
            fread(&prd,sizeof(prd),1,arsprd);
        }
        fclose(arsprd);
    }
}

void UbahPrd()
{
    FILE *temp;
    int idupdate, found=0, choose, i=0;
    char ans;

    LihatPrd(); /* menampilkan data produser */

    gotoxy(75,44);	printf("  Ubah Data Produser           ");
    gotoxy(136,44);	printf("Untuk kembali, ketik '0'\n");

    arsprd = fopen("dat/Data Produser.dat","rb");
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuProduser();
    }
    fclose(arsprd);

    gotoxy(151,15);	printf("   ");
    gotoxy(134,15);	printf("ID Produser = PRD");
    scanf("%d", &idupdate);
    if(idupdate == 0){
    	CleanKanan();
        MenuProduser();
    }

    temp = fopen ("dat/Temp Data Produser.dat", "wb"); /* buka file temp untuk ditulis */
    arsprd = fopen("dat/Data Produser.dat", "rb"); /* buka file produser untuk dibaca */
    while(!found && !feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        if(prd.id == idupdate){ /* mencari id yang sesuai */
            found = 1;
        }else{
            fwrite(&prd,sizeof(prd),1,temp); /* menulis data yang bukan dicari kedalam temp */
        }
    }
    if (found){
    	CleanTengah();
    	DesainUbahData();
        gotoxy(63,28);	printf("ID Produser 	= PRD%d", prd.id);
        gotoxy(63,29);	printf("Nama Perusahaan 	= %s", prd.nama);
        gotoxy(63,30);	printf("Alamat 		= %s", prd.alamat);
        gotoxy(63,31);	printf("No Telepon 	= %s", prd.telp);
        gotoxy(63,32);	printf("E-mail 		= %s", prd.email);

        gotoxy(134,16);	printf("Pilih yang akan diupdate");
        gotoxy(134,18);	printf("[1] Nama Perusahaan\n");
        gotoxy(134,19);	printf("[2] Alamat");
        gotoxy(134,20);	printf("[3] No Telepon");
        gotoxy(134,21);	printf("[4] E-mail");
        gotoxy(134,22);	printf("[0] Keluar");

        do {
            gotoxy(141,24); printf("   ");
            gotoxy(134,24);	printf("Pilih : ");
            gotoxy(142,24);	scanf("%d",&choose);

            switch(choose){
            case 1 :
                gotoxy(134,26);	printf("Nama Perusahaan = ");
                fflush(stdin);
                gotoxy(134,27);	gets(prd.nama);
                break;
            case 2 :
                gotoxy(134,26);	printf("Alamat = ");
                fflush(stdin);
                gotoxy(134,27);	gets(prd.alamat);
                break;
            case 3 :
                gotoxy(134,26);	printf("No Telepon = ");
                fflush(stdin);
                gotoxy(134,27);	gets(prd.telp);
                break;
            case 4 :
                gotoxy(134,26);	printf("E-mail = ");
                fflush(stdin);
                gotoxy(134,27);	gets(prd.email);
                break;
            case 0 :
                CleanKanan();
                MenuProduser();
                break;
            }
        } while (choose > 4);

        fwrite(&prd,sizeof(prd),1,temp); /* menulid data baru kedalam temp */
        fread(&prd,sizeof(prd),1,arsprd);
        while(!feof(arsprd)){
            fwrite(&prd,sizeof(prd),1,temp); /* menyalin sisa data */
            fread(&prd,sizeof(prd),1,arsprd);
        }
        fclose(temp);
        fclose(arsprd);

        /* menyalin temp ke data produser */
        temp = fopen("dat/Temp Data Produser.dat","rb");
        arsprd = fopen("dat/Data Produser.dat","wb");
        fread(&prd,sizeof(prd),1,temp);
        while(!feof(temp))
        {
        	fwrite(&prd,sizeof(prd),1,arsprd);
        	fread(&prd,sizeof(prd),1,temp);
		}
		fclose(temp);
		fclose(arsprd);

        MessageBoxA(0,"Data Berhasil di Update","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

        do {
            gotoxy(166,29);	printf("   ");
            gotoxy(134,29);	printf("Ingin update data lagi? [Y/N] : ");
            gotoxy(166,29);	scanf("%s", &ans);

            switch (toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                UbahPrd();
                break;
            case 'N':
                CleanKanan();
                MenuProduser();
                break;
            }
        } while (toupper(ans) != 'Y' && ' N');
    }else{
        MessageBox(NULL,"ID Produser Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        UbahPrd();
    }
}

void HapusPrd()
{
    FILE *temp;
    int idhapus, found=0, i=0;
    char ans;

    LihatPrd();

    gotoxy(75,44);	printf("  Hapus Data Produser            ");
    gotoxy(137,44);	printf("Untuk kembali, ketik '0'\n");

    arsprd = fopen("dat/Data Produser.dat","rb"); /*buka file untuk dibaca */
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuProduser();
    }
    fclose(arsprd);

	gotoxy(151,17);	printf("  ");
    gotoxy(134,17);	printf("ID Produser : PRD");
    gotoxy(151,17);	scanf("%d", &idhapus);
    if(idhapus == 0){
    	CleanKanan();
        MenuProduser();
    }

    temp = fopen("dat/Temp Data Produser.dat", "wb"); /* buka file temp untuk ditulis */
    arsprd = fopen("dat/Data Produser.dat", "rb"); /* buka file produser untuk dibaca */
    while(!found && !feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        if(prd.id == idhapus){ /* mencari id yang akan dihapus */
            found = 1;
        }else{
            fwrite(&prd,sizeof(prd),1,temp); /* menulis data yang tidak dihapus ke temp */
        }
    }
    if(found){
    	CleanTengah();
    	DesainUbahData();
        gotoxy(63,28);	printf("ID Produser 	= PRD%d", prd.id);
        gotoxy(63,29);	printf("Nama Perusahaan 	= %s", prd.nama);
        gotoxy(63,30);	printf("Alamat 		= %s", prd.alamat);
        gotoxy(63,31);	printf("No Telepon 	= %s", prd.telp);
        gotoxy(63,32);	printf("E-mail 		= %s", prd.email);

        do {
            gotoxy(166,19);	printf("  ");
            gotoxy(134,19);	printf("Yakin data akan dihapus?[Y/N] : ");
            gotoxy(166,19);	scanf("%s", &ans);

            switch(toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                fread(&prd,sizeof(prd),1,arsprd); /* menyalin sisa data yang tidak dihapus */
                while(!feof(arsprd)){
                    fwrite(&prd,sizeof(prd),1,temp);
                    fread(&prd,sizeof(prd),1,arsprd);
                }
                break;
            case 'N':
                CleanTengah();
                CleanKanan();
                HapusPrd();
                break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Produser Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        HapusPrd();
    }
    fclose(temp);
    fclose(arsprd);

    /* menyalin temp ke data produser */
    temp = fopen("dat/Temp Data Produser.dat","rb");
    arsprd = fopen("dat/Data Produser.dat","wb");
    fread(&prd,sizeof(prd),1,temp);
    while(!feof(temp))
    {
        fwrite(&prd,sizeof(prd),1,arsprd);
        fread(&prd,sizeof(prd),1,temp);
    }
    fclose(temp);
    fclose(arsprd);

    MessageBoxA(0,"Data Berhasil Dihapus","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(158,22);	printf("   ");
        gotoxy(134,22);	printf("Hapus data lagi?[Y/N] : ");
        gotoxy(158,22);	scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
        	CleanTengah();
        	CleanKanan();
        	LihatPrd();
            HapusPrd();
            break;
        case 'N':
            CleanKanan();
            MenuProduser();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}
