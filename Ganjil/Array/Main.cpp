#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Data{
	string kode, nama, nomorDebit, jenisDebit;
	int totalBel, jumlahUang, kembalian;
}kasir, pembeli;

struct Info{
	string kode;
	int jumlah, total, harga, diskon, minBel;
	string nama;
}barang[100], belanja[100];

char tombol;
int indeksBelanja = 0;

	
string CetakGaris(int banyak);
char GetOption();
void Config();
int Total(int harga, int jumlah, int diskon);
void RincianBelanja();
void CetakStruk();
void InputBelanja();

int main() {
	barang[0].kode = "P01";
	barang[0].harga = 10000;
	barang[0].nama = "Pulpen";
	barang[0].diskon = 10;
	barang[0].minBel = 10;
	
	barang[1].kode = "P02";
	barang[1].harga = 3000;
	barang[1].nama = "Pensil";
	barang[1].diskon = 5;
	barang[1].minBel = 5;
	
	barang[2].kode = "P03";
	barang[2].harga = 2000;
	barang[2].nama = "Penghapus";
	barang[2].diskon = 10;
	barang[2].minBel = 10;
	
	barang[3].kode = "P04";
	barang[3].harga = 5000;
	barang[3].nama = "Penggaris";
	barang[3].diskon = 10;
	barang[3].minBel = 5;
	
	barang[4].kode = "P05";
	barang[4].harga = 6000;
	barang[4].nama = "Rautan";
	barang[4].diskon = 0;
	barang[4].minBel = 0;

	
	Menu:
	barang[0].kode = "P01";
	char pilihan = GetOption();
	switch(pilihan) {
		case '1':
			Config();
			goto Menu;
		case '2':
			InputBelanja();
			goto Menu;
		case '3':
			CetakStruk();
			goto Menu;
		case '4':
			system("cls");
			cout << "Bye....";
			Sleep(2000);
			break;
		default:
			cout << "Anda salah memasukan pilihan"; getch();
			goto Menu;
	}

 	return 0;
}

string CetakGaris(int banyak) {
	string garis;
	for(int i = 0; i < banyak; i++) {
		garis += "-";
	}
	return garis;
}

char GetOption() {
	char pilihan;
	
	system("cls");
	cout << CetakGaris(20) << endl;
	cout << "\tMENU" << endl;
	cout << CetakGaris(20) << endl;
	cout << "1. Config" << endl;
	cout << "2. Input belanja" << endl;
	cout << "3. Cetak struk terakhir" << endl;
	cout << "4. Exit" << endl;
	cout << CetakGaris(20) << endl;
	cout << "Masukan pilihan [1..4] ";
	cin >> pilihan;
	cin.ignore();
	return pilihan;
}

void Config() {
	system("cls");
	cout << "Masukan kode kasir : ";
	cin >> kasir.kode; cin.ignore();
	
	Nama:
	cout << "Masukan nama kasir : ";
	getline(cin, kasir.nama);
	if(kasir.nama == "") {
		cout << "     Masukan nama terlebih dahulu" << endl;
		goto Nama;
	} else {
		cout << "\n******Selamat datang kasir " << kasir.nama << ", selamat bekerja********" << endl;
		cout << "Tekan ENTER untuk lanjut ";
		do {
			tombol = getch();
		} while(!(tombol == (char)13));
	}
}

int Total(int harga, int jumlah, int diskon) {
	int total, totalSem;
	totalSem = harga*jumlah;
	total = totalSem - (totalSem*diskon/100);
	return total;
}

void RincianBelanja(int indeks) {
	pembeli.totalBel = 0;
	
	cout << CetakGaris(65) << endl;
	cout << setiosflags(ios::left) << setw(6) << "| No" << setw(23) << "| Nama Barang "
		 << setw(8) << "| Banyaknya " << setw(9) << "| Diskon "
		 << setw(14) << "| total " << "|" << endl;
	cout << CetakGaris(65) << endl;
	
	for(int i = 0; i <= indeks; i++) {
		cout << "| " << setw(3) << i+1 << " | " << setw(20) << belanja[i].nama << " | "
			 << setw(9) << belanja[i].jumlah << " | " << belanja[i].diskon;
		if(belanja[i].diskon < 10) {
			cout << setw(5) << "%";
		} else{
			cout << setw(4) << "%";
		}
		cout  << " | Rp. " << setw(7) << belanja[i].total <<" |" << endl;
		pembeli.totalBel += belanja[i].total;
	}
	cout << CetakGaris(65) << endl;
	cout << "\t\t\tTotal: Rp. " << pembeli.totalBel;
}

