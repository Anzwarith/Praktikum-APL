#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Nested struct untuk menyimpan data jam tayang dan kursi terisi
struct JamTayang {
    string jam;
    int kursiTerisi;
};

// Struct untuk menyimpan data film
struct FilmData {
    string namaFilm;
    JamTayang jamTayang[5];
};

// Struct untuk menyimpan data user
struct User {
    string username;
    string password;
    bool isAdmin;
};

// Struct untuk menyimpan data booking
struct Booking {
    int filmId;
    int jamId;
    bool isPaid;
    int userId;  // Menyimpan ID user yang melakukan booking
};

// Deklarasi fungsi dan prosedur
void tampilkanMenuUtama();
void registrasiUser(User users[], int &userCount);
bool login(User users[], int userCount, bool &isAdmin, int &currentUserId);
bool menuAdmin(FilmData films[], int &filmCount, Booking bookings[], int &bookingCount, User users[], int userCount, const int maksKursi);
bool menuUser(FilmData films[], int filmCount, Booking bookings[], int &bookingCount, int currentUserId, User users[], const int maksKursi);
void tambahFilm(FilmData films[], int &filmCount);
void hapusFilm(FilmData films[], int &filmCount);
void lihatFilm(const FilmData films[], int filmCount, const int maksKursi);
void lihatTransaksi(const Booking bookings[], int bookingCount, const FilmData films[], const User users[]);
void pesanTiket(FilmData films[], int filmCount, Booking bookings[], int &bookingCount, int currentUserId, const int maksKursi);
void lihatTiketUser(const Booking bookings[], int bookingCount, const FilmData films[], int currentUserId);
void gantiJamTayang(FilmData films[], Booking bookings[], int bookingCount, int currentUserId, const int maksKursi);
void batalkanTiket(FilmData films[], Booking bookings[], int bookingCount);
void bayarTiket(Booking bookings[], int bookingCount, const FilmData films[]);
void tampilkanFilmTersedia(const FilmData films[], int filmCount, int index, const int maksKursi); // Fungsi rekursif
void tampilkanJamTayang(const JamTayang jamTayang[], int index, const int maksKursi); // Fungsi overloading
void tampilkanJamTayang(const JamTayang jamTayang); // Fungsi overloading

int main() {
    // Array of struct untuk menyimpan data film
    FilmData films[10] = {
        {"Kimi No Nawa", {{"10:00", 0}, {"12:00", 0}, {"15:00", 0}, {"17:00", 0}, {"19:00", 0}}},
        {"Godzilla : Minus one", {{"10:00", 0}, {"12:00", 0}, {"15:00", 0}, {"17:00", 0}, {"19:00", 0}}},
        {"Avengers : secret wars", {{"10:00", 0}, {"12:00", 0}, {"15:00", 0}, {"17:00", 0}, {"19:00", 0}}},
        {"Your Lie In April", {{"10:00", 0}, {"12:00", 0}, {"15:00", 0}, {"17:00", 0}, {"19:00", 0}}},
        {"Cek Toko Sebelah", {{"10:00", 0}, {"12:00", 0}, {"15:00", 0}, {"17:00", 0}, {"19:00", 0}}}
    };

    int filmCount = 5; // Jumlah film awal

    // Array untuk menyimpan data user
    User users[10];
    int userCount = 0;

    // Array untuk menyimpan booking
    Booking bookings[10];
    int bookingCount = 0;

    // Kapasitas maksimum per film dan jam
    const int maksKursi = 20;

    // Inisialisasi admin dan user
    users[userCount++] = {"admin", "selalubenar", true};  // Admin
    users[userCount++] = {"Danendra Hazzel PW", "2409106096", false};  // User biasa

    int pilihan = 0;
    bool isRunning = true;
    int loginAttempts = 0;  // Menghitung percobaan login
    bool isAdmin = false;
    int currentUserId = -1;

    // Menu utama
    while (isRunning) {
        tampilkanMenuUtama();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                registrasiUser(users, userCount);
                break;
            }
            case 2: {
                if (login(users, userCount, isAdmin, currentUserId)) {
                    cout << "Login berhasil!\n";
                    cout << "Selamat Datang " << (isAdmin ? "Bos" : "Tuan") << " " << users[currentUserId].username << endl;
            
                    // Menu setelah login
                    bool isLoggedIn = true;
                    while (isLoggedIn) {
                        if (isAdmin) {
                            isLoggedIn = menuAdmin(films, filmCount, bookings, bookingCount, users, userCount, maksKursi);
                        } else {
                            isLoggedIn = menuUser(films, filmCount, bookings, bookingCount, currentUserId, users, maksKursi);
                        }
                    }
                } else {
                    loginAttempts++;
                    cout << "Login gagal, Username atau Password salah! Sisa percobaan anda sebanyak " << 3 - loginAttempts << endl;
            
                    if (loginAttempts >= 3) {
                        cout << "Kesempatan anda telah habis, silahkan mencoba lagi dalam beberapa saat.\n";
                        isRunning = false;
                    }
                }
                break;
            }
            case 3: {
                cout << "Terima kasih telah menggunakan aplikasi ini, enjoy the movie!\n";
                isRunning = false;
                break;
            }
            default: {
                cout << "Pilihan tidak valid!\n";
                break;
            }
        }
    }

    return 0;
}

