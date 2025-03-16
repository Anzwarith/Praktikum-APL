#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    // Film data
    string films[5] = {"Kimi No Nawa", "Godzilla : Minus one", "Avengers : secret wars", "Your Lie In April", "Cek Toko Sebelah"};
    
    // Jam tayang: 10:00, 12:00, 15:00, 17:00, 19:00
    string jamTayang[5] = {"10:00", "12:00", "15:00", "17:00", "19:00"};
    
    // Array untuk menyimpan booking
    // [user_id][0] = film_id, [user_id][1] = jam_id, [user_id][2] = status_bayar (0=belum, 1=sudah)
    int bookings[10][3];
    
    // Array untuk tracking apakah kursi sudah dibooking
    // [film_id][jam_id] = jumlah kursi terisi
    int kursiTerisi[5][5] = {0};
    
    // Kapasitas maksimum per film dan jam
    int maksKursi = 20;
    
    // Inisialisasi bookings dengan -1 (tidak ada booking)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            bookings[i][j] = -1;
        }
    }
    
    int userId = 0; // User ID counter
    int pilihan = 0;
    bool isRunning = true;
    int loginAttempts = 0;
    string nama, password;

    // Login system
    while (loginAttempts < 3) {
        cout << "===== SELAMAT DATANG! SILAHKAN LOGIN TERLEBIH DAHULU =====\n";
        cout << "Masukkan Nama: ";
        cin >> nama;
        cout << "Masukkan Password: ";
        cin >> password;

        if (nama == "DHPW" && password == "096") {
            cout << "Login berhasil!\n";
            cout << "Selamat Datang Diaplikasi Pemesanan Tiket Online Tuan " << nama << endl;
            break;
        } else {
            loginAttempts++;
            cout << "Login gagal, Username atau Password salah! Sisa percobaan: " << 3 - loginAttempts << endl;
        }
    }

    if (loginAttempts == 3) {
        cout << "Kesempatan anda telah habis, silahkan mencoba dalam beberapa saat lagi\n";
        return 0;
    }

    while (isRunning) {
        // Menu utama
        cout << "\n===== SISTEM BOOKING TIKET BIOSKOP =====\n";
        cout << "1. Pesan Tiket\n";
        cout << "2. Lihat Film yang Tersedia\n";
        cout << "3. Lihat Tiket yang Sudah Dipesan\n";
        cout << "4. Ganti Jam Tayang\n";
        cout << "5. Batalkan Tiket\n";
        cout << "6. Bayar Tiket\n";
        cout << "7. Keluar Aplikasi\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                // Pesan tiket
                cout << "\n===== PESAN TIKET =====\n";
                
                // Tampilkan film yang tersedia
                cout << "Film yang tersedia:\n";
                for (int i = 0; i < 5; i++) {
                    cout << i+1 << ". " << films[i] << endl;
                }
                
                int filmPilihan;
                cout << "Pilih film (1-5): ";
                cin >> filmPilihan;
                
                if (filmPilihan < 1 || filmPilihan > 5) {
                    cout << "Film tidak valid!\n";
                    break;
                }
                
                // Tampilkan jam tayang
                cout << "Jam tayang yang tersedia:\n";
                for (int i = 0; i < 5; i++) {
                    int kursiTersisa = maksKursi - kursiTerisi[filmPilihan-1][i];
                    cout << i+1 << ". " << jamTayang[i] << " (Kursi tersisa: " << kursiTersisa << ")\n";
                }
                
                int jamPilihan;
                cout << "Pilih jam tayang (1-5): ";
                cin >> jamPilihan;
                
                if (jamPilihan < 1 || jamPilihan > 5) {
                    cout << "Jam tayang tidak valid!\n";
                    break;
                }
                
                // Cek apakah kursi masih tersedia
                if (kursiTerisi[filmPilihan-1][jamPilihan-1] >= maksKursi) {
                    cout << "Maaf, kursi untuk film dan jam tersebut sudah penuh!\n";
                    break;
                }
                
                // Simpan booking
                bookings[userId][0] = filmPilihan - 1;
                bookings[userId][1] = jamPilihan - 1;
                bookings[userId][2] = 0; // Belum bayar
                
                // Update kursi terisi
                kursiTerisi[filmPilihan-1][jamPilihan-1]++;
                
                cout << "Booking berhasil!\n";
                cout << "ID Booking Anda: " << userId << endl;
                cout << "Film: " << films[filmPilihan-1] << endl;
                cout << "Jam: " << jamTayang[jamPilihan-1] << endl;
                cout << "Status: Belum dibayar\n";
                
                userId++;
                break;
            }
            case 2: {
                // Lihat film yang tersedia
                cout << "\n===== FILM YANG TERSEDIA =====\n";
                for (int i = 0; i < 5; i++) {
                    cout << i+1 << ". " << films[i] << endl;
                    cout << "   Jam Tayang: ";
                    for (int j = 0; j < 5; j++) {
                        int kursiTersisa = maksKursi - kursiTerisi[i][j];
                        cout << jamTayang[j] << " (" << kursiTersisa << " kursi) ";
                    }
                    cout << endl;
                }
                break;
            }
            case 3: {
                // Lihat tiket yang sudah dipesan
                cout << "\n===== TIKET YANG SUDAH DIPESAN =====\n";
                bool adaTiket = false;
                
                for (int i = 0; i < userId; i++) {
                    if (bookings[i][0] != -1) {
                        adaTiket = true;
                        cout << "ID Booking: " << i << endl;
                        cout << "Film: " << films[bookings[i][0]] << endl;
                        cout << "Jam: " << jamTayang[bookings[i][1]] << endl;
                        cout << "Status: " << (bookings[i][2] == 1 ? "Sudah dibayar" : "Belum dibayar") << endl;
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
                
                if (idBooking < 0 || idBooking >= userId || bookings[idBooking][0] == -1) {
                    cout << "ID Booking tidak valid!\n";
                    break;
                }
                
                if (bookings[idBooking][2] == 1) {
                    cout << "Tidak dapat mengubah jam tayang tiket yang sudah dibayar!\n";
                    break;
                }
                
                int filmId = bookings[idBooking][0];
                int jamLama = bookings[idBooking][1];
                
                // Tampilkan jam tayang yang tersedia
                cout << "Jam tayang saat ini: " << jamTayang[jamLama] << endl;
                cout << "Jam tayang baru yang tersedia:\n";
                
                for (int i = 0; i < 5; i++) {
                    int kursiTersisa = maksKursi - kursiTerisi[filmId][i];
                    cout << i+1 << ". " << jamTayang[i] << " (Kursi tersisa: " << kursiTersisa << ")\n";
                }
                
                int jamBaru;
                cout << "Pilih jam tayang baru (1-5): ";
                cin >> jamBaru;
                
                if (jamBaru < 1 || jamBaru > 5) {
                    cout << "Jam tayang tidak valid!\n";
                    break;
                }
                
                if (kursiTerisi[filmId][jamBaru-1] >= maksKursi) {
                    cout << "Maaf, kursi untuk jam tersebut sudah penuh!\n";
                    break;
                }
                
                // Update kursi terisi
                kursiTerisi[filmId][jamLama]--;
                kursiTerisi[filmId][jamBaru-1]++;
                
                // Update booking
                bookings[idBooking][1] = jamBaru - 1;
                
                cout << "Jam tayang berhasil diubah!\n";
                cout << "Film: " << films[filmId] << endl;
                cout << "Jam tayang baru: " << jamTayang[jamBaru-1] << endl;
                break;
            }
            case 5: {
                // Batalkan tiket
                cout << "\n===== BATALKAN TIKET =====\n";
                
                int idBooking;
                cout << "Masukkan ID Booking: ";
                cin >> idBooking;
                
                if (idBooking < 0 || idBooking >= userId || bookings[idBooking][0] == -1) {
                    cout << "ID Booking tidak valid!\n";
                    break;
                }
                
                if (bookings[idBooking][2] == 1) {
                    cout << "Tidak dapat membatalkan tiket yang sudah dibayar!\n";
                    break;
                }
                
                int filmId = bookings[idBooking][0];
                int jamId = bookings[idBooking][1];
                
                // Update kursi terisi
                kursiTerisi[filmId][jamId]--;
                
                // Hapus booking
                bookings[idBooking][0] = -1;
                bookings[idBooking][1] = -1;
                bookings[idBooking][2] = -1;
                
                cout << "Tiket berhasil dibatalkan!\n";
                break;
            }
            case 6: {
                // Bayar tiket
                cout << "\n===== BAYAR TIKET =====\n";
                
                int idBooking;
                cout << "Masukkan ID Booking: ";
                cin >> idBooking;
                
                if (idBooking < 0 || idBooking >= userId || bookings[idBooking][0] == -1) {
                    cout << "ID Booking tidak valid!\n";
                    break;
                }
                
                if (bookings[idBooking][2] == 1) {
                    cout << "Tiket sudah dibayar sebelumnya!\n";
                    break;
                }
                
                // Update status pembayaran
                bookings[idBooking][2] = 1;
                
                cout << "Pembayaran berhasil!\n";
                cout << "Film: " << films[bookings[idBooking][0]] << endl;
                cout << "Jam: " << jamTayang[bookings[idBooking][1]] << endl;
                cout << "Status: Sudah dibayar\n";
                break;
            }
            case 7: {
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