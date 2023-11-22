void CekJadwal()
{
    FILE *temp;
    int hari, bulan, tahun, found=0;

    remove("dat/temp.dat");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    hari=tm.tm_mday;
    bulan=tm.tm_mon + 1;
    tahun=tm.tm_year + 1900;

    arsjdwl = fopen("dat/Data Jadwal.dat", "rb");
    temp = fopen("dat/temp.dat", "wb");

    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl))
    {
        if(jd.hari==hari && jd.bulan==bulan && jd.tahun==tahun)
        {
            jd.status = 3;
            fwrite(&jd,sizeof(jd),1,temp);
        }
        else if((jd.hari < hari && jd.bulan == bulan && jd.tahun == tahun) || (jd.bulan < bulan && jd.tahun >= tahun)|| (jd.tahun < tahun))
        {
            jd.status = 1;
            fwrite(&jd,sizeof(jd),1,temp);
        }
        else if((jd.bulan > bulan && jd.tahun >= tahun) || (jd.tahun > tahun))
        {
            jd.status = 2;
            fwrite(&jd,sizeof(jd),1,temp);
        }
        else
        {
            fwrite(&jd,sizeof(jd),1,temp);
        }
        fread(&jd,sizeof(jd),1,arsjdwl);
    }
    fclose(arsjdwl);
    fclose(temp);

    arsjdwl = fopen("dat/Data Jadwal.dat", "wb");
    temp = fopen("dat/temp.dat", "rb");
    fread(&jd,sizeof(jd),1,temp);
    while(!feof(temp))
    {
        fwrite(&jd,sizeof(jd),1,arsjdwl);
        fread(&jd,sizeof(jd),1,temp);
    }
    fclose(arsjdwl);
    fclose(temp);
}

void MenuJadwal()
{
    remove("dat/tempjadwal.dat");

    int choose;

	CleanKiri();
	CleanTengah();

    gotoxy(14,22);	printf("MASTER JADWAL");

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
            Tambahjdwl();
            break;
        case 2 :
            lihatjdwl();
            gotoxy(22,30);	getch();
            MenuJadwal();
            break;
        case 3 :
            Ubahjdwl();
            break;
        case 4 :
            Hapusjdwl();
            break;
        case 5 :
        	CleanKiri();
            MenuAdmin();
        break;

        default :
            MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            MenuJadwal();
        break;
    }
}

