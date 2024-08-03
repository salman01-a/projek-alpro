#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// struct menu restoran
struct restoran
{
    char kode;
    string nama;
    int jumlahroti;
    string menupesan;
    int harga;
    int sub_tot;
};

// fungsi yang digunakan untuk seluruh menu
restoran res[100];
void input();
void menu();
void output();
void search();
void edit();
void reset();
void bayar();
void bacafile();
void sort(restoran res[], int jml);
string underscore2space(string text);
void writeFile();

string filename = "bread.txt";
int total = 0;
float tot = 0;

int main()
{
    system("cls");
    string pick, yn;
    // menu
    cout << "=====================================" << endl;
    cout << "|      SELAMAT DATANG DI MAKO       |" << endl;
    cout << "=====================================" << endl;
    cout << "|1. Pesan                           |" << endl;
    cout << "|2. Lihat Pesanan                   |" << endl;
    cout << "|3. Cari Pesanan                    |" << endl;
    cout << "|4. Edit Pesanan                    |" << endl;
    cout << "|5. Bayar                           |" << endl;
    cout << "|6. Reset                           |" << endl;
    cout << "|7. Exit                            |" << endl;
    cout << "=====================================" << endl;
    cout << "Pilih Menu : ";
    cin >> pick;

    // pilihan menu
    if (pick == "1")
    {
        system("cls");
        menu();
        input();
    }
    else if (pick == "2")
    {
        system("cls");
        bacafile();
        output();
    }
    else if (pick == "3")
    {
        system("cls");
        bacafile();
        search();
    }
    else if (pick == "4")
    {
        system("cls");
        edit();
    }
    else if (pick == "5")
    {
        system("cls");
        bayar();
    }
    else if (pick == "6")
    {
        system("cls");
        reset();
    }
    else if (pick == "7")
    {
        system("cls");
       cout<<"Terima Kasih Telah Menggunakan Program ini"<<endl;
       cout<<"Kami Mohon Maaf Jika Ada Kekurangan"<<endl; 
		cout << "=========================================" << endl;
        cout << "|	Nama Anggota Kelompok 7		 |" << endl;
		cout << "=========================================" << endl;
        cout << "|Melania Intan Sagita   (123230005)	 |" << endl;
        cout << "|Fadilah Nur Sabiyyah   (123230006)	 |" << endl;
        cout << "|Imam Khusain           (123230018)	 |" << endl;
        cout << "|Anindya Aurellia Salma (123230023)	 |" << endl;
        cout << "|Salman Faris           (123230024)	 |" << endl;
		cout << "=========================================" << endl;
		exit(0);
    }

    // menu kembali
    cout << "\nKembali ke menu utama (y/n)? ";
    cin >> yn;
    if (yn == "y" || yn == "Y")
    {
        system("cls");
        main();
    }
    else
    {
        cout << endl;
        cout << "Terima Kasih Telah Membeli :)";
    }
}

// fungsi pilihan menu (makanan dan minuman)
void menu()
{   
    cout << "=========================================" << endl;
    cout << "|          Menu [Rekomendasi]           |" << endl;
    cout << "=========================================" << endl;
    cout << "|1.  Spicy Floss        [a] Rp 12.500   |" << endl;
    cout << "|5.  Rendang Floss      [e] Rp 12.500   |" << endl;
    cout << "=========================================" << endl;
    
    cout << "=========================================" << endl;
    cout << "|            Menu [Kode]                |" << endl;
    cout << "=========================================" << endl;
    cout << "|1.  Spicy Floss        [a] Rp 12.500   |" << endl;
    cout << "|2.  Sausage Diva       [b] Rp 12.500   |" << endl;
    cout << "|3.  Floss Roll         [c] Rp 14.500   |" << endl;
    cout << "|4.  Choco Meises       [d] Rp 12.500   |" << endl;
    cout << "|5.  Rendang Floss      [e] Rp 12.500   |" << endl;
    cout << "|6.  Milky Bun          [f] Rp 9.000    |" << endl;
    cout << "|7.  Coffee Bun         [g] Rp 12.000   |" << endl;
    cout << "|8.  Choco Bun          [h] Rp 9.000    |" << endl;
    cout << "|9.  Sugar Pillow       [i] Rp 10.000   |" << endl;
    cout << "|10. Banana Choco Cheese[j] Rp 12.500   |" << endl;
    cout << "=========================================" << endl;
}

// fungsi file
void bacafile()
{
    ifstream myfile(filename);
    total = 0;
    if (myfile.is_open())
    {
        int i = 0;
        while (myfile >> res[i].kode >> res[i].menupesan >> res[i].jumlahroti >> res[i].nama >> res[i].harga >> res[i].sub_tot)
        {
            res[i].menupesan = underscore2space(res[i].menupesan);
            res[i].nama = underscore2space(res[i].nama);
            i++;
        }
        total = i;
        myfile.close();
    }
    else
        cout << "File Tidak Ditemukan!!" << endl;
}

