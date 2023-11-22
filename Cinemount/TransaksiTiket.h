void TTiket()
{
    int choose;

    CleanKiri();
    CleanTengah();

    gotoxy(17,21);	printf("TRANSAKSI");
	gotoxy(17,22);	printf("BELI TIKET");

    gotoxy(14,26);	printf("[1] Tambah");
    gotoxy(14,27);	printf("[2] Riwayat");
    gotoxy(14,28);	printf("[0] Keluar");

    gotoxy(22,30);	printf("   ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahTrns();
        break;
    case 2 :
        LihatTrns();
    	gotoxy(22,30);	getch();
    	TTiket();
        break;
    case 0 :
        MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        CleanKiri();
        MenuKasir();
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        TTiket();
        break;
    }
}

void TambahTrns()
{
    FILE *Temp;
    int id, tunai, kembali, cekstok, found=0, i=0;
    char ans, uang[25];

    gotoxy(138,44);	printf("--0 untuk kembali--\n\n");

    lihatjdwl(); /* menampilkan jadwal film */

    /* buka file transaksi untuk ditambahkan dan dibaca */
    arstiket = fopen("dat/Transaksi Tiket.dat", "ab+");
    fread(&tik,sizeof(tik),1,arstiket);
    while(!feof(arstiket)){
        fread(&tik,sizeof(tik),1,arstiket);
        id = tik.id;
        i++;
    }
    if(i==0){
        tik.id = 1;
    }else{
        tik.id = id+1;
    }

    gotoxy(134,17);	printf("ID Transaksi = TRN%d", tik.id);

    gotoxy(148,18);	printf("   ");
    gotoxy(134,18);	printf("ID Event = EVN");
    fflush(stdin);
    scanf("%d", &tik.evn);
    if (tik.evn == 0){
    	CleanKanan();
        TTiket();
    }

    /* proses pencarian id jadwal beserta datanya */
    arsjdwl = fopen("dat/Data Jadwal.dat","rb"); /* buka data jadwal untuk dibaca */
    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl) && !found){
        if (jd.idjadwal == tik.evn && jd.status == 3 && jd.stok > 0){ /* mengecek apakah id yg dicari ada dalam data, dengan syarat status aktif dan stok > 0 */
            tik.hrg = jd.harga;
            strcpy(tik.film,jd.judul);
            strcpy(tik.tempat,jd.tempat);
            cekstok = jd.stok;
            found = 1;
        } else if (jd.idjadwal == tik.evn && jd.status < 3 ) { /* jika id yg dicari statusnya tidak aktif */
			MessageBoxA(NULL,"Film tidak tayang!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            TambahTrns();
        } else if (jd.idjadwal == tik.evn && jd.stok <= 0) { /* jika id yg dicari stoknya habis */
			MessageBoxA(NULL,"Tiket sudah habis!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            TambahTrns();
        }
        fread(&jd,sizeof(jd),1,arsjdwl);
    }
    fclose(arsjdwl);

    if (!found){ /* jika id yg dicari tidak ada dalam data */
        gotoxy(134,19);	printf("ID salah!"); getch();
        gotoxy(134,19);	printf("                    ");
        gotoxy(151,18);	printf("   ");
        TambahTrns();
    }

    gotoxy(134,17);	printf("ID Transaksi = TRN%d\n", tik.id);
    gotoxy(134,18);	printf("ID Event = EVN%d\n", tik.evn);
    gotoxy(134,19);	printf("Judul Film = %s\n", tik.film);
    gotoxy(134,20);	printf("Tempat = %s\n", tik.tempat);
    gotoxy(134,21);	rupiah(tik.hrg,uang); printf("Harga = Rp %s\n", uang);

    do {
        gotoxy(138,44);	printf("--999 untuk kembali--\n\n");
        gotoxy(148,22);	printf("       ");
        gotoxy(134,22);	printf("Banyak Tiket = ");
        fflush(stdin);
        scanf("%d", &tik.qty);
        if(tik.qty == 999){
            CleanKanan();
            TambahTrns();
        }

        if(tik.qty == 0){
			gotoxy(134,23);	printf("Input Tidak Boleh Kosong!\n");
			getch();
			gotoxy(134,23);	printf("                             ");
        	gotoxy(148,22);	printf("   ");
        }else if(tik.qty>cekstok){				/* jika jumlah yg dibeli lebih banyak dari jumlah stok */
            gotoxy(134,23);	printf("Tiket Tidak Mencukupi!\n");
            getch();
            gotoxy(134,23);	printf("                             ");
        	gotoxy(148,22);	printf("   ");
        }
    } while (tik.qty>cekstok || tik.qty == 0);

    tik.total = tik.hrg*tik.qty;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tmk.bulan = tm.tm_mon;
    tmk.tahun = tm.tm_year + 1900;
    tik.hari=tm.tm_mday;
    tik.bulan=tm.tm_mon + 1;
    tik.tahun=tm.tm_year + 1900;

    gotoxy(134,23);	rupiah(tik.total,uang); printf("Total Harga = Rp %s\n", uang);

    do {
        gotoxy(134,25);	printf("Uang Tunai = Rp ");
        fflush(stdin);
        getRp(&tunai,4,9,150,25);

        if(tunai<tik.total){
            gotoxy(134,26);	printf("Uang kurang\n");
            getch();
            gotoxy(134,26);	printf("                         ");
            gotoxy(134,25);	printf("                   ");
        }
    } while (tunai<tik.total);

    gotoxy(134,26);	rupiah(kembali,uang); printf("Kembalian  = %s\n", uang);

    strcpy(tik.kasir,U.Nama);
    gotoxy(134,27);	printf("KASIR	 = %s",tik.kasir);

	gotoxy(134,28);	printf("Tanggal	 = %02d-%02d-%d",  tik.hari, tik.bulan, tik.tahun);
    kembali = tunai-tik.total;

    fwrite(&tik,sizeof(tik),1,arstiket); /* menambahkan kedalam file transaksi */
    fclose(arstiket);

    MessageBox(NULL,"Transaksi tiket berhasil!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    /* proses pengurangan stok tiket */
    arsjdwl = fopen("dat/Data Jadwal.dat","rb"); /* buka file jadwal untuk dibaca */
    Temp  = fopen ("dat/tempjadwal.dat","wb"); /* buka file temp untuk ditulis */
    fread(&jd,sizeof(jd),1,arsjdwl);
    while(!feof(arsjdwl)){
        if(tik.evn==jd.idjadwal){
            jd.stok = jd.stok-tik.qty;
            fwrite(&jd,sizeof(jd),1,Temp);
        }else{
            fwrite(&jd,sizeof(jd),1,Temp);
        }
        fread(&jd,sizeof(jd),1,arsjdwl);
    }
    fclose(arsjdwl);
    fclose(Temp);

    /* memindahkan dari temp ke file data jadwal */
    //remove("dat/Data Jadwal.dat");
    //rename("dat/tempjadwal.dat","dat/Data Jadwal.dat");

    arsjdwl = fopen("dat/Data Jadwal.dat","wb"); /* buka file jadwal untuk dibaca */
    Temp  = fopen ("dat/tempjadwal.dat","rb"); /* buka file temp untuk ditulis */

    fread(&jd,sizeof(jd),1,Temp);
     while(!feof(Temp)){
            fwrite(&jd,sizeof(jd),1,arsjdwl);
            fread(&jd,sizeof(jd),1,Temp);
    }
    fclose(arsjdwl);
    fclose(Temp);

    do {
        gotoxy(164,30); printf("   ");
        gotoxy(134,30);	printf("Tambah transaksi lagi? [Y/N] : ");
        gotoxy(164,30); scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanTengah();
        	CleanKanan();
            TambahTrns();
            break;
        case 'N':
            CleanKanan();
            TTiket();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void LihatTrns()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;
    char uang[25];

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--\n\n");

    /* buka file transaksi untuk dibaca */
    arstiket = fopen("dat/Transaksi Tiket.dat", "rb");
    fread(&tik,sizeof(tik),1,arstiket);
    while(!feof(arstiket)){
        fread(&tik,sizeof(tik),1,arstiket);
        i++;
    }
    fclose(arstiket);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk melakukan transaksi!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        TTiket();
    }else{
        /* buka file transaksi untuk dibaca */
        arstiket = fopen("dat/Transaksi Tiket.dat","rb");
        fread(&tik,sizeof(tik),1,arstiket);
        while(!feof(arstiket)){
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
            gotoxy(Kolom+1,Baris);	printf("TRN%d\n", tik.id);
            gotoxy(Kolom+8,Baris);	printf("%s",tik.film);
            gotoxy(Kolom+30,Baris);	printf("%s",tik.tempat);
            gotoxy(Kolom+48,Baris);	printf("%d", tik.qty);
            gotoxy(Kolom+54,Baris);	rupiah(tik.total,uang); printf("Rp %s", uang);
            gotoxy(Kolom+68,Baris);	printf("%02d-%02d-%d",  tik.hari, tik.bulan, tik.tahun);
            gotoxy(Kolom+82,Baris); printf("%s",tik.kasir);
            if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
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
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
				}
            fread(&tik,sizeof(tik),1,arstiket);
        }
        fclose(arstiket);
    }
}

void LaporanTiket()
{
    int cekbulan, cektahun, found=0, choose, total=0;
    int Baris=16, Kolom=36, Next=0;
    char uang[25];

    CleanKiri();

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

        /* buka file transaksi untuk dibaca */
        arstiket = fopen("dat/Transaksi Tiket.dat", "rb");
        fread(&tik,sizeof(tik),1,arstiket);
        while(!feof(arstiket) && !found){
            if (cekbulan == tik.bulan && cektahun == tik.tahun){ /* mengecek apakah tanggal transaksi yang sesuai ada dalam file */
                found = 1;
            }else{
                fread(&tik,sizeof(tik),1,arstiket);
            }
        }

        if (found){
            while(!feof(arstiket)){
            if (cekbulan == tik.bulan && cektahun == tik.tahun){ /* hanya menampilkan sesuai tanggal yg dicari */
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");

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
                gotoxy(Kolom+1,Baris);	printf("TRN%d\n", tik.id);
                gotoxy(Kolom+8,Baris);	printf("%s",tik.film);
                gotoxy(Kolom+30,Baris);	printf("%s",tik.tempat);
                gotoxy(Kolom+48,Baris);	printf("%d", tik.qty);
                gotoxy(Kolom+54,Baris);	rupiah(tik.total,uang); printf("Rp %s", uang);
                gotoxy(Kolom+68,Baris);	printf("%02d-%02d-%d",  tik.hari, tik.bulan, tik.tahun);
                gotoxy(Kolom+82,Baris); printf("%s",tik.kasir);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
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
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
				}
				total = total+tik.total;
                fread(&tik,sizeof(tik),1,arstiket);
            }else{
                fread(&tik,sizeof(tik),1,arstiket);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanTiket();
        }
        fclose(arstiket);
        gotoxy(135,42); rupiah(total,uang); printf("Total Pemasukan = Rp %s", uang);

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
        CleanKanan();
        LaporanTiket();
        break;
    case 2 :
        CleanKiri();
        gotoxy(14,27); printf("Tahun : "); scanf("%d", &cektahun);

        /* buka file transaksi untuk dibaca */
        arstiket = fopen("dat/Transaksi Tiket.dat", "rb");
        fread(&tik,sizeof(tik),1,arstiket);
        while(!feof(arstiket) && !found){
            if (cektahun == tik.tahun){ /* mengecek apakah transaksi pd tahun yg dicari ada dalam file */
                found = 1;
            }else{
                fread(&tik,sizeof(tik),1,arstiket);
            }
        }

        if (found){
            while(!feof(arstiket)){
            if (cektahun == tik.tahun){ /* hanya menampilkan transaksi pada tahun yg dicari */
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");

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
                gotoxy(Kolom+1,Baris);	printf("TRN%d\n", tik.id);
                gotoxy(Kolom+8,Baris);	printf("%s",tik.film);
                gotoxy(Kolom+30,Baris);	printf("%s",tik.tempat);
                gotoxy(Kolom+48,Baris);	printf("%d", tik.qty);
                gotoxy(Kolom+54,Baris);	rupiah(tik.total,uang); printf("Rp %s", uang);
                gotoxy(Kolom+68,Baris);	printf("%02d-%02d-%d",  tik.hari, tik.bulan, tik.tahun);
                gotoxy(Kolom+82,Baris); printf("%s",tik.kasir);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
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
					gotoxy(Kolom,15); printf("  ID            Film               Tempat      Qty       Total       Tanggal        Kasir");
				}
				total = total+tik.total;
                fread(&tik,sizeof(tik),1,arstiket);
            }else{
                fread(&tik,sizeof(tik),1,arstiket);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanTiket();
        }
        fclose(arstiket);
        gotoxy(135,42); rupiah(total,uang); printf("Total Pemasukan = Rp %s", uang);
        gotoxy(135,43); printf("Tahun %d", cektahun);
        getch();
        CleanTengah();
        CleanKanan();
        LaporanTiket();
        break;
    case 0 :
        Pemasukan();
        break;
    }
}