void Tambahjdwl()
{
    int found=0, id, i=0;
    char ans;
    char judul[50];

    LihatFlm(); /* menampilkan data film */
    gotoxy(75,44); printf("                                      ");

    gotoxy(138,44);	printf("Untuk kembali, ketik '0'\n");

    arsjdwl = fopen("dat/Data Jadwal.dat", "rb"); /*membuka file untuk dibaca */
    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl)){
        fread(&jd,sizeof(jd),1,arsjdwl);
        id = jd.idjadwal;
        i++;
    }
    if(i==0){
        jd.idjadwal = 1;
    }else{
        jd.idjadwal = id+1; /* id otomatis */
    }
    fclose(arsjdwl);

    gotoxy(134,17);	printf("ID Jadwal = EVN%d", jd.idjadwal);

    /* RELASI FILM */
    do {
        gotoxy(146,18);	printf("    ");
        gotoxy(134,18);	printf("ID Film : FM");
        fflush(stdin);
        gotoxy(146,18);	scanf("%d", &jd.idfilm);
        if(jd.idfilm == 0){
            CleanKanan();
            MenuJadwal();
        }
        found=0;
        arsflm = fopen("dat/Data Film.dat","rb");
        fread(&flm,sizeof(flm),1,arsflm);
        while(!found && !feof(arsflm)){
            if(jd.idfilm == flm.id){ /* mencari id film yang dicari dalam data */
                found = 1;
                break;
            }else{
                fread(&flm,sizeof(flm),1,arsflm);
            }
        }
        fclose(arsflm);
        if(found && flm.status == 1){ /* jika status sudah hak milik, dapat di eksekusi */
            strcpy(jd.judul,flm.judul);
            break;
        }else if(found && flm.status == 0){
            MessageBoxA(NULL,"Status harus Hak Milik!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        }else{
            MessageBoxA(NULL,"ID Film tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        }
    } while (!found || flm.status == 0);

	CleanKanan();
    gotoxy(138,44);	printf("Untuk kembali, ketik '0'\n");
    gotoxy(134,17);	printf("ID Jadwal = EVN%d", jd.idjadwal);
    gotoxy(134,18);	printf("Judul Film  = %s", jd.judul);

    gotoxy(134,19);	printf("Tempat = ");
    fflush(stdin);
    gets(jd.tempat);
    if(!strcmp(jd.tempat,"0")){
        CleanKanan();
        MenuJadwal();
    }

    gotoxy(134,20);	printf("Tanggal =   -  -    ");
    fflush(stdin);
    gotoxy(144,20); scanf("%d", &jd.hari);
    if(jd.hari == 0){
        CleanKanan();
        MenuJadwal();
    }
    gotoxy(147,20); scanf("%d", &jd.bulan);
    if(jd.bulan == 0){
        CleanKanan();
        MenuJadwal();
    }
    gotoxy(150,20); scanf("%d", &jd.tahun);
    if(jd.tahun == 0){
        CleanKanan();
        MenuJadwal();
    }

    gotoxy(134,21);	printf("Kapasitas = ");
    fflush(stdin);
    scanf("%d", &jd.kapasitastetap);
    if(jd.kapasitastetap == 0){
        CleanKanan();
        MenuJadwal();
    }

    jd.stok = jd.kapasitastetap;

    gotoxy(134,22);	printf("Harga = Rp ");
    fflush(stdin);
    getRp(&jd.harga,4,9,145,22);

    jd.status=2;

    if(jd.status==2){
        gotoxy(134,23);	printf("Status = Belum Tayang");
    }

	arsjdwl = fopen("dat/Data Jadwal.dat", "ab");
    fwrite(&jd,sizeof(jd),1,arsjdwl);
    fclose(arsjdwl);

    MessageBox(NULL,"Data berhasil ditambahkan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(159,29);	printf("   ");
        gotoxy(134,29);	printf("Tambah data lagi? [Y/N] : ");
        scanf("%s", &ans);

        switch (toupper(ans)){
            case 'Y':
                CleanKanan();
                Tambahjdwl();
                break;
            case 'N':
                CleanKanan();
                MenuJadwal();
                break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void lihatjdwl()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;
    char harga[25];

    CekJadwal();
	gotoxy(75,44);	printf("--Klik apapun untuk kembali--");

    arsjdwl = fopen("dat/Data Jadwal.dat", "rb");
    fread(&jd,sizeof(jd),1,arsjdwl);

    while(!feof(arsjdwl)){
        fread(&jd,sizeof(jd),1,arsjdwl);
        i++;
    }
    fclose(arsjdwl);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("  ID       Judul\t          Tempat\t  Tanggal     Stok      Harga\t       Status");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuJadwal();
    }else{
        arsjdwl = fopen("dat/Data Jadwal.dat", "rb");
        fread(&jd,sizeof(jd),1,arsjdwl);
        while(!feof(arsjdwl)){
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
            gotoxy(Kolom+1,Baris);	printf("EVN%d", jd.idjadwal);
            gotoxy(Kolom+8,Baris);  printf("%s", jd.judul);
            gotoxy(Kolom+27,Baris); printf("%s", jd.tempat);
            gotoxy(Kolom+44,Baris);	printf("%02d-%02d-%d", jd.hari, jd.bulan, jd.tahun);
            gotoxy(Kolom+59,Baris);	printf("%d", jd.stok);
            gotoxy(Kolom+66,Baris);	rupiah(jd.harga,harga); printf("Rp %s", harga);
            switch(jd.status){
            case 1 :
                gotoxy(Kolom+80,Baris);    printf("Sudah Tayang"); break;
            case 2 :
                gotoxy(Kolom+80,Baris);    printf("Belum Tayang"); break;
            case 3 :
                gotoxy(Kolom+80,Baris);    printf("Sedang Tayang"); break;
            }
            fread(&jd,sizeof(jd),1,arsjdwl);
        }
        fclose(arsjdwl);
    }
}

void Ubahjdwl()
{
    FILE *temp;
    int idupdate, found=0, choose, i=0;
    char ans, harga[25];

	lihatjdwl();
	gotoxy(75,44); printf("                                      ");
    gotoxy(138,44);	printf("Untuk kembali, ketik '0'\n");

    arsjdwl = fopen("dat/Data Jadwal.dat","rb");
    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl)){
        fread(&jd,sizeof(jd),1,arsjdwl);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuJadwal();
    }
    fclose(arsjdwl);

    gotoxy(158,15);	printf("  ");
    gotoxy(134,15);	printf("Masukkan ID Jadwal : EVN");
    gotoxy(158,15);	scanf("%d", &idupdate);
    if(idupdate == 0){
    	CleanKanan();
        MenuJadwal();
    }

    temp = fopen ("dat/tempjadwal.dat", "wb"); /* buka file temp untuk ditulis */
    arsjdwl = fopen("dat/Data Jadwal.dat","rb");
    while(!found && !feof(arsjdwl)){
        fread(&jd,sizeof(jd),1,arsjdwl);
        if(jd.idjadwal == idupdate){
            found = 1;
        }else{
            fwrite(&jd,sizeof(jd),1,temp);
        }
    }
    if (found){
    	CleanTengah();
    	DesainUbahData();

        gotoxy(63,26);	printf("ID Event            = EVN%d", jd.idjadwal);
        gotoxy(63,27);	printf("Judul Film          = %s", jd.judul);
        gotoxy(63,28);	printf("Tempat              = %s", jd.tempat);
        gotoxy(63,29);	printf("Tanggal             = %02d-%02d-%d", jd.hari, jd.bulan, jd.tahun);
        gotoxy(63,30);	printf("Kapasitas           = %d", jd.kapasitastetap);
        gotoxy(63,31);	rupiah(jd.harga,harga);
                        printf("Harga               = Rp %s", harga);

        gotoxy(134,16);	printf("Pilih yang akan diupdate");
        gotoxy(134,18);	printf("[1] Film");
        gotoxy(134,19);	printf("[2] Tempat");
        gotoxy(134,20);	printf("[3] Tanggal");
        gotoxy(134,21);	printf("[4] Kapasitas");
        gotoxy(134,22);	printf("[5] Harga");
        gotoxy(134,24);	printf("[0] Keluar");

    do{
        gotoxy(141,25); printf("   ");
        gotoxy(134,25);	printf("Pilih : ");
        gotoxy(141,25);	scanf("%d",&choose);

        switch(choose){
        case 1:
            CleanTengah();
            LihatFlm();
            gotoxy(75,44); printf("                                      ");
            do {
                gotoxy(146,27);	printf("   ");
                gotoxy(134,27);	printf("ID Film = FM");
                fflush(stdin);
                scanf("%d", &jd.idfilm);

                found=0;
                arsflm = fopen("dat/Data Film.dat","rb");
                fread(&flm,sizeof(flm),1,arsflm);
                while(!feof(arsflm) && !found){
                    if(jd.idfilm == flm.id){
                        found = 1;
                    }else{
                        fread(&flm,sizeof(flm),1,arsflm);
                    }
                }
                fclose(arsflm);

                if(found && flm.status == 1){
                    strcpy(jd.judul,flm.judul);
                }else if(found && flm.status == 0){
                    MessageBoxA(NULL,"Status harus Hak Milik!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                }else{
                    MessageBoxA(NULL,"ID Film tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                }
            } while (!found || flm.status != 1);
            break;
        case 2 :
            gotoxy(134,27);	printf("Tempat = ");
            fflush(stdin);
            gotoxy(134,28);	gets(jd.tempat);
            break;
        case 3:
            gotoxy(134,27);	printf("Tanggal = ");
            fflush(stdin);
            gotoxy(134,28);	printf("  -  -    ");
            fflush(stdin);
            gotoxy(134,28); scanf("%d",&jd.hari);
            fflush(stdin);
            gotoxy(137,28); scanf("%d",&jd.bulan);
            fflush(stdin);
            gotoxy(140,28); scanf("%d",&jd.tahun);
            break;
        case 4:
            gotoxy(134,27);	printf("Kapasitas = ");
            fflush(stdin);
            gotoxy(134,28);	scanf("%d",&jd.kapasitastetap);
            jd.stok = jd.kapasitastetap;
            break;
        case 5:
            gotoxy(134,27);	printf("Harga = ");
            gotoxy(134,28);	printf("Rp ");
            fflush(stdin);
            getRp(&jd.harga,4,9,137,28);
            break;
        case 0 :
        	CleanKanan();
        	CleanTengah();
            Ubahjdwl();
            break;
        default :
            MessageBoxA(NULL,"Incorrect input!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        }
    } while (choose > 6);

        fwrite(&jd,sizeof(jd),1,temp);
        fread(&jd,sizeof(jd),1,arsjdwl);
        while(!feof(arsjdwl)){
            fwrite(&jd,sizeof(jd),1,temp);
            fread(&jd,sizeof(jd),1,arsjdwl);
        }
        fclose(temp);
        fclose(arsjdwl);

        temp = fopen("dat/tempjadwal.dat","rb");
        arsjdwl = fopen("dat/Data Jadwal.dat","wb");
        fread(&jd,sizeof(jd),1,temp);
        while(!feof(temp))
        {
        	fwrite(&jd,sizeof(jd),1,arsjdwl);
        	fread(&jd,sizeof(jd),1,temp);
		}
		fclose(temp);
        fclose(arsjdwl);

        MessageBoxA(NULL,"Data Berhasil di update","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

        do {
            gotoxy(166,31);	printf("   ");
            gotoxy(134,31);	printf("Ingin update data lagi? [Y/N] : ");
            gotoxy(166,31);	scanf("%s", &ans);

            switch (toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                Ubahjdwl();
                break;
            case 'N':
                CleanKanan();
                CleanTengah();
                MenuJadwal();
                break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Jadwal Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        Ubahjdwl();
    }
}

void Hapusjdwl(){
    FILE *temp;
    int idhapus, found=0, i=0;
    char ans, harga[25];

    gotoxy(138,44); printf("Untuk kembali, ketik '0'\n");

	lihatjdwl();
	gotoxy(75,44); printf("                                      ");

    arsjdwl = fopen("dat/Data Jadwal.dat","rb");
    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl)){
        fread(&jd,sizeof(jd),1,arsjdwl);
        i++;
    }
    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuJadwal();
    }
    fclose(arsjdwl);

    gotoxy(134,17);	printf("Masukkan ID Jadwal : EVN");
    scanf("%d", &idhapus);

    if(idhapus == 0){
    	CleanKanan();
        MenuJadwal();
    }

    //buka file temp untuk ditulis
    temp = fopen("dat/tempjadwal.dat","wb");
    //buka file untuk dibaca
    arsjdwl = fopen("dat/Data Jadwal.dat","rb");

    while(!found && !feof(arsjdwl)){
    	fread(&jd,sizeof(jd),1,arsjdwl);
        if(jd.idjadwal == idhapus){
            found = 1;
        }else{
            fwrite(&jd,sizeof(jd),1,temp);
        }
    }

    if(found){
    	CleanTengah();
    	DesainUbahData();
        gotoxy(63,26);	printf("ID Event            = EVN%d", jd.idjadwal);
        gotoxy(63,27);	printf("Judul Film          = %s", jd.judul);
        gotoxy(63,28);	printf("Tempat              = %s", jd.tempat);
        gotoxy(63,29);	printf("Tanggal             = %02d-%02d-%d", jd.hari, jd.bulan, jd.tahun);
        gotoxy(63,30);	printf("Kapasitas Tiket     = %d", jd.kapasitastetap);
        gotoxy(63,31);	rupiah(jd.harga,harga); printf("Harga               = Rp %s", harga);

        do {
            gotoxy(166,19);	printf("   ");
            gotoxy(134,19);	printf("Yakin data akan dihapus?[Y/N] : ");
            gotoxy(166,19);	scanf("%s", &ans);

            switch(toupper(ans)){
            case 'Y':
                CleanTengah();
                CleanKanan();
                fread(&jd,sizeof(jd),1,arsjdwl);
                while(!feof(arsjdwl)){
                    fwrite(&jd,sizeof(jd),1,temp);
                    fread(&jd,sizeof(jd),1,arsjdwl);
                }
                break;
            case 'N':
                CleanTengah();
                CleanKanan();
                Hapusjdwl();
                break;
            }
        } while (toupper(ans) != 'Y' && 'N');
    }else{
        MessageBox(NULL,"ID Jadwal Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        Hapusjdwl();
    }
    //tutup file
    fclose(temp);
    fclose(arsjdwl);

    temp = fopen("dat/tempjadwal.dat","rb");
    arsjdwl = fopen("dat/Data Jadwal.dat","wb");

    fread(&jd,sizeof(jd),1,temp);
    while(!feof(temp)){
        fwrite(&jd,sizeof(jd),1,arsjdwl);
        fread(&jd,sizeof(jd),1,temp);
    }

    fclose(temp);
    fclose(arsjdwl);

    MessageBox(NULL,"Data Berhasil Di Hapus","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);;

    do {
        gotoxy(158,22);	printf("   ");
        gotoxy(134,22);	printf("Hapus data lagi?[Y/N] : ");
        gotoxy(158,22);	scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
            CleanTengah();
            CleanKanan();
            Hapusjdwl();
            break;
        case 'N':
            CleanTengah();
            CleanKanan();
            MenuJadwal();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}
