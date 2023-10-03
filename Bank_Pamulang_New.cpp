#include <iostream>
#include <fstream>
using namespace std;

struct BankAccount {
    string userID;
    int mPin;
    unsigned int saldo;
};

bool loginUser(BankAccount* account) {
    int attempts = 0;
    
    while (attempts < 3) {
        cout << " ________________________________________________ \n";
        cout << "|                                                |\n";
        cout << "|                                                |\n";
        cout << "|============= BANK PAMULANG SYARIAH ============|\n";
        cout << "|                                                |\n";
        cout << "|________________________________________________|\n";
        cout << endl;
        cout << "USER ID\t\t: ";
        cin >> account->userID;
        cout << "MPIN\t\t: ";
        cin >> account->mPin;
        cout << endl;
        
        ifstream inputFile("D:\\db_C++\\data.txt");
        
        if (!inputFile) {
            cerr << "Gagal membuka file data.\n";
            exit(1);
        }
        
        string fileUserID;
        int fileMPIN;
        unsigned int fileSaldo;

        bool loggedIn = false;

        while (inputFile >> fileUserID >> fileMPIN >> fileSaldo) {
            if (account->userID == fileUserID && account->mPin == fileMPIN) {
                cout << "=========== Selamat Anda Berhasil Login =========\n";
                account->saldo = fileSaldo; // Update saldo dari file
                loggedIn = true;
                break;
            }
        }

        inputFile.close();

        if (loggedIn) {
            return true;
        } else {
            attempts++;
            if (attempts == 3) {
                cout << "Anda telah mencoba 3 kali. Silakan coba lagi nanti.\n";
                exit(0);
            }
            cout << "User ID atau MPIN salah. Silakan coba lagi.\n";
        }
    }

    return false;
}

void createAccount() {
    cout << " ________________________________________________ \n";
    cout << "|                                                |\n";
    cout << "|                                                |\n";
    cout << "|============= BANK PAMULANG SYARIAH ============|\n";
    cout << "|                                                |\n";
    cout << "|________________________________________________|\n";
    cout << endl;

    BankAccount newAccount;
    cout << "Buat User ID Baru\t: ";
    cin >> newAccount.userID;
    cout << "Buat MPIN Baru\t\t: ";
    cin >> newAccount.mPin;
    newAccount.saldo = 0;

    ofstream outputFile("D:\\db_C++\\data.txt", ios::app);

    if (!outputFile) {
        cerr << "Gagal membuka file data.\n";
        exit(1);
    }

    outputFile << endl;
    outputFile << newAccount.userID << " " << newAccount.mPin << " " << newAccount.saldo << endl;
    outputFile.close();

    cout << "============= Akun Baru Berhasil Dibuat ==========\n";
    cout << "==================================================\n";
}

void viewMenuBank() {
    cout << endl;
    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|========== MENU BANK PAMULANG SYARIAH ==========|\n";
    cout << "|________________________________________________|\n";
    cout << "|                        |                       |\n";
    cout << "| 1. Cek Saldo           | 4. Setor Tunai        |\n";
    cout << "|________________________|_______________________|\n";
    cout << "|                        |                       |\n";
    cout << "| 2. Tarik Tunai         | 5. Top Up E-Wallet    |\n";
    cout << "|________________________|_______________________|\n";
    cout << "|                        |                       |\n";
    cout << "| 3. Transfer            | 6. Keluar             |\n";
    cout << "|________________________|_______________________|\n";
    cout << endl;
}

void cekSaldo(BankAccount* account) {
    cout << "SISA SALDO ANDA\t\t: " << account->saldo << endl;
    cout << "==================================================\n";
}

