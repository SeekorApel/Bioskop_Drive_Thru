void TransaksiMakanan()
{
    int choose;

    remove("dat/Temp Transaksi Makanan.dat");

    CleanKiri();
    CleanTengah();

    gotoxy(17,21);	printf("TRANSAKSI");
	gotoxy(18,22);	printf("MAKANAN");

    gotoxy(14,26);	printf("[1] Tambah");
    gotoxy(14,27);	printf("[2] Riwayat");
    gotoxy(14,28);	printf("[3] Detail");
    gotoxy(14,29);	printf("[0] Keluar");

    gotoxy(22,31);	printf("  ");
    gotoxy(14,31);	printf("Pilih : ");
    gotoxy(22,31);	scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahTMakan();
        break;
    case 2 :
        LihatTMakan();
        gotoxy(22,31);	getch();
        TransaksiMakanan();
        break;
    case 3 :
        LihatDetail();
        gotoxy(22,31);	getch();
        CleanKanan();
        TransaksiMakanan();
        break;
    case 0 :
        CleanKiri();
        MenuKasir();
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        TransaksiMakanan();
        break;
    }
}

void TambahTMakan()
{
    int found=0, cekstok, tunai, kembali, id, i=0;
    char ans;

    total = 0;

    arskrj = fopen ("dat/Keranjang.dat", "wb");
    fclose(arskrj);

    LihatMK(); /* menampilkan menu makanan */
    gotoxy(138,44);	printf("--0 untuk kembali--");
    tmk.total = 0;

    /* buka file transaksi untuk dibaca (id otomatis) */
    arstmk = fopen("dat/Transaksi Makanan.dat", "rb");
    fread(&tmk,sizeof(tmk),1,arstmk);

    while(!feof(arstmk)){
        fread(&tmk,sizeof(tmk),1,arstmk);
        id = tmk.id;
        i++;
    }
    if(i==0){
        tmk.id = 1;
    }else{
        tmk.id = id+1;
    }
    fclose(arstmk); /* tutup file setelah dibaca */

    gotoxy(134,17);	printf("ID Transaksi = TRM%d", tmk.id);

    TambahDetailMK(); /* prosedur tambah item makanan */
}

