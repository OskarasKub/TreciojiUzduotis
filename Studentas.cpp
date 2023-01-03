#include "funkcijos.h"

double avg(vector<int>& arr, int n) {
    if (n > 0) {
        return std::accumulate(arr.begin(), arr.end(), 0.0) / (double)n;
    }
    return 0;
}

double vidurkis(double temp, double egz) {
    return 0.4 * temp + 0.6 * (double)egz;
}

void mediana(vector<Studentas>& A, int x) {

    int t;
    int p = A[x].n_;
    A[x].paz_.push_back(1);

    for (int i = p; i > 0; i--) {
        A[x].paz_[i] = A[x].paz_[i - 1];
    }

    A[x].paz_[0] = A[x].egz_;
    p++;

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p - i - 1; j++) {
            if (A[x].paz_[j] < A[x].paz_[j + 1]) {
                t = A[x].paz_[j];
                A[x].paz_[j] = A[x].paz_[j + 1];
                A[x].paz_[j + 1] = t;
            }
        }
    }

    if (p == 0) {
        A[x].mediana_ = A[x].paz_[p];
    }
    else if (p % 2 == 0) {
        A[x].mediana_ = (A[x].paz_[p / 2] + A[x].paz_[p / 2 - 1]) / 2.0;
    }
    else {
        A[x].mediana_ = A[x].paz_[p / 2];
    }
}

void sugeneravimas(vector<Studentas>& A, int x) {
    srand((unsigned int)time(0));

    int rPaz = rand() % 10 + 1;
    cout << "\nSugeneruotas egzamino pazymys: " << rPaz << endl;
    A[x].egz_ = rPaz;

    int rKiek = rand() % 15 + 1;
    cout << "\nSugeneruotas namu darbu pazymiu kiekis: " << rKiek << endl;
    A[x].n_ = rKiek;

    for (int i = 0; i < A[x].n_; i++) {
        A[x].paz_.push_back(1);
        int rPaz = rand() % 10 + 1;
        cout << "Sugeneruotas " << i + 1 << "-asis pazymys: " << rPaz << endl;
        A[x].paz_[i] = rPaz;
        A[x].sum_ += rPaz;
    }
}

void ivedimas(vector<Studentas>& A, int& kiek) {

    cout << "\nIveskite studentu kieki: "; cin >> kiek;
    while (cin.fail() || kiek < 1) {
        cout << "Studentu kiekis turi buti SKAICIUS didesnis uz nuli!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Iveskite studentu kieki: "; cin >> kiek;
        continue;
    }

    for (int x = 0; x < kiek; x++) {

        A.push_back(Studentas());

        cout << "\n" << x + 1 << "-asis studentas." << endl;
        cout << "Iveskite studento varda: "; cin >> A[x].vardas_;
        cout << "Iveskite studento pavarde: "; cin >> A[x].pavarde_;

        string gen; //Ar ives pazymius pats ar juos sugeneruos
        cout << "\nAr norite patys ivesti studento pazymius? (T-suvesti, N-sugeneruoti atsitiktinai): "; cin >> gen;
        while (gen != "T" && gen != "t" && gen != "N" && gen != "n") {
            cout << "Kazka ne taip ivedete!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Iveskite T, jei norite patys ivesti studento pazymius arba N, jei norite, kad jie butu sugeneruoti atsitiktinai: "; cin >> gen;
            continue;
        }

        if (gen == "T" || gen == "t") {
            cout << "\nIveskite egzamino pazymi: "; cin >> A[x].egz_;
            while (cin.fail() || A[x].egz_ < 1 || A[x].egz_ > 10) {
                cout << "Egzamino pazymys turi buti skaicius nuo 1 iki 10!" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Iveskite egzamino pazymi: "; cin >> A[x].egz_;
                continue;
            }

            string zin; //Ar namu darbu skaicius zinomas ar ne
            cout << "\nAr zinote namu darbu pazymiu skaiciu? (T-taip, N-ne): "; cin >> zin;
            while (zin != "T" && zin != "t" && zin != "N" && zin != "n") {
                cout << "Kazka ne taip ivedete!" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Iveskite T, jei zinote namu darbu skaiciu arba N, jei nezinote: "; cin >> zin;
                continue;
            }

            if (zin == "T" || zin == "t") {
                cout << "\nKiek turi namu darbu pazymiu?: "; cin >> A[x].n_;
                while (cin.fail() || A[x].n_ < 0) {
                    cout << "Pazymiu kiekis turi buti teigiamas SKAICIUS!" << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Kiek turi namu darbu pazymiu?: "; cin >> A[x].n_;
                    continue;
                }

                A[x].paz_.push_back(A[x].n_);

                for (int i = 0; i < A[x].n_; i++) {
                    cout << "Iveskite " << i + 1 << "-aji pazymi: ";
                    A[x].paz_.push_back(1);
                    cin >> A[x].paz_[i];
                    while (cin.fail() || A[x].paz_[i] < 1 || A[x].paz_[i] > 10) {
                        cout << "Pazymys turi buti SKAICIUS nuo 1 iki 10!" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Iveskite " << i + 1 << "-aji pazymi: "; cin >> A[x].paz_[i];
                        continue;
                    }
                    A[x].sum_ += A[x].paz_[i];
                }
            }
            else {
                int i = 0;
                A[x].paz_.push_back(1);
                cout << "\nVeskite namu darbu pazymius. Jei pazymiu nebera iveskite 0." << endl;
                while (A[x].paz_[i] != 0) {
                    cout << "Iveskite " << i + 1 << "-aji namu darbu pazymi: ";
                    cin >> A[x].paz_[i];
                    while (cin.fail() || A[x].paz_[i] < 0 || A[x].paz_[i] > 10) {
                        cout << "Pazymys turi buti SKAICIUS nuo 1 iki 10!" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Iveskite " << i + 1 << "-aji namu darbu pazymi: "; cin >> A[x].paz_[i];
                        continue;
                    }
                    if (A[x].paz_[i] != 0) {
                        A[x].sum_ += A[x].paz_[i];
                        i++;
                        A[x].n_++;
                        A[x].paz_.push_back(1);
                    }
                }
            }
        }
        else {
            sugeneravimas(A, x);
        }

        string pas; //Ar pasirinks vidurki ar mediana
        cout << "\nJei norite pazymiu vidurkio spauskite ""V"", jei norite medianos spauskite ""M"": "; cin >> pas;
        while (pas != "V" && pas != "v" && pas != "M" && pas != "m") {
            cout << "Kazka ne taip ivedete!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Iveskite V, jei norite, kad butu apskaiciuotas vidurkis arba M, jei norite medianos: "; cin >> pas;
            continue;
        }

        if (pas == "V" || pas == "v") {
            A[x].mediana_ = 0;
            double temp;
            temp = avg(A[x].paz_, A[x].n_);
            A[x].vidurkis_ = vidurkis(temp, A[x].egz_);
        }
        else {
            A[x].vidurkis_ = 0;
            mediana(A, x);
        }
    }
}

