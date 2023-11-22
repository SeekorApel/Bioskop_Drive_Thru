void SewaFilm(){

	int choose;

	CleanKiri();
    CleanTengah();

    gotoxy(17,21);	printf("TRANSAKSI");
	gotoxy(17,22);	printf("BELI FILM");

    gotoxy(14,26);	printf("[1] Tambah");
    gotoxy(14,27);	printf("[2] Riwayat");
    gotoxy(14,28);	printf("[0] Keluar");

    gotoxy(22,30);	printf("   ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &choose);
    switch(choose){
    	case 1:
    		tambahtransaksi();
    		break;
    	case 2:
    		Lihattransaksi();
    		gotoxy(22,30);	getch();
    		SewaFilm();
    		break;
    	case 0 :
            MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            CleanKiri();
            MenuAdmin();
        	break;
    	default :
            MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            SewaFilm();
        	break;
	}
}

void tambahtransaksi()
{
    FILE *Temp;
	int id;
    int tunai, kembali;
    int found=0, i=0;
    char ans, harga[25];

    gotoxy(138,44);	printf("--0 untuk kembali--");

    arssewaflm = fopen("dat/Transaksi sewafilm.dat", "ab+"); /* buka file transaksi unutk dibaca dan ditambah */
    fread(&sf,sizeof(sf),1,arssewaflm);
    while(!feof(arssewaflm)){
        fread(&sf,sizeof(sf),1,arssewaflm);
        id = sf.idtrns;
        i++;
    }
    if(i==0){
        sf.idtrns = 1;
    }else{
        sf.idtrns = id+1;
    }

	LihatFlm(); /* menampilkan data film */
	gotoxy(134,17);	printf("ID Transaksi = TSF%d", sf.idtrns);

	/* mengambil data film yang akan dibeli */
    gotoxy(146,18); printf("    ");
    gotoxy(134,18);	printf("ID Film = FM");
    fflush(stdin);
    scanf("%d", &sf.idFilm);
    if (sf.idFilm == 0){
        CleanKanan();
        SewaFilm();
    }

    found=0;
    arsflm = fopen("dat/Data Film.dat","rb");
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm) && !found){
        if (flm.id == sf.idFilm){
            found=1;
        }else{
            fread(&flm,sizeof(flm),1,arsflm);
        }
    }
    fclose(arsflm);
    if (found && flm.status == 0){
        sf.hrg = flm.harga;
        strcpy(sf.NamaProduser,flm.produser);
        strcpy(sf.judulFilm,flm.judul);
    } else if (found && flm.status == 1){
        MessageBoxA(NULL,"Film sudah menjadi Hak Milik!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        tambahtransaksi();
    } else {
        MessageBoxA(NULL,"ID Film tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        tambahtransaksi();
    }

	CleanKanan();
    gotoxy(134,17);	printf("ID Transaksi = TSF%d", sf.idtrns);
    gotoxy(134,18);	printf("Judul Film = %s", sf.judulFilm);
    gotoxy(134,19);	printf("Produser = %s", sf.NamaProduser);
    gotoxy(134,20);	rupiah(sf.hrg,harga); printf("Harga Film = Rp %s", harga);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sf.bulan = tm.tm_mon;
    sf.tahun = tm.tm_year + 1900;

    do{
        gotoxy(134,23); printf("Uang Tunai = Rp ");
        fflush(stdin);
        getRp(&tunai,4,9,150,23);
        if(tunai<sf.hrg){
            gotoxy(134,25); printf("Uang Kurang");
            getch();
            gotoxy(134,25); printf("                                 ");
            gotoxy(134,23); printf("                                 ");
        }
    }while(tunai<sf.hrg);

    kembali = tunai-sf.hrg;
    gotoxy(134,24); rupiah(kembali,harga); printf("Kembalian  = Rp %s", harga);
    strcpy(sf.admin,U.Nama);
    gotoxy(134,25);	printf("ADMIN	 = %s",sf.admin);

    sf.hari=tm.tm_mday;
    sf.bulan=tm.tm_mon +1;
    sf.tahun=tm.tm_year + 1900;
    gotoxy(134,26);	printf("Tanggal	 = %02d-%02d-%d", sf.hari, sf.bulan, sf.tahun);

    fwrite(&sf,sizeof(sf),1,arssewaflm);  /* menambahkan kedalam file transaksi */
    fclose(arssewaflm);

    MessageBox(NULL,"Transaksi berhasil!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    /* merubah status film menjadi hak milik */
    Temp = fopen("dat/Temp Data Film.dat","wb");
    arsflm = fopen("dat/Data Film.dat","rb");
    fread(&flm,sizeof(flm),1,arsflm);
    while (!feof(arsflm)){
        if (flm.id == sf.idFilm){
            flm.status = 1;
            fwrite(&flm,sizeof(flm),1,Temp);
        } else {
            fwrite(&flm,sizeof(flm),1,Temp);
        }
        fread(&flm,sizeof(flm),1,arsflm);
    }
    fclose(Temp);
    fclose(arsflm);

    Temp = fopen("dat/Temp Data Film.dat","rb");
    arsflm = fopen("dat/Data Film.dat","wb");
    fread(&flm,sizeof(flm),1,Temp);
    while (!feof(Temp)){
        fwrite(&flm,sizeof(flm),1,arsflm);
        fread(&flm,sizeof(flm),1,Temp);
    }
    fclose(Temp);
    fclose(arsflm);

    do {
        gotoxy(164,28); printf("   ");
        gotoxy(134,28);	printf("Tambah transaksi lagi? [Y/N] : ");
        gotoxy(164,28); scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanTengah();
        	CleanKanan();
            tambahtransaksi();
            break;
        case 'N':
            CleanKanan();
            SewaFilm();
            break;
        }
    } while(toupper(ans) != 'Y' && 'N');
}

void Lihattransaksi(){
	int Baris=16, Kolom=36, Next=0;
	int i=0;
	char harga[25];

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--");

    arssewaflm = fopen("dat/Transaksi sewafilm.dat", "rb"); /* buka file untuk dibaca */
    fread(&sf,sizeof(sf),1,arssewaflm);
    while(!feof(arssewaflm)){
        fread(&sf,sizeof(sf),1,arssewaflm);
        i++;
    }
    fclose(arssewaflm);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");

    if(i==0){
    	MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        SewaFilm();
	}else{
		arssewaflm = fopen("dat/Transaksi sewafilm.dat", "rb");
    	fread(&sf,sizeof(sf),1,arssewaflm);
    	while(!feof(arssewaflm)){
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
    		gotoxy(Kolom+1,Baris);	printf("TSF%d", sf.idtrns);
    		gotoxy(Kolom+8,Baris);	printf("%s", sf.judulFilm);
    		gotoxy(Kolom+30,Baris);	printf("%s", sf.NamaProduser);
    		gotoxy(Kolom+52,Baris);	rupiah(sf.hrg,harga); printf("Rp %s", harga);
    		gotoxy(Kolom+66,Baris);	printf("%02d-%02d-%d",  sf.hari, sf.bulan, sf.tahun);
    		gotoxy(Kolom+80,Baris); printf("%s", sf.admin);
    		if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
                if (Next==52)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
            fread(&sf,sizeof(sf),1,arssewaflm);
		}
	fclose(arssewaflm);
	}
}

void LaporanFilm()
{
    int cekbulan, cektahun, found, choose, total=0;
    int Baris=16, Kolom=36, Next=0;
    char harga[25];

    CleanKiri();
    CleanKanan();
    gotoxy(14,25); printf("[1] Bulanan\n");
    gotoxy(14,26); printf("[2] Tahunan\n");
    gotoxy(14,27); printf("[0] Keluar\n");
    gotoxy(14,29); printf("Pilih : ");
    scanf("%d", &choose);

    switch(choose){
    case 1 :
        CleanKiri();
        gotoxy(14,27); printf("Bulan : "); scanf("%d", &cekbulan);
        gotoxy(14,28); printf("Tahun : "); scanf("%d", &cektahun);

        arssewaflm = fopen("dat/Transaksi sewafilm.dat", "rb");
        fread(&sf,sizeof(sf),1,arssewaflm);
        found = 0;

        while(!feof(arssewaflm) && !found){
            if (cekbulan == sf.bulan && cektahun == sf.tahun){
                found = 1;
            }else{
                fread(&sf,sizeof(sf),1,arssewaflm);
            }
        }

        if (found){
            while(!feof(arssewaflm)){
            if (cekbulan == sf.bulan && cektahun == sf.tahun){
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");

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
                gotoxy(Kolom+1,Baris);	printf("TSF%d", sf.idtrns);
                gotoxy(Kolom+8,Baris);	printf("%s", sf.judulFilm);
                gotoxy(Kolom+30,Baris);	printf("%s", sf.NamaProduser);
                gotoxy(Kolom+52,Baris);	rupiah(sf.hrg,harga); printf("Rp %s", harga);
                gotoxy(Kolom+66,Baris);	printf("%02d-%02d-%d",  sf.hari, sf.bulan, sf.tahun);
                gotoxy(Kolom+80,Baris); printf("%s", sf.admin);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
                if (Next==52)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
                total = total+sf.hrg;
                fread(&sf,sizeof(sf),1,arssewaflm);
            }else{
                fread(&sf,sizeof(sf),1,arssewaflm);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanFilm();
        }
        fclose(arssewaflm);
        gotoxy(135,42); rupiah(total,harga); printf("Total Pemasukan = Rp %s", harga);
        switch(cekbulan){
        case 1 : gotoxy(135,43); printf("Januari %d", cektahun); break;
        case 2 : gotoxy(135,43); printf("Februari %d", cektahun); break;
        case 3 : gotoxy(135,43); printf("Maret %d", cektahun); break;
        case 4 : gotoxy(135,43); printf("April %d", cektahun); break;
        case 5 : gotoxy(135,43); printf("Mei %d", cektahun); break;
        case 6 : gotoxy(135,43); printf("Juni %d", cektahun); break;
        case 7 : gotoxy(135,43); printf("Juli %d", cektahun); break;
        case 8 : gotoxy(135,43); printf("Agustus %d", cektahun); break;
        case 9 : gotoxy(135,43); printf("September %d", cektahun); break;
        case 10 : gotoxy(135,43); printf("Oktober %d", cektahun); break;
        case 11 : gotoxy(135,43); printf("November %d", cektahun); break;
        case 12 : gotoxy(135,43); printf("Desember %d", cektahun); break;
        }
        getch();
        CleanTengah();
        LaporanFilm();
        break;
    case 2 :
        CleanKiri();
        gotoxy(14,27); printf("Tahun : "); scanf("%d", &cektahun);

        arssewaflm = fopen("dat/Transaksi sewafilm.dat", "rb");
        fread(&sf,sizeof(sf),1,arssewaflm);
        found = 0;

        while(!feof(arssewaflm) && !found){
            if (cektahun == sf.tahun){
                found = 1;
            }else{
                fread(&sf,sizeof(sf),1,arssewaflm);
            }
        }

        if (found){
            while(!feof(arssewaflm)){
            if (cektahun == sf.tahun){
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");

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
                gotoxy(Kolom+1,Baris);	printf("TSF%d", sf.idtrns);
                gotoxy(Kolom+8,Baris);	printf("%s", sf.judulFilm);
                gotoxy(Kolom+30,Baris);	printf("%s", sf.NamaProduser);
                gotoxy(Kolom+52,Baris);	rupiah(sf.hrg,harga); printf("Rp %s", harga);
                gotoxy(Kolom+66,Baris);	printf("%02d-%02d-%d",  sf.hari, sf.bulan, sf.tahun);
                gotoxy(Kolom+80,Baris); printf("%s", sf.admin);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
                if (Next==52)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("  ID          Judul\t              Produser\t          Harga\t       Tanggal\t       Admin");
				}
                total = total+sf.hrg;
                fread(&sf,sizeof(sf),1,arssewaflm);
            }else{
                fread(&sf,sizeof(sf),1,arssewaflm);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanFilm();
        }
        fclose(arssewaflm);
        gotoxy(135,42); rupiah(total,harga); printf("Total Pemasukan = Rp %s", harga);
        gotoxy(135,43); printf("Tahun %d", cektahun);
        getch();
        CleanTengah();
        LaporanFilm();
        break;
    case 0 :
        MenuManager();
        break;
    }
}
