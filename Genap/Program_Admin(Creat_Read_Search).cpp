#include <iostream>
#include <fstream> //ofstream, ifstream
#include <string>
#include <conio.h> // getch
#include <iomanip> // setiosflags, setw
#include <string.h> //strcmp
#include <windows.h> // Sleep
#include <ctime> // time_t, time, ctime
using namespace std;

struct Data {
	char NIM[11], nama[100], mataKuliah[50], huruf;
	int sks, absen;
	float tugas[3];
	float uts, uas, akhir, rataTugas;
}mhs;

string CetakGaris(int banyak);
char GetOption();
void InputBio();
float RataTugas(float tugas1, float tugas2, float tugas3);
float NilaiAkhir(int absen, float rataTugas, float uts, float uas);
char KonversiHuruf(float nilaiAkhir);
string CetakWaktu();
void ReadBio();
void DetailNilai();

int main() {
	Menu:
	char pilihan = GetOption();
	switch(pilihan) {
		case '1':
			InputBio();
			goto Menu;
		case '2':
			ReadBio();
			goto Menu;
		case '3':
			DetailNilai();
			goto Menu;
		case '4':
			system("cls");
			cout << "Bye....";
			Sleep(2000);
			break;
		default:
			cout << "Data yang anda masukin salah, silakan ulangi"; getch();
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
	cout << "1. Input Biodata" << endl;
	cout << "2. Lihat Nilai" << endl;
	cout << "3. Detail Nilai" << endl;
	cout << "4. Exit" << endl;
	cout << CetakGaris(20) << endl;
	cout << "Masukan pilihan [1..4]: ";
	cin >> pilihan;
	return pilihan;
}

float RataTugas(float tugas1, float tugas2, float tugas3) {
	return (tugas1+tugas2+tugas3)/3;
}

float NilaiAkhir(int absen, float rataTugas, float uts, float uas) {
	return (((absen/14)10)+(rataTugas*20/100)+(uts*30/100)+(uas*40/100));
}

char KonversiHuruf(float nilaiAkhir) {
	char huruf;
	huruf = nilaiAkhir >= 90 ? 'A' : nilaiAkhir >= 79 ? 'B' :
			nilaiAkhir >= 69 ? 'C' : nilaiAkhir >= 59 ? 'D' : 'E';
	return huruf;
}

void InputBio() {
	char tombol;
	
	do {
		Input:
		ofstream fileOut("data.bin", ios::app | ios::binary);
		int tugasKe = 0;
		system("cls");
		cout << CetakGaris(26) << endl;
		cout << "\tInput Data" << endl;
		cout << CetakGaris(26) << endl << endl;
		cout << "Masukan NIM \t\t: "; cin >> mhs.NIM; cin.ignore();
		cout << "Masukan nama \t\t: "; gets(mhs.nama);
		cout << "Masukan mata kuliah \t: "; gets(mhs.mataKuliah);
		cout << "Masukan SKS \t\t: "; cin >> mhs.sks;
	
		Absen:
		cout << "Masukan jumlah absen[0..14] : "; cin >> mhs.absen;
		if(mhs.absen >= 0 && mhs.absen <= 11) {
			do {
				cout << "nilai absen yang dimasukan tidak memenuhi kriteria, data yang anda masukan sudah benar? [y/n] ";
				cin >> tombol;
				if(tombol == 'n' || tombol == 'N') {
					goto Input;
				} else if(tombol == 'y' || tombol == 'Y') {
					mhs.uas = 0;
					mhs.uts = 0;
					for(int i = 0; i < 3; i++) {
						mhs.tugas[i] = 0;
					}
				}
			} while(!(tombol == 'y' || tombol == 'Y'));	
		} else if(mhs.absen > 11 && mhs.absen <= 14) {
			cout << "Masukan nilai tugas";
			do {
				cout << "\nmasukan nilai tugas " << tugasKe+1 << "\t: ";
				cin >> mhs.tugas[tugasKe];
				if(tugasKe == 2) break;
				cout << "   Ada nilai tugas lagi? [tekan X bila tidak ada tugas lagi]";
				tombol = getch();
				tugasKe++;
				if(tombol == 'x' || tombol == 'X') {
					if(tugasKe == 1) {
						mhs.tugas[tugasKe] = 0;
						mhs.tugas[tugasKe+1] = 0;
					} else {
						mhs.tugas[tugasKe] = 0;
					}
					cout << endl;
					break;
				}
			} while(!(tombol == 'x' || tombol == 'X'));
			cout << "Masukan UTS \t\t: "; cin >> mhs.uts;
			cout << "Masukan UAS \t\t: "; cin >> mhs.uas;
			
			Check_Data:
			cout << "Data yang dimasukan sudah benar ?[y/n] "; cin >> tombol;
			if(tombol == 'n' || tombol == 'N') {
				goto Input;
			} else if(!(tombol == 'y' || tombol == 'Y')){
				goto Check_Data;
			}
		} else {
			cout << "Anda memasuki di luar batas, silakan ulangi"; getch();
			cout << endl;
			goto Absen;
		}
		
		mhs.rataTugas = RataTugas(mhs.tugas[0], mhs.tugas[1], mhs.tugas[2]);
		mhs.akhir = NilaiAkhir(mhs.absen, mhs.rataTugas, mhs.uts, mhs.uas);
		mhs.huruf = KonversiHuruf(mhs.akhir);
		fileOut.write((char*)&mhs, sizeof(mhs));
		do {
			cout << "Ada data lagi [y/n] "; cin >> tombol;
			if(tombol == 'y' || tombol == 'Y') break;
		} while(!(tombol == 'n' || tombol == 'N'));
		
		fileOut.close();
	} while(tombol == 'y' || tombol == 'Y');
}

string CetakWaktu() {
	time_t waktuSekarang;
	time(&waktuSekarang);
	return ctime(&waktuSekarang);
}

void ReadBio() {
	system("cls");
	ifstream fileIn("data.bin", ios::binary);
	fileIn.read((char*)&mhs, sizeof(mhs));
	if(!fileIn | mhs.NIM == 0) {
		cout << "Tidak ada data"; getch();
	} else {
		cout << CetakGaris(97) << endl;
		cout << setiosflags(ios::left) << setw(13) << "| NIM "
		 	 << setw(28) << "| Nama " << setw(33) << "| Mata Kuliah "
		 	 << setw(3) << "| SKS " << setw(8) << "| Akhir "
		 	 << setw(5) << "| Huruf |" << endl;
		cout << CetakGaris(97) << endl;
		while(!fileIn.eof()) {
			cout << "| " << mhs.NIM << " | ";
			if(strlen(mhs.nama) > 25) {
				for(int i = 0; i < 25; i++) {
					cout << mhs.nama[i];
				}
			} else {
				cout << setw(25) << mhs.nama;
			}
			cout << " | " << setw(30) << mhs.mataKuliah << " | " << setw(3) << mhs.sks << " | "
		 		 << setw(5) << setprecision(4) << mhs.akhir << " | " << setw(5) << mhs.huruf << " |" << endl;
			fileIn.read((char*)&mhs, sizeof(mhs));
		}
		cout << CetakGaris(97) << endl;
		cout << "Data diatas di cetak pada " << CetakWaktu(); getch();
	}
	fileIn.close();
}

void DetailNilai() {
	char NIM[10];
	ifstream fileIn("data.bin", ios::binary);
	
	system("cls");
	cout << CetakGaris(35) << endl;
	cout << "\tCari Data Mahasiswa" << endl;
	cout << CetakGaris(35) << endl;
	cout << "Masukan NIM : ";
	cin >> NIM;
	cout << endl;
	fileIn.read((char*)&mhs, sizeof(mhs));
	if(!fileIn) {
		cout << "Data tidak ditemukan"; getch();
	} else {
		while(!(fileIn.eof())) {
			if(strcmp(NIM, mhs.NIM) == 0) {
				cout << CetakGaris(114) << endl;
				cout << setiosflags(ios::left) << setw(13) << "| NIM "
		 			 << setw(28) << "| Nama " << setw(33) << "| Mata Kuliah "
		 			 << setw(3) << "| SKS " << setw(5) << "| Absen " << setw(13) << "| Rata Tugas "
		 			 << setw(6) << "| UTS " << setw(6) << "| UAS |" << endl;
		 		cout << CetakGaris(114) << endl;
				cout << "| " << mhs.NIM << " | ";
					if(strlen(mhs.nama) > 25) {
						for(int i = 0; i < 25; i++) {
							cout << mhs.nama[i];
						}
					} else {
						cout << setw(25) << mhs.nama;
					}	
				cout << " | " << setw(30) << mhs.mataKuliah << " | " << setw(3) << mhs.sks << " | "
					 << setw(5) << mhs.absen << " | " << setw(10) << mhs.rataTugas << " | " << setw(3) << mhs.uts
					 << " | " << setw(3) << mhs.uas << " |" << endl; 
				cout << CetakGaris(114) << endl;
				cout << "Data diatas di cetak pada " << CetakWaktu(); getch();
				break;
			}
			fileIn.read((char*)&mhs, sizeof(mhs));
		}
		if(!(strcmp(NIM, mhs.NIM) == 0)) {
			cout << "Data tidak ditemukan"; getch();
		}
	}
}
