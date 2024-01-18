#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <limits>

using namespace std;

class Studentas {
private:
    static vector<Studentas> visiStudentai;
    string vardas;
    string pavarde;
    vector<double> nd_rezultatai;
    double galutinis_vidurkis;

public:
    Studentas(const string& vardas, const string& pavarde)
        : vardas(vardas), pavarde(pavarde), galutinis_vidurkis(0.0) {}

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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Blogas įvedimas. Prašome įvesti skaičių: ";
                } else {
                    break;
                }
            }
        }

        skaiciuotiGalutini();
    }

    void isvestiDuomenis() const {
        cout << left << setw(12) << "Vardas" << setw(12) << "Pavardė" << setw(18) << "Galutinis (Vid.)" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << left << setw(12) << vardas << setw(12) << pavarde << fixed << setprecision(2) << setw(18);
        cout << galutinis_vidurkis << endl;
    }

    void skaiciuotiGalutini() {
        if (!nd_rezultatai.empty()) {
            galutinis_vidurkis = accumulate(nd_rezultatai.begin(), nd_rezultatai.end(), 0.0) / nd_rezultatai.size();
        }
    }

    static void priskirtiStudentus(const vector<Studentas>& studentai) {
        visiStudentai = studentai;
    }

    static void isvestiVisusStudentus() {
        cout << left << setw(12) << "Vardas" << setw(12) << "Pavardė" << setw(18) << "Galutinis (Vid.)" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        for (const Studentas& studentas : visiStudentai) {
            cout << left << setw(12) << studentas.vardas << setw(12) << studentas.pavarde << fixed << setprecision(2) << setw(18);
            cout << studentas.galutinis_vidurkis << endl;
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


    Studentas::isvestiVisusStudentus();

    return 0;
}