unsigned int kiekPazymiu(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

void nuskaitymas(vector<Studentas>& A, int& kiek) {

    using std::ifstream;

    string zodziai;
    ifstream fin;
    double temp;
    kiek = 0;

    try {
        fin.open("kursiokai.txt");
        if (!fin.is_open()) {
            throw 0;
        }

        getline(fin >> std::ws, zodziai);
        int n = kiekPazymiu(zodziai) - 3;

        A.push_back(Studentas());
        A[kiek].paz_.push_back(n);

        while (!fin.eof()) {
            A.push_back(Studentas());
            A[kiek].n_ = n;
            fin >> A[kiek].vardas_;
            fin >> A[kiek].pavarde_;

            for (int i = 0; i < n; i++) {
                A[kiek].paz_.push_back(1);
                fin >> A[kiek].paz_[i];
                A[kiek].sum_ += A[kiek].paz_[i];
            }
            fin >> A[kiek].egz_;
            kiek++;
        }

        fin.close();

        for (int x = 0; x < kiek; x++) {
            temp = avg(A[x].paz_, A[x].n_);
            A[x].vidurkis_ = vidurkis(temp, A[x].egz_);
            mediana(A, x);
        }
    }
    catch (...) {
        cout << "\nToks failas neegzistuoja!";
    }
}

void pazymiai(vector<Studentas>& A, int x) {

    A[x].sum_ = 0;

    int rPaz = rand() % 10 + 1;
    A[x].egz_ = rPaz;

    int rKiek = 5;
    A[x].n_ = rKiek;

    for (int i = 0; i < A[x].n_; i++) {
        A[x].paz_.push_back(1);
        int rPaz = rand() % 10 + 1;
        A[x].paz_[i] = rPaz;
        A[x].sum_ += rPaz;
    }
}

void studentai(vector<Studentas>& A, int kiek) {

    A.push_back(Studentas());

    for (int x = 0; x < kiek; x++) {

        A.push_back(Studentas());

        A[x].vardas_ = "Vardas" + to_string(x + 1);
        A[x].pavarde_ = "Pavarde" + to_string(x + 1);

        pazymiai(A, x);
    }
}

//bool compare(Studentas a, Studentas b) {
//    return a.getVidurkis() < b.getVidurkis();
//}