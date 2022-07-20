#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


/*fungsi pendukung system*/
void gotoxy(int x,int y){
	COORD c = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void konfigurasiUI(){
	SetConsoleTitle("Sistem Perbankan Sederhana - Bank Indonesia");
	system("color 1F");
	SetConsoleOutputCP(CP_UTF8);
}

void tanggal(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("TANGGAL : %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void jam(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("WAKTU   : %02d:%02d:%02d\n",  tm.tm_hour, tm.tm_min, tm.tm_sec);
}

//-------------------------------------------------------------------------------

/*variabel */
struct admin{
	char user[100];
	char pass[100];
	int  history[9999][8];
	char keterangan[9999][300];
};

struct nasabah{
	int rekening;
	char nama[100];
	char alamat[200];
	float saldo;
	char nomortelepon[100];
};

struct admin adm;
char user[30];
char pass[30];
int r_sekarang = 0;

int max_nasabah =9999;
int jumlah_nasabah = 0;
struct nasabah n[9999];



//-------------------------------------------------------------------------------

/*fungsi edit variabel*/
	/*riwayat*/
		void tambahriwayat(int akses,int data){
			
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			
			adm.history[r_sekarang][0] = tm.tm_mday;
			adm.history[r_sekarang][1] = tm.tm_mon+1;
			adm.history[r_sekarang][2] = tm.tm_year+1900;
			adm.history[r_sekarang][3] = tm.tm_hour;
			
			adm.history[r_sekarang][4] = tm.tm_min;
			adm.history[r_sekarang][5] = tm.tm_sec;
			adm.history[r_sekarang][6] = akses;
			adm.history[r_sekarang][7] = data;
			
			r_sekarang++;
		}
		
		void lihatriwayat(){
			tambahriwayat(7,-1);
			int x;
			system("cls");
			printf("------RIWAYAT ADMINISTRASI DI BANK INDONESIA------\n");
			printf("==================================================\n");
			for(x= 0; x< r_sekarang;x++){
				printf("%d/%02d/%02d - %02d:%02d:%02d = Akses ",adm.history[x][0] ,adm.history[x][1], adm.history[x][2],adm.history[x][3],adm.history[x][4],adm.history[x][5] );
					/*
						1. Membuat data nasabah
						2. Melihat data nasabah
						3. Menambah data nasabah
						4. Menghapus data nasabah
						5. Mengedit data nasabah
						6. Mencari data nasabah
						7. Melihat riwayat aktivitas
						8. Mentransfer dana nasabah
						9. Mensortir data nasabah
					*/
				if(adm.history[x][6]==1){
					printf("membuat data nasabah");
					printf(" sebanyak %d data",adm.history[x][7]);
				}else if(adm.history[x][6]==2){
					printf("melihat data nasabah");
				}else if(adm.history[x][6]==3){
					printf("menambah data nasabah");
					printf(" sebanyak %d data",adm.history[x][7]);
				}else if(adm.history[x][6]==4){
					printf("menghapus data nasabah");
					printf(" sebanyak %d data",adm.history[x][7]);
				}else if(adm.history[x][6]==5){
					printf("mengedit data nasabah");
					printf(" dengan nomor rekening %d",adm.history[x][7]);
				}else if(adm.history[x][6]==6){
					printf("mencari data nasabah");
					if(adm.history[x][7]==1){
						printf(" berdasarkan nama");
					}else if(adm.history[x][7]==2){
						printf(" berdasarkan saldo");
					}else if(adm.history[x][7]==3){
						printf(" berdasarkan alamat");
					}else if(adm.history[x][7]==4){
						printf(" berdasarkan nomor telepon");
					}else if(adm.history[x][7]==5){
						printf(" berdasarkan nomor rekening");
					}
				}else if(adm.history[x][6]==7){
					printf("melihat riwayat aktivitas");
				}else if(adm.history[x][6]==8){
					printf("Mentransfer dana nasabah");
				}else if(adm.history[x][6]==9){
					printf("mensortir data nasabah");
					if(adm.history[x][7]==1){
						printf(" berdasarkan nama");
					}else if(adm.history[x][7]==2){
						printf(" berdasarkan saldo");
					}else if(adm.history[x][7]==3){
						printf(" berdasarkan alamat");
					}else if(adm.history[x][7]==4){
						printf(" berdasarkan nomor telepon");
					}else if(adm.history[x][7]==5){
						printf(" berdasarkan nomor rekening");
					}
				}
				printf("\n");
			}
			printf("Tekan apapun untuk kembali ke menu awal");
			getch();
		}
	//---------------------------------------------

//-------------------------------------------------------------------------------

/*fungsi ubah tampilan*/
	/*login*/
	void login(){
		int locked = 1;
		char deteksi;
		int x,y,z;
		while(locked==1){
			system("cls");
			system("color 1F");
			strcpy(adm.user,"admin");
			strcpy(adm.pass,"admin");
		
			system("color 1F");
			gotoxy(35,10);
			printf("           DATA NASABAH BANK INDONESIA");
			gotoxy(35,11);
			printf("=================================================");
			gotoxy(35,12);
			printf("\x1b[33m");
			printf("Masukan Username [admin] : \x1b[0m\x1b[47m                      \x1b[33m\x1b[44m");
			gotoxy(35,13);
			printf("Masukan Password [admin] : \x1b[0m                      \x1b[31m");
			printf("\x1b[0m");
			printf("\x1b[44m");
			//system("color 1F");
			gotoxy(35,14);
			printf("=================================================");
			gotoxy(35,15);
			tanggal();
			gotoxy(35,16);
			jam();
			gotoxy(62,12);
			system("color 00");
			scanf("%s",&user);
			gotoxy(62,13);
			y=0;
			for(x=0;x<5;x++){
				y= y + 1;
				deteksi = getch();
				pass[x] = deteksi;
				pass[x+1] = '\0';
				int detek = (int) deteksi;
				if(detek==13){
					break;
				}
				printf("%c%c%c ",'\xE2', '\x99', '\xA5');
			};
			gotoxy(35,17);
		
			if((strcmp(adm.user,user)==0)&&(strcmp(adm.pass,pass)==0)){
				locked = 0;
				printf("Login Berhasil!!");
				gotoxy(35,18);
				printf("Tekan apapun untuk masuk ke sistem perbankan!!");
				getch();
			}else{
				locked = 1;
				printf("Password / Username salah ...!!");
				gotoxy(35,18);
				printf("Tekan apapun untuk mengulang ...!!");
				getch();
			}
		}
	}
	//------------
	
	/*menu utama*/
	void tampilmenu(){
		system("cls");
		system("color 9F");
		gotoxy(0,19);
		printf("%d",strlen(""));
		gotoxy(31,18);
		printf("GUNAKAN KURSOR atas dan bawah untuk melakukan seleksi,");
		gotoxy(31,19);
		printf("Tekan enter untuk memilih menu ...");
		gotoxy(15,4);
		printf("\x1b[40m ---------------");
		gotoxy(15,5);
		printf("\x1b[40m/ Bank InDo =");
		gotoxy(30,5);
		printf("\x1b[40m=");
		gotoxy(31,4);
		printf("\x1b[40m=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+");
		gotoxy(31,5);
		printf("\x1b[40m  SELAMAT DATANG DI SISTEM PERBANKAN BANK INDONESIA   ");
		gotoxy(30,6);
		printf("=======================================================");
		
		gotoxy(30,17);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		int lock = 1;
		int posisi =7;
		int range[] = {7,16};
		char x;
		gotoxy(15,6);
		//printf("\x1b[41m+++++++++++++++=");
		printf("\x1b[42m                ");
		gotoxy(15,17);
		printf("                ");						
		gotoxy(15,7);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,8);
	   	printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,9);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,10);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,11);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,12);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,13);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,14);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,15);
		printf("\x1b[41m|\x1b[0m              |");
		gotoxy(15,16);
		printf("\x1b[41m|\x1b[0m              |");
		
		
		
		gotoxy(30,7);
		printf("|\x1b[0m 1 . Membuat Data Nasabah              [CREATE    ]  |");
		gotoxy(30,8);
		printf("|\x1b[0m 2 . Lihat Data Nasabah                [READ      ]  |");
		gotoxy(30,9);
		printf("|\x1b[0m 3 . Tambah Data Nasabah               [ADD       ]  |");
		gotoxy(30,10);
		printf("|\x1b[0m 4 . Hapus Data Nasabah                [DELETE    ]  |");
		gotoxy(30,11);
		printf("|\x1b[0m 5 . Edit Data Nasabah                 [UPDATE    ]  |");
		gotoxy(30,12);
		printf("|\x1b[0m 6 . Mencari Data Nasabah              [SEARCH    ]  |");
		gotoxy(30,13);
		printf("|\x1b[0m 7 . Riwayat Aktivitas                 [HISTORY   ]  |");
		gotoxy(30,14);
		printf("|\x1b[0m 8 . Transfer Dana Nasabah             [FEATURE ++]  |");
		gotoxy(30,15);
		printf("|\x1b[0m 9 . Sortir Data Nasabah               [SORT      ]  |");
		gotoxy(30,16);
		printf("|\x1b[0m 10. KELUAR PROGRAM                                  |");
		gotoxy(16,7);
		printf("\x1b[38mPILIH >>>>>>>>>\x1b[48m");
		gotoxy(30,7);
		printf("|\x1b[41m 1 . Membuat Data Nasabah              [CREATE    ]  |");
		
		while(lock ==1){
			x = getch();
			if((int)x==13){
				lock=0;
				break;
			}
			if((int)x==72){
				if(7<posisi){
					posisi = posisi -1;
				}
			}else if((int)x==80){
				if(16>posisi){
					posisi = posisi +1;
				}
			}
			
			gotoxy(15,7);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,8);
		   	printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,9);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,10);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,11);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,12);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,13);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,14);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,15);
			printf("\x1b[41m|\x1b[0m              |");
			gotoxy(15,16);
			printf("\x1b[41m|\x1b[0m              |");
			if(posisi==7){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}
			gotoxy(30,7);			
			printf("| 1 . Membuat Data Nasabah              [CREATE    ]  \x1b[0m|");
			if(posisi==8){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}				
			gotoxy(30,8);
			printf("| 2 . Lihat Data Nasabah                [READ      ]  \x1b[0m|");
	
			if(posisi==9){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,9);
			printf("| 3 . Tambah Data Nasabah               [ADD       ]  \x1b[0m|");
			
			if(posisi==10){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,10);
			printf("| 4 . Hapus Data Nasabah                [DELETE    ]  \x1b[0m|");
			
			if(posisi==11){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,11);
			printf("| 5 . Edit Data Nasabah                 [UPDATE    ]  \x1b[0m|");
			
			if(posisi==12){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,12);
			printf("| 6 . Mencari Data Nasabah              [SEARCH    ]  \x1b[0m|");
			
			if(posisi==13){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,13);
			printf("| 7 . Riwayat Aktivitas                 [HISTORY   ]  \x1b[0m|");
			
			if(posisi==14){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,14);
			printf("| 8 . Transfer Dana Nasabah             [FEATURE ++]  \x1b[0m|");
			
			if(posisi==15){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,15);
			printf("| 9 . Sortir Data Nasabah               [SORT      ]  \x1b[0m|");
			
			if(posisi==16){
				printf("\x1b[41m");
			}else{
				printf("\x1b[0m");
			}		
			gotoxy(30,16);
			printf("| 10. KELUAR PROGRAM                                  \x1b[0m|");
			
			gotoxy(16,posisi);
			printf("\x1b[38mPILIH >>>>>>>>>\x1b[48m");
		}
		gotoxy(0,20);
		if(posisi==7){
			membuat_data_nasabah();
		}else if(posisi==8){
			tampilkan_data_nasabah();
		}else if(posisi==9){
			tambah_data_nasabah();
		}else if(posisi==10){
			hapus_data_nasabah();
		}else if(posisi==11){
			edit_data_nasabah();
		}else if(posisi==12){
			cari_data_nasabah();
		}else if(posisi==13){
			lihatriwayat();
		}else if(posisi==14){
			transfer_dana_nasabah();
		}else if(posisi==15){
			sort_data_nasabah();
		}else if(posisi==16){
			exit(0);
		}
	}
	//////////////////////////

	/*membuat data nasabah*/
	void membuat_data_nasabah(){
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+========================================+\n");
		printf("|-------------Bank InDoNesIa-------------|\n");
		printf("|        Membuat Database Nasabah        |\n");
		printf("+========================================+\n");
		gotoxy(0,6);
		printf("------------------------------------------\n");
		gotoxy(0,4);
		printf("Data input nasabah maksimum = %d\n",max_nasabah);
		printf("Banyak data yang ingin diinput =\x1b[36m");
		scanf("%d",&jumlah_nasabah);
		gotoxy(0,7);
		if(jumlah_nasabah>max_nasabah){
			jumlah_nasabah=max_nasabah;
			printf("\x1b[31mMaximum data nasabah yang dapat dibuat adalah %d\x1b[32m\n",max_nasabah);
		}
		int i;
		for(i=0;i<jumlah_nasabah;i++){
			printf("\x1b[36m::Data Nasabah Bank Ke-%d\n",i+1);
			printf("::Nomor Rekening      : ");
			scanf("%d",&n[i].rekening);
			printf("::Nama Nasabah        : ");
			scanf(" %[^\n]",&n[i].nama);
			printf("::Alamat Nasabah      : ");
			scanf(" %[^\n]",&n[i].alamat);
			printf("::Saldo Nasabah       : ");
			scanf("%f",&n[i].saldo);
			printf("::Nomor Telepon       : ");
			scanf(" %[^\n]",&n[i].nomortelepon);
			printf("\x1b[32m------------------------------------------\n");
		}
		tambahriwayat(1,jumlah_nasabah);
		printf("\x1b[32mDatabase berhasil dibuat \n");
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//-------------------------------------
	
	/*tampilkan data nasabah*/
	void tampilkan_data_nasabah(){
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+========================================+\n");
		printf("|-------------Bank InDoNesIa-------------|\n");
		printf("|       Tampilkan Database Nasabah       |\n");
		printf("+========================================+\n");
		gotoxy(0,5);
		printf("------------------------------------------\n");
		gotoxy(0,4);
		printf("\x1b[31mTerdapat \x1b[32m%d \x1b[31mdata nasabah\n",jumlah_nasabah);
		gotoxy(0,6);
		int i;
		if(jumlah_nasabah <= 0 ){
			printf("\x1b[31mTidak Ditemukan Data \n");
		}else{
			for(i=0;i<jumlah_nasabah;i++){
				printf("\x1b[36m::Data Nasabah Bank Ke-%d\n",i+1);
				printf("::Nomor Rekening      : %d\n",n[i].rekening);
				printf("::Nama Nasabah        : %s\n",n[i].nama);
				printf("::Alamat Nasabah      : %s\n",n[i].alamat);
				printf("::Saldo Nasabah       : %f\n",n[i].saldo);
				printf("::Nomor Telepon       : %s\n",n[i].nomortelepon);
				printf("\x1b[32m------------------------------------------\n");
			}
			printf("\x1b[32mDatabase berhasil ditampilkan \n");
		}
		tambahriwayat(2,-1);
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//-------------------------------------
	
	/*tambah data nasabah*/
	void tambah_data_nasabah(){
		int i,temp,banyakdata;
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+========================================+\n");
		printf("|-------------Bank InDoNesIa-------------|\n");
		printf("|       Tambahkan Database Nasabah       |\n");
		printf("+========================================+\n");
		gotoxy(0,6);
		printf("------------------------------------------\n");
		gotoxy(0,4);
		printf("Data input nasabah maksimum = %d\n",max_nasabah-jumlah_nasabah);
		printf("Banyak data yang ingin ditambahkan =\x1b[36m");
		scanf("%d",&temp);
		banyakdata = temp;
		temp += jumlah_nasabah;
		gotoxy(0,7);
		if(temp>max_nasabah){
			printf("\x1b[31mMaximum data nasabah yang dapat ditambahkan adalah %d\x1b[32m\n",max_nasabah-jumlah_nasabah);
		}else{
			for(i=jumlah_nasabah;i<temp;i++){
				printf("\x1b[36m::Data Nasabah Bank Ke-%d\n",i+1);
				printf("::Nomor Rekening      : ");
				scanf("%d",&n[i].rekening);
				printf("::Nama Nasabah        : ");
				scanf(" %[^\n]",&n[i].nama);
				printf("::Alamat Nasabah      : ");
				scanf(" %[^\n]",&n[i].alamat);
				printf("::Saldo Nasabah       : ");
				scanf("%f",&n[i].saldo);
				printf("::Nomor Telepon       : ");
				scanf(" %[^\n]",&n[i].nomortelepon);
				printf("\x1b[32m------------------------------------------\n");
			}
			jumlah_nasabah = temp;
			tambahriwayat(3,banyakdata);
			printf("\x1b[32mDatabase berhasil ditambahkan \n");
		}
		
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//------------------------------------
	
	/*hapus data nasabah*/
	void hapus_data_nasabah(){
		int no_rekening_hapus;
		int jumlah_dihapus =0;
		int lock = 1;
		int flag = 0;
		int i,j;
		char pilih;
		char yes = 'y';
		char no = 'n';
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+========================================+\n");
		printf("|-------------Bank InDoNesIa-------------|\n");
		printf("|         Hapus Database Nasabah         |\n");
		printf("+========================================+\n");
		gotoxy(0,6);
		printf("------------------------------------------\n");
		gotoxy(0,4);
		printf("Terdapat data nasabah sebanyak = %d\n",jumlah_nasabah);
		printf("Masukkan No Rekening yang akan dihapus =\x1b[36m");
		scanf("%d",&no_rekening_hapus);
		gotoxy(0,7);
		for(i=0;i<jumlah_nasabah;i++){
			if(n[i].rekening==no_rekening_hapus){
				flag=1;
				printf("\x1b[36m::Data Nasabah Bank Ke-%d\n",i+1);
				printf("::Nomor Rekening      : %d\n",n[i].rekening);
				printf("::Nama Nasabah        : %s\n",n[i].nama);
				printf("::Alamat Nasabah      : %s\n",n[i].alamat);
				printf("::Saldo Nasabah       : %f\n",n[i].saldo);
				printf("::Nomor Telepon       : %s\n",n[i].nomortelepon);
				printf("\x1b[32m------------------------------------------\n");
				lock =1;
				while(lock==1){
					printf("\x1b[32mApakah ingin dihapus (y/n)?");
					pilih = getch();
					printf("\n");
					if((int)pilih==(int)yes||(int)pilih==(int)no){	
						lock=0;
					}else{
						printf("\x1b[31mPilihan hanya y dan n saja!!\n");		
					}
				}
				if((int)pilih==(int)yes){
					jumlah_dihapus+=1;
					for(j=i;j<jumlah_nasabah-1;j++){
						n[j].rekening = n[j+1].rekening;
						n[j].saldo = n[j+1].saldo;
						strcpy(n[j].nama, n[j+1].nama);
						strcpy(n[j].alamat, n[j+1].alamat);
						strcpy(n[j].nomortelepon, n[j+1].nomortelepon);
					}
				}
			}
		}
		if(flag == 0){
			printf("\x1b[31mTidak ditemukan data yang dicari\n");
		}
		jumlah_nasabah -= jumlah_dihapus;
		if(jumlah_dihapus>0){
			tambahriwayat(4,jumlah_dihapus);
		};
		printf("\x1b[32mDatabase yang dihapus ada %d  \n",jumlah_dihapus);
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//------------
	
	/*edit data nasabah*/
	void edit_data_nasabah(){
		int no_rekening_edit;
		int jumlah_diedit =0;
		int lock = 1;
		int flag = 0;
		int i,j;
		char pilih;
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+=========================================+\n");
		printf("|--------------Bank InDoNesIa-------------|\n");
		printf("|          Edit Database Nasabah          |\n");
		printf("+=========================================+\n");
		printf("Data apa yang akan anda edit ?");
		gotoxy(0,5);
		printf("1. Nama Nasabah");
		gotoxy(0,6);
		printf("2. Saldo Nasabah");
		gotoxy(18,5);
		printf("3. Alamat Nasabah");
		gotoxy(18,6);
		printf("4. Nomor Telepon Nasabah");
		gotoxy(0,8);
		printf("Terdapat data nasabah sebanyak = %d\n",jumlah_nasabah);
		gotoxy(0,9);
		printf("------------------------------------------\n");
		printf("Pilihan Anda         = \n");
		printf("Masukkan No Rekening = ");
		gotoxy(0,12);
		printf("------------------------------------------\n");
		lock =1;
		while(lock==1){
			gotoxy(23,10);
			pilih = getch();
			
			if((int)pilih==(int)'1'||(int)pilih==(int)'2'||(int)pilih==(int)'3'||(int)pilih==(int)'4'){
				lock = 0;
				printf("\x1b[36m%c",pilih);
				gotoxy(0,13);
				printf("                                    ");
			}else{
				gotoxy(0,13);
				printf("\x1b[31mInput Pilihan Tidak Valid !!");
			}
		}
		
		
		gotoxy(23,11);
		scanf("%d",&no_rekening_edit);
		gotoxy(0,13);
		for(i=0;i<jumlah_nasabah;i++){
			if(n[i].rekening==no_rekening_edit){
				jumlah_diedit+=1;
				flag=1;
				tambahriwayat(5,no_rekening_edit);
				printf("\x1b[36mxxData Nasabah Bank Ke-%d\n",i+1);
			
				if((int)pilih==(int)'1'){	
					printf("--EDIT NAMA\n");
					printf("::Nama Nasabah        : %s\n",n[i].nama);
					printf("::Ubah Nama           : ");
					scanf(" %[^\n]",&n[i].nama);
				}else if((int)pilih==(int)'2'){	
					printf("--EDIT SALDO\n");
					printf("::Saldo Nasabah       : %f\n",n[i].saldo);
					printf("::Ubah Saldo          : ");
					scanf("%f",n[i].saldo);
				}else if((int)pilih==(int)'3'){
					printf("--EDIT ALAMAT\n");
					printf("::Alamat Nasabah      : %s\n",n[i].alamat);
					printf("::Ubah Alamat         : ");
					scanf(" %[^\n]",&n[i].alamat);
				}else if((int)pilih==(int)'4'){
					printf("--EDIT NOMOR TELEPON\n");
					printf("::Nomor Telepon       : %s\n",n[i].nomortelepon);
					printf("::Ubah Nomor Telepon  : ");
					scanf(" %[^\n]",&n[i].nomortelepon);
				};		
				printf("\x1b[32m--Data berhasil di Edit\n");
				printf("\x1b[32m------------------------------------------\n");
			}
		}
		if(flag == 0){
			printf("\x1b[31mTidak ditemukan data yang dicari\n");
		}
		printf("\x1b[32mDatabase yang diEdit ada %d  \n",jumlah_diedit);
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//----------------------------
	
	/*cari data nasabah*/
	void cari_data_nasabah(){
		int jumlah_dicari =0;
		int lock = 1;
		int flag = 0;
		int i,j;
		int input_int;
		int data_ketemu = 0;
		float input_float;
		char input_text1[100];
		char input_text2[200];
		char pilih;
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+=========================================+\n");
		printf("|--------------Bank InDoNesIa-------------|\n");
		printf("|          Cari Database Nasabah          |\n");
		printf("+=========================================+\n");
		printf("Data apa yang akan anda cari ?");
		gotoxy(0,5);
		printf("1. Nama Nasabah");
		gotoxy(0,6);
		printf("2. Saldo Nasabah");
		gotoxy(18,5);
		printf("3. Alamat Nasabah");
		gotoxy(18,6);
		printf("4. Nomor Telepon Nasabah");
		gotoxy(18,7);
		printf("5. Rekening Nasabah");
		gotoxy(0,8);
		printf("------------------------------------------\n");
		gotoxy(0,9);
		printf("Terdapat data nasabah sebanyak = %d\n",jumlah_nasabah);
		printf("Pilihan Anda         = \n");
		printf("                     ");
		//printf("Masukkan No Rekening = ");
		gotoxy(0,12);
		printf("------------------------------------------\n");
		lock =1;
		while(lock==1){
			gotoxy(23,10);
			pilih = getch();
			
			if((int)pilih==(int)'1'||(int)pilih==(int)'2'||(int)pilih==(int)'3'||(int)pilih==(int)'4'||(int)pilih==(int)'5'){
				lock = 0;
				printf("\x1b[36m%c",pilih);
				gotoxy(0,13);
				printf("                                    ");
				gotoxy(0,11);
				switch((int)pilih){
					case (int)'1':
						tambahriwayat(6,1);
						printf("Masukkan Nama        = ");
						scanf(" %[^\n]",&input_text1);
						break;
					case (int)'2':
						tambahriwayat(6,2);
						printf("Masukkan Saldo       = ");
						scanf("%f",&input_float);
						break;
					case (int)'3':
						tambahriwayat(6,3);
						printf("Masukkan Alamat      = ");
						scanf(" %[^\n]",&input_text2);
						break;
					case (int)'4':
						tambahriwayat(6,4);
						printf("Masukkan No Telepon  = ");
						scanf(" %[^\n]",&input_text1);
						break;
					case (int)'5':
						tambahriwayat(6,5);
						printf("Masukkan No Rekening = ");
						scanf("%d",&input_int);
						break;
				}
			}else{
				gotoxy(0,13);
				printf("\x1b[31mInput Pilihan Tidak Valid !!");
			}
		}
		gotoxy(0,13);
		for(i=0;i<jumlah_nasabah;i++){
			data_ketemu = 0;
			switch((int)pilih){
				case (int)'1':
					if(strcmp(input_text1,n[i].nama)==0){
						data_ketemu=1;
						flag=1;	
						jumlah_dicari+=1;
					};
				break;
				case (int)'2':
					if(input_float==n[i].saldo){
						data_ketemu=1;
						flag=1;
						jumlah_dicari+=1;
					};
				break;
				case (int)'3':
					if(strcmp(input_text2,n[i].alamat)==0){
						data_ketemu=1;
						flag=1;
						jumlah_dicari+=1;
					};
				break;
				case (int)'4':
					if(strcmp(input_text1,n[i].nomortelepon)==0){
						data_ketemu=1;
						flag=1;
						jumlah_dicari+=1;
					};
				break;
				case (int)'5':
					if(input_int == n[i].rekening){
						data_ketemu=1;
						flag=1;
						jumlah_dicari+=1;
					};
				break;
			};
			
			if(data_ketemu==1){
				printf("\x1b[36m::Data Nasabah Bank Ke-%d\n",jumlah_dicari);
				printf("::Nomor Rekening      : %d\n",n[i].rekening);
				printf("::Nama Nasabah        : %s\n",n[i].nama);
				printf("::Alamat Nasabah      : %s\n",n[i].alamat);
				printf("::Saldo Nasabah       : %f\n",n[i].saldo);
				printf("::Nomor Telepon       : %s\n",n[i].nomortelepon);
				printf("\x1b[32m------------------------------------------\n");
			}
		}
		if(flag == 0){
			printf("\x1b[31mTidak ditemukan data yang dicari\n");
		}
		printf("\x1b[32mDatabase yang dicari ada %d  \n",jumlah_dicari);
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	
	//----
	
	/*transfer dana nasabah*/
	void transfer_dana_nasabah(){
		int i;
		int id_pengirim=-1;
		int id_penerima=-1;
		float jumlah_transfer = 0;
		int rekening_pengirim;
		int rekening_penerima;
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+=========================================+\n");
		printf("|-------------Bank  InDoNesIa-------------|\n");
		printf("|          Transfer Dana Nasabah          |\n");
		printf("+=========================================+\n");
		gotoxy(0,4);
		printf("Jumlah database nasabah = %d\n",jumlah_nasabah);
		printf("\x1b[36mNomor Rekening Pengirim = ");
		scanf("%d",&rekening_pengirim);
		printf("Nomor Rekening Penerima = ");
		scanf("%d",&rekening_penerima);
		printf("Jumlah Transfer         = ");
		scanf("%f",&jumlah_transfer);
		gotoxy(0,8);
		printf("------------------------------------------\n");
		for(i=0;i<jumlah_nasabah;i++){
			if(id_pengirim!=-1&&id_penerima!=-1){
				break;
			};
			if(rekening_pengirim==n[i].rekening){
				id_pengirim=i;
			}
			if(rekening_penerima==n[i].rekening){
				id_penerima=i;
			}
		};
		
		gotoxy(0,9);
		if(id_pengirim!=-1&&id_penerima!=-1){
			printf("Saldo rekening pengirim sebelumnya = %f\n",n[id_pengirim].saldo);
			if(n[id_pengirim].saldo>=jumlah_transfer){
				n[id_pengirim].saldo -= jumlah_transfer;
				n[id_penerima].saldo += jumlah_transfer;
				printf("Saldo rekening pengirim sekarang   = %f\n",n[id_pengirim].saldo);
				tambahriwayat(8,-1);
				printf("\x1b[32mBerhasil ditransfer \n");
			}else{
				printf("\x1b[31mSaldo tidak mencukupi untuk melakukan transfer\x1b[32m\n");
			}
			
		}else{
			printf("\x1b[31mrekening_pengirim atau rekening_penerima tidak ditemukan\x1b[32m\n");
		}
		
		printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
		getch();
	}
	//------------------------------------
	
	/*sort data nasabah*/
	void sort_data_nasabah(){
		int lock = 1;
		int flag = 0;
		char pilih;
		system("cls");
		system("color 02");
		gotoxy(0,0);
		printf("+=========================================+\n");
		printf("|--------------Bank InDoNesIa-------------|\n");
		printf("|          Sort Database Nasabah          |\n");
		printf("+=========================================+\n");
		printf("Berdasar data apa yang akan anda sortir ?");
		gotoxy(0,5);
		printf("1. Nama Nasabah");
		gotoxy(0,6);
		printf("2. Saldo Nasabah");
		gotoxy(18,5);
		printf("3. Alamat Nasabah");
		gotoxy(18,6);
		printf("4. Nomor Telepon Nasabah");
		gotoxy(18,7);
		printf("5. Rekening Nasabah");
		gotoxy(0,8);
		printf("------------------------------------------\n");
		gotoxy(0,9);
		printf("Terdapat data nasabah sebanyak = %d\n",jumlah_nasabah);
		printf("Pilihan Anda         = \n");
		printf("                     ");
		//printf("Masukkan No Rekening = ");
		gotoxy(0,12);
		printf("------------------------------------------\n");
		lock =1;
		while(lock==1){
			gotoxy(23,10);
			pilih = getch();
			printf("\x1b[36m%c",pilih);
			if((int)pilih==(int)'1'||(int)pilih==(int)'2'||(int)pilih==(int)'3'||(int)pilih==(int)'4'||(int)pilih==(int)'5'){
				lock = 0;
				
				gotoxy(0,13);
				printf("                                    ");
				gotoxy(0,11);
				switch((int)pilih){
					case (int)'1':
						flag = 1;
						tambahriwayat(9,1);
						sort_ascending_nama();
						tampilkan_data_nasabah();
						break;
					case (int)'2':
						flag = 1;
						tambahriwayat(9,2);
						sort_ascending_saldo();
						tampilkan_data_nasabah();
						break;
					case (int)'3':
						flag = 1;
						tambahriwayat(9,3);
						sort_ascending_alamat();
						tampilkan_data_nasabah();
						break;
					case (int)'4':
						flag = 1;
						tambahriwayat(9,4);
						sort_ascending_nomortelepon();
						tampilkan_data_nasabah();
						break;
					case (int)'5':
						flag = 1;
						tambahriwayat(9,5);
						sort_ascending_rekening();
						tampilkan_data_nasabah();
						break;
				}
			}else{
				gotoxy(0,13);
				lock = 0;
				printf("\x1b[31mInput Pilihan Tidak Valid !!");
			}
		}
		gotoxy(0,14);
		if(flag == 0){
			printf("\x1b[32mTekan tombol apa saja untuk kembali ke menu awal");
			getch();
		}
		
	}
	
	//----
	
	
	void sort_ascending_nama(){
		struct nasabah temp;
		int i,j;
		for(i=0;i<jumlah_nasabah-1;i++){
			for(j=jumlah_nasabah-1;j>i;j--){
				if(strcmp(n[j-1].nama,n[j].nama)>0){
					strcpy(temp.nama,n[j-1].nama);
					strcpy(temp.alamat,n[j-1].alamat);
					strcpy(temp.nomortelepon,n[j-1].nomortelepon);
					temp.rekening = n[j-1].rekening;
					temp.saldo = n[j-1].saldo;	
					//-----------------------------
					strcpy(n[j-1].nama,n[j].nama);
					strcpy(n[j-1].alamat,n[j].alamat);
					strcpy(n[j-1].nomortelepon,n[j].nomortelepon);
					n[j-1].rekening = n[j].rekening;
					n[j-1].saldo = n[j].saldo;
					//-----------------------------
					strcpy(n[j].nama,temp.nama);
					strcpy(n[j].alamat,temp.alamat);
					strcpy(n[j].nomortelepon,temp.nomortelepon);
					n[j].rekening = temp.rekening;
					n[j].saldo = temp.saldo;
				}
			}		
		}
	}
	
	void sort_ascending_alamat(){
		struct nasabah temp;
		int i,j;
		for(i=0;i<jumlah_nasabah-1;i++){
			for(j=jumlah_nasabah-1;j>i;j--){
				if(strcmp(n[j-1].alamat,n[j].alamat)>0){
					strcpy(temp.nama,n[j-1].nama);
					strcpy(temp.alamat,n[j-1].alamat);
					strcpy(temp.nomortelepon,n[j-1].nomortelepon);
					temp.rekening = n[j-1].rekening;
					temp.saldo = n[j-1].saldo;	
					//-----------------------------
					strcpy(n[j-1].nama,n[j].nama);
					strcpy(n[j-1].alamat,n[j].alamat);
					strcpy(n[j-1].nomortelepon,n[j].nomortelepon);
					n[j-1].rekening = n[j].rekening;
					n[j-1].saldo = n[j].saldo;
					//-----------------------------
					strcpy(n[j].nama,temp.nama);
					strcpy(n[j].alamat,temp.alamat);
					strcpy(n[j].nomortelepon,temp.nomortelepon);
					n[j].rekening = temp.rekening;
					n[j].saldo = temp.saldo;
				}
			}		
		}
	}
	
	void sort_ascending_nomortelepon(){
		struct nasabah temp;
		int i,j;
		for(i=0;i<jumlah_nasabah-1;i++){
			for(j=jumlah_nasabah-1;j>i;j--){
				if(strcmp(n[j-1].nomortelepon,n[j].nomortelepon)>0){
					strcpy(temp.nama,n[j-1].nama);
					strcpy(temp.alamat,n[j-1].alamat);
					strcpy(temp.nomortelepon,n[j-1].nomortelepon);
					temp.rekening = n[j-1].rekening;
					temp.saldo = n[j-1].saldo;	
					//-----------------------------
					strcpy(n[j-1].nama,n[j].nama);
					strcpy(n[j-1].alamat,n[j].alamat);
					strcpy(n[j-1].nomortelepon,n[j].nomortelepon);
					n[j-1].rekening = n[j].rekening;
					n[j-1].saldo = n[j].saldo;
					//-----------------------------
					strcpy(n[j].nama,temp.nama);
					strcpy(n[j].alamat,temp.alamat);
					strcpy(n[j].nomortelepon,temp.nomortelepon);
					n[j].rekening = temp.rekening;
					n[j].saldo = temp.saldo;
				}
			}		
		}
	}
	
	void sort_ascending_saldo(){
		struct nasabah temp;
		int i,j;
		for(i=0;i<jumlah_nasabah-1;i++){
			for(j=jumlah_nasabah-1;j>i;j--){
				if(n[j-1].saldo > n[j].saldo){
					strcpy(temp.nama,n[j-1].nama);
					strcpy(temp.alamat,n[j-1].alamat);
					strcpy(temp.nomortelepon,n[j-1].nomortelepon);
					temp.rekening = n[j-1].rekening;
					temp.saldo = n[j-1].saldo;	
					//-----------------------------
					strcpy(n[j-1].nama,n[j].nama);
					strcpy(n[j-1].alamat,n[j].alamat);
					strcpy(n[j-1].nomortelepon,n[j].nomortelepon);
					n[j-1].rekening = n[j].rekening;
					n[j-1].saldo = n[j].saldo;
					//-----------------------------
					strcpy(n[j].nama,temp.nama);
					strcpy(n[j].alamat,temp.alamat);
					strcpy(n[j].nomortelepon,temp.nomortelepon);
					n[j].rekening = temp.rekening;
					n[j].saldo = temp.saldo;
				}
			}		
		}
	}
	
	void sort_ascending_rekening(){
		struct nasabah temp;
		int i,j;
		for(i=0;i<jumlah_nasabah-1;i++){
			for(j=jumlah_nasabah-1;j>i;j--){
				if(n[j-1].rekening > n[j].rekening){
					strcpy(temp.nama,n[j-1].nama);
					strcpy(temp.alamat,n[j-1].alamat);
					strcpy(temp.nomortelepon,n[j-1].nomortelepon);
					temp.rekening = n[j-1].rekening;
					temp.saldo = n[j-1].saldo;	
					//-----------------------------
					strcpy(n[j-1].nama,n[j].nama);
					strcpy(n[j-1].alamat,n[j].alamat);
					strcpy(n[j-1].nomortelepon,n[j].nomortelepon);
					n[j-1].rekening = n[j].rekening;
					n[j-1].saldo = n[j].saldo;
					//-----------------------------
					strcpy(n[j].nama,temp.nama);
					strcpy(n[j].alamat,temp.alamat);
					strcpy(n[j].nomortelepon,temp.nomortelepon);
					n[j].rekening = temp.rekening;
					n[j].saldo = temp.saldo;
				}
			}		
		}
	}
//---------------------------------------------
void main() {
	konfigurasiUI();
	login();
	int x=1;
	while(x==1){
		tampilmenu();
	}
}
