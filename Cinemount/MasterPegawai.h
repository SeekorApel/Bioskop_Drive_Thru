void Lihatdata();
void Tambahuser();
void Role();
void Updatedata();
void hapusdata();

void MenuMasterPegawai()
{
    remove("dat/usertemp.dat");

	int pilih;

	CleanKiri();
	CleanTengah();

    gotoxy(14,22);	printf("MASTER PEGAWAI");

	gotoxy(14,25);	printf("[1] Tambah User\n");
    gotoxy(14,26);	printf("[2] Lihat User\n");
    gotoxy(14,27);	printf("[3] Update User\n");
    gotoxy(14,28);	printf("[4] Hapus User\n");
    gotoxy(14,29);	printf("[5] Keluar\n");
    back1:
    gotoxy(22,30);	printf("    ");
    gotoxy(14,30);	printf("Pilih : ");
    gotoxy(22,30);	scanf("%d", &pilih);

    switch(pilih){
        case 1:
            Tambahuser();
            break;
        case 2:
            Lihatdata();
            gotoxy(22,30);	getch();
            MenuMasterPegawai();
            break;
        case 3:
            Updatedata();
            break;
        case 4:
            hapusdata();
            break;
        case 5:
        	CleanKiri();
        	MenuAdmin();
            break;
        default:
            MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
            MenuMasterPegawai();
            break;
	}
}