// Implementasi fungsi dan prosedur
void tampilkanMenuUtama() {
    cout << "\n===== MENU UTAMA =====\n";
    cout << "1. Registrasi\n";
    cout << "2. Login\n";
    cout << "3. Keluar\n";
    cout << "Pilihan Anda: ";
}

void registrasiUser(User users[], int &userCount) {
    if (userCount >= 10) {
        cout << "Maaf, kapasitas user sudah penuh!\n";
        return;
    }
    
    cout << "\n===== REGISTRASI =====\n";
    string username, password;
    cout << "Masukkan Username: ";
    cin >> ws;
    getline(cin, username);
    cout << "Masukkan Password: ";
    cin >> password;
    
    // Cek apakah username sudah ada
    bool usernameExists = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            usernameExists = true;
            break;
        }
    }
    
    if (usernameExists) {
        cout << "Registrasi gagal! Akun telah tersedia.\n";
    } else {
        users[userCount++] = {username, password, false};
        cout << "Registrasi berhasil!\n";
    }
}

bool login(User users[], int userCount, bool &isAdmin, int &currentUserId) {
    cout << "\n===== LOGIN =====\n";
    cout << "Ingin login sebagai apa?\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "Pilihan Anda: ";
    int loginType;
    cin >> loginType;

    if (loginType < 1 || loginType > 2) {
        cout << "Pilihan tidak valid!\n";
        return false;
    }

    string username, password;
    cout << "Masukkan Username: ";
    cin >> ws;
    getline(cin, username);
    cout << "Masukkan Password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            if ((loginType == 1 && users[i].isAdmin) || (loginType == 2 && !users[i].isAdmin)) {
                isAdmin = users[i].isAdmin;
                currentUserId = i;
                return true;
            }
        }
    }
    return false;
}

bool menuAdmin(FilmData films[], int &filmCount, Booking bookings[], int &bookingCount, User users[], int userCount, const int maksKursi) {
    cout << "\n===== MENU ADMIN =====\n";
    cout << "1. Tambah Film\n";
    cout << "2. Hapus Film\n";
    cout << "3. Lihat Film\n";
    cout << "4. Lihat Transaksi\n";
    cout << "5. Log out\n";
    cout << "Pilihan Anda: ";
    
    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1: tambahFilm(films, filmCount); break;
        case 2: hapusFilm(films, filmCount); break;
        case 3: lihatFilm(films, filmCount, maksKursi); break;
        case 4: lihatTransaksi(bookings, bookingCount, films, users); break;
        case 5: {
            cout << "Kembali ke menu utama\n";
            return false; // Indikator untuk logout
        }
        default: cout << "Pilihan tidak valid!\n"; break;
    }
    return true; // Tetap di menu admin
}

