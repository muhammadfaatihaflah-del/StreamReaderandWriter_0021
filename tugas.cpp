#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>

using namespace std;

// KELAS TOKO ELEKTRONIK
class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    // Constructor
    TokoElektronik() {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Tablet";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw runtime_error(
                "Gagal Mengambil Barang : Rak nomor "
                + to_string(nomorRak)
                + " kosong atau tidak tersedia!"
            );
        }
    }
};

// FUNGSI CRUD FILE
const string NAMA_FILE = "gudang.txt";

// Read
void tampilkanBarang() {
    ifstream file(NAMA_FILE);

    cout << "\n===== DAFTAR BARANG GUDANG =====\n";

    if (!file) {
        cout << "File belum tersedia.\n";
        return;
    }

    string barang;
    int nomor = 1;

    while (getline(file, barang)) {
        cout << nomor++ << ". " << barang << endl;
    }

    if (nomor == 1) {
        cout << "Gudang masih kosong.\n";
    }

    file.close();
}

// Create
void tambahBarang() {
    ofstream file(NAMA_FILE, ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

// Update
void updateBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Tidak ada data untuk diubah.\n";
        return;
    }

    tampilkanBarang();

    int indeks;
    cout << "\nPilih nomor barang yang akan diubah: ";
    cin >> indeks;

    if (indeks < 1 || indeks > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru: ";
    getline(cin, data[indeks - 1]);

    ofstream tulis(NAMA_FILE);

    for (string item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil diperbarui.\n";
}

// Delete
void hapusBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Tidak ada data untuk dihapus.\n";
        return;
    }

    tampilkanBarang();

    int indeks;
    cout << "\nPilih nomor barang yang akan dihapus: ";
    cin >> indeks;

    if (indeks < 1 || indeks > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    data.erase(data.begin() + (indeks - 1));

    ofstream tulis(NAMA_FILE);

    for (string item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil dihapus.\n";
}

// SIMULASI ETALASE
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    // Skenario 1
    try {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Produk ditemukan: "
             << toko.ambilProduk(1)
             << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Skenario 2
    try {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Produk ditemukan: "
             << toko.ambilProduk(5)
             << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}

// MAIN
int main() {
    int pilihan;

    do {
        cout << "\n================================";
        cout << "\n SISTEM MANAJEMEN GUDANG TOKO";
        cout << "\n================================\n";

        tampilkanBarang();

        cout << "\nMenu:";
        cout << "\n1. Tambah Barang";
        cout << "\n2. Update Barang";
        cout << "\n3. Hapus Barang";
        cout << "\n4. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            hapusBarang();
            break;

        case 4:
            simulasiEtalase();
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}