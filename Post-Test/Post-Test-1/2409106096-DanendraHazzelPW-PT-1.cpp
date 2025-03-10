#include <iostream>
using namespace std;

int main() {
    // Variabel untuk login
    string username, password;
    string Username = "Danendra Hazzel Putra Wahana"; // Ganti dengan nama lengkap kalian
    string Password = "2409106096"; // Ganti dengan NIM kalian

    // Login
    cout << "Silahkan Login terlebih dahulu\n";
    cout << "Masukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);

    // Cek login
    if (username == Username && password == Password) {
        int choice;
        do {
            // Menu Utama
            cout << "== SISTEM HITUNG BANGUN DATAR DAN BANGUN RUANG ==\n";
            cout << "1. Hitung Luas\n";
            cout << "2. Hitung Keliling\n";
            cout << "3. Hitung Volume\n";
            cout << "4. Logout\n";
            cout << "Pilih menu: ";
            cin >> choice;

            switch (choice) {
                case 1: { // Hitung Luas
                    int luasChoice;
                    cout << "== HITUNG LUAS ==\n";
                    cout << "1. Persegi\n";
                    cout << "2. Persegi Panjang\n";
                    cout << "3. Lingkaran\n";
                    cout << "4. Segitiga\n";
                    cout << "5. Kembali\n";
                    cout << "Pilih bangun: ";
                    cin >> luasChoice;

                    if (luasChoice == 1) {
                        float sisi;
                        cout << "Masukkan panjang sisi persegi: ";
                        cin >> sisi;
                        cout << "Luas Persegi: " << sisi * sisi << endl;
                    } else if (luasChoice == 2) {
                        float panjang, lebar;
                        cout << "Masukkan panjang persegi panjang: ";
                        cin >> panjang;
                        cout << "Masukkan lebar persegi panjang: ";
                        cin >> lebar;
                        cout << "Luas Persegi Panjang: " << panjang * lebar << endl;
                    } else if (luasChoice == 3) {
                        float jariJari;
                        cout << "Masukkan jari-jari lingkaran: ";
                        cin >> jariJari;
                        cout << "Luas Lingkaran: " << 3.14 * jariJari * jariJari << endl;
                    } else if (luasChoice == 4) {
                        float alas, tinggi;
                        cout << "Masukkan alas segitiga: ";
                        cin >> alas;
                        cout << "Masukkan tinggi segitiga: ";
                        cin >> tinggi;
                        cout << "Luas Segitiga: " << 0.5 * alas * tinggi << endl;
                    }
                    break;
                }
                case 2: { // Hitung Keliling
                    int kelilingChoice;
                    cout << "== HITUNG KELILING ==\n";
                    cout << "1. Persegi\n";
                    cout << "2. Persegi Panjang\n";
                    cout << "3. Lingkaran\n";
                    cout << "4. Segitiga\n";
                    cout << "5. Kembali\n";
                    cout << "Pilih bangun: ";
                    cin >> kelilingChoice;

                    if (kelilingChoice == 1) {
                        float sisi;
                        cout << "Masukkan panjang sisi persegi: ";
                        cin >> sisi;
                        cout << "Keliling Persegi: " << 4 * sisi << endl;
                    } else if (kelilingChoice == 2) {
                        float panjang, lebar;
                        cout << "Masukkan panjang persegi panjang: ";
                        cin >> panjang;
                        cout << "Masukkan lebar persegi panjang: ";
                        cin >> lebar;
                        cout << "Keliling Persegi Panjang: " << 2 * (panjang + lebar) << endl;
                    } else if (kelilingChoice == 3) {
                        float jariJari;
                        cout << "Masukkan jari-jari lingkaran: ";
                        cin >> jariJari;
                        cout << "Keliling Lingkaran: " << 2 * 3.14 * jariJari << endl;
                    } else if (kelilingChoice == 4) {
                        float a, b, c;
                        cout << "Masukkan panjang sisi segitiga (a, b, c): ";
                        cin >> a >> b >> c;
                        cout << "Keliling Segitiga: " << (a + b + c) << endl;
                    }
                    break;
                }
                case 3: { // Hitung Volume
                    int volumeChoice;
                    cout << "== HITUNG VOLUME ==\n";
                    cout << "1. Kubus\n";
                    cout << "2. Balok\n";
                    cout << "3. Bola\n";
                    cout << "4. Kerucut\n";
                    cout << "5. Kembali\n";
                    cout << "Pilih bangun: ";
                    cin >> volumeChoice;

                    if (volumeChoice == 1) {
                        float sisi;
                        cout << "Masukkan panjang sisi kubus: ";
                        cin >> sisi;
                        cout << "Volume Kubus: " << sisi * sisi * sisi << endl;
                    } else if (volumeChoice == 2) {
                        float panjang, lebar, tinggi;
                        cout << "Masukkan panjang balok: ";
                        cin >> panjang;
                        cout << "Masukkan lebar balok: ";
                        cin >> lebar;
                        cout << "Masukkan tinggi balok: ";
                        cin >> tinggi;
                        cout << "Volume Balok: " << panjang * lebar * tinggi << endl;
                    } else if (volumeChoice == 3) {
                        float jariJari;
                        cout << "Masukkan jari-jari bola: ";
                        cin >> jariJari;
                        cout << "Volume Bola: " << (4.0 / 3.0) * 3.14 * jariJari * jariJari * jariJari << endl;
                    } else if (volumeChoice == 4) {
                        float jariJari, tinggi;
                        cout << "Masukkan jari-jari kerucut: ";
                        cin >> jariJari;
                        cout << "Masukkan tinggi kerucut: ";
                        cin >> tinggi;
                        cout << "Volume Kerucut: " << (1.0 / 3.0) * 3.14 * jariJari * jariJari * tinggi << endl;
                    }
                    break;
                }
                case 4: // Logout
                    cout << "Anda telah logout.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                    break;
            }
        } while (choice != 4);
    } else {
        cout << "Username atau Password salah.\n";

    }

    return 0;
}