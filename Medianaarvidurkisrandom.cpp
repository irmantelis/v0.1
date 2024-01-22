#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <random>
#include <algorithm>

using namespace std;

class Studentas {
private:
    static vector<Studentas> visiStudentai;
    string vardas;
    string pavarde;
    vector<double> nd_rezultatai;
    double galutinis_vidurkis;
    double galutinis_mediana;

public:
    Studentas(const string& vardas, const string& pavarde)
        : vardas(vardas), pavarde(pavarde), galutinis_vidurkis(0.0), galutinis_mediana(0.0) {
        ivestiBalus();
    }

    void ivestiBalus() {
        char pasirinkimas;
        cout << "Ar norite ivesti balus rankiniu budu? (t/n): ";
        cin >> pasirinkimas;

        if (pasirinkimas == 't' || pasirinkimas == 'T') {
            cout << "Iveskite namu darbu rezultatus (baigti ivedima ivedus negatyvu skaiciu): ";
            double balas;
            while (cin >> balas && balas >= 0) {
                nd_rezultatai.push_back(balas);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            generuotiBalus();
        }

        skaiciuotiGalutini();
    }

    void isvestiDuomenis(bool skaiciuotiMediana) const {
        cout << left << setw(12) << "Vardas" << setw(12) << "Pavardė" << setw(18);
        cout << (skaiciuotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << left << setw(12) << vardas << setw(12) << pavarde << fixed << setprecision(2) << setw(18);
        cout << (skaiciuotiMediana ? galutinis_mediana : galutinis_vidurkis) << endl;
    }

    static void priskirtiStudentus(const vector<Studentas>& studentai) {
        visiStudentai = studentai;
    }

    static void isvestiVisusStudentus(bool skaiciuotiMediana) {
        cout << left << setw(12) << "Vardas" << setw(12) << "Pavardė" << setw(18);
        cout << (skaiciuotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        for (const Studentas& studentas : visiStudentai) {
            cout << left << setw(12) << studentas.vardas << setw(12) << studentas.pavarde << fixed << setprecision(2) << setw(18);
            cout << (skaiciuotiMediana ? studentas.galutinis_mediana : studentas.galutinis_vidurkis) << endl;
        }
    }

private:
    void generuotiBalus() {
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(0.0, 10.0);

        for (int i = 0; i < 5; ++i) {
            nd_rezultatai.push_back(dist(mt));
        }

        double egzamino_balas = dist(mt);
        nd_rezultatai.push_back(egzamino_balas);
    }

    void skaiciuotiGalutini() {
        if (!nd_rezultatai.empty()) {
            galutinis_vidurkis = accumulate(nd_rezultatai.begin(), nd_rezultatai.end(), 0.0) / nd_rezultatai.size();

            vector<double> temp_nd = nd_rezultatai;
            sort(temp_nd.begin(), temp_nd.end());
            if (temp_nd.size() % 2 == 0) {
                double mediana1 = temp_nd[temp_nd.size() / 2 - 1];
                double mediana2 = temp_nd[temp_nd.size() / 2];
                galutinis_mediana = (mediana1 + mediana2) / 2.0;
            }
            else {
                galutinis_mediana = temp_nd[temp_nd.size() / 2];
            }
        }
    }
};

vector<Studentas> Studentas::visiStudentai;

int main() {
    vector<Studentas> studentuSarasas;

    while (true) {
        string vardas, pavarde;
        cout << "Įveskite studento vardą (arba 'pabaiga' jei norite baigti): ";
        cin >> vardas;

        if (vardas == "pabaiga") {
            break;
        }

        cout << "Įveskite studento pavardę: ";
        cin >> pavarde;

        Studentas naujasStudentas(vardas, pavarde);
        studentuSarasas.push_back(naujasStudentas);
    }

    Studentas::priskirtiStudentus(studentuSarasas);

    bool skaiciuotiMediana;
    cout << "Skaiciuoti galutinio balo medianą ar vidurkį? (1 - mediana, 0 - vidurkis): ";
    cin >> skaiciuotiMediana;

    Studentas::isvestiVisusStudentus(skaiciuotiMediana);

    return 0;
}
