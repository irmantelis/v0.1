#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
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
        : vardas(vardas), pavarde(pavarde), galutinis_vidurkis(0.0), galutinis_mediana(0.0) {}

    void ivestiDuomenis() {
        cout << "Įveskite studento vardą: ";
        cin >> vardas;

        cout << "Įveskite studento pavardę: ";
        cin >> pavarde;

        cout << "Įveskite namų darbų skaičių: ";
        int nd_sk;
        cin >> nd_sk;

        nd_rezultatai.resize(nd_sk);

        for (int i = 0; i < nd_sk; ++i) {
            cout << "Įveskite " << i + 1 << "-ojo namų darbo rezultatą: ";
            while (true) {
                cin >> nd_rezultatai[i];
                if (cin.fail()) {
                    cin.clear();

                }
                else {
                    break;
                }
            }
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
};

vector<Studentas> Studentas::visiStudentai;

int main() {
    vector<Studentas> studentuSarasas;
    char testi = 't';

    while (testi == 't' || testi == 'T') {
        Studentas naujasStudentas("", "");
        naujasStudentas.ivestiDuomenis();

        studentuSarasas.push_back(naujasStudentas);

        cout << "Ar norite įvesti dar vieną studentą (t/n)? ";
        cin >> testi;
    }

    Studentas::priskirtiStudentus(studentuSarasas);

    bool skaiciuotiMediana;
    cout << "Skaiciuoti galutinio balo mediana ar vidurki? (1 - mediana, 0 - vidurkis): ";
    cin >> skaiciuotiMediana;

    Studentas::isvestiVisusStudentus(skaiciuotiMediana);

    return 0;
}
