#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include "Deklarasi.h"
#include "Design.h"
#include "lib.h"
#include "MasterPegawai.h"
#include "MasterMakanan.h"
#include "MasterProduser.h"
#include "MasterJadwal.h"
#include "MasterFilm.h"
#include "TransaksiMakanan.h"
#include "Transaksi Sewa Film.h"
#include "TransaksiTiket.h"
#include "Login.h"

main()
{
	fullscreen();
	CekJadwal();
	Login();
}
