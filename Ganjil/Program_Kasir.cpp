#include <iostream>
#include <string>
#include <windows.h>
#include <string.h>
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
	char kode[3];
	int jumlah, total, harga, diskon, minBel;
	string nama;
}barang[100];

char tombol;
int indeks = 0;

string CetakGaris(int banyak);
char GetOption();
void Config();
int Total(int harga, int jumlah, int diskon);
void RincianBelanja();
void CetakStruk();
void InputBelanja();

int main() {
	Menu:
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
	system("cls");
	char pilihan;
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
	
	cout << CetakGaris(62) << endl;
	cout << setiosflags(ios::left) << setw(6) << "| No" << setw(23) << "| Nama Barang "
		 << setw(8) << "| Banyaknya " << setw(9) << "| Diskon "
		 << setw(11) << "| total " << "|" << endl;
	cout << CetakGaris(62) << endl;
	
	for(int i = 0; i <= indeks; i++) {
		cout << "| " << setw(3) << i+1 << " | " << setw(20) << barang[i].nama << " | "
			 << setw(9) << barang[i].jumlah << " | " << barang[i].diskon;
		if(barang[i].diskon < 10) {
			cout << setw(5) << "%";
		} else{
			cout << setw(4) << "%";
		}
		cout  << " | " << setw(8) << barang[i].total <<" |" << endl;
		pembeli.totalBel += barang[i].total;
	}
	cout << CetakGaris(62) << endl;
	cout << "\t\t\tTotal: Rp. " << pembeli.totalBel;
}

void CetakStruk() {
	time_t waktu;
	time(&waktu);
	
	if(kasir.kode == "") {
		cout << "\nMasukan data kasir terlebih dahulu"; getch();
	} else if(barang[indeks].nama == "") {
		cout << "\nBelum ada pembeli"; getch();
	} else {
		system("cls");
		cout << "\t\t      Toko Serba Diskon" << endl;
		cout << "\t\tJalan Cemara 20 Jakarta Selatan" << endl;
		cout << "\t\t   Senyum Anda, Bahagia Kami" << endl;
		cout << "\t\t   " << ctime(&waktu) << endl;
		RincianBelanja(indeks);
		cout << "\n\nBarang yang telah dibeli tidak dapat dikembalikan," << endl;
		cout << "terima kasih " << pembeli.nama << " atas kunjungan anda" << endl;
		cout << "Kasir : " << kasir.nama << ", " << kasir.kode << endl;
		getch();
	}
}

void InputBelanja() {
	indeks = 0;
	int diskMem = 0;
	
	if(kasir.kode == ""){
		cout << "\nMasukan data kasir terlebih dahulu"; getch();
	} else {
		system("cls");
		int member;
		char kodeBarang[3];
		
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
			cout << "Masukan kode barang \t: ";
			cin >> kodeBarang;
			ifstream fileIn("data.txt");
			while(!(fileIn.eof())) {
				fileIn >> barang[indeks].kode >> barang[indeks].harga
					   >> barang[indeks].nama >> barang[indeks].diskon
					   >> barang[indeks].minBel;
				if(strcmp(kodeBarang, barang[indeks].kode) == 0) {
					break;
				}
			}
			if(!(strcmp(kodeBarang, barang[indeks].kode) == 0)) {
				cout << "    Barang tidak ditemukan"; getch();
				cout << endl;
				goto Kode_Barang;
			}
			cout << "Masukan banyaknya \t: ";
			cin >> barang[indeks].jumlah;
			
			Check_Data:
			cout << "Data yang dimasukan benar? [y/n] : ";
			cin >> tombol;
			if(tombol == 'y' || tombol == 'Y') {
				if(barang[indeks].jumlah >= barang[indeks].minBel) {
					barang[indeks].diskon += diskMem;
				} else {
					barang[indeks].diskon = diskMem;
				}
				barang[indeks].total = Total(barang[indeks].harga, barang[indeks].jumlah, barang[indeks].diskon);
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
					indeks++;
					cin.ignore();
					system("cls");
					break;
				}
			} while(!(tombol == 'n' || tombol == 'N'));
		} while(tombol == 'y' || tombol == 'Y');
		
		system("cls");
		cout << "Rincian belanja " << pembeli.nama << " : " << endl;
		RincianBelanja(indeks);
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
			cout << "Jumlah kembalian " << pembeli.nama << " adalah " << pembeli.kembalian << endl;
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
