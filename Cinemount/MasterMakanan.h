void TambahMK();
void LihatMK();
void UbahMK();
void HapusMK();

void MenuMakanan()
{
    int choose;

	CleanKiri();
	CleanTengah();

    remove("dat/Temp Data Makanan.dat");

    gotoxy(14,22);	printf("MASTER MAKANAN");
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
        TambahMK();
        break;
    case 2 :
        LihatMK();
        gotoxy(22,30);	getch();
        MenuMakanan();
        break;
    case 3 :
        UbahMK();
        break;
    case 4 :
        HapusMK();
        break;
    case 5 :
        CleanKiri();
        MenuKasir();
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMakanan();
        break;
    }
}

void TambahMK()
{
    int id, i=0;
    char ans, harga[25];

    LihatMK(); /* menampilkan menu makanan */

    gotoxy(80,44);	printf("Tambah Data Makanan\n");
    gotoxy(136,44);	printf("Untuk kembali, ketik '0'\n");

    /* buka file makanan untuk ditambah dan dibaca */
    arsmk = fopen("dat/Data Makanan.dat", "ab+");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        id = mk.id;
        i++;
    }
    if(i==0){
        mk.id = 1;
    }else{
        mk.id = id+1;
    }

    gotoxy(136,17);	printf("ID Makanan = MK%d\n", mk.id);

    gotoxy(136,18);	printf("Nama = ");
    fflush(stdin);
    gets(mk.nama);
    if(!strcmp(mk.nama,"0")){
    	CleanKanan();
        MenuMakanan();
    }

    gotoxy(136,19);	printf("Stok = ");
    fflush(stdin);
    scanf("%d", &mk.stok);
    if(mk.stok == 0){
    	CleanKanan();
        MenuMakanan();
    }

    gotoxy(136,20);	printf("Harga = Rp ");
    fflush(stdin);
    getRp(&mk.harga,4,9,147,20);

    gotoxy(136,21); printf("[1] Makanan");
    gotoxy(136,22); printf("[2] Minuman");

    gotoxy(136,23);	printf("Jenis = ");
    fflush(stdin);
    scanf("%d", &mk.jenis);

    fwrite(&mk,sizeof(mk),1,arsmk); /* menambahkan data ke file makanan */
    fclose(arsmk);

    MessageBoxA(0,"Data Berhasil di Tambahkan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(160,25); printf("   ");
        gotoxy(136,25);	printf("Tambah data lagi? [Y/N]: ");
        scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanKanan();
            TambahMK();
            break;
        case 'N':
            CleanKanan();
            MenuMakanan();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void LihatMK()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;
    char Harga[10];

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--");

    /* buka file makanan untuk dibaca */
    arsmk = fopen("dat/Data Makanan.dat", "rb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
    fclose(arsmk);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("\t\t ID_MK        Nama             Jenis        Stok          Harga");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMakanan();
    }else{
        /* buka file makanan untuk dibaca */
        arsmk = fopen("dat/Data Makanan.dat","rb");
        fread(&mk,sizeof(mk),1,arsmk);
        while(!feof(arsmk)){
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
            gotoxy(Kolom+14,Baris);	printf("MK%d", mk.id);
            gotoxy(Kolom+24,Baris);	printf("%s", mk.nama);
            if(mk.jenis == 1){
                gotoxy(Kolom+42,Baris);	printf("Makanan");
            }else{
                gotoxy(Kolom+42,Baris);	printf("Minuman");
            }
            gotoxy(Kolom+56,Baris);	printf("%d", mk.stok);
            gotoxy(Kolom+68,Baris);	rupiah(mk.harga,Harga); printf("Rp %s", Harga);
            fread(&mk,sizeof(mk),1,arsmk);
        }
        fclose(arsmk);
    }
}

