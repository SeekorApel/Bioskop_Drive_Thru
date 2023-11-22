#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct{int id;
               char nama[20];
               char alamat[50];
               char telp[15];
               char email[50];
               }Produser;
Produser prd;
char name[20];
FILE *arsprd;

int main()
{
    int choose;

    remove("Temp Data Produser.dat");
    system("cls");
    printf("Program CRUD Data Produser\n\n");
    printf("Pilih menu :\n");

    printf("[1]. Tambah Data Produser\n");
    printf("[2]. Lihat Data Produser\n");
    printf("[3]. Ubah Data Produser\n");
    printf("[4]. Hapus Data Produser\n");
    printf("[0]. Keluar\n\n");

    printf("Pilihan : "); scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahPrd();
        break;
    case 2 :
        LihatPrd();
        break;
    case 3 :
        UbahPrd();
        break;
    case 4 :
        HapusPrd();
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

void TambahPrd()
{
    int id, i=0;
    char ans;

    system("cls");
    printf("Tambah Data Produser\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk ditambah dan dibaca ab+
    arsprd = fopen("Data Produser.dat", "ab+");
    fread(&prd,sizeof(prd),1,arsprd);

    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        id = prd.id;
        i++;
    }
    if(i==0){
        prd.id = 1;
    }else{
        prd.id = id+1;
    }

    printf("ID Produser = PRD%d\n", prd.id);

    printf("Nama Perusahaan = ");
    fflush(stdin);
    gets(name);
    strcpy(prd.nama,name);
    if(!strcmp(prd.nama,"0")){
        main();
    }

    printf("Alamat = ");
    fflush(stdin);
    gets(name);
    strcpy(prd.alamat,name);
    if(!strcmp(prd.alamat,"0")){
        main();
    }

    printf("No Telepon = ");
    fflush(stdin);
    gets(name);
    strcpy(prd.telp,name);
    if(!strcmp(prd.telp,"0")){
        main();
    }

    printf("E-mail = ");
    fflush(stdin);
    gets(name);
    strcpy(prd.email,name);
    if(!strcmp(prd.email,"0")){
        main();
    }

    fwrite(&prd,sizeof(prd),1,arsprd);

//tutup file
    fclose(arsprd);

    ddd:
    printf("Tambah data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch (toupper(ans))
    {
        case 'Y':
            TambahPrd();
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

void LihatPrd()
{
    int i=0;

    system("cls");
    printf("Lihat Data Produser\n");
    printf("--Klik apapun untuk kembali--\n\n");

//buka file untuk dibaca
    arsprd = fopen("Data Produser.dat", "rb");
    fread(&prd,sizeof(prd),1,arsprd);

    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
//tutup file
    fclose(arsprd);

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }else{

//buka file untuk dibaca
        arsprd = fopen("Data Produser.dat","rb");
        fread(&prd,sizeof(prd),1,arsprd);
        while(!feof(arsprd)){
            printf("ID Produser = PRD%d\n", prd.id);
            printf("Nama Perusahaan = %s\n", prd.nama);
            printf("Alamat = %s\n", prd.alamat);
            printf("No Telepon = %s\n", prd.telp);
            printf("E-mail = %s\n\n", prd.email);
            fread(&prd,sizeof(prd),1,arsprd);
        }
//tutup file
        fclose(arsprd);
    }
    getch();
    main();
}

void UbahPrd()
{
    FILE *temp;
    int idupdate, found, choose, i=0;
    char ans;

    system("cls");
    printf("Ubah Data Produser\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsprd = fopen("Data Produser.dat","rb");
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsprd);

    printf("Masukkan ID Produser = PRD");
    scanf("%d", &idupdate);
    if(idupdate == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen ("Temp Data Produser.dat", "wb");
//buka file untuk dibaca
    arsprd = fopen("Data Produser.dat", "rb");

    found=0;
    while(!found && !feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        if(prd.id == idupdate){
            found = 1;
        }else{
            fwrite(&prd,sizeof(prd),1,temp);
        }
    }
    if (found){
        printf("\nID Produser = PRD%d\n", prd.id);
        printf("Nama Perusahaan = %s\n", prd.nama);
        printf("Alamat = %s\n", prd.alamat);
        printf("No Telepon = %s\n", prd.telp);
        printf("E-mail = %s\n", prd.email);

        printf("\nPilih data yang akan di update\n");
        printf("[1]. Nama Perusahaan\n");
        printf("[2]. Alamat\n");
        printf("[3]. No Telepon\n");
        printf("[4]. E-mail\n");
        printf("[0]. Keluar\n\n");

        printf("Pilihan : ");
        scanf("%d",&choose);

        switch(choose){
        case 1 :
            printf("Nama Perusahaan = ");
            fflush(stdin);
            gets(name);
            strcpy(prd.nama,name);
            break;
        case 2 :
            printf("Alamat = ");
            fflush(stdin);
            gets(name);
            strcpy(prd.alamat,name);
            break;
        case 3 :
            printf("No Telepon = ");
            fflush(stdin);
            gets(name);
            strcpy(prd.telp,name);
            break;
        case 4 :
            printf("E-mail = ");
            fflush(stdin);
            gets(name);
            strcpy(prd.email,name);
            break;
        case 0 :
            main();
            break;
        default :
            MessageBoxA(NULL,"Incorrect Answer","ATTENTION",MB_OK);
            UbahPrd();
        }
        fwrite(&prd,sizeof(prd),1,temp);

        fread(&prd,sizeof(prd),1,arsprd);
        while(!feof(arsprd)){
            fwrite(&prd,sizeof(prd),1,temp);
            fread(&prd,sizeof(prd),1,arsprd);
        }
//tutup file
        fclose(temp);
        fclose(arsprd);

        printf("Data berhasil di update\n");

        remove("Data Produser.dat");
        rename("Temp Data Produser.dat","Data Produser.dat");

        ddd:
        printf("Ingin update data lagi? [Y/N] ");
        scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
            UbahPrd();
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
        MessageBox(NULL,"ID Produser Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Produser.dat");
        rename("Temp Data Produser.dat", "Data Produser.dat");
        UbahPrd();
    }
}

void HapusPrd()
{
    FILE *temp;
    int idhapus, found, i=0;
    char ans;

    system("cls");
    printf("Hapus Data Produser\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsprd = fopen("Data Produser.dat","rb");
    fread(&prd,sizeof(prd),1,arsprd);
    while(!feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsprd);

    printf("Masukan ID Produser yang akan dihapus : PRD");
    scanf("%d", &idhapus);
    if(idhapus == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen("Temp Data Produser.dat", "wb");
//buka file untuk dibaca
    arsprd = fopen("Data Produser.dat", "rb");

    found=0;
    while(!found && !feof(arsprd)){
        fread(&prd,sizeof(prd),1,arsprd);
        if(prd.id == idhapus){
            found = 1;
        }else{
            fwrite(&prd,sizeof(prd),1,temp);
        }
    }
    if(found){
        printf("\nID Produser = PRD%d\n", prd.id);
        printf("Nama Perusahaan = %s\n", prd.nama);
        printf("Alamat = %s\n", prd.alamat);
        printf("No Telepon = %s\n", prd.telp);
        printf("E-mail = %s\n\n", prd.email);

        ddd:
        printf("Yakin data akan dihapus? [Y/N] ");
        scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
            fread(&prd,sizeof(prd),1,arsprd);
            while(!feof(arsprd)){
                fwrite(&prd,sizeof(prd),1,temp);
                fread(&prd,sizeof(prd),1,arsprd);
            }
            break;
        case 'N':
            HapusPrd();
            break;
        default :
            MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
            goto ddd;
        }
    }else{
        MessageBox(NULL,"ID Produser Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Produser.dat");
        rename("Temp Data Produser.dat", "Data Produser.dat");
        HapusPrd();
    }
//tutup file
    fclose(temp);
    fclose(arsprd);

    printf("\nData berhasil di hapus\n");

    remove("Data Produser.dat");
    rename("Temp Data Produser.dat", "Data Produser.dat");

    dddd:
    printf("Hapus data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch(toupper(ans))
    {
        case 'Y':
            HapusPrd();
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