bool menuUser(FilmData films[], int filmCount, Booking bookings[], int &bookingCount, int currentUserId, User users[], const int maksKursi) {
    cout << "\n===== MENU USER =====\n";
    cout << "1. Pesan Tiket\n";
    cout << "2. Lihat Film yang Tersedia\n";
    cout << "3. Lihat Tiket yang Sudah Dipesan\n";
    cout << "4. Ganti Jam Tayang\n";
    cout << "5. Batalkan Tiket\n";
    cout << "6. Bayar Tiket\n";
    cout << "7. Log out\n";
    cout << "Pilihan Anda: ";
    
    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1: pesanTiket(films, filmCount, bookings, bookingCount, currentUserId, maksKursi); break;
        case 2: lihatFilm(films, filmCount, maksKursi); break;
        case 3: lihatTiketUser(bookings, bookingCount, films, currentUserId); break;
        case 4: gantiJamTayang(films, bookings, bookingCount, currentUserId, maksKursi); break;
        case 5: batalkanTiket(films, bookings, bookingCount); break;
        case 6: bayarTiket(bookings, bookingCount, films); break;
        case 7: {
            cout << "Kembali ke menu utama\n";
            return false; // Indikator untuk logout
        }
        default: cout << "Pilihan tidak valid!\n"; break;
    }
    return true; // Tetap di menu user
}

void tambahFilm(FilmData films[], int &filmCount) {
    if (filmCount >= 10) {
        cout << "Maaf, kapasitas film sudah penuh!\n";
        return;
    }

    cout << "\n===== TAMBAH FILM =====\n";
    cout << "Masukkan Nama Film: ";
    cin >> ws;
    getline(cin, films[filmCount].namaFilm);

    for (int i = 0; i < 5; i++) {
        films[filmCount].jamTayang[i].jam = to_string(10 + i * 2) + ":00";
        films[filmCount].jamTayang[i].kursiTerisi = 0;
    }

    cout << "Film berhasil ditambahkan!\n";
    filmCount++;
}

void hapusFilm(FilmData films[], int &filmCount) {
    cout << "\n===== HAPUS FILM =====\n";
    cout << "Daftar Film:\n";
    for (int i = 0; i < filmCount; i++) {
        cout << i + 1 << ". " << films[i].namaFilm << endl;
    }

    int filmPilihan;
    cout << "Pilih film yang ingin ditarik (1-" << filmCount << "): ";
    cin >> filmPilihan;

    if (filmPilihan < 1 || filmPilihan > filmCount) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    for (int i = filmPilihan - 1; i < filmCount - 1; i++) {
        films[i] = films[i + 1];
    }

    filmCount--;
    cout << "Film berhasil ditarik dari penayangan!\n";
}

void lihatFilm(const FilmData films[], int filmCount, const int maksKursi) {
    cout << "\n===== DAFTAR FILM =====\n";
    tampilkanFilmTersedia(films, filmCount, 0, maksKursi);
}

// Fungsi rekursif untuk menampilkan film yang tersedia
void tampilkanFilmTersedia(const FilmData films[], int filmCount, int index, const int maksKursi) {
    if (index >= filmCount) return;
    
    cout << index + 1 << ". " << films[index].namaFilm << endl;
    cout << "   Jam Tayang: ";
    tampilkanJamTayang(films[index].jamTayang, 0, maksKursi);
    cout << endl;
    
    tampilkanFilmTersedia(films, filmCount, index + 1, maksKursi);
}

// Fungsi overloading untuk menampilkan jam tayang (array)
void tampilkanJamTayang(const JamTayang jamTayang[], int index, const int maksKursi) {
    if (index >= 5) return;
    
    int kursiTersisa = maksKursi - jamTayang[index].kursiTerisi;
    cout << jamTayang[index].jam << " (" << kursiTersisa << " kursi) ";
    
    tampilkanJamTayang(jamTayang, index + 1, maksKursi);
}

