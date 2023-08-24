#include<iostream>
#include<iomanip>
#include<math.h>
#include<string>

using namespace std;

void luasPersegiPanjang (){
    double tinggi, lebar;
    
    cout << "--------------------------------------------\n";
    cout << "Masukan Lebar Persegi Panjang\t: ";
    cin >> lebar;
    cout << "Masukan Tinggi Persegi Panjang\t: ";
    cin >> tinggi;
    cout << "--------------------------------------------\n";
    double luas = lebar * tinggi;
    cout << "Luas Persegi Panjang\t: " << luas <<endl;
}

void kelilingPersegiPanjang(){
    double tinggi, lebar;
    
    cout << "--------------------------------------------\n";
    cout << "Masukan Lebar Persegi Panjang\t: ";
    cin >> lebar;
    cout << "Masukan Tinggi Persegi Panjang\t: ";
    cin >> tinggi;
    cout << "--------------------------------------------\n";
    double keliling = 2 * (lebar + tinggi);
    cout << "Luas Persegi Panjang\t: " << keliling <<endl;
}

void viewList (){
    int pilihan, attempt = 0;
    bool login = false;
    while(!login){
    cout << " ____________________________________________\n";
    cout << "|                                            |\n";
    cout << "|     Program Menghitung Luas & Keliling     |\n";
    cout << "|              Persegi Panjang               |\n";
    cout << "|____________________________________________|\n";
    cout << "|                     |                      |\n";
    cout << "|       1. Luas       |     2. Keliling      |\n";
    cout << "|_____________________|______________________|\n";
    cout << endl;
    cout << "Silahkan Pilih (1/2)\t: ";
    cin >> pilihan;
    if (pilihan == 1){
        luasPersegiPanjang ();
        login = true;
    }else if (pilihan == 2){
        kelilingPersegiPanjang();
        login = true;
    }else{
        attempt++;
        if (attempt == 3){
        cout << "------- Lakukan Kembali Setelah 30 Menit -------\n";
            break;
        }
        cout << "------------ Silahkan Coba Kembali -------------\n";
    }
    }
}

int main (){
    char jawaban;
    do {
    viewList ();
    cout << "--------------------------------------------\n";
    cout << "Apakah anda akan mencoba kembali (y/t) ? ";
    cin >> jawaban;
    } while (jawaban == 'Y'|| jawaban == 'y');
    system("BREAK");
    return 0;
}
