#include <iostream>  // Untuk input dan output
#include <cstdlib>   // Untuk fungsi rand()
#include <ctime>     // Untuk waktu acak
#include <vector>    // Untuk vektor (opsional, tapi berguna)
#include <string>    // Untuk string

using namespace std;

// Fungsi untuk menampilkan grid (hanya tunjukkan yang terlihat oleh pemain)
void tampilkanGrid(char grid[10][10], bool adalahKomputer) {
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;  // Header kolom
    for(int i = 0; i < 10; i++) {
        cout << i << " ";  // Header baris
        for(int j = 0; j < 10; j++) {
            if (adalahKomputer) {
                // Untuk grid komputer, sembunyikan kapal yang belum ditebak
                if (grid[i][j] == 'K') cout << ' ';  // Kapal tersembunyi
                else cout << grid[i][j] << " ";  // Tunjukkan hit atau miss
            } else {
                cout << grid[i][j] << " ";  // Tampilkan grid pemain (jika ada)
            }
        }
        cout << endl;
    }
}

// Fungsi untuk menempatkan kapal secara acak
bool tempatkanKapal(char grid[10][10], int panjangKapal) {
    bool horizontal = rand() % 2 == 0;  // Pilih horizontal atau vertikal
    int baris = rand() % 10;
    int kolom = rand() % 10;
    
    if (horizontal && kolom + panjangKapal <= 10) {  // Horizontal
        bool bisa = true;
        for(int i = 0; i < panjangKapal; i++) {
            if (grid[baris][kolom + i] != '.') {  // '.' berarti kosong
                bisa = false;
                break;
            }
        }
        if (bisa) {
            for(int i = 0; i < panjangKapal; i++) {
                grid[baris][kolom + i] = 'K';  // 'K' untuk kapal
            }
            return true;
        }
    } else if (!horizontal && baris + panjangKapal <= 10) {  // Vertikal
        bool bisa = true;
        for(int i = 0; i < panjangKapal; i++) {
            if (grid[baris + i][kolom] != '.') {
                bisa = false;
                break;
            }
        }
        if (bisa) {
            for(int i = 0; i < panjangKapal; i++) {
                grid[baris + i][kolom] = 'K';
            }
            return true;
        }
    }
    return false;  // Gagal, coba lagi
}

// Fungsi utama untuk memeriksa apakah semua kapal tenggelam
bool cekMenang(char grid[10][10], int totalSelKapal) {
    int selTenggelam = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if (grid[i][j] == 'X') selTenggelam++;  // 'X' berarti sel kapal yang sudah kena
        }
    }
    return selTenggelam >= totalSelKapal;  // Total sel kapal: 5+4+3+3+2=17
}

int main() {
    srand(time(0));  // Inisialisasi random
    
    char gridKomputer[10][10];  // Grid untuk komputer
    char gridPemain[10][10];    // Grid untuk pemain (opsional, tapi tidak digunakan di sini)
    
    // Inisialisasi grid kosong
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            gridKomputer[i][j] = '.';
            gridPemain[i][j] = '.';
        }
    }
    
    // Tempatkan kapal untuk komputer
    vector<int> panjangKapal = {5, 4, 3, 3, 2};  // Ukuran kapal
    for(int p : panjangKapal) {
        while (!tempatkanKapal(gridKomputer, p)) {
            // Coba lagi jika gagal menempatkan
        }
    }
    
    int tebakan = 0;
    char mainLagi = 'y';
    int skorPemain = 0;  // Hitungan tebakan benar
    
    cout << "Selamat datang di Game Battleship!" << endl;
    cout << "Kamu menebak posisi kapal komputer di grid 10x10." << endl;
    cout << "Masukkan baris dan kolom (0-9) untuk menyerang." << endl;
    
    while (mainLagi == 'y' || mainLagi == 'Y') {
        tebakan = 0;
        skorPemain = 0;  // Reset skor per game
        
        // Reset grid untuk game baru
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                gridKomputer[i][j] = '.';  // Reset, tapi sebenarnya kapal sudah ditempatkan
                // Di sini, kita tidak reset kapal agar game baru punya kapal baru
            }
        }
        for(int p : panjangKapal) {
            while (!tempatkanKapal(gridKomputer, p)) {}  // Tempatkan ulang
        }
        
        bool gameBerjalan = true;
        
        while (gameBerjalan) {
            cout << "\nGrid Komputer (yang kamu lihat):" << endl;
            tampilkanGrid(gridKomputer, true);  // Tampilkan grid komputer dengan sembunyi
            
            int baris, kolom;
            cout << "Masukkan baris (0-9): ";
            cin >> baris;
            cout << "Masukkan kolom (0-9): ";
            cin >> kolom;
            
            if (baris >= 0 && baris < 10 && kolom >= 0 && kolom < 10) {
                tebakan++;
                if (gridKomputer[baris][kolom] == 'K') {  // Kena kapal
                    gridKomputer[baris][kolom] = 'X';  // Tandai sebagai hit
                    skorPemain++;
                    cout << "HIT! Kamu menembak kapal." << endl;
                    if (cekMenang(gridKomputer, 17)) {  // Total sel kapal 17
                        cout << "Selamat! Kamu menenggelamkan semua kapal dalam " << tebakan << " tebakan." << endl;
                        gameBerjalan = false;
                    }
                } else {
                    gridKomputer[baris][kolom] = 'M';  // 'M' untuk miss
                    cout << "MISS! Tidak ada kapal di sana." << endl;
                }
            } else {
                cout << "Posisi tidak valid! Masukkan 0-9." << endl;
            }
        }
        
        cout << "Skor: Tebakan benar = " << skorPemain << ", Total tebakan = " << tebakan << endl;
        cout << "Ingin main lagi? (y/n): ";
        cin >> mainLagi;
    }
    
    cout << "Terima kasih telah bermain! Sampai jumpa." << endl;
    return 0;
}