void tarikTunai(BankAccount* account) {
    int nominal;
    cout << "MASUKAN NOMINAL\t\t: ";
    cin >> nominal;
    cout << "==================================================\n";
    if (nominal <= account->saldo) {
        account->saldo -= nominal;
        cout << "             SILAHKAN AMBIL UANG ANDA             \n";
        cout << "==================================================\n";
        cekSaldo(account);

        // Memperbarui saldo di file data.txt
        ifstream inputFile("D:\\db_C++\\data.txt");
        ofstream tempFile("D:\\db_C++\\temp.txt");

        if (!inputFile || !tempFile) {
            cerr << "Gagal membuka file data.\n";
            exit(1);
        }

        string fileUserID;
        int fileMPIN;
        unsigned int fileSaldo;

        while (inputFile >> fileUserID >> fileMPIN >> fileSaldo) {
            if (fileUserID == account->userID) {
                tempFile << fileUserID << " " << fileMPIN << " " << account->saldo << endl;
            } else {
                tempFile << fileUserID << " " << fileMPIN << " " << fileSaldo << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        // Mengganti file asli dengan file sementara
        remove("D:\\db_C++\\data.txt");
        rename("D:\\db_C++\\temp.txt", "D:\\db_C++\\data.txt");
    }
    else {
        cout << "SALDO ANDA TIDAK CUKUP\n";
    }
}

void transfer(BankAccount* account) {
    int nomorTujuan, nominal;
    cout << "NOMOR REKENING TUJUAN\t: ";
    cin >> nomorTujuan;
    cout << "NOMINAL TRANSFER SALDO\t: ";
    cin >> nominal;
    cout << "==================================================\n";

    if (nominal >= 20000 && nominal <= account->saldo) {
        account->saldo -= nominal;
        cout << "              ANDA BERHASIL TRANSFER              \n";
        cout << "KE NOMOR REKENING " << nomorTujuan << " DENGAN NOMINAL " << nominal << endl;
        cekSaldo(account);

        // Memperbarui saldo di file data.txt
        ifstream inputFile("D:\\db_C++\\data.txt");
        ofstream tempFile("D:\\db_C++\\temp.txt");

        if (!inputFile || !tempFile) {
            cerr << "Gagal membuka file data.\n";
            exit(1);
        }

        string fileUserID;
        int fileMPIN;
        unsigned int fileSaldo;

        while (inputFile >> fileUserID >> fileMPIN >> fileSaldo) {
            if (fileUserID == account->userID) {
                tempFile << fileUserID << " " << fileMPIN << " " << account->saldo << endl;
            } else {
                tempFile << fileUserID << " " << fileMPIN << " " << fileSaldo << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        // Mengganti file asli dengan file sementara
        remove("D:\\db_C++\\data.txt");
        rename("D:\\db_C++\\temp.txt", "D:\\db_C++\\data.txt");
    }
    else {
        cout << "MAAF, TRANSFER GAGAL. NOMINAL KURANG DARI 20.000 ATAU SALDO TIDAK CUKUP\n";
    }
}

void setorTunai(BankAccount* account) {
    int nominal;
    cout << "NOMINAL SETORAN ANDA\t: ";
    cin >> nominal;
    cout << "==================================================\n";
    account->saldo += nominal; // Menambahkan setoran ke saldo akun

    // Menyimpan saldo baru ke dalam file teks
    ifstream inputFile("D:\\db_C++\\data.txt");
    ofstream tempFile("D:\\db_C++\\temp.txt");

    if (!inputFile || !tempFile) {
        cerr << "Gagal membuka file data.\n";
        exit(1);
    }

    string fileUserID;
    int fileMPIN;
    unsigned int fileSaldo;

    while (inputFile >> fileUserID >> fileMPIN >> fileSaldo) {
        if (fileUserID == account->userID) {
            tempFile << fileUserID << " " << fileMPIN << " " << account->saldo << endl;
        } else {
            tempFile << fileUserID << " " << fileMPIN << " " << fileSaldo << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Mengganti file asli dengan file sementara
    remove("D:\\db_C++\\data.txt");
    rename("D:\\db_C++\\temp.txt", "D:\\db_C++\\data.txt");

    cekSaldo(account); // Menampilkan saldo terbaru
}

void topUpEwallet(BankAccount* account) {
    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|================= MENU E-WALLET ================|\n";
    cout << "|________________________________________________|\n";
    cout << "|                        |                       |\n";
    cout << "| 1. TOP UP GOPAY        | 2. TOP UP OVO         |\n";
    cout << "|________________________|_______________________|\n";
    cout << "MASUKAN PILIHAN\t: ";
    int pilihan;
    cin >> pilihan;
    cout << "==================================================\n";

    switch (pilihan) {
        case 1:
            int nomorGopay;
            cout << "MASUKAN NOMOR GOPAY\t: ";
            cin >> nomorGopay;
            int topUpGopay;
            cout << "MASUKAN NOMINAL TOPUP\t: ";
            cin >> topUpGopay;
            cout << "==================================================\n";
            if (topUpGopay >= 20000 && topUpGopay <= account->saldo) {
                account->saldo -= topUpGopay;
                cout << "         TOP UP SALDO GOPAY ANDA BERHASIL         \n";
                cekSaldo(account);

                // Memperbarui saldo di file data.txt
                ifstream inputFile("D:\\db_C++\\data.txt");
                ofstream tempFile("D:\\db_C++\\temp.txt");

                if (!inputFile || !tempFile) {
                    cerr << "Gagal membuka file data.\n";
                    exit(1);
                }

                string fileUserID;
                int fileMPIN;
                unsigned int fileSaldo;

                while (inputFile >> fileUserID >> fileMPIN >> fileSaldo) {
                    if (fileUserID == account->userID) {
                        tempFile << fileUserID << " " << fileMPIN << " " << account->saldo << endl;
                    } else {
                        tempFile << fileUserID << " " << fileMPIN << " " << fileSaldo << endl;
                    }
                }

                inputFile.close();
                tempFile.close();

                remove("D:\\db_C++\\data.txt");
                rename("D:\\db_C++\\temp.txt", "D:\\db_C++\\data.txt");
            }
            else {
                cout << "MAAF, TOP UP GAGAL. NOMINAL KURANG DARI 20.000 ATAU SALDO TIDAK CUKUP\n";
            }
            break;
    }
}

int bankPamulang(BankAccount* account) {
    while (true) {
        cout << endl;
        cout << "MASUKAN PILIHAN\t: ";
        int pilihan;
        cin >> pilihan;
        cout << "==================================================\n";
        switch (pilihan) {
            case 1:
                cekSaldo(account);
                break;
            case 2:
                tarikTunai(account);
                break;
            case 3:
                transfer(account);
                break;
            case 4:
                setorTunai(account);
                break;
            case 5:
                topUpEwallet(account);
                break;
            case 6:
                cout << "TERIMA KASIH TELAH BERTRANSAKSI\n";
                cout << "==================================================\n";
                return 0;
            default:
                cout << "PILIHAN YANG ANDA MASUKAN SALAH\n";
                cout << "SILAHKAN COBA KEMBALI\n";
                cout << "==================================================\n";
        }
    }
}

int main() {
    BankAccount account;
    //account.saldo = 0; // Inisialisasi saldo awal

    int choice;

    cout << " ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|                 Selamat Datang                 |\n";
    cout << "|                    Nasabah                     |\n";
    cout << "|             Bank Pamulang Syariah              |\n";
    cout << "|________________________________________________|\n";
    cout << "|                        |                       |\n";
    cout << "|        1. Login        |     2. Buat Akun      |\n";
    cout << "|________________________|_______________________|\n\n";
    cout << "Pilih opsi\t\t: ";
    cin >> choice;

    switch (choice) {
        case 1:
            loginUser(&account);
            viewMenuBank();
            bankPamulang(&account);
            break;
        case 2:
            createAccount();
            break;
        default:
            cout << "Opsi yang Anda pilih tidak valid.\n";
            break;
    }

    return 0;
}