void UbahMK()
{
    FILE *temp;
    int idupdate, found=0, choose, i=0;
    char ans, Harga[10];

    gotoxy(75,44);	printf("Ubah Data Makanan\n");
    gotoxy(136,44);	printf("Untuk kembali, ketik '0'\n");

	LihatMK(); /* menampilkan menu makanan */

	/* buka file makanan untuk dibaca */
    arsmk = fopen("dat/Data Makanan.dat","rb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMakanan();
    }
    fclose(arsmk);

	gotoxy(149,15);	printf("   ");
    gotoxy(134,15);	printf("ID Makanan = MK");
    gotoxy(149,15);	scanf("%d", &idupdate);
    if(idupdate == 0){
    	CleanKanan();
        MenuMakanan();
    }

    temp = fopen ("dat/Temp Data Makanan.dat", "wb");   /* buka file temp untuk ditulis */
    arsmk = fopen("dat/Data Makanan.dat", "rb");    /* buka file makanan untuk dibaca */
    fread(&mk,sizeof(mk),1,arsmk);
    while(!found && !feof(arsmk)){
        if(mk.id == idupdate){  /* pencarian id yang akan di update */
            found = 1;
        }else{
            fwrite(&mk,sizeof(mk),1,temp); /* tulis kedalam temp jika bukan id yg dicari */
        }
        fread(&mk,sizeof(mk),1,arsmk);
    }
    if (found){
    	CleanTengah();
    	DesainUbahData();

        gotoxy(71,28);	printf("ID Makanan  = MK%d", mk.id);
        gotoxy(71,29);	printf("Nama        = %s\n", mk.nama);
        if(mk.jenis == 1){
            gotoxy(71,30);	printf("Jenis       = Makanan");
        }else{
            gotoxy(71,30);	printf("Jenis       = Minuman");
        }
        gotoxy(71,31);	printf("Stok        = %d\n", mk.stok);
        gotoxy(71,32);	rupiah(mk.harga,Harga); printf("Harga       = Rp %s\n\n", Harga);

        gotoxy(134,17);	printf("Pilih yang akan diupdate : ");
        gotoxy(134,18);	printf("[1] Nama Makanan\n");
        gotoxy(134,19);	printf("[2] Jenis");
        gotoxy(134,20);	printf("[3] Stok");
        gotoxy(134,21);	printf("[4] Harga");
        gotoxy(134,22);	printf("[0] Keluar");

        do {
            gotoxy(142,24); printf("  ");
            gotoxy(134,24);	printf("Pilih : ");
            gotoxy(142,24);	scanf("%d",&choose);

            switch(choose){
            case 1 :
                gotoxy(134,26);	printf("Nama = ");
                fflush(stdin);
                gotoxy(134,27);	gets(mk.nama);
                break;
            case 2 :
                gotoxy(134,26);	printf("[1] Makanan");
                gotoxy(134,27);	printf("[2] Minuman");
                gotoxy(134,28); printf("Jenis = ");
                fflush(stdin);
                scanf("%d", &mk.jenis);
                break;
            case 3 :
                gotoxy(134,26);	printf("Stok = ");
                fflush(stdin);
                gotoxy(134,27);	scanf("%d", &mk.stok);
                break;
            case 4 :
                gotoxy(134,26);	printf("Harga = Rp ");
                fflush(stdin);
                getRp(&mk.harga,4,9,145,26);
                break;
            case 0 :
                CleanKanan();
                MenuMakanan();
                break;
            default :
                MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                break;
            }
        } while (choose > 3);

        fwrite(&mk,sizeof(mk),1,temp);  /* tulis data makanan yg sudah dirubah kedalam temp */
        fread(&mk,sizeof(mk),1,arsmk);  /* baca sisa data makanan */
        while(!feof(arsmk)){
            fwrite(&mk,sizeof(mk),1,temp);
            fread(&mk,sizeof(mk),1,arsmk);
        }
        fclose(temp);
        fclose(arsmk);

        /* proses memindahkan temp ke data makanan */
        temp = fopen("dat/Temp Data Makanan.dat","rb");
        arsmk = fopen("dat/Data Makanan.dat","wb");
        fread(&mk,sizeof(mk),1,temp);
        while(!feof(temp))
        {
        	fwrite(&mk,sizeof(mk),1,arsmk);
        	fread(&mk,sizeof(mk),1,temp);
		}
		fclose(temp);
        fclose(arsmk);

        MessageBoxA(0,"Data Berhasil di Update","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

        do {
            gotoxy(166,30);	printf("   ");
            gotoxy(134,30);	printf("Ingin update data lagi? [Y/N] : ");
            gotoxy(166,30);	scanf("%s", &ans);

            switch (toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                UbahMK();
                break;
            case 'N':
                CleanKanan();
                MenuMakanan();
                break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Makanan Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        UbahMK();
    }
}

void HapusMK()
{
    FILE *temp;
    int idhapus, found=0, i=0;
    char ans, Harga[10];

    gotoxy(75,44);	printf("Hapus Data Makanan                        ");
    gotoxy(137,44);	printf("Untuk kembali, ketik '0'\n");

	LihatMK(); /* menampilkan menu makanan */

	/* buka file makanan untuk dibaca */
    arsmk = fopen("dat/Data Makanan.dat","rb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMakanan();
    }
    fclose(arsmk);

    gotoxy(134,17);	printf("ID Makanan = MK");
    scanf("%d", &idhapus);
    if(idhapus == 0){
    	CleanKanan();
        MenuMakanan();
    }

    temp = fopen("dat/Temp Data Makanan.dat", "wb"); /* buka file temp untuk ditulis */
    arsmk = fopen("dat/Data Makanan.dat", "rb"); /* buka file makanan untuk dibaca */
    while(!found && !feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        if(mk.id == idhapus){ /* mencari id yang akan dihapus */
            found = 1;
        }else{
            fwrite(&mk,sizeof(mk),1,temp);
        }
    }
    if(found){
    	CleanTengah();
    	DesainUbahData();

        gotoxy(71,28);	printf("ID Makanan  = MK%d", mk.id);
        gotoxy(71,29);	printf("Nama        = %s", mk.nama);
        if (mk.jenis == 1){
            gotoxy(71,30);  printf("Jenis       = Makanan");
        }else{
            gotoxy(71,30);  printf("Jenis       = Minuman");
        }
        gotoxy(71,31);	printf("Stok        = %d", mk.stok);
        gotoxy(71,32);	rupiah(mk.harga,Harga); printf("Harga       = Rp %s", Harga);

        do {
            gotoxy(166,19);	printf("   ");
            gotoxy(134,19);	printf("Yakin data akan dihapus?[Y/N] : ");
            gotoxy(166,19);	scanf("%s", &ans);

            switch(toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                fread(&mk,sizeof(mk),1,arsmk);
                while(!feof(arsmk)){
                    fwrite(&mk,sizeof(mk),1,temp);
                    fread(&mk,sizeof(mk),1,arsmk);
                }
                break;
            case 'N':
                CleanKanan();
                CleanTengah();
                HapusMK();
                break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Makanan Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        CleanKanan();
        HapusMK();
    }
    fclose(temp);
    fclose(arsmk);

    /* proses pemindahan temp ke data makanan */
    temp = fopen("dat/Temp Data Makanan.dat","rb");
    arsmk = fopen("dat/Data Makanan.dat","wb");
    fread(&mk,sizeof(mk),1,temp);
    while(!feof(temp))
    {
        fwrite(&mk,sizeof(mk),1,arsmk);
        fread(&mk,sizeof(mk),1,temp);
    }
    fclose(temp);
    fclose(arsmk);

    MessageBoxA(0,"Data Berhasil Dihapus","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(164,22);	printf("   ");
        gotoxy(134,22);	printf("Ingin Hapus data lagi?[Y/N] : ");
        gotoxy(164,22);	scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
            CleanTengah();
            CleanKanan();
            LihatMK();
            HapusMK();
            break;
        case 'N':
            CleanKanan();
            MenuMakanan();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}
