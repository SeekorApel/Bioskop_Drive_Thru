#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct{int id;
               char nama[20];
               int stok;
               int harga;
               }Makanan;
Makanan mk;
char name[20];
char Harga[25];
FILE *arsmk;

int main()
{
    int choose;

    remove("Temp Data Makanan.dat");
    system("cls");
    printf("Program CRUD Data Makanan\n\n");
    printf("Pilih menu :\n");

    printf("[1]. Tambah Data Makanan\n");
    printf("[2]. Lihat Data Makanan\n");
    printf("[3]. Ubah Data Makanan\n");
    printf("[4]. Hapus Data Makanan\n");
    printf("[0]. Keluar\n\n");

    printf("Pilihan : "); scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahMK();
        break;
    case 2 :
        LihatMK();
        break;
    case 3 :
        UbahMK();
        break;
    case 4 :
        HapusMK();
        break;
    case 0 :
        MessageBoxA(NULL,"Thank You","NOTIFICATION",MB_OK);
        system("cls");
        exit(0);
        break;
    default :
        MessageBoxA(NULL,"Incorrect input","ATTENTION",MB_OK);
        main();
        break;
    }
}

void TambahMK()
{
    int id, i=0;
    char ans;

    system("cls");
    printf("Tambah Data Makanan\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk ditambah dan dibaca ab+
    arsmk = fopen("Data Makanan.dat", "ab+");
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

    printf("ID Makanan = MK%d\n", mk.id);

    printf("Nama = ");
    fflush(stdin);
    gets(name);
    strcpy(mk.nama,name);
    if(!strcmp(mk.nama,"0")){
        main();
    }

    printf("Stok = ");
    fflush(stdin);
    scanf("%d", &mk.stok);
    if(mk.stok == 0){
        main();
    }

    printf("Harga = ");
    fflush(stdin);
    scanf("%d", &mk.harga);
    if(mk.harga == 0){
        main();
    }

    fwrite(&mk,sizeof(mk),1,arsmk);

//tutup file
    fclose(arsmk);

    ddd:
    printf("Tambah data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch (toupper(ans)){
        case 'Y':
            TambahMK();
            break;
        case 'N':
            MessageBox(NULL,"Data berhasil ditambahkan!","NOTIFICATION",MB_OK);
            main();
            break;
        default :
            MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
            goto ddd;
    }
}

void LihatMK()
{
    int i=0;

    system("cls");
    printf("Lihat Data Makanan\n");
    printf("--Klik apapun untuk kembali--\n\n");

//buka file untuk dibaca
    arsmk = fopen("Data Makanan.dat", "rb");
    fread(&mk,sizeof(mk),1,arsmk);

    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
//tutup file
    fclose(arsmk);

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }else{

//buka file untuk dibaca
        arsmk = fopen("Data Makanan.dat","rb");
        fread(&mk,sizeof(mk),1,arsmk);
        while(!feof(arsmk)){
            printf("ID Makanan = MK%d\n", mk.id);
            printf("Nama = %s\n", mk.nama);
            printf("Stok = %d\n", mk.stok);
            rupiah(mk.harga,Harga); printf("Harga = RP. %s\n\n", Harga);
            fread(&mk,sizeof(mk),1,arsmk);
        }
//tutup file
        fclose(arsmk);
    }
    getch();
    main();
}

void UbahMK()
{
    FILE *temp;
    int idupdate, found, choose, i=0;
    char ans;

    system("cls");
    printf("Ubah Data Makanan\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsmk = fopen("Data Makanan.dat","rb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsmk);

    printf("Masukkan ID Makanan = MK");
    scanf("%d", &idupdate);
    if(idupdate == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen ("Temp Data Makanan.dat", "wb");
//buka file untuk dibaca
    arsmk = fopen("Data Makanan.dat", "rb");

    found=0;
    while(!found && !feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        if(mk.id == idupdate){
            found = 1;
        }else{
            fwrite(&mk,sizeof(mk),1,temp);
        }
    }
    if (found){
        printf("\nID Makanan = MK%d\n", mk.id);
        printf("Nama = %s\n", mk.nama);
        printf("Stok = %d\n", mk.stok);
        rupiah(mk.harga,Harga); printf("Harga = RP. %s\n\n", Harga);

        printf("\nPilih data yang akan di update\n");
        printf("[1]. Nama Makanan\n");
        printf("[2]. Stok\n");
        printf("[3]. Harga\n");
        printf("[0]. Keluar\n");

        printf("Pilihan : ");
        scanf("%d",&choose);

        switch(choose){
        case 1 :
            printf("Nama Makanan = ");
            fflush(stdin);
            gets(name);
            strcpy(mk.nama,name);
            break;
        case 2 :
            printf("Stok = ");
            fflush(stdin);
            scanf("%d", &mk.stok);
            break;
        case 3 :
            printf("Harga = ");
            fflush(stdin);
            scanf("%d", &mk.harga);
            break;
        case 0 :
            main();
            break;
        default :
            MessageBoxA(NULL,"Incorrect Answer","ATTENTION",MB_OK);
            UbahMK();
        }
        fwrite(&mk,sizeof(mk),1,temp);

        fread(&mk,sizeof(mk),1,arsmk);
        while(!feof(arsmk)){
            fwrite(&mk,sizeof(mk),1,temp);
            fread(&mk,sizeof(mk),1,arsmk);
        }
//tutup file
        fclose(temp);
        fclose(arsmk);

        printf("Data berhasil di update\n");

        remove("Data Makanan.dat");
        rename("Temp Data Makanan.dat","Data Makanan.dat");

        ddd:
        printf("Ingin update data lagi? [Y/N] ");
        scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
            UbahMK();
            break;
        case 'N':
            MessageBox(NULL,"Data berhasil diubah!","NOTIFICATION",MB_OK);
            main();
            break;
        default :
            MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
            goto ddd;
        }
    }else{
        MessageBox(NULL,"ID Makanan Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Makanan.dat");
        rename("Temp Data Makanan.dat", "Data Makanan.dat");
        UbahMK();
    }
}

void HapusMK()
{
    FILE *temp;
    int idhapus, found, i=0;
    char ans;

    system("cls");
    printf("Hapus Data Makanan\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsmk = fopen("Data Makanan.dat","rb");
    fread(&mk,sizeof(mk),1,arsmk);
    while(!feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsmk);

    printf("Masukan ID Makanan yang akan dihapus : MK");
    scanf("%d", &idhapus);
    if(idhapus == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen("Temp Data Makanan.dat", "wb");
//buka file untuk dibaca
    arsmk = fopen("Data Makanan.dat", "rb");

    found=0;
    while(!found && !feof(arsmk)){
        fread(&mk,sizeof(mk),1,arsmk);
        if(mk.id == idhapus){
            found = 1;
        }else{
            fwrite(&mk,sizeof(mk),1,temp);
        }
    }
    if(found){
        printf("\nID Makanan = MK%d\n", mk.id);
        printf("Nama = %s\n", mk.nama);
        printf("Stok = %d\n", mk.stok);
        rupiah(mk.harga,Harga); printf("Harga = RP. %s\n\n", Harga);

        ddd:
        printf("Yakin data akan dihapus? [Y/N] ");
        scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
            fread(&mk,sizeof(mk),1,arsmk);
            while(!feof(arsmk)){
                fwrite(&mk,sizeof(mk),1,temp);
                fread(&mk,sizeof(mk),1,arsmk);
            }
            break;
        case 'N':
            HapusMK();
            break;
        default :
            MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
            goto ddd;
        }
    }else{
        MessageBox(NULL,"ID Makanan Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Makanan.dat");
        rename("Temp Data Makanan.dat", "Data Makanan.dat");
        HapusMK();
    }
//tutup file
    fclose(temp);
    fclose(arsmk);

    printf("\nData berhasil di hapus\n");

    remove("Data Makanan.dat");
    rename("Temp Data Makanan.dat", "Data Makanan.dat");

    dddd:
    printf("Hapus data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch(toupper(ans)){
    case 'Y':
        HapusMK();
        break;
    case 'N':
        MessageBox(NULL,"Data berhasil dihapus!","NOTIFICATION",MB_OK);
        main();
        break;
    default :
        MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
        goto dddd;
    }
}

void rupiah(int number, char output[])
{
	// menampilkan Bentuk Rupiah
	if(number < 1000) sprintf(output, "%d", number);
    else if(number < 1000000) sprintf(output, "%d.%03d", number/1000, number%1000);
    else if(number < 1000000000) sprintf(output, "%d.%03d.%03d", number/1000000, (number%1000000)/1000, number%1000);
    else sprintf(output, "%d.%03d.%03d.%03d", number/1000000000, (number%1000000000)/1000, (number%1000000)/1000, number%1000);
}
