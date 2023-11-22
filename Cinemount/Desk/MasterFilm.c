#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct{int id;
               int prd;
               char judul[50];
               char durasi[50];
               int tahun;
               char genre[50];
               }Film;
Film flm;
char name[20];
FILE *arsflm;

typedef struct{int id;
               char nama[20];
               char alamat[50];
               char telp[15];
               char email[50];
               }Produser;
Produser prd;
FILE *arsprd;

int main()
{
    int choose;

    remove("Temp Data Film.dat");
    system("cls");
    printf("Program CRUD Data Film\n\n");
    printf("Pilih menu :\n");

    printf("[1]. Tambah Data Film\n");
    printf("[2]. Lihat Data Film\n");
    printf("[3]. Ubah Data Film\n");
    printf("[4]. Hapus Data Film\n");
    printf("[0]. Keluar\n\n");

    printf("Pilihan : "); scanf("%d", &choose);
    switch(choose){
    case 1 :
        TambahFlm();
        break;
    case 2 :
        LihatFlm();
        break;
    case 3 :
        UbahFlm();
        break;
    case 4 :
        HapusFlm();
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

void TambahFlm()
{
    int id, i=0;
    char ans;

    system("cls");
    printf("Tambah Data Film\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk ditambah dan dibaca ab+
    arsflm = fopen("Data Film.dat", "ab+");
    fread(&flm,sizeof(flm),1,arsflm);

    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        id = flm.id;
        i++;
    }
    if(i==0){
        flm.id = 1;
    }else{
        flm.id = id+1;
    }

    LihatPrd();

    printf("ID Film = FM%d\n", flm.id);

//ID PRODUSER

    printf("ID Produser = PRD");
    fflush(stdin);
    scanf("%d", &flm.prd);
    if(flm.prd == 0){
        main();
    }

    system("cls");
    printf("Tambah Data Film\n");
    printf("--0 untuk kembali--\n\n");

    printf("ID Film = FM%d\n", flm.id);
    printf("ID Produser = PRD%d\n", flm.prd);
    fflush(stdin);

    printf("Judul = ");
    fflush(stdin);
    gets(name);
    strcpy(flm.judul,name);
    if(!strcmp(flm.judul,"0")){
        main();
    }

    printf("Durasi = ");
    fflush(stdin);
    gets(name);
    strcpy(flm.durasi,name);
    if(!strcmp(flm.durasi,"0")){
        main();
    }

    printf("Tahun Rilis = ");
    fflush(stdin);
    scanf("%d", &flm.tahun);
    if(flm.tahun == 0){
        main();
    }

    printf("Genre = ");
    fflush(stdin);
    gets(name);
    strcpy(flm.genre,name);
    if(!strcmp(flm.genre,"0")){
        main();
    }

    fwrite(&flm,sizeof(flm),1,arsflm);

//tutup file
    fclose(arsflm);

    ddd:
    printf("Tambah data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch (toupper(ans))
    {
        case 'Y':
            TambahFlm();
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

void LihatFlm()
{
    int i=0;

    system("cls");
    printf("Lihat Data Film\n");
    printf("--Klik apapun untuk kembali--\n\n");

//buka file untuk dibaca
    arsflm = fopen("Data Film.dat", "rb");
    fread(&flm,sizeof(flm),1,arsflm);

    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
//tutup file
    fclose(arsflm);

    if(i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }else{

//buka file untuk dibaca
        arsflm = fopen("Data Film.dat","rb");
        fread(&flm,sizeof(flm),1,arsflm);
        while(!feof(arsflm)){
            printf("ID Film = FM%d\n", flm.id);

            arsprd = fopen("Data Produser.dat","rb");
            fread(&prd,sizeof(prd),1,arsprd);
            while(!feof(arsprd)){
                if(flm.prd == prd.id){
                    printf("Produser = %s\n", prd.nama);
                }
                fread(&prd,sizeof(prd),1,arsprd);
            }
            fclose(arsprd);

            printf("Judul = %s\n", flm.judul);
            printf("Durasi = %s\n", flm.durasi);
            printf("Tahun Rilis = %d\n", flm.tahun);
            printf("Genre = %s\n\n", flm.genre);
            fread(&flm,sizeof(flm),1,arsflm);
        }
//tutup file
        fclose(arsflm);
    }
    getch();
    main();
}

void UbahFlm()
{
    FILE *temp;
    int idupdate, found, choose, i=0;
    char ans;

    system("cls");
    printf("Ubah Data Film\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsflm = fopen("Data Film.dat","rb");
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsflm);

    printf("Masukkan ID Film = FM");
    scanf("%d", &idupdate);
    if(idupdate == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen ("Temp Data Film.dat", "wb");
//buka file untuk dibaca
    arsflm = fopen("Data Film.dat", "rb");

    found=0;
    while(!found && !feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        if(flm.id == idupdate){
            found = 1;
        }else{
            fwrite(&flm,sizeof(flm),1,temp);
        }
    }
    if (found){
        printf("\nID Film = FM%d\n", flm.id);
        printf("Judul = %s\n", flm.judul);
        printf("Durasi = %s\n", flm.durasi);
        printf("Tahun Rilis = %d\n", flm.tahun);
        printf("Genre = %s\n", flm.genre);

        printf("\nPilih data yang akan di update\n");
        printf("[1]. Judul\n");
        printf("[2]. Durasi\n");
        printf("[3]. Tahun Rilis\n");
        printf("[4]. Genre\n");
        printf("[0]. Keluar\n\n");

        printf("Pilihan : ");
        scanf("%d",&choose);

        switch(choose){
        case 1 :
            printf("Judul = ");
            fflush(stdin);
            gets(name);
            strcpy(flm.judul,name);
            break;
        case 2 :
            printf("Durasi = ");
            fflush(stdin);
            gets(name);
            strcpy(flm.durasi,name);
            break;
        case 3 :
            printf("Tahun Rilis = ");
            fflush(stdin);
            scanf("%d", &flm.tahun);
            break;
        case 4 :
            printf("Genre = ");
            fflush(stdin);
            gets(name);
            strcpy(flm.genre,name);
            break;
        case 0 :
            main();
            break;
        default :
            MessageBoxA(NULL,"Incorrect Answer","ATTENTION",MB_OK);
            UbahFlm();
        }
        fwrite(&flm,sizeof(flm),1,temp);

        fread(&flm,sizeof(flm),1,arsflm);
        while(!feof(arsflm)){
            fwrite(&flm,sizeof(flm),1,temp);
            fread(&flm,sizeof(flm),1,arsflm);
        }
//tutup file
        fclose(temp);
        fclose(arsflm);

        printf("Data berhasil di update\n");

        remove("Data Film.dat");
        rename("Temp Data Film.dat","Data Film.dat");

        ddd:
        printf("Ingin update data lagi? [Y/N] ");
        scanf("%s", &ans);

        switch (toupper(ans)){
        case 'Y':
            UbahFlm();
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
        MessageBox(NULL,"ID Film Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Film.dat");
        rename("Temp Data Film.dat", "Data Film.dat");
        UbahFlm();
    }
}

void HapusFlm()
{
    FILE *temp;
    int idhapus, found, i=0;
    char ans;

    system("cls");
    printf("Hapus Data Film\n");
    printf("--0 untuk kembali--\n\n");

//buka file untuk dibaca
    arsflm = fopen("Data Film.dat","rb");
    fread(&flm,sizeof(flm),1,arsflm);
    while(!feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        i++;
    }
    if (i==0){
        MessageBoxA(NULL,"Data Tidak Ada, Pilih 1 untuk Menambah Data!","ATTENTION",MB_OK);
        main();
    }
//tutup file
    fclose(arsflm);

    printf("Masukan ID Film yang akan dihapus : FM");
    scanf("%d", &idhapus);
    if(idhapus == 0){
        main();
    }

//buka file temp untuk ditulis
    temp = fopen("Temp Data Film.dat", "wb");
//buka file untuk dibaca
    arsflm = fopen("Data Film.dat", "rb");

    found=0;
    while(!found && !feof(arsflm)){
        fread(&flm,sizeof(flm),1,arsflm);
        if(flm.id == idhapus){
            found = 1;
        }else{
            fwrite(&flm,sizeof(flm),1,temp);
        }
    }
    if(found){
        printf("\nID Film = FM%d\n", flm.id);
        printf("Judul = %s\n", flm.judul);
        printf("Durasi = %s\n", flm.durasi);
        printf("Tahun Rilis = %d\n", flm.tahun);
        printf("Genre = %s\n\n", flm.genre);

        ddd:
        printf("Yakin data akan dihapus? [Y/N] ");
        scanf("%s", &ans);

        switch(toupper(ans)){
        case 'Y':
            fread(&flm,sizeof(flm),1,arsflm);
            while(!feof(arsflm)){
                fwrite(&flm,sizeof(flm),1,temp);
                fread(&flm,sizeof(flm),1,arsflm);
            }
            break;
        case 'N':
            HapusFlm();
            break;
        default :
            MessageBox(NULL,"Input yang anda masukkan salah!","ATTENTION",MB_OK);
            goto ddd;
        }
    }else{
        MessageBox(NULL,"ID Film Tidak Ada!","ATTENTION",MB_OK);
        remove("Data Film.dat");
        rename("Temp Data Film.dat", "Data Film.dat");
        HapusFlm();
    }
//tutup file
    fclose(temp);
    fclose(arsflm);

    printf("\nData berhasil di hapus\n");

    remove("Data Film.dat");
    rename("Temp Data Film.dat", "Data Film.dat");

    dddd:
    printf("Hapus data lagi? [Y/N] ");
    scanf("%s", &ans);

    switch(toupper(ans))
    {
        case 'Y':
            HapusFlm();
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

void LihatPrd()
{
    int i=0;

    //printf("Lihat Data Produser\n");
    //printf("--Klik apapun untuk kembali--\n\n");

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
}