void TambahDetailMK()
{
    FILE *Temp;
    int found=0, cekstok;
    char ans, uang[25];
    int Baris=32, Kolom=134;

    dtmk.idtrm = tmk.id; /* id trm menjadi FK karna masih dalam transaksi yg sama */

    gotoxy(134,17);	printf("ID Transaksi = TRM%d", dtmk.idtrm);
    gotoxy(149,18);	printf("   ");
    gotoxy(134,18);	printf("ID Makanan = MK");
    fflush(stdin);
    scanf("%d", &dtmk.idmkn);
    if (dtmk.idmkn == 0){
    	CleanKanan();
        TransaksiMakanan();
    }

    /* buka file makanan untuk melihat data makanan */
    arsmk = fopen("dat/Data Makanan.dat","rb");
    fread(&mk,sizeof(mk),1,arsmk);

    while(!feof(arsmk) && !found){
        if (dtmk.idmkn == mk.id){
            strcpy(dtmk.desk,mk.nama);
            dtmk.harga = mk.harga;
            cekstok = mk.stok;
            found = 1;
        }
        fread(&mk,sizeof(mk),1,arsmk);
    }
    fclose(arsmk);

    if (!found){
        MessageBoxA(NULL,"ID Makanan tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        TambahTMakan();
    }

    CleanKanan();

    gotoxy(134,17);	printf("ID Transaksi = TRM%d", tmk.id);
    gotoxy(134,18);	printf("Deskripsi Makanan = %s", dtmk.desk);
    gotoxy(134,19);	rupiah(dtmk.harga,uang); printf("Harga = Rp %s", uang);

    do {
        gotoxy(147,20);	printf("             ");
        gotoxy(134,20);	printf("Banyak item = ");
        fflush(stdin);
        gotoxy(148,20);	scanf("%d", &dtmk.qty);

        if(dtmk.qty <= 0){
			CleanTengah();
			CleanKanan();
			TambahTMakan();
        }else if(dtmk.qty > cekstok){				//jika jumlah yg dibeli lebih banyak dari jumlah stock
			MessageBoxA(NULL,"Stok Tidak Mencukupi","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        }
    } while (dtmk.qty>cekstok);

    dtmk.subtotal = dtmk.qty * dtmk.harga;
    gotoxy(134,21); rupiah(dtmk.subtotal,uang); printf("Subtotal = Rp %s\n", uang);

    total = total + dtmk.subtotal;
    gotoxy(134,22);	rupiah(total,uang); printf("Total Harga = Rp %s", uang);

    strcpy(krj.nama,dtmk.desk);
    krj.qty = dtmk.qty;

    /* buka file untuk menambah data */
    arsdetail = fopen("dat/Detail Makanan.dat","ab");
    fwrite(&dtmk,sizeof(dtmk),1,arsdetail);
    fclose(arsdetail);

    /* proses pengurangan stok */
    arsmk = fopen("dat/Data Makanan.dat","rb");
    Temp  = fopen ("dat/Temp Data Makanan.dat","wb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        if(dtmk.idmkn == mk.id){
            mk.stok = mk.stok-dtmk.qty;
            fwrite(&mk,sizeof(mk),1,Temp);
        }else{
            fwrite(&mk,sizeof(mk),1,Temp);
        }
        fread(&mk,sizeof(mk),1,arsmk);
    }
    fclose(arsmk);
    fclose(Temp);

    /* mengganti data makanan terbaru */
    remove("dat/Data Makanan.dat");
    rename("dat/Temp Data Makanan.dat","dat/Data Makanan.dat");

    gotoxy(134,32); printf("Keranjang Makanan");

    arskrj = fopen ("dat/Keranjang.dat", "ab");
    fwrite(&krj,sizeof(krj),1,arskrj);
    fclose(arskrj);

    arskrj = fopen ("dat/Keranjang.dat", "rb");
    fread(&krj,sizeof(krj),1,arskrj);
    while(!feof(arskrj)){
        Baris++;
        if(Baris%2==0)
        {
            gotoxy(Kolom,Baris);
        }
        else
        {
            gotoxy(Kolom,Baris);
        }
        gotoxy(Kolom+1,Baris); printf("- %s X %d\n", krj.nama,krj.qty);
        fread(&krj,sizeof(krj),1,arskrj);
    }
    fclose(arskrj);

    do {
        gotoxy(157,23); printf("   ");
        gotoxy(134,23); printf("Tambah item lagi? [Y/N] ");
        gotoxy(157,23); scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y' :
            CleanKanan();
            TambahDetailMK();
            break;
        case 'N' :
            tmk.total = total;
            BayarMK();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void BayarMK()
{
    int tunai, kembali;
    char ans, uang[25];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    tmk.bulan = tm.tm_mon;
    tmk.tahun = tm.tm_year + 1900;

    gotoxy(150,25);	printf("              ");
    gotoxy(134,25);	printf("Uang Tunai = Rp ");
    fflush(stdin);
    getRp(&tunai,4,9,150,25);

    while (tunai<tmk.total){ /* perulangan jika uang tunai kurang dari total */
        gotoxy(134,26);	printf("Uang kurang");
        getch();
        gotoxy(134,26);	printf("              ");
        gotoxy(150,25);	printf("              ");
        gotoxy(134,25);	printf("Uang Tunai = Rp ");
        fflush(stdin);
        getRp(&tunai,4,9,150,25);
    }

    kembali = tunai-tmk.total;

    gotoxy(134,26);	rupiah(kembali,uang); printf("Kembalian  = Rp %s", uang);

    strcpy(tmk.kasir,U.Nama);
    gotoxy(134,27);	printf("KASIR	 = %s",tmk.kasir);

    tmk.hari=tm.tm_mday;
    tmk.bulan=tm.tm_mon + 1;
    tmk.tahun=tm.tm_year + 1900;
    gotoxy(134,28);	printf("Tanggal	 = %02d-%02d-%d",  tmk.hari, tmk.bulan, tmk.tahun);

    arstmk = fopen("dat/Transaksi Makanan.dat", "ab");
    fwrite(&tmk,sizeof(tmk),1,arstmk);
    fclose(arstmk);

    MessageBox(NULL,"Transaksi berhasil!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(164,30); printf("   ");
        gotoxy(134,30);	printf("Tambah transaksi lagi? [Y/N] : ");
        gotoxy(164,30); scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
        	CleanTengah();
        	CleanKanan();
            TambahTMakan();
            break;
        case 'N':
            CleanKanan();
            TransaksiMakanan();
            break;
        }
    } while (toupper(ans) != 'Y' && 'N'); /* lakukan perulangan selama jawaban bukan Y atau N */
}

void LihatTMakan()
{
	int Baris=16, Kolom=36, Next=0;
    int i=0;
    char uang[25];

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--\n\n");

    /* buka file transaksi untuk dibaca */
    arstmk = fopen("dat/Transaksi Makanan.dat", "rb");
    fread(&tmk,sizeof(tmk),1,arstmk);

    while(!feof(arstmk)){
        fread(&tmk,sizeof(tmk),1,arstmk);
        i++;
    }
    fclose(arstmk);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        TransaksiMakanan();
    }else{
        /* buka file transaksi untuk dibaca */
        arstmk = fopen("dat/Transaksi Makanan.dat","rb");
        fread(&tmk,sizeof(tmk),1,arstmk);
        while(!feof(arstmk)){
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
            gotoxy(Kolom+14,Baris);	 printf("TRM%d",tmk.id);
            gotoxy(Kolom+30,Baris);	 rupiah (tmk.total,uang); printf("Rp %s",uang);
            gotoxy(Kolom+49,Baris);	 printf("%02d-%02d-%d", tmk.hari,tmk.bulan,tmk.tahun);
            gotoxy(Kolom+69,Baris);	 printf("%s",tmk.kasir);
            fread(&tmk,sizeof(tmk),1,arstmk);
        }
        fclose(arstmk);
    }
}

void LihatDetail()
{
    int Baris=16, Kolom=36, Next=0;
    int cekId=0, found=0;
    char uang[25];

    LihatTMakan(); /* menampilkan transaksi makanan */

    gotoxy(134,17); printf("Lihat detail");
    gotoxy(134,18); printf("ID Transaksi = TRM");
    fflush(stdin);
    scanf("%d", &cekId);

    /* buka file detail untuk dibaca */
    arsdetail = fopen ("dat/Detail Makanan.dat", "rb");
    fread(&dtmk,sizeof(dtmk),1,arsdetail);
    while(!feof(arsdetail) && !found){
        if (cekId == dtmk.idtrm){ /* mengecek apakah id yang dicari ada dalam id transaksi */
            found = 1;
        }
        fread(&dtmk,sizeof(dtmk),1,arsdetail);
    }
    fclose(arsdetail);

    if (!found){
        MessageBoxA(NULL,"ID Transaksi tidak ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        CleanKanan();
        LihatDetail();
    }

    CleanTengah();

    gotoxy(75,44);	printf("--Klik apapun untuk kembali--\n\n");

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}
	gotoxy(36,15);printf("\t\tID_TRM     ID_MK            Deskripsi           Qty          Subtotal");

    /* buka file untuk dibaca */
    arsdetail = fopen("dat/Detail Makanan.dat","rb");
    fread(&dtmk,sizeof(dtmk),1,arsdetail);
    while(!feof(arsdetail)){
    if (cekId == dtmk.idtrm){ /* munculkan data yang id nya sesuai saja */
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
            gotoxy(Kolom+13,Baris);	 printf("TRM%d", dtmk.idtrm);
            gotoxy(Kolom+24,Baris);	 printf("MK%d", dtmk.idmkn);
            gotoxy(Kolom+38,Baris);	 printf("%s", dtmk.desk);
            gotoxy(Kolom+61,Baris);	 printf("%d", dtmk.qty);
            gotoxy(Kolom+72,Baris);	rupiah(dtmk.subtotal,uang); printf("Rp %s",uang);
        }
    fread(&dtmk,sizeof(dtmk),1,arsdetail);
    }
    fclose(arsdetail);
}

void LaporanMakanan()
{
    int cekbulan, cektahun, found=0, choose;
    int Baris=16, Kolom=36, Next=0;
    char uang[25];

    total = 0;

    CleanKanan();
    CleanKiri();

    gotoxy(14,25); printf("[1] Bulanan\n");
    gotoxy(14,26); printf("[2] Tahunan\n");
    gotoxy(14,27); printf("[3] Detail\n");
    gotoxy(14,28); printf("[0] Keluar\n");
    gotoxy(14,30); printf("Pilih : ");
    scanf("%d", &choose);

    switch(choose){
    case 1 :
        CleanKiri();
        gotoxy(14,27); printf("Bulan : "); scanf("%d", &cekbulan);
        gotoxy(14,28); printf("Tahun : "); scanf("%d", &cektahun);

        /* buka file transaksi untuk dibaca */
        arstmk = fopen("dat/Transaksi Makanan.dat", "rb");
        fread(&tmk,sizeof(tmk),1,arstmk);
        while(!feof(arstmk) && !found){
            if (cekbulan == tmk.bulan && cektahun == tmk.tahun){ /* cek apakah dalam bulan yg dicari terdapat transaksi */
                found = 1;
            }else{
                fread(&tmk,sizeof(tmk),1,arstmk);
            }
        }

        if (found){
            while(!feof(arstmk)){
            if (cekbulan == tmk.bulan && cektahun == tmk.tahun){ /* tampilkan data hanya dalam bulan & tahun yang dicari */
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");

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
                gotoxy(Kolom+14,Baris);	 printf("TRM%d",tmk.id);
                gotoxy(Kolom+30,Baris);	 rupiah (tmk.total,uang); printf("Rp %s",uang);
                gotoxy(Kolom+49,Baris);	 printf("%02d-%02d-%d", tmk.hari,tmk.bulan,tmk.tahun);
                gotoxy(Kolom+69,Baris);	 printf("%s",tmk.kasir);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");
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
					gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");
				}
                total = total+tmk.total;
                fread(&tmk,sizeof(tmk),1,arstmk);
            }else{
                fread(&tmk,sizeof(tmk),1,arstmk);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanMakanan();
        }
        fclose(arstmk);
        gotoxy(135,42); rupiah(total,uang); printf("Total Pemasukan = Rp %s", uang);

        /* merubah input bulan (integer) */
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
        LaporanMakanan();
        break;
    case 2 :
        CleanKiri();
        gotoxy(14,27); printf("Tahun : "); scanf("%d", &cektahun);

        /* buka file transaksi untuk dibaca */
        arstmk = fopen("dat/Transaksi Makanan.dat", "rb");
        fread(&tmk,sizeof(tmk),1,arstmk);
        while(!feof(arstmk) && !found){
            if (cektahun == tmk.tahun){
                found = 1;
            }else{
                fread(&tmk,sizeof(tmk),1,arstmk);
            }
        }

        if (found){
            while(!feof(arstmk)){
            if (cektahun == tmk.tahun){ /* tampilkan data hanya dalam tahun yang dicari */
                for (x=Kolom; x<=131; x++)
                {
                    gotoxy(x,14);printf("%c",205);
                    gotoxy(x,16);printf("%c",205);
                }

                gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");

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
                gotoxy(Kolom+14,Baris);	 printf("TRM%d",tmk.id);
                gotoxy(Kolom+30,Baris);	 rupiah (tmk.total,uang); printf("Rp %s",uang);
                gotoxy(Kolom+49,Baris);	 printf("%02d-%02d-%d", tmk.hari,tmk.bulan,tmk.tahun);
                gotoxy(Kolom+69,Baris);	 printf("%s",tmk.kasir);
                if (Next==26)
				{
					gotoxy(75,44); printf("Enter untuk Pindah Halaman... "); getch();
					Kolom=36; Baris=16; Next=0; CleanTengah();
					for (x=Kolom; x<=131; x++)
					{

						gotoxy(x,14);printf("%c",205);
						gotoxy(x,16);printf("%c",205);
					}
					gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");
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
					gotoxy(36,15);printf("\t\t ID_TRM             Total              Tanggal             Kasir");
				}
                total = total+tmk.total;
                fread(&tmk,sizeof(tmk),1,arstmk);
            }else{
                fread(&tmk,sizeof(tmk),1,arstmk);
            }
            }
        }else{
                gotoxy(70,25); printf("--- TIDAK ADA TRANSAKSI ---");
                getch();
                CleanTengah();
                LaporanMakanan();
            }
        fclose(arstmk);

        gotoxy(135,42); rupiah(total,uang); printf("Total Pemasukan = Rp %s", uang);
        gotoxy(135,43); printf("Tahun %d", cektahun);
        getch();
        CleanTengah();
        LaporanMakanan();
        break;
    case 3 :
        LihatDetail();
        gotoxy(22,31);	getch();
        CleanKanan();
        CleanTengah();
        LaporanMakanan();
    case 0 :
        Pemasukan();
        break;
    }
}
