#define ENTER 13
#define TAB 9
#define BCKSPC 8

//MASTER PEGAWAI
struct user
{
	int  No;
	char Nama[50];
	char Username[50];
	char Password[50];
	char Tlpn[50];
	int  Role;
	int  hari, bulan, tahun;
};
struct user U;
struct user Unew;
FILE *User;

//MASTER MAKANAN
typedef struct{int  id;
               char nama[20];
               int  stok;
               int  harga;
               int  jenis;
               }Makanan;
Makanan mk;
FILE *arsmk;

//MASTER PRODUSER
typedef struct{int  id;
               char nama[20];
               char alamat[50];
               char telp[15];
               char email[50];
               }Produser;
Produser prd;
FILE *arsprd;

//MASTER FILM
typedef struct{int  id;
               int  prd;
               char produser[50];
               char judul[50];
               char durasi[50];
               int  tahun;
               char genre[50];
               int  status;
               int  harga;
               }Film;
Film flm;
FILE *arsflm;

//MASTER JADWAL
typedef struct{int  idjadwal;
               int  idfilm;
               char judul[50];
               char tempat[20];
               int  kapasitastetap;
               int  stok;
               int  harga;
               int  status;
               int  hari, bulan, tahun;
               }Jadwal;
Jadwal jd;
FILE *arsjdwl;

//TRANSAKSI MAKANAN
typedef struct{int  id;
               int  total;
               int  hari;
               int  bulan;
               int  tahun;
               char kasir[50];
               }TMakan;
TMakan tmk;
FILE *arstmk;
int total;

//DETAIL TRANSAKSI MAKANAN
typedef struct{int  idtrm;
               int  idmkn;
               char desk[20];
               int  harga;
               int  qty;
               int  subtotal;
               }detailTmakan;
detailTmakan dtmk;
FILE *arsdetail;

//BELI FILM
typedef struct{int  idtrns;
               int  idFilm;
               char NamaProduser[50];
               char judulFilm[50];
               int  hrg;
               int  hari;
               int  bulan;
               int  tahun;
               char admin[50];
               }sewafilm;
sewafilm sf;
FILE *arssewaflm;

//TRANSAKSI TIKET
typedef struct{int  id;
               int  evn;
               int  hrg;
               int  qty;
               int  total;
               char film[50];
               char tempat[50];
               char kasir[50];
               int  hari;
               int  bulan;
               int  tahun;
               }Tiket;
Tiket tik;
FILE *arstiket;

//KERANJANG
typedef struct{ char nama [25];
                int qty;
}keranjang;
keranjang krj;
FILE *arskrj;

char usn[25];
char psw[25];