// Fungsi overloading untuk menampilkan jam tayang (single)
void tampilkanJamTayang(const JamTayang jamTayang) {
    cout << jamTayang.jam;
}

void lihatTransaksi(const Booking bookings[], int bookingCount, const FilmData films[], const User users[]) {
    cout << "\n===== TRANSAKSI =====\n";
    for (int i = 0; i < bookingCount; i++) {
        cout << "ID Booking: " << i << endl;
        cout << "Film: " << films[bookings[i].filmId].namaFilm << endl;
        cout << "Jam: " << films[bookings[i].filmId].jamTayang[bookings[i].jamId].jam << endl;
        cout << "User: " << users[bookings[i].userId].username << endl;
        cout << "Status: " << (bookings[i].isPaid ? "Sudah dibayar" : "Belum dibayar") << endl;
        cout << "-----------------------\n";
    }
}

void pesanTiket(FilmData films[], int filmCount, Booking bookings[], int &bookingCount, int currentUserId, const int maksKursi) {
    cout << "\n===== PESAN TIKET =====\n";

    // Tampilkan film yang tersedia
    cout << "Film yang tersedia:\n";
    for (int i = 0; i < filmCount; i++) {
        cout << i + 1 << ". " << films[i].namaFilm << endl;
    }

    int filmPilihan;
    cout << "Pilih film (1-" << filmCount << "): ";
    cin >> filmPilihan;

    if (filmPilihan < 1 || filmPilihan > filmCount) {
        cout << "Film tidak valid!\n";
        return;
    }

    // Tampilkan jam tayang
    cout << "Jam tayang yang tersedia:\n";
    for (int i = 0; i < 5; i++) {
        int kursiTersisa = maksKursi - films[filmPilihan - 1].jamTayang[i].kursiTerisi;
        cout << i + 1 << ". " << films[filmPilihan - 1].jamTayang[i].jam << " (Kursi tersisa: " << kursiTersisa << ")\n";
    }

    int jamPilihan;
    cout << "Pilih jam tayang (1-5): ";
    cin >> jamPilihan;

    if (jamPilihan < 1 || jamPilihan > 5) {
        cout << "Jam tayang tidak valid!\n";
        return;
    }

    // Cek apakah kursi masih tersedia
    if (films[filmPilihan - 1].jamTayang[jamPilihan - 1].kursiTerisi >= maksKursi) {
        cout << "Maaf, kursi untuk film dan jam tersebut sudah penuh!\n";
        return;
    }

    // Simpan booking
    bookings[bookingCount].filmId = filmPilihan - 1;
    bookings[bookingCount].jamId = jamPilihan - 1;
    bookings[bookingCount].isPaid = false;
    bookings[bookingCount].userId = currentUserId;

    // Update kursi terisi
    films[filmPilihan - 1].jamTayang[jamPilihan - 1].kursiTerisi++;

    cout << "Booking berhasil!\n";
    cout << "ID Booking Anda: " << bookingCount << endl;
    cout << "Film: " << films[filmPilihan - 1].namaFilm << endl;
    cout << "Jam: " << films[filmPilihan - 1].jamTayang[jamPilihan - 1].jam << endl;
    cout << "Status: Belum dibayar\n";

    bookingCount++;
}

void lihatTiketUser(const Booking bookings[], int bookingCount, const FilmData films[], int currentUserId) {
    cout << "\n===== TIKET YANG SUDAH DIPESAN =====\n";
    bool adaTiket = false;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].filmId != -1 && bookings[i].userId == currentUserId) {
            adaTiket = true;
            cout << "ID Booking: " << i << endl;
            cout << "Film: " << films[bookings[i].filmId].namaFilm << endl;
            cout << "Jam: " << films[bookings[i].filmId].jamTayang[bookings[i].jamId].jam << endl;
            cout << "Status: " << (bookings[i].isPaid ? "Sudah dibayar" : "Belum dibayar") << endl;
            cout << "-----------------------\n";
        }
    }

    if (!adaTiket) {
        cout << "Belum ada tiket yang dipesan!\n";
    }
}

