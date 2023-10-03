#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef struct {
    int Sks;
    string Matkul;
    string grade;
} MataKuliah;

void infoNilaiGrade() {
    cout << "===================================================\n";
    cout << "====== PROGRAM MENGHITUNG NILAI IPK MAHASISWA =====\n";
    cout << "===================================================\n";
    cout << "                INFO NILAI GRADE                   \n";
    cout << "===================================================\n";
    cout << "GRADE A\t\t= 4\n";
    cout << "GRADE B\t\t= 3\n";
    cout << "GRADE C\t\t= 2\n";
    cout << "GRADE D\t\t= 1\n";
    cout << "GRADE E\t\t= 0\n";
    cout << "===================================================\n";
}

void inputMatakuliah(vector<MataKuliah> &matakuliah) {
    int jumlahMatakuliah;
    cout << "Masukan Total Matakuliah\t: ";
    cin >> jumlahMatakuliah;
    cin.ignore();
    cout << "===================================================\n";
    for (int i = 0; i < jumlahMatakuliah; i++) {
        MataKuliah mk;
        cout << "Nama Matakuliah\t\t\t: ";
        getline(cin, mk.Matkul);
        cout << "Grade (A/B/C/D/E)\t\t: ";
        getline(cin, mk.grade);
        while (mk.grade != "A" && mk.grade != "B" && mk.grade != "C" && mk.grade != "D" && mk.grade != "E") {
            cout << "Grade yang dimasukkan tidak valid.\nMasukkan kembali: ";
            getline(cin, mk.grade);
        }
        cout << "Jumlah SKS\t\t\t: ";
        cin >> mk.Sks;
        cin.ignore();
        matakuliah.push_back(mk);
        cout << "===================================================\n";
    }
}

void hasilNilai(vector<MataKuliah> &matakuliah) {
    float totalSks = 0, totalNilai = 0, ipk;

    cout << "\n\n---------------------------------------------------\n";
    cout << "NO";
    cout << setw(19) << "MATA KULIAH" << "\t\t";
    cout << setw(4) << "NILAI" << "\t\t";
    cout << setw(4) << "SKS" << endl;
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < matakuliah.size(); i++) {
        int nilaiSKS;
        if (matakuliah[i].grade == "A") {
            nilaiSKS = 4 * matakuliah[i].Sks;
        } else if (matakuliah[i].grade == "B") {
            nilaiSKS = 3 * matakuliah[i].Sks;
        } else if (matakuliah[i].grade == "C") {
            nilaiSKS = 2 * matakuliah[i].Sks;
        } else if (matakuliah[i].grade == "D") {
            nilaiSKS = 1 * matakuliah[i].Sks;
        } else if (matakuliah[i].grade == "E") {
            nilaiSKS = 0 * matakuliah[i].Sks;
        }

        int k = i + 1;
        cout << k;
        cout << setw(20) << matakuliah[i].Matkul << "\t\t";
        cout << setw(3) << matakuliah[i].grade;
        cout << setw(15) << matakuliah[i].Sks << endl;

        totalNilai += nilaiSKS;
        totalSks += matakuliah[i].Sks;
    }

    cout << "---------------------------------------------------\n";
    ipk = totalNilai / totalSks;
    cout << "TOTAL NILAI\t: " << totalNilai << endl;
    cout << "TOTAL SKS\t: " << totalSks << endl;
    cout << "TOTAL IPK\t: " << ipk << endl;
}

int main() {
    infoNilaiGrade();
    vector<MataKuliah> matakuliah;
    inputMatakuliah(matakuliah);
    hasilNilai(matakuliah);
    return 0;
}