string space2underscore(string text)
{
    int a = text.length();
    for (int i = 0; i < a; i++)
    {
        if (text[i] == ' ')
            text[i] = '_';
    }
    return text;
}

string underscore2space(string text)
{
    int a = text.length();
    for (int i = 0; i < a; i++)
    {
        if (text[i] == '_')
            text[i] = ' ';
    }
    return text;
}

// fungsi input menu/res
void input()
{
    int num_items;
    string customer_name;

    cout << endl;
    cout << "===========" << endl;
    cout << "|  INPUT  |" << endl;
    cout << "===========" << endl;
    cout << "Atas Nama: ";
    getline(cin >> ws, customer_name);
    cout << "Jumlah Jenis Pesanan yang Ingin Dipesan: ";
    cin >> num_items;
    cout << endl;

    for (int i = total; i < total + num_items; i++)
    {
        res[i].nama = customer_name;
        cout << "Pesanan [" << i - total + 1 << "]" << endl;
        cout << "Kode Roti: ";
        cin >> res[i].kode;

        // pilihan menu menggunakan kode
        switch (tolower(res[i].kode))
        {
        case 'a':
            res[i].menupesan = "Spicy Floss";
            res[i].harga = 12500;
            break;
        case 'b':
            res[i].menupesan = "Sausage Diva";
            res[i].harga = 12500;
            break;
        case 'c':
            res[i].menupesan = "Floss Roll";
            res[i].harga = 14500;
            break;
        case 'd':
            res[i].menupesan = "Choco Meises";
            res[i].harga = 12500;
            break;
        case 'e':
            res[i].menupesan = "Rendang Floss";
            res[i].harga = 12500;
            break;
        case 'f':
            res[i].menupesan = "Milky Bun";
            res[i].harga = 9000;
            break;
        case 'g':
            res[i].menupesan = "Coffee Bun";
            res[i].harga = 12000;
            break;
        case 'h':
            res[i].menupesan = "Choco Bun";
            res[i].harga = 9000;
            break;
        case 'i':
            res[i].menupesan = "Sugar Pillow";
            res[i].harga = 10000;
            break;
        case 'j':
            res[i].menupesan = "Banana Choco Cheese";
            res[i].harga = 12500;
            break;
        default:
            cout << "Kode Roti tidak valid." << endl;
            i--;
            continue;
        }

        cout << "Jumlah Menu yang dipesan: ";
        cin >> res[i].jumlahroti;
        res[i].sub_tot = res[i].jumlahroti * res[i].harga;
        tot += res[i].sub_tot;
        cout << endl;
    }

    ofstream myfile(filename, ios::app);
    if (myfile.is_open())
    {
        for (int i = total; i < total + num_items; i++)
        {
            myfile << left << setw(3) << res[i].kode << setw(25) << space2underscore(res[i].menupesan) << setw(5) << res[i].jumlahroti << setw(20) << space2underscore(res[i].nama) << setw(10) << res[i].harga << setw(10) << res[i].sub_tot << endl;
        }
        myfile.close();
        total += num_items;
    }
    else
        cout << "File tidak ditemukan!!" << endl;

    cout << endl;
}

// fungsi output pesanan
void output()
{
    cout << "=================================================================================" << endl;
    cout << "|"
         << left << setw(3) << "No"
         << "|"
         << left << setw(25) << "Menu Pesanan"
         << "|"
         << left << setw(5) << "Jumlah"
         << "|"
         << left << setw(20) << "Atas Nama"
         << "|"
         << left << setw(10) << "Harga"
         << "|"
         << left << setw(10) << "Sub Total"
         << "|" << endl;
      cout << "=================================================================================" << endl;
    for (int i = 0; i < total; i++)
    {
        cout << "|"
             << left << setw(3) << i + 1
             << "|"
             << left << setw(25) << res[i].menupesan
             << "|"
             << left << setw(5) << res[i].jumlahroti
             << "|"
             << left << setw(20) << res[i].nama
             << "|"
             << left << setw(10) << res[i].harga
             << "|"
             << left << setw(10) << res[i].sub_tot
             << "|" << endl;
    }
    cout << "=================================================================================" << endl;
}