void Tambahuser()
{
    gotoxy(80,44);	printf("Tambah User\n");

    char answer;
    char ans;
    int id,loop = 0, found = 0;
    FILE *ek;

	Lihatdata(); /* Menampilkan data pegawai */

    gotoxy(134,44);	printf("Untuk kembali, ketik '0'");

    ek = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    fread(&U, sizeof(U),1,ek);
    while(!feof(ek)){
    	fread(&U,sizeof(U),1,ek);
        id = U.No;
        loop++;
	}
	if(loop == 0){
		U.No = 1;
	}else{
		U.No = id+1; /* id otomatis */
	}
	fclose(ek);

	/* ***********ID Pegawai********** */
    gotoxy(134,17);	printf("ID Pegawai = PG%d\n",U.No);

    /* **********Nama********* */
    gotoxy(134,18);printf("Nama Lengkap = ");
    fflush(stdin);
    gets(U.Nama);
    if(!strcmp(U.Nama,"0")){
    	CleanKanan();
        MenuMasterPegawai();
    }

    U.Nama[0] = toupper(U.Nama[0]);

	/* ************Username*********** */
    gotoxy(134,19);	printf("Username = ");
    fflush(stdin);
    scanf("%s",&U.Username); /* tidak dapat menggunakan spasi */
    if(!strcmp(U.Username, "0")){
    	CleanKanan();
        MenuMasterPegawai();
    }

    /* username tidak boleh sama */
    ek = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    fread(&Unew, sizeof(Unew),1,ek);
    while(!feof(ek) && !found){
        if (strcmp(Unew.Username,U.Username)==0){ /* pemgecekan kondisi jika username sudah digunakan */
            found = 1;
        }else{
            fread(&Unew,sizeof(Unew),1,ek);
        }
	}
    fclose(ek);
    if (found){
        CleanKanan();
        MessageBox(NULL,"Username sudah digunakan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        Tambahuser();
    }

    /* ************Password*********** */
    gotoxy(134,20);	printf("Password = ");
    fflush(stdin);
    takePassword(U.Password);
    if(!strcmp(U.Password, "0")){
    	CleanKanan();
        MenuMasterPegawai();
    }
    printf("\n");

    /* ************No Telp*********** */
    gotoxy(134,21);	printf("No Telp = ");
    fflush(stdin);
    scanf("%s", &U.Tlpn);
    if(!strcmp(U.Tlpn, "0")){
    	CleanKanan();
        MenuMasterPegawai();
    }

    /* ************Tanggal Lahir*********** */
    gotoxy(134,22);	printf("Tanggal Lahir =   -  -    ");
    fflush(stdin);
    gotoxy(150,22); scanf("%02d",&U.hari);
    if(U.hari == 0){
    	CleanKanan();
        MenuMasterPegawai();
    }
    gotoxy(153,22); scanf("%02d",&U.bulan);
    if(U.bulan == 0){
    	CleanKanan();
        MenuMasterPegawai();
    }
    gotoxy(156,22); scanf("%d",&U.tahun);
    if(U.tahun == 0){
    	CleanKanan();
        MenuMasterPegawai();
    }

    /* ************Role*********** */
    Role();

    ek = fopen("dat/user.dat","ab"); /* buka file user untuk ditambahkan */
    fwrite(&U, sizeof(U),1,ek);
    fclose(ek);

    MessageBox(NULL,"Data Berhasil Ditambahkan!","NOTIFICATION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        gotoxy(158,28); printf("    ");
        gotoxy(134,28); printf("Tambah data lagi? [Y/N]: ");
        scanf("%s",&ans);

        switch(toupper(ans)){
            case 'Y':
                CleanKanan();
                Tambahuser();
                break;
            case 'N':
                CleanKanan();
                MenuMasterPegawai();
                break;
        }
    } while (toupper(ans) != 'Y' && 'N');
}

void Role()
{
    gotoxy(134,23);	printf("[1] Kasir");
    gotoxy(134,24);	printf("[2] Admin");
    gotoxy(134,25);	printf("[3] Manager");

    do {
        gotoxy(147,26);	printf("    ");
        gotoxy(134,26);	printf("Pilih Role = ");
        fflush(stdin);
        gotoxy(147,26);	scanf("%d",&U.Role);
        if (U.Role == 0){
            CleanKanan();
            MenuMasterPegawai();
        }
    } while (U.Role != 1 && U.Role != 2 && U.Role != 3);
}

void URole()
{
    gotoxy(134,29);	printf("[1] Kasir");
    gotoxy(134,30);	printf("[2] Admin");
    gotoxy(134,31);	printf("[3] Manager");

    do {
        gotoxy(147,32);	printf("    ");
        gotoxy(134,32);	printf("Pilih Role = ");
        fflush(stdin);
        gotoxy(147,32);	scanf("%d",&U.Role);
        if (U.Role == 0){
            CleanKanan();
            CleanTengah();
            Updatedata();
        }
    } while (U.Role != 1 && U.Role != 2 && U.Role != 3);
}

void Lihatdata()
{
	int Baris=16, Kolom=36, Next=0;
    int loop = 0;
    FILE *lihat;

    gotoxy(80,44);	printf("Lihat user\n");

    lihat = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    fread(&U,sizeof(U),1,lihat);
    while(!feof(lihat)){
    	fread(&U,sizeof(U),1,lihat);
    	loop++;
    }
    fclose(lihat);

    for (x=Kolom; x<=131; x++)
	{
		gotoxy(x,14);printf("%c",205);
		gotoxy(x,16);printf("%c",205);
	}

	gotoxy(36,15);printf("   ID\t      Nama Lengkap\t         Telepon\t      TTL\t        Role\t");

    if(loop == 0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMasterPegawai();
    }else{
    	lihat = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    	fread(&U,sizeof(U),1,lihat);

    	while(!feof(lihat)){
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
            gotoxy(Kolom+3,Baris);	printf("PG%d",U.No);
            fflush(stdin);
            gotoxy(Kolom+12,Baris);  printf("%s",U.Nama);
            fflush(stdin);
            gotoxy(Kolom+42,Baris);  printf("%s",U.Tlpn);
            fflush(stdin);
            gotoxy(Kolom+63,Baris);    printf("%02d-%02d-%d",U.hari,U.bulan,U.tahun);
            fflush(stdin);
            switch(U.Role){
                case 1 :
                    gotoxy(Kolom+82,Baris);    printf("Kasir"); break;
                case 2 :
                    gotoxy(Kolom+82,Baris);    printf("Admin"); break;
                case 3 :
                    gotoxy(Kolom+82,Baris);    printf("Manager"); break;
            }
            fread(&U,sizeof(U),1,lihat);
    	}
    	fclose(lihat);
    }
}

void Updatedata()
{
    FILE *ek, *ft;
    int found=0;
    int pilih,loop = 0,id,row,idupdate;
    char answer;
    char ans;

    gotoxy(80,44);	printf("Edit user\n");
    gotoxy(134,44);	printf("Untuk kembali, ketik '0'\n");

    ek = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    fread(&U,sizeof(U),1,ek);
    while(!feof(ek)){
    	fread(&U, sizeof(U),1,ek);
        loop++;
	}
	fclose(ek);
	if(loop == 0){
		MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMasterPegawai();
	}

	Lihatdata(); /* menampilkan data pegawai */

	gotoxy(134,15);	printf("ID Pegawai = PG");
    scanf("%d",&idupdate);

    gotoxy(134,44);	printf("                         ");
    if(idupdate == 0){
    	CleanKanan();
        MenuMasterPegawai();
    }

    ek = fopen("dat/user.dat","rb"); /* buka file user untuk dibaca */
    ft = fopen("dat/usertemp.dat","wb"); /* buka file temp untuk ditulis */
    fread(&U,sizeof(U),1,ek);
    while(!found && !feof(ek)){
        if(U.No == idupdate){ /* pengecekan kondisi jika id update sama dengan id dalam data */
            found = 1;
            break;
        }else{
            fwrite(&U,sizeof(U),1,ft); /* menulis id yang bukan dicari kedalam temp */
        }
        fread(&U,sizeof(U),1,ek);
	}

	if(found){
		CleanTengah();
		DesainUbahData();
    	gotoxy(63,26);	printf("ID Pegawai	= PG%d",U.No);
        gotoxy(63,27);	printf("Nama        	= %s",U.Nama);
        gotoxy(63,28);	printf("Username		= %s",U.Username);
        gotoxy(63,29);	printf("Password		= %s",U.Password);
        gotoxy(63,30);	printf("Nomor Telphone	= %s",U.Tlpn);
        gotoxy(63,31);	printf("Tanggal lahir	= %02d-%02d-%d",U.hari,U.bulan,U.tahun);
        switch(U.Role){
            case 1 :
                gotoxy(63,32);    printf("Role		= Kasir"); break;
            case 2 :
                gotoxy(63,32);    printf("Role		= Admin"); break;
            case 3 :
                gotoxy(63,32);    printf("Role		= Manager"); break;
        }

        gotoxy(134,17);	printf("Pilih yang akan diupdate : ");
        gotoxy(134,19);	printf("[1] Nama user \n");
        gotoxy(134,20);	printf("[2] Password \n");
        gotoxy(134,21);	printf("[3] Nomor Telphone \n");
        gotoxy(134,22);	printf("[4] Tanggal lahir \n");
        gotoxy(134,23);	printf("[5] Role \n");
        gotoxy(134,24);	printf("[0] Keluar \n");

        do {
            gotoxy(141,26); printf("     ");
            gotoxy(134,26);	printf("Pilih : ");
            gotoxy(142,26);	scanf("%d",&pilih);

            switch(pilih){
            case 1 :
                gotoxy(134,29);	printf("Update Nama user = ");
                fflush(stdin);
                gotoxy(134,30);	gets(U.Nama);
                U.Nama[0] = toupper(U.Nama[0]);
                break;
            case 2 :
                gotoxy(134,29);	printf("Update Password = ");
                fflush(stdin);
                gotoxy(134,30);	scanf("%s",U.Password);
                break;
            case 3 :
                gotoxy(134,29);	printf("Update No Telphone = ");
                fflush(stdin);
                gotoxy(134,30);	scanf("%s",U.Tlpn);
                break;
            case 4 :
                gotoxy(134,29);	printf("Update Tanggal Lahir = ");
                gotoxy(134,30);	printf("  -  -    ");
                fflush(stdin);
                gotoxy(134,30); scanf("%d",&U.hari);
                fflush(stdin);
                gotoxy(137,30); scanf("%d",&U.bulan);
                fflush(stdin);
                gotoxy(140,30); scanf("%d",&U.tahun);
                break;
            case 5 :
                URole();
                break;
            case 0 :
                CleanKanan();
                MenuMasterPegawai();
                break;
            default :
                MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
                break;
            }
        } while (pilih > 5);

		fwrite(&U,sizeof(U),1,ft); /* menulis data terbaru kedalam temp */
        fread(&U,sizeof(U),1,ek); /* menyalin sisa data kedalam temp */
        while(!feof(ek))
		{
            fwrite(&U, sizeof(U),1,ft);
            fread(&U,sizeof(U),1,ek);
        }

		fclose(ek);
		fclose(ft);

		/* menyalin dari temp ke data user */
		ft = fopen("dat/usertemp.dat","rb");
		ek = fopen("dat/user.dat","wb");
		fread(&U,sizeof(U),1,ft);
		while(!feof(ft))
		{
			fwrite(&U,sizeof(U),1,ek);
			fread(&U,sizeof(U),1,ft);
		}
		fclose(ft);
		fclose(ek);

        MessageBoxA(0,"Data Berhasil di Update","Notification",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

        do {
            gotoxy(164,34);	printf("  ");
            gotoxy(134,34);	printf("Ingin update data lagi?[Y/N] : ");
            gotoxy(165,34);	scanf("%s",&ans);

            switch(toupper(ans)){
                case 'Y':
                    CleanTengah();
                    CleanKanan();
                    Updatedata();
                    break;
                case 'N':
                    CleanKanan();
                    MenuMasterPegawai();
                    break;
            }
        } while (toupper(ans) != 'Y' && toupper(ans) != 'N');
	} else {
		MessageBox(NULL,"ID Pegawai Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
		CleanKanan();
		Updatedata();
	}
}

void hapusdata()
{
    FILE *ek, *ft;
    int idhapus, found=0, i=0;
    char ans;

    Lihatdata();

    gotoxy(138,44);	printf("Untuk kembali, ketik '0'\n");

    ek = fopen("dat/user.dat","rb");
    fread(&U,sizeof(U),1,ek);
    while(!feof(ek)){
    	fread(&U,sizeof(U),1,ek);
    	i++;
	}
	if(i==0){
		MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        MenuMasterPegawai();
	}
    fclose(ek);

    gotoxy(134,15);	printf("ID Pegawai : PG");
    scanf("%d", &idhapus);
    printf("\n");
    if(idhapus == 0){
    	CleanKanan();
        MenuMasterPegawai();
    }

    ft = fopen("dat/usertemp.dat", "wb"); /* buka file temp untuk ditulis */
    ek = fopen("dat/user.dat", "rb"); /* buke file user untuk dibaca */
    while(!found && !feof(ek)){
    	fread(&U,sizeof(U),1,ek);
    	if(U.No == idhapus){
    		found = 1;
		}else{
			fwrite(&U,sizeof(U),1,ft); /* menulis data yang bukan id hapus */
		}
	}
	if(found){
		CleanTengah();
		DesainUbahData();

		gotoxy(63,26);	printf("ID Pegawai      = PG%d\n",U.No);
        gotoxy(63,27);	printf("Nama            = %s\n",U.Nama);
        gotoxy(63,28);	printf("Username        = %s\n",U.Username);
        gotoxy(63,29);	printf("Password        = %s\n",U.Password);
        gotoxy(63,30);	printf("Nomor Telphone  = %s\n",U.Tlpn);
        gotoxy(63,31);	printf("Tanggal lahir   = %02d-%02d-%d",U.hari,U.bulan,U.tahun);
        switch(U.Role){
            case 1 :
            	gotoxy(63,32);	printf("Role            = Kasir\n");
				break;
			case 2 :
            	gotoxy(63,32);	printf("Role            = Admin\n");
				break;
			case 3 :
            	gotoxy(63,32);	printf("Role            = Manager\n");
				break;
		}

		do {
            gotoxy(165,18);	printf("  ");
            gotoxy(134,18);	printf("Yakin data akan dihapus?[Y/N] : ");
            gotoxy(166,18);	scanf("%s", &ans);

            switch(toupper(ans)){
                case 'Y':
                    CleanKanan();
                    CleanTengah();
                    fread(&U,sizeof(U),1,ek); /* menyalin sisa */
                    while(!feof(ek)){
                        fwrite(&U,sizeof(U),1,ft);
                        fread(&U,sizeof(U),1,ek);
                    }
                    break;
                case 'N':
                    CleanKanan();
                    CleanTengah();
                    hapusdata();
				break;
            }
		} while (toupper(ans) != 'Y' && toupper(ans) != 'N');
	}else{
		MessageBox(NULL,"ID Pegawai Tidak Ada!","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);
        CleanKanan();
        hapusdata();
	}
    fclose(ft);
    fclose(ek);

    /* menyalin data dari temp ke data user */
    ek = fopen("dat/user.dat","wb");
    ft = fopen("dat/usertemp.dat","rb");
    fread(&U,sizeof(U),1,ft);
    while(!feof(ft))
    {
        fwrite(&U,sizeof(U),1,ek);
        fread(&U,sizeof(U),1,ft);
    }
    fclose(ek);
    fclose(ft);

    MessageBox(NULL,"Data Berhasil Di Hapus","ATTENTION",MB_OK | MB_DEFAULT_DESKTOP_ONLY);

    do {
        CleanKanan();
        CleanTengah();
        gotoxy(166,18);	printf("   ");
        gotoxy(135,18);	printf("Ingin hapus data lagi? [Y/N] : ");
        gotoxy(166,18);	scanf("%s", &ans);

        switch(toupper(ans)){
            case 'Y':
                CleanKanan();
                CleanTengah();
                hapusdata();
                break;
            case 'N':
                CleanKanan();
                CleanTengah();
                MenuMasterPegawai();
            break;
        }
    } while (toupper(ans) != 'Y' && toupper(ans) != 'N');
}
