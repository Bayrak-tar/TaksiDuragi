#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

struct Taksi {
    string plaka;
    string model;
    string surucuAdi;
    bool bos;
};

const int MAX_TAKSI = 10;

void kullaniciKaydet(Taksi taksiler[], int toplamTaksi) {
    ofstream dosya("taksi_dosya.txt");

    for (int i = 0; i < toplamTaksi; i++) {
        dosya << taksiler[i].plaka << " "
              << taksiler[i].model << " "
              << taksiler[i].surucuAdi << " "
              << taksiler[i].bos << endl;
    }

    dosya.close();
}

void kullaniciOku(Taksi taksiler[], int& toplamTaksi) {
    ifstream dosya("taksi_dosya.txt");

    toplamTaksi = 0;
    while (dosya >> taksiler[toplamTaksi].plaka
                  >> taksiler[toplamTaksi].model
                  >> taksiler[toplamTaksi].surucuAdi
                  >> taksiler[toplamTaksi].bos) {
        toplamTaksi++;
    }

    dosya.close();
}

int taksiAra(Taksi taksiler[], int toplamTaksi, string plaka) {
    for (int i = 0; i < toplamTaksi; i++) {
        if (taksiler[i].plaka == plaka) {
            return i;
        }
    }
    return -1;
}

void taksiGuncelle(Taksi taksiler[], int toplamTaksi) {
    string plaka;
    cout << "Guncellenecek taksi plakasini giriniz: ";
    cin >> plaka;

    int index = taksiAra(taksiler, toplamTaksi, plaka);

    if (index != -1) {
        cout << "Yeni taksi modelini giriniz: ";
        cin >> taksiler[index].model;
        cout << "Yeni surucu adini giriniz: ";
        cin >> taksiler[index].surucuAdi;
        cout << "Taksi bilgileri guncellendi." << endl;

        kullaniciKaydet(taksiler, toplamTaksi); // Dosyaya kaydet
    } else {
        cout << "Taksi bulunamadi." << endl;
    }
}

void taksiSil(Taksi taksiler[], int& toplamTaksi) {
    string plaka;
    cout << "Silinecek taksi plakasini giriniz: ";
    cin >> plaka;

    int index = taksiAra(taksiler, toplamTaksi, plaka);

    if (index != -1) {
        for (int i = index; i < toplamTaksi - 1; i++) {
            taksiler[i] = taksiler[i + 1];
        }
        toplamTaksi--;
        cout << "Taksi silindi." << endl;

        kullaniciKaydet(taksiler, toplamTaksi); // Dosyaya kaydet
    } else {
        cout << "Taksi bulunamadi." << endl;
    }
}

void taksiListele(Taksi taksiler[], int toplamTaksi) {
    cout << "Taksi Listesi:" << endl;
    for (int i = 0; i < toplamTaksi; i++) {
        cout << "Plaka: " << taksiler[i].plaka << ", Model: " << taksiler[i].model
             << ", Surucu Adi: " << taksiler[i].surucuAdi
             << ", Durumu: " << (taksiler[i].bos ? "Bos" : "Dolu") << endl;
    }
}

void taksiKayit(Taksi taksiler[], int& toplamTaksi) {
    if (toplamTaksi < MAX_TAKSI) {
        cout << "Taksi plakasini giriniz: ";
        cin >> taksiler[toplamTaksi].plaka;
        cout << "Taksi modelini giriniz: ";
        cin >> taksiler[toplamTaksi].model;
        cout << "Surucu adini giriniz: ";
        cin >> taksiler[toplamTaksi].surucuAdi;
        taksiler[toplamTaksi].bos = true;

        toplamTaksi++;
        cout << "Taksi kaydi basarili." << endl;

        kullaniciKaydet(taksiler, toplamTaksi); // Dosyaya kaydet
    } else {
        cout << "Daha fazla taksi eklenemez. Kapasite doldu." << endl;
    }
}

int main() {
    Taksi taksiler[MAX_TAKSI];
    int toplamTaksi = 0;

    kullaniciOku(taksiler, toplamTaksi); // Dosyadan oku

    int secim;
    do {
        cout << "\n***** TAKSI DURAGI OTOMASYONU *****" << endl;
        cout << "1-Taksi Kaydi\n2-Taksi Ara\n3-Taksi Guncelle\n4-Taksi Sil\n5-Taksi Listele\n6-Cikis\n";
        cout << "Seciminizi yapiniz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                taksiKayit(taksiler, toplamTaksi);
                break;
            case 2: {
                string plaka;
                cout << "Aranacak taksi plakasini giriniz: ";
                cin >> plaka;
                int index = taksiAra(taksiler, toplamTaksi, plaka);
                if (index != -1) {
                    cout << "Taksi bulundu. Surucu Adi: " << taksiler[index].surucuAdi << endl;
                } else {
                    cout << "Taksi bulunamadi." << endl;
                }
                break;
            }
            case 3:
                taksiGuncelle(taksiler, toplamTaksi);
                break;
            case 4:
                taksiSil(taksiler, toplamTaksi);
                break;
            case 5:
                taksiListele(taksiler, toplamTaksi);
                break;
            case 6:
                cout << "Programdan cikis yapiliyor." << endl;
                break;
            default:
                cout << "Gecersiz secim. Tekrar deneyiniz." << endl;
        }

    } while (secim != 6);

    return 0;
}