// fungsi searching pesanan
void search()
{
    string xnama;
    int z = 0;
    cout << "Cari Pesanan Atas Nama : ";
    getline(cin >> ws, xnama);
    cout << "Hasil Pencarian" << endl;
  cout << "=================================================================================" << endl;
    cout << "|"
         << left << setw(3) << "No"
         << "|"
         << left << setw(25) << "Menu Pesanan"
         << "|"
         << left << setw(5) << "Jumlah"
         << "|"
         << left << setw(20) << "Atas Nama"
         << "|"
         << left << setw(10) << "Harga"
         << "|"
         << left << setw(10) << "Sub Total"
         << "|" << endl;
    cout << "=================================================================================" << endl;
    for (int i = 0; i < total; i++)
    {
        if (xnama == res[i].nama)
        {
            z = 1;
            cout << "|"
                 << left << setw(3) << i + 1
                 << "|"
                 << left << setw(25) << res[i].menupesan
                 << "|"
                 << left << setw(5) << res[i].jumlahroti
                 << "|"
                 << left << setw(20) << res[i].nama
                 << "|"
                 << left << setw(10) << res[i].harga
                 << "|"
                 << left << setw(10) << res[i].sub_tot
                 << "|" << endl;
        }
    }
    if (z == 0)
    {
        cout << "Data Tidak Ada" << endl;
    }
 cout << "=================================================================================" << endl;
}

// fungsi edit pesanan
void edit()
{
	bool found= false;
    bacafile();
    string xnama;
    cout << "Edit Pesanan" << endl;
    cout << "Cari Pesanan Atas Nama : ";
    getline(cin >> ws, xnama);
    for (int i = 0; i < total; i++)
    {
        if (xnama == res[i].nama)
        {
			found= true;
			cout<< "Data Pesanan Ke- "<<i+1<<endl;
            cout << "Kode Roti [a/b/c/d/e/f/g/h/i/j]: ";
            cin >> res[i].kode;
            switch (tolower(res[i].kode))
            {
            case 'a':
                res[i].menupesan = "Spicy Floss";
                res[i].harga = 12500;
                break;
            case 'b':
                res[i].menupesan = "Sausage Diva";
                res[i].harga = 12500;
                break;
            case 'c':
                res[i].menupesan = "Floss Roll";
                res[i].harga = 14500;
                break;
            case 'd':
                res[i].menupesan = "Choco Meises";
                res[i].harga = 12500;
                break;
            case 'e':
                res[i].menupesan = "Rendang Floss";
                res[i].harga = 12500;
                break;
            case 'f':
                res[i].menupesan = "Milky Bun";
                res[i].harga = 9000;
                break;
            case 'g':
                res[i].menupesan = "Coffee Bun";
                res[i].harga = 12000;
                break;
            case 'h':
                res[i].menupesan = "Choco Bun";
                res[i].harga = 9000;
                break;
            case 'i':
                res[i].menupesan = "Sugar Pillow";
                res[i].harga = 10000;
                break;
            case 'j':
                res[i].menupesan = "Banana Choco Cheese";
                res[i].harga = 12500;
                break;
            default:
                cout << "Kode Roti tidak valid." << endl;
                continue;
            }
            cout << "Jumlah Menu yang dipesan: ";
            cin >> res[i].jumlahroti;
            res[i].sub_tot = res[i].jumlahroti * res[i].harga;
        }
    }if(!found) cout<<"Pesanan Tidak Ditemukan"<<endl;
    writeFile();
}

// fungsi reset pesanan
void reset()
{
    ofstream myfile(filename);
    if (myfile.is_open())
    {
        myfile << "";
        myfile.close();
    }
    cout << "Data telah direset!" << endl;
}

void bayar()
{
    string xnama;
    cout << "Atas Nama yang ingin Membayar: ";
    getline(cin >> ws, xnama);
    float bayar = 0;
    for (int i = 0; i < total; i++)
    {
        if (xnama == res[i].nama)
        {
            bayar += res[i].sub_tot;
        }
    }
    if (bayar > 0)
    {
        cout << "Total Bayar : Rp " << bayar << endl;
        cout << "==============================================" << endl;
        cout << "| Terima Kasih Telah Membeli Di Toko Kami :) |" << endl;
        cout << "==============================================" << endl;
        
        // Menghapus res yang telah membayar dari array
        int j = 0;
        for (int i = 0; i < total; i++)
        {
            if (xnama != res[i].nama)
            {
                res[j] = res[i];
                j++;
            }
        }
        total = j;

        // Tulis ulang file dengan res yang diperbarui
        writeFile();
    }
    else
    {
        cout << "Nama tidak ditemukan!" << endl;
    }
}

// Fungsi untuk menulis ulang file dengan res yang diperbarui
void writeFile()
{
    ofstream myfile(filename);
    if (myfile.is_open())
    {
        for (int i = 0; i < total; i++)
        {
            myfile << left << setw(3) << res[i].kode << setw(25) << space2underscore(res[i].menupesan) << setw(5) << res[i].jumlahroti << setw(20) << space2underscore(res[i].nama) << setw(10) << res[i].harga << setw(10) << res[i].sub_tot << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "File tidak ditemukan!" << endl;
    }
}
