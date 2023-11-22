void MenuFilm()
{
    remove("dat/Temp Data Film.dat");

    int choose;

    CleanKiri();
	CleanTengah();

    gotoxy(14,22);	printf("MASTER FILM");

    gotoxy(14,25);	printf("[1] Tambah Data");
    gotoxy(14,26);	printf("[2] Lihat Data");
    gotoxy(14,27);	printf("[3] Ubah Data");
    gotoxy(14,28);	printf("[4] Hapus Data");
    gotoxy(14,29);	printf("[5] Keluar");

    gotoxy(22,30);	printf("   ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &choose);

    switch(choose){
    case 1 :
        TambahFlm();
        break;
    case 2 :
    	LihatFlm();
    	gotoxy(22,30);	getch();
        MenuFilm();
        break;
    case 3 :
        UbahFlm();
        break;
    case 4 :
        HapusFlm();
        break;
    case 5 :
        CleanKiri();
        MenuAdmin();
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuFilm();
        break;
    }
}

void TambahFlm()
{
    int found = 0,id, i=0;
    char ans;

    LihatFlm(); /* menampilkan data film */

    gotoxy(138,44);	printf("Untuk kembali, ketik '0'");

    arsflm = fopen("dat/Data Film.dat", "ab+"); /* buka file untuk ditambah dan dibaca */
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        id = flm.id;
        i++;
    }
    if(i==0){
        flm.id = 1;
    }else{
        flm.id = id+1; /* id otomatis */
    }

    gotoxy(134,17);	printf("ID Film = FM%d\n", flm.id);

    gotoxy(134,18);	printf("Judul = ");
    fflush(stdin);
    gets(flm.judul);
    if(!strcmp(flm.judul,"0")){
    	CleanKanan();
        MenuFilm();
    }

    CleanTengah();
    LihatPrd(); /* menampilkan data produser */

    do {
        gotoxy(151,19);	printf("     ");
        gotoxy(134,19);	printf("ID Produser = PRD");
        fflush(stdin);
        gotoxy(151,19);	scanf("%d", &flm.prd);
        if(flm.prd == 0){
            CleanKanan();
            MenuFilm();
        }

        arsprd = fopen("dat/Data Produser.dat","rb");
        fread(&prd,sizeof(prd),1,arsprd);
        while(!feof(arsprd)){
            if(flm.prd == prd.id){
                found = 1;
                break;
            } else {
                fread(&prd,sizeof(prd),1,arsprd);
            }
        }
        if(!found){
            MessageBoxA(NULL,"ID Produser tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        }
    } while (!found);

    strcpy(flm.produser,prd.nama);
    fclose(arsprd);

    CleanKanan();
    CleanTengah();
    gotoxy(134,44);	printf("Untuk kembali, ketik '0'");

    gotoxy(134,17);	printf("ID Film = FM%d\n", flm.id);
    gotoxy(134,18);	printf("Judul = %s", flm.judul);
    gotoxy(134,19);	printf("Produser = %s", flm.produser);

    gotoxy(134,20);	printf("Durasi = ");
    fflush(stdin);
    gets(flm.durasi);
    if(!strcmp(flm.durasi,"0")){
        CleanKanan();
        MenuFilm();
    }

    gotoxy(134,21);	printf("Tahun Rilis = ");
    fflush(stdin);
    scanf("%d", &flm.tahun);
    if(flm.tahun == 0){
        CleanKanan();
        MenuFilm();
    }

    gotoxy(134,22);	printf("Genre = ");
    fflush(stdin);
    gets(flm.genre);
    if(!strcmp(flm.genre,"0")){
        CleanKanan();
        MenuFilm();
    }

    flm.status = 0;
    if (flm.status == 0) {
        gotoxy(134,23); printf("Status = Bukan Hak Milik");
    }

    gotoxy(134,24);	printf("Harga = Rp ");
    fflush(stdin);
    getRp(&flm.harga,4,9,145,24);

    fwrite(&flm,sizeof(flm),1,arsflm); /* menambahkan data kedalam file film */
    fclose(arsflm);

    MessageBox(NULL,"Data berhasil ditambahkan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(160,26); printf("   ");
        gotoxy(134,26);	printf("Tambah data lagi? [Y/N] : ");
        scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanKanan();
            TambahFlm();
            break;
        case 'N':
            CleanKanan();
            MenuFilm();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void LihatFlm()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;
    char harga[25];

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--");

    arsflm = fopen("dat/Data Film.dat", "rb"); /* buka file untuk dibaca */
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
    fclose(arsflm);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("  ID        Judul\t           Produser\t   Durasi   Tahun   Genre    Status       Harga");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuFilm();
    }else{
        arsflm = fopen("dat/Data Film.dat","rb"); /* buka file untuk dibaca */
        fread(&flm,sizeof(flm),1,arsflm);
        while(!feof(arsflm)){
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
            gotoxy(Kolom+1,Baris);	 printf("FM%d", flm.id);
            gotoxy(Kolom+7,Baris);   printf("%s", flm.judul);
            gotoxy(Kolom+28,Baris);  printf("%s", flm.produser);
            gotoxy(Kolom+47,Baris);	 printf("%s", flm.durasi);
            gotoxy(Kolom+56,Baris);	 printf("%d", flm.tahun);
            gotoxy(Kolom+63,Baris);	 printf("%s", flm.genre);
            if (flm.status == 0){
                gotoxy(Kolom+72,Baris);	 printf("Bukan Hak");
            }else{
                gotoxy(Kolom+72,Baris);	 printf("Hak Milik");
            }
            gotoxy(Kolom+83,Baris); rupiah(flm.harga,harga); printf("Rp %s", harga);
            fread(&flm,sizeof(flm),1,arsflm);
        }
        fclose(arsflm);
    }
}

void UbahFlm()
{
    FILE *temp;
    int idupdate, found=0, choose, i=0;
    char ans, harga[25];

    LihatFlm();
	gotoxy(75,44);	printf("      Ubah Data Film      \n");
    gotoxy(136,44);	printf("--0 untuk kembali--");

    arsflm = fopen("dat/Data Film.dat","rb"); /* buka file untuk dibaca */
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuFilm();
    }
    fclose(arsflm);

    gotoxy(134,15);	printf("ID Film = FM");
    scanf("%d", &idupdate);
    if(idupdate == 0){
    	CleanKanan();
        MenuFilm();
    }

    temp = fopen ("dat/Temp Data Film.dat", "wb"); /* buka file temp untuk ditulis */
    arsflm = fopen("dat/Data Film.dat", "rb");
    while(!found && !feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        if(flm.id == idupdate){
            found = 1;
        }else{
            fwrite(&flm,sizeof(flm),1,temp);
        }
    }
    if (found){
    	CleanTengah();
    	DesainUbahData();

        gotoxy(63,26);	printf("ID Film     = FM%d", flm.id);
        gotoxy(63,27);	printf("Judul       = %s", flm.judul);
        gotoxy(63,28);	printf("Produser    = %s", flm.produser);
        gotoxy(63,29);	printf("Durasi      = %s", flm.durasi);
        gotoxy(63,30);	printf("Tahun Rilis = %d", flm.tahun);
        gotoxy(63,31);	printf("Genre       = %s", flm.genre);
        gotoxy(63,32);	rupiah(flm.harga,harga); printf("Harga       = Rp %s", harga);

        gotoxy(134,16);	printf("Pilih yang akan diupdate");
        gotoxy(134,17);	printf("[1] Judul");
        gotoxy(134,18);	printf("[2] Produser");
        gotoxy(134,19);	printf("[3] Durasi");
        gotoxy(134,20);	printf("[4] Tahun Rilis");
        gotoxy(134,21);	printf("[5] Genre");
        gotoxy(134,22);	printf("[6] Harga");
        gotoxy(134,23);	printf("[0] Keluar");

        do {
            gotoxy(141,25); printf("   ");
            gotoxy(134,25);	printf("Pilih : ");
            gotoxy(141,25);	scanf("%d",&choose);

            switch(choose){
            case 1 :
                gotoxy(134,26);	printf("Judul = ");
                fflush(stdin);
                gotoxy(134,27);	gets(flm.judul);
                break;
            case 2 :
                CleanTengah();
                LihatPrd();
                do {
                    gotoxy(151,26); printf("   ");
                    gotoxy(134,26);	printf("ID Produser = PRD");
                    fflush(stdin); scanf("%d", &flm.prd);

                    found = 0;
                    arsprd = fopen("dat/Data Produser.dat","rb");
                    fread(&prd,sizeof(prd),1,arsprd);
                    while(!feof(arsprd) && !found){
                        if(flm.prd == prd.id){
                            found = 1;
                        }else{
                            fread(&prd,sizeof(prd),1,arsprd);
                        }
                    }
                    fclose(arsprd);
                    if (!found){
                        MessageBoxA(NULL,"ID Produser tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                    }
                } while(!found);
                strcpy(flm.produser,prd.nama);
                break;
            case 3 :
                gotoxy(134,26);	printf("Durasi = ");
                fflush(stdin);
                gotoxy(134,27);	gets(flm.durasi);
                break;
            case 4 :
                gotoxy(134,26);	printf("Tahun Rilis = ");
                fflush(stdin);
                gotoxy(134,27);	scanf("%d", &flm.tahun);
                break;
            case 5 :
                gotoxy(134,26);	printf("Genre = ");
                fflush(stdin);
                gotoxy(134,27);	gets(flm.genre);
                break;
            case 6 :
                gotoxy(134,26);	printf("Harga = ");
                gotoxy(134,27);	printf("Rp ");
                fflush(stdin);
                getRp(&flm.harga,4,9,137,27);
                break;
            case 0 :
                CleanKanan();
                CleanTengah();
                UbahFlm();
                break;
            default :
                MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            }
        } while (choose > 6);

        fwrite(&flm,sizeof(flm),1,temp); /* menulis data yg diupdate kedalam temp */
        fread(&flm,sizeof(flm),1,arsflm);
        while(!feof(arsflm)){
            fwrite(&flm,sizeof(flm),1,temp);
            fread(&flm,sizeof(flm),1,arsflm);
        }
        fclose(temp);
        fclose(arsflm);

        /* menyalin dari temp ke data film */
        temp = fopen("dat/Temp Data Film.dat","rb");
        arsflm = fopen("dat/Data Film.dat","wb");
        fread(&flm,sizeof(flm),1,temp);
        while(!feof(temp))
        {
        	fwrite(&flm,sizeof(flm),1,arsflm);
        	fread(&flm,sizeof(flm),1,temp);
		}
		fclose(temp);
        fclose(arsflm);

        MessageBoxA(0,"Data Berhasil di Update","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

        do {
        gotoxy(166,29);	printf("   ");
        gotoxy(134,29);	printf("Ingin update data lagi? [Y/N] : ");
        gotoxy(166,29);	scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanTengah();
        	CleanKanan();
            UbahFlm();
            break;
        case 'N':
            CleanKanan();
            CleanTengah();
            MenuFilm();
            break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Film Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        CleanKanan();
        UbahFlm();
    }
}

void HapusFlm()
{
    FILE *temp;
    int idhapus, found=0, i=0;
    char ans, harga[25];

	LihatFlm();
    gotoxy(75,44);	printf("      Hapus Data Film      \n");
    gotoxy(137,44);	printf("--0 untuk kembali--");

    arsflm = fopen("dat/Data Film.dat","rb"); /* buka file untuk dibaca  */
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuFilm();
    }
    fclose(arsflm);

    gotoxy(134,17);	printf("ID Film : FM");
    scanf("%d", &idhapus);
    if(idhapus == 0){
    	CleanKanan();
        MenuFilm();
    }

    temp = fopen("dat/Temp Data Film.dat", "wb"); /* buka file temp untuk ditulis */
    arsflm = fopen("dat/Data Film.dat", "rb");
    while(!found && !feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        if(flm.id == idhapus){
            found = 1;
        }else{
            fwrite(&flm,sizeof(flm),1,temp);
        }
    }
    if(found){
    	CleanTengah();
    	DesainUbahData();

        gotoxy(63,26);	printf("ID Film     = FM%d", flm.id);
        gotoxy(63,27);	printf("Judul       = %s", flm.judul);
        gotoxy(63,28);	printf("Produser    = %s", flm.produser);
        gotoxy(63,29);	printf("Durasi      = %s", flm.durasi);
        gotoxy(63,30);	printf("Tahun Rilis = %d", flm.tahun);
        gotoxy(63,31);	printf("Genre       = %s", flm.genre);
        gotoxy(63,32);	printf("Status      = %d", flm.status);
        gotoxy(63,33);	rupiah(flm.harga,harga); printf("Harga       = Rp %s", harga);

        do {
            gotoxy(142,20); printf("    ");
            gotoxy(134,19);	printf("Yakin data akan dihapus?");
            gotoxy(134,20);	printf("[Y/N] : ");
            scanf("%s", &ans);

            switch(toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                fread(&flm,sizeof(flm),1,arsflm);
                while(!feof(arsflm)){
                    fwrite(&flm,sizeof(flm),1,temp);
                    fread(&flm,sizeof(flm),1,arsflm);
                }
                break;
            case 'N':
                CleanTengah();
                CleanKanan();
                HapusFlm();
                break;
            }
        } while(toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Film Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        gotoxy(152,17);	printf(" ");
        HapusFlm();
    }
    fclose(temp);
    fclose(arsflm);

    /* menyalin dari temp ke data film */
    temp = fopen("dat/Temp Data Film.dat","rb");
    arsflm = fopen("dat/Data Film.dat","wb");
    fread(&flm,sizeof(flm),1,temp);
    while(!feof(temp))
    {
        fwrite(&flm,sizeof(flm),1,arsflm);
        fread(&flm,sizeof(flm),1,temp);
    }
    fclose(temp);
    fclose(arsflm);

    MessageBoxA(0,"Data Berhasil Dihapus","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do{
        gotoxy(158,22);	printf("  ");
        gotoxy(134,22);	printf("Hapus data lagi?[Y/N] : ");
        gotoxy(158,22);	scanf("%s", &ans);

        switch(toupper(ans))
        {
            case 'Y':
                CleanTengah();
                CleanKanan();
                HapusFlm();
                break;
            case 'N':
                CleanKanan();
                MenuFilm();
                break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