void CetakStruk() {
	time_t waktu;
	time(&waktu);
	
	if(kasir.kode == "") {
		cout << "\nMasukan data kasir terlebih dahulu"; getch();
	} else if(belanja[indeksBelanja].nama == "") {
		cout << "\nBelum ada pembeli"; getch();
	} else {
		system("cls");
		cout << "\t\t      Toko Serba Diskon" << endl;
		cout << "\t\tJalan Cemara 20 Jakarta Selatan" << endl;
		cout << "\t\t   Senyum Anda, Bahagia Kami" << endl;
		cout << "\t\t   " << ctime(&waktu) << endl;
		RincianBelanja(indeksBelanja);
		cout << "\n\nBarang yang telah dibeli tidak dapat dikembalikan," << endl;
		cout << "terima kasih " << pembeli.nama << " atas kunjungan anda" << endl;
		cout << "Kasir : " << kasir.nama << ", " << kasir.kode << endl;
		getch();
	}
}

void InputBelanja() {
	indeksBelanja = 0;
	int indeksBarang = 0;
	int diskMem = 0;
	
	if(kasir.kode == ""){
		cout << "\nMasukan data kasir terlebih dahulu"; getch();
	} else {
		system("cls");
		int member;
		string kodeBarang;
		
		cout << "Masukan nama \t\t: ";
		getline(cin, pembeli.nama);
		do {
			cout << "Ada member [0..1] \t: ";
			cin >> member;
		} while(!((member == 0) || (member == 1)));
		
		if(member == 1) {
			diskMem = 1;
		}

		Input:
		do {
			Kode_Barang:
			indeksBarang = 0;
			cout << "Masukan kode barang \t: ";
			cin >> kodeBarang;

			while(indeksBarang < 5) {
				if(kodeBarang == barang[indeksBarang].kode) {
					belanja[indeksBelanja].nama = barang[indeksBarang].nama;
					belanja[indeksBelanja].diskon = barang[indeksBarang].diskon;
					break;
				}
				indeksBarang++;
			}
			if(!(kodeBarang == barang[indeksBarang].kode)) {
				cout << "    Barang tidak ditemukan"; getch();
				cout << endl;
				goto Kode_Barang;
			}
			cout << "Masukan banyaknya \t: ";
			cin >> belanja[indeksBelanja].jumlah;
			
			Check_Data:
			cout << "Data yang dimasukan benar? [y/n] : ";
			cin >> tombol;
			if(tombol == 'y' || tombol == 'Y') {
				if(barang[indeksBarang].jumlah >= barang[indeksBarang].minBel) {
					belanja[indeksBelanja].diskon += diskMem;
				} else {
					belanja[indeksBelanja].diskon = diskMem;
				}
				belanja[indeksBelanja].total = Total(barang[indeksBarang].harga, belanja[indeksBelanja].jumlah, belanja[indeksBelanja].diskon);
			} else if(tombol == 'n' || tombol == 'N') {
				cin.ignore();
				system("cls");
				goto Input;
			} else {
				goto Check_Data;
			}
			
			do {
				cout << "Ada data lagi [y/n] ";
				cin >> tombol;
				if(tombol == 'y' || tombol == 'Y') {
					indeksBelanja++;
					cin.ignore();
					system("cls");
					break;
				}
			} while(!(tombol == 'n' || tombol == 'N'));
		} while(tombol == 'y' || tombol == 'Y');
		
		system("cls");
		cout << "Rincian belanja " << pembeli.nama << " : " << endl;
		RincianBelanja(indeksBelanja);
		cout << endl;
		
		Bayar:
		string bayar;
		cout <<"Bayar tunai [ya/tidak]: ";
		cin >> bayar;
		cout << endl;
		if(bayar == "ya" || bayar == "YA") {
			cout << "Masukan jumlah uang : ";
			cin >> pembeli.jumlahUang;
			pembeli.kembalian = pembeli.jumlahUang - pembeli.totalBel;
			cout << "Jumlah kembalian " << pembeli.nama << " adalah Rp. " << pembeli.kembalian << endl;
		} else if(bayar == "tidak" || bayar == "TIDAK") {
			cout << "Masukan nomor kartu debit \t: ";
			cin >> pembeli.nomorDebit;
			cout << "Masukan jenis debit \t\t: ";
			cin >> pembeli.jenisDebit;
			cout << pembeli.nama << ", menggunakan debit " << pembeli.jenisDebit
				 << " dengan nomor " << pembeli.nomorDebit << endl;
		} else {
			goto Bayar;
		}
		cout << "Tekan enter untuk mencetak struk";
		do {
			tombol = getch();
		} while(!(tombol == (char)13));
		CetakStruk();
	}
}
