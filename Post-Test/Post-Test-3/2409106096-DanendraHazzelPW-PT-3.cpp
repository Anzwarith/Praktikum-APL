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
    int maksKursi = 20;

    // Inisialisasi admin dan user
    users[userCount++] = {"admin", "selalubenar", true};  // Admin
    users[userCount++] = {"Danendra Hazzel PW", "2409106096", false};  // User biasa

    int pilihan = 0;
    bool isRunning = true;
    int loginAttempts = 0;  // Menghitung percobaan login
    string username, password;
    bool isAdmin = false;
    int currentUserId = -1;

    // Menu utama
    while (isRunning) {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Registrasi\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                // Registrasi
                if (userCount >= 10) {
                    cout << "Maaf, kapasitas user sudah penuh!\n";
                    break;
                }
            
                cout << "\n===== REGISTRASI =====\n";
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
                break;
            }
            case 2: {
                // Login
                cout << "\n===== LOGIN =====\n";
                cout << "Ingin login sebagai apa?\n";
                cout << "1. Admin\n";
                cout << "2. User\n";
                cout << "Pilihan Anda: ";
                int loginType;
                cin >> loginType;

                if (loginType < 1 || loginType > 2) {
                    cout << "Pilihan tidak valid!\n";
                    break;
                }

                cout << "Masukkan Username: ";
                cin >> ws;
                getline(cin, username);
                cout << "Masukkan Password: ";
                cin >> password;

                bool loginSuccess = false;
                for (int i = 0; i < userCount; i++) {
                    if (users[i].username == username && users[i].password == password) {
                        if ((loginType == 1 && users[i].isAdmin) || (loginType == 2 && !users[i].isAdmin)) {
                            loginSuccess = true;
                            isAdmin = users[i].isAdmin;
                            currentUserId = i;
                            break;
                        }
                    }
                }

                if (loginSuccess) {
                    cout << "Login berhasil!\n";
                    cout << "Selamat Datang " << (isAdmin ? "Bos" : "Tuan") << " " << username << endl;

                    // Menu setelah login
                    bool isLoggedIn = true;
                    while (isLoggedIn) {
                        if (isAdmin) {
                            // Menu admin
                            cout << "\n===== MENU ADMIN =====\n";
                            cout << "1. Tambah Film\n";
                            cout << "2. Hapus Film\n";
                            cout << "3. Lihat Film\n";
                            cout << "4. Lihat Transaksi\n";
                            cout << "5. Log out\n";
                            cout << "Pilihan Anda: ";
                            cin >> pilihan;

                            switch (pilihan) {
                                case 1: {
                                    // Tambah film
                                    if (filmCount >= 10) {
                                        cout << "Maaf, kapasitas film sudah penuh!\n";
                                        break;
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
                                    break;
                                }
                                case 2: {
                                    // Hapus film
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
                                        break;
                                    }

                                    for (int i = filmPilihan - 1; i < filmCount - 1; i++) {
                                        films[i] = films[i + 1];
                                    }

                                    filmCount--;
                                    cout << "Film berhasil ditarik dari penayangan!\n";
                                    break;
                                }
                                case 3: {
                                    // Lihat film yang tersedia
                                    cout << "\n===== DAFTAR FILM =====\n";
                                    for (int i = 0; i < filmCount; i++) {
                                        cout << i + 1 << ". " << films[i].namaFilm << endl;
                                        cout << "   Jam Tayang: ";
                                        for (int j = 0; j < 5; j++) {
                                            int kursiTersisa = maksKursi - films[i].jamTayang[j].kursiTerisi;
                                            cout << films[i].jamTayang[j].jam << " (" << kursiTersisa << " kursi) ";
                                        }
                                        cout << endl;
                                    }
                                    break;
                                }
                                case 4: {
                                    // Lihat transaksi
                                    cout << "\n===== TRANSAKSI =====\n";
                                    for (int i = 0; i < bookingCount; i++) {
                                        cout << "ID Booking: " << i << endl;
                                        cout << "Film: " << films[bookings[i].filmId].namaFilm << endl;
                                        cout << "Jam: " << films[bookings[i].filmId].jamTayang[bookings[i].jamId].jam << endl;
                                        cout << "User: " << users[bookings[i].userId].username << endl;  // Menampilkan nama user
                                        cout << "Status: " << (bookings[i].isPaid ? "Sudah dibayar" : "Belum dibayar") << endl;
                                        cout << "-----------------------\n";
                                    }
                                    break;
                                }
                                case 5: {
                                    // Keluar dari menu admin, kembali ke menu utama
                                    cout << "Kembali ke menu utama\n";
                                    isLoggedIn = false;
                                    break;
                                }
                                default: {
                                    cout << "Pilihan tidak valid!\n";
                                    break;
                                }
                            }
                        } else {
                            // Menu user
                            cout << "\n===== MENU USER =====\n";
                            cout << "1. Pesan Tiket\n";
                            cout << "2. Lihat Film yang Tersedia\n";
                            cout << "3. Lihat Tiket yang Sudah Dipesan\n";
                            cout << "4. Ganti Jam Tayang\n";
                            cout << "5. Batalkan Tiket\n";
                            cout << "6. Bayar Tiket\n";
                            cout << "7. Log out\n";
                            cout << "Pilihan Anda: ";
                            cin >> pilihan;

                            switch (pilihan) {
                                case 1: {
                                    // Pesan tiket
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
                                        break;
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
                                        break;
                                    }

                                    // Cek apakah kursi masih tersedia
                                    if (films[filmPilihan - 1].jamTayang[jamPilihan - 1].kursiTerisi >= maksKursi) {
                                        cout << "Maaf, kursi untuk film dan jam tersebut sudah penuh!\n";
                                        break;
                                    }

                                    // Simpan booking
                                    bookings[bookingCount].filmId = filmPilihan - 1;
                                    bookings[bookingCount].jamId = jamPilihan - 1;
                                    bookings[bookingCount].isPaid = false;
                                    bookings[bookingCount].userId = currentUserId;  // Simpan ID user yang melakukan booking

                                    // Update kursi terisi
                                    films[filmPilihan - 1].jamTayang[jamPilihan - 1].kursiTerisi++;

                                    cout << "Booking berhasil!\n";
                                    cout << "ID Booking Anda: " << bookingCount << endl;
                                    cout << "Film: " << films[filmPilihan - 1].namaFilm << endl;
                                    cout << "Jam: " << films[filmPilihan - 1].jamTayang[jamPilihan - 1].jam << endl;
                                    cout << "Status: Belum dibayar\n";

                                    bookingCount++;
                                    break;
                                }
                                case 2: {
                                    // Lihat film yang tersedia
                                    cout << "\n===== FILM YANG TERSEDIA =====\n";
                                    for (int i = 0; i < filmCount; i++) {
                                        cout << i + 1 << ". " << films[i].namaFilm << endl;
                                        cout << "   Jam Tayang: ";
                                        for (int j = 0; j < 5; j++) {
                                            int kursiTersisa = maksKursi - films[i].jamTayang[j].kursiTerisi;
                                            cout << films[i].jamTayang[j].jam << " (" << kursiTersisa << " kursi) ";
                                        }
                                        cout << endl;
                                    }
                                    break;
                                }
                                case 3: {
                                    // Lihat tiket yang sudah dipesan
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
                                    break;
                                }
                                case 4: {
                                    // Ganti jam tayang
                                    cout << "\n===== GANTI JAM TAYANG =====\n";

                                    int idBooking;
                                    cout << "Masukkan ID Booking: ";
                                    cin >> idBooking;

                                    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
                                        cout << "ID Booking tidak valid!\n";
                                        break;
                                    }

                                    if (bookings[idBooking].isPaid) {
                                        cout << "Tidak dapat mengubah jam tayang tiket yang sudah dibayar!\n";
                                        break;
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
                                        break;
                                    }

                                    if (films[filmId].jamTayang[jamBaru - 1].kursiTerisi >= maksKursi) {
                                        cout << "Maaf, kursi untuk jam tersebut sudah penuh!\n";
                                        break;
                                    }

                                    // Update kursi terisi
                                    films[filmId].jamTayang[jamLama].kursiTerisi--;
                                    films[filmId].jamTayang[jamBaru - 1].kursiTerisi++;

                                    // Update booking
                                    bookings[idBooking].jamId = jamBaru - 1;

                                    cout << "Jam tayang berhasil diubah!\n";
                                    cout << "Film: " << films[filmId].namaFilm << endl;
                                    cout << "Jam tayang baru: " << films[filmId].jamTayang[jamBaru - 1].jam << endl;
                                    break;
                                }
                                case 5: {
                                    // Batalkan tiket
                                    cout << "\n===== BATALKAN TIKET =====\n";

                                    int idBooking;
                                    cout << "Masukkan ID Booking: ";
                                    cin >> idBooking;

                                    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
                                        cout << "ID Booking tidak valid!\n";
                                        break;
                                    }

                                    if (bookings[idBooking].isPaid) {
                                        cout << "Tidak dapat membatalkan tiket yang sudah dibayar!\n";
                                        break;
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
                                    break;
                                }
                                case 6: {
                                    // Bayar tiket
                                    cout << "\n===== BAYAR TIKET =====\n";

                                    int idBooking;
                                    cout << "Masukkan ID Booking: ";
                                    cin >> idBooking;

                                    if (idBooking < 0 || idBooking >= bookingCount || bookings[idBooking].filmId == -1) {
                                        cout << "ID Booking tidak valid!\n";
                                        break;
                                    }

                                    if (bookings[idBooking].isPaid) {
                                        cout << "Tiket sudah dibayar sebelumnya!\n";
                                        break;
                                    }

                                    // Update status pembayaran
                                    bookings[idBooking].isPaid = true;

                                    cout << "Pembayaran berhasil!\n";
                                    cout << "Film: " << films[bookings[idBooking].filmId].namaFilm << endl;
                                    cout << "Jam: " << films[bookings[idBooking].filmId].jamTayang[bookings[idBooking].jamId].jam << endl;
                                    cout << "Status: Sudah dibayar\n";
                                    break;
                                }
                                case 7: {
                                    // Keluar dari menu user, kembali ke menu utama
                                    cout << "Kembali ke menu utama\n";
                                    isLoggedIn = false;
                                    break;
                                }
                                default: {
                                    cout << "Pilihan tidak valid!\n";
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    loginAttempts++;  // Tambahkan percobaan login yang gagal
                    cout << "Login gagal, Username atau Password salah! Sisa percobaan anda sebanyak " << 3 - loginAttempts << endl;

                    if (loginAttempts >= 3) {
                        cout << "Kesempatan anda telah habis, silahkan mencoba lagi dalam beberapa saat.\n";
                        isRunning = false;  // Menghentikan program
                    }
                }
                break;
            }
            case 3: {
                // Keluar dari program
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