void gantiJamTayang(FilmData films[], Booking bookings[], int bookingCount, int currentUserId, const int maksKursi) {
    cout << "\n===== GANTI JAM TAYANG =====\n";

    int idBooking;
    cout << "Masukkan ID Booking: ";
    cin >> idBooking;

    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
        cout << "ID Booking tidak valid!\n";
        return;
    }

    if (bookings[idBooking].isPaid) {
        cout << "Tidak dapat mengubah jam tayang tiket yang sudah dibayar!\n";
        return;
    }

    int filmId = bookings[idBooking].filmId;
    int jamLama = bookings[idBooking].jamId;

    // Tampilkan jam tayang yang tersedia
    cout << "Jam tayang saat ini: " << films[filmId].jamTayang[jamLama].jam << endl;
    cout << "Jam tayang baru yang tersedia:\n";

    for (int i = 0; i < 5; i++) {
        int kursiTersisa = maksKursi - films[filmId].jamTayang[i].kursiTerisi;
        cout << i + 1 << ". " << films[filmId].jamTayang[i].jam << " (Kursi tersisa: " << kursiTersisa << ")\n";
    }

    int jamBaru;
    cout << "Pilih jam tayang baru (1-5): ";
    cin >> jamBaru;

    if (jamBaru < 1 || jamBaru > 5) {
        cout << "Jam tayang tidak valid!\n";
        return;
    }

    if (films[filmId].jamTayang[jamBaru - 1].kursiTerisi >= maksKursi) {
        cout << "Maaf, kursi untuk jam tersebut sudah penuh!\n";
        return;
    }

    // Update kursi terisi
    films[filmId].jamTayang[jamLama].kursiTerisi--;
    films[filmId].jamTayang[jamBaru - 1].kursiTerisi++;

    // Update booking
    bookings[idBooking].jamId = jamBaru - 1;

    cout << "Jam tayang berhasil diubah!\n";
    cout << "Film: " << films[filmId].namaFilm << endl;
    cout << "Jam tayang baru: " << films[filmId].jamTayang[jamBaru - 1].jam << endl;
}

void batalkanTiket(FilmData films[], Booking bookings[], int bookingCount) {
    cout << "\n===== BATALKAN TIKET =====\n";

    int idBooking;
    cout << "Masukkan ID Booking: ";
    cin >> idBooking;

    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
        cout << "ID Booking tidak valid!\n";
        return;
    }

    if (bookings[idBooking].isPaid) {
        cout << "Tidak dapat membatalkan tiket yang sudah dibayar!\n";
        return;
    }

    int filmId = bookings[idBooking].filmId;
    int jamId = bookings[idBooking].jamId;

    // Update kursi terisi
    films[filmId].jamTayang[jamId].kursiTerisi--;

    // Hapus booking
    bookings[idBooking].filmId = -1;
    bookings[idBooking].jamId = -1;
    bookings[idBooking].isPaid = false;

    cout << "Tiket berhasil dibatalkan!\n";
}

void bayarTiket(Booking bookings[], int bookingCount, const FilmData films[]) {
    cout << "\n===== BAYAR TIKET =====\n";

    int idBooking;
    cout << "Masukkan ID Booking: ";
    cin >> idBooking;

    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
        cout << "ID Booking tidak valid!\n";
        return;
    }

    if (bookings[idBooking].isPaid) {
        cout << "Tiket sudah dibayar sebelumnya!\n";
        return;
    }

    // Update status pembayaran
    bookings[idBooking].isPaid = true;

    cout << "Pembayaran berhasil!\n";
    cout << "Film: " << films[bookings[idBooking].filmId].namaFilm << endl;
    cout << "Jam: " << films[bookings[idBooking].filmId].jamTayang[bookings[idBooking].jamId].jam << endl;
    cout << "Status: Sudah dibayar\n";
}