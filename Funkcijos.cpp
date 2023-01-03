#include "Funkcijos.h"
#include "Timer.h"


void failai(vector<Studentas>& A, int& kiek) {
    ofstream fout, fout2;
    Timer t;
    double temp, laik = 0;


    srand((unsigned int)time(0));
    for (int i = 0; i < 4; i++) {
        kiek = 1000;
        for (int j = 0; j < i; j++) {
            kiek = kiek * 10;
        }
        studentai(A, kiek);
        fout.open(to_string(kiek) + ".txt");

        cout << "\n" << kiek << " studentu irasu sugeneravimo laikas: " << t.elapsed() << endl;
        laik = t.elapsed();
        t.reset();

        int ilgvardas = 0, ilgpavarde = 0;
        for (int x = 1; x < kiek; x++) {
            if (A[x].vardas_.length() > A[x - 1].vardas_.length() && A[x].vardas_.length() > ilgvardas) {
                ilgvardas = A[x].vardas_.length();
            }
            else if (A[x - 1].vardas_.length() > ilgvardas) {
                ilgvardas = A[x - 1].vardas_.length();
            }

            if (A[x].pavarde_.length() > A[x - 1].pavarde_.length() && A[x].pavarde_.length() > ilgpavarde) {
                ilgpavarde = A[x].pavarde_.length();
            }
            else if (A[x - 1].pavarde_.length() > ilgpavarde) {
                ilgpavarde = A[x - 1].pavarde_.length();
            }
        }

        if (kiek == 1) {
            ilgvardas = A[0].vardas_.length();
            ilgpavarde = A[0].pavarde_.length();
        }

        fout << left << setw(ilgvardas + 5) << "Vardas" << left << setw(ilgpavarde + 5) << "Pavarde" << left << setw(5) << "ND1" << left << setw(5) << "ND2" << left << setw(5) << "ND3" << left << setw(5) << "ND4" << left << setw(5) << "ND5" << left << setw(5) << "EGZ" << endl;
        fout << "\n";
        for (int x = 0; x < kiek; x++) {
            temp = avg(A[x].paz_, A[x].n_);
            A[x].vidurkis_ = vidurkis(temp, A[x].egz_);
            fout << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_;
            for (int j = 0; j < A[x].n_; j++) {
                fout << left << setw(5) << A[x].paz_[j];
            }
            fout << left << setw(5) << A[x].egz_ << endl;
        }
        fout.close();

        cout << kiek << " studentu surasymo i faila laikas: " << t.elapsed() << endl;
        laik += t.elapsed();
        t.reset();

        sort(A.begin(), A.end(), compare);

        cout << kiek << " studentu surusiavimo laikas: " << t.elapsed() << endl;
        laik += t.elapsed();
        t.reset();

        fout.open(to_string(kiek) + "nevykeliai.txt");
        fout << left << setw(ilgvardas + 5) << "Vardas" << left << setw(ilgpavarde + 5) << "Pavarde" << left << setw(15) << "Galutinis(Vid.)" << endl;
        fout << "\n";
        fout2.open(to_string(kiek) + "protinguoliai.txt");
        fout2 << left << setw(ilgvardas + 5) << "Vardas" << left << setw(ilgpavarde + 5) << "Pavarde" << left << setw(15) << "Galutinis(Vid.)" << endl;
        fout2 << "\n";
        for (int x = 0; x < kiek; x++) {
            if (A[x].vidurkis_ < 5 && A[x].vidurkis_ > 0) {
                fout << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_ << left << setw(18) << fixed << setprecision(2) << A[x].vidurkis_ << endl;
            }
            else if (A[x].vidurkis_ >= 5){
                fout2 << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_ << left << setw(18) << fixed << setprecision(2) << A[x].vidurkis_ << endl;
            }
        }
        fout.close();
        fout2.close();

        cout << kiek << " studentu padalinimo i dvi grupes ir surasymo i failus laikas: " << t.elapsed() << endl;
        laik += t.elapsed();
        t.reset();
        cout << "\nDarbo su " << kiek << " irasu testo laikas: " << laik << endl;

    }
}

void duomenys_vector(string filename, vector<Studentas>& A, int& kiek) {
    try {
        std::ifstream fin(filename);
        if (!fin.fail()) {
            int sk;
            double temp2;
            string line;
            string temp, pirmaEil;
            int kiekNd = -3;
            std::getline(fin >> std::ws, pirmaEil);
            stringstream iss(pirmaEil);
            while (iss >> temp)
            {
                kiekNd++;
            }
            while (std::getline(fin >> std::ws, line)) {
                Studentas s;
                stringstream iss(line);
                iss >> s.vardas_;
                iss >> s.pavarde_;
                for (int i = 0; i < kiekNd; i++) {
                    iss >> sk;
                    s.paz_.resize(s.paz_.size() + 1);
                }
                iss >> sk;
                s.egz_ = sk;
                temp2 = avg(s.paz_, kiekNd);
                s.vidurkis_ = vidurkis(temp2, s.egz_);
                A.resize(A.size() + 1);
            }
        }
        else {
            throw std::runtime_error(filename);
        }
        kiek = A.size();
    }
    catch (std::exception& e) {
        cout << "\nIvyko problema nuskaitant faila: " << e.what() << "\n";
        std::exit(0);
    }
}

void duomenys_list(string filename, list<Studentas>& A, int& kiek) {
    try {
        std::ifstream fin(filename);
        if (!fin.fail()) {
            int sk;
            double temp2;
            string line;
            string temp, pirmaEil;
            int kiekNd = -3;
            std::getline(fin >> std::ws, pirmaEil);
            stringstream iss(pirmaEil);
            while (iss >> temp)
            {
                kiekNd++;
            }
            while (std::getline(fin >> std::ws, line)) {
                Studentas s;
                stringstream iss(line);
                iss >> s.vardas_;
                iss >> s.pavarde_;
                for (int i = 0; i < kiekNd; i++) {
                    iss >> sk;
                    s.paz_.resize(s.paz_.size() + 1);
                }
                iss >> sk;
                s.egz_ = sk;
                temp2 = avg(s.paz_, kiekNd);
                s.vidurkis_ = vidurkis(temp2, s.egz_);
                A.resize(A.size() + 1 );
            }
        }
        else {
            throw std::runtime_error(filename);
        }
        kiek = A.size();
    }
    catch (std::exception& e) {
        cout << "Ivyko problema nuskaitant faila: " << e.what() << "\n";
        std::exit(0);
    }
}

void dvigrupes_vector(vector<Studentas>& A, vector<Studentas>& nevykeliai, vector<Studentas>& protinguoliai) {
    for (auto& s : A) {
        if (s.vidurkis_ < 5.00) nevykeliai.resize(nevykeliai.size() + 1);
        else protinguoliai.resize(protinguoliai.size() + 1); 
    }
    A.clear();
}

void dvigrupes_list(list<Studentas>& A, list<Studentas>& nevykeliai, list<Studentas>& protinguoliai) {
    for (auto& s : A) {
        if (s.vidurkis_ < 5.00) nevykeliai.resize(nevykeliai.size() + 1);
        else protinguoliai.resize(protinguoliai.size() + 1);
    }
    A.clear();
}

void vienagrupe_vector(vector<Studentas>& A, vector<Studentas>& nevykeliai) {
    auto x = A.begin();
    while (x != A.end()) {
        if ((*x).vidurkis_ < 5.00) {
            nevykeliai.push_back(*x);
            x++;
        }
        else {
            break;
        }
    }
    A.erase(A.begin(), x);
}

void vienagrupe_list(list<Studentas>& A, list<Studentas>& nevykeliai) {
    auto x = A.begin();
    while (x != A.end()) {
        if ((*x).vidurkis_ < 5.00) {
            nevykeliai.push_back(*x);
            x++;
        }
        else {
            break;
        }
    }
    A.erase(A.begin(), x);
}

void optimizacija(vector<Studentas>& A, vector <Studentas>& nevykeliai) {
    stable_partition(A.begin(), A.end(), [](const Studentas& s) { return s.vidurkis_ < 5.00; });
    auto x = find_if(A.begin(), A.end(), [](const Studentas& s) { return s.vidurkis_ >= 5.00; });
    copy(A.begin(), x, back_inserter(nevykeliai));
    A.erase(A.begin(), x);
}

void optimizacija(list<Studentas>& A, list <Studentas>& nevykeliai) {
    stable_partition(A.begin(), A.end(), [](const Studentas& s) { return s.vidurkis_ < 5.00; });
    auto x = find_if(A.begin(), A.end(), [](const Studentas& s) { return s.vidurkis_ >= 5.00; });
    copy(A.begin(), x, back_inserter(nevykeliai));
    A.erase(A.begin(), x);
}

void printToFile(string filename, vector<Studentas>& A, int ndSkaicius) {
    stringstream buffer;
    ofstream out(filename);
    buffer << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << "Galutinis(Vid.)" << "\n";
    for (int i = 0; i < A.size(); i++) {
        buffer << left << setw(15) << A[i].vardas_ << setw(15) << A[i].pavarde_ << fixed
            << setprecision(2) << A[i].vidurkis_ << "\n";
    }
    out << buffer.str();
    buffer.clear();
    out.close();
}


bool compare(Studentas a, Studentas b) {
    return a.vidurkis_ < b.vidurkis_;
}


void isvedimas(vector<Studentas> A, int kiek) {

    int ilgvardas = 0, ilgpavarde = 0;
    for (int x = 1; x < kiek; x++) {
        if (A[x].vardas_.length() > A[x - 1].vardas_.length() && A[x].vardas_.length() > ilgvardas) {
            ilgvardas = A[x].vardas_.length();
        }
        else if (A[x - 1].vardas_.length() > ilgvardas) {
            ilgvardas = A[x - 1].vardas_.length();
        }

        if (A[x].pavarde_.length() > A[x - 1].pavarde_.length() && A[x].pavarde_.length() > ilgpavarde) {
            ilgpavarde = A[x].pavarde_.length();
        }
        else if (A[x - 1].pavarde_.length() > ilgpavarde) {
            ilgpavarde = A[x - 1].pavarde_.length();
        }
    }

    if (kiek == 1) {
        ilgvardas = A[0].vardas_.length();
        ilgpavarde = A[0].pavarde_.length();
    }

    cout << "\n\n" << left << setw(ilgvardas + 5) << "Vardas" << left << setw(ilgpavarde + 5) << "Pavarde" << left << setw(15) << "Galutinis(Vid.)" << " / " << left << setw(15) << "Galutinis(Med.)" << endl;
    cout << setfill('-') << setw(ilgvardas + ilgpavarde + 43) << '-' << endl;
    for (int x = 0; x < kiek; x++) {
        if (A[x].mediana_ == 0) {
            cout << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_ << left << setw(18) << fixed << setprecision(2) << A[x].vidurkis_ << left << setw(15) << fixed << setprecision(2) << " - " << endl;
        }
        else if (A[x].vidurkis_ == 0) {
            cout << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_ << left << setw(18) << fixed << setprecision(2) << " - " << left << setw(15) << fixed << setprecision(2) << A[x].mediana_ << endl;
        }
        else
            cout << setfill(' ') << left << setw(ilgvardas + 5) << A[x].vardas_ << left << setw(ilgpavarde + 5) << A[x].pavarde_ << left << setw(18) << fixed << setprecision(2) << A[x].vidurkis_ << left << setw(15) << fixed << setprecision(2) << A[x].mediana_ << endl;

    }
}

void testavimas(vector<Studentas> A, list<Studentas> B, int kiek) {
    Timer t;
    double laik1 = 0, laik2 = 0;
    srand(time(NULL));

    string filename;
    string s;
    int dydziai[5] = { 1000, 10000, 100000, 1000000, 10000000};

    vector<Studentas> protinguoliai, nevykeliai, A2, A3;
    list<Studentas> protinguoliai2, nevykeliai2, B2;


    printf("%-47s %-20s %-0s \n", "", "Vector laikas (s.)", "List laikas (s.)");
    cout << string(87, '-') << "\n";
    for (int i = 0; i < 4; i++) {
        s = std::to_string(dydziai[i]);
        filename = s + ".txt";

        t.reset();
        duomenys_vector(filename, A, kiek);
        laik1 = t.elapsed();

        t.reset();
        duomenys_list(filename, B, kiek);
        laik2 = t.elapsed();

        A2 = A;
        A3 = A;
        B2 = B;


        printf("%-47s %-20.8lf %-0lf\n", (s + " studentu failo nuskaitymas").c_str(), laik1, laik2);

        t.reset();
        sort(A.begin(), A.end(), compare);
        dvigrupes_vector(A, nevykeliai, protinguoliai);
        laik1 = t.elapsed();
        nevykeliai.clear();

        t.reset();
        B.sort(compare);
        dvigrupes_list(B, nevykeliai2, protinguoliai2);
        laik2 = t.elapsed();
        nevykeliai.clear();
         
        printf("%-47s %-20.8lf %-20.8lf\n", (s + " studentu failo rusiavimas i kategorijas").c_str(), laik1, laik2);

        t.reset();
        sort(A2.begin(), A2.end(), compare);
        vienagrupe_vector(A2, nevykeliai);
        laik1 = t.elapsed();
        nevykeliai.clear();

        t.reset();
        B2.sort(compare);
        vienagrupe_list(B2, nevykeliai2);
        laik2 = t.elapsed();
        nevykeliai.clear();

        printf("%-47s %-20.8lf %-20.8lf\n", (s + " studentu dalinimas su vienu konteineriu").c_str(), laik1, laik2);

        t.reset();
        optimizacija(A3, nevykeliai);
        laik1 = t.elapsed();
        nevykeliai.clear();
        printf("%-47s %-20.8lf\n", (s + " irasu optimizuotas dalijimas i grupes").c_str(), laik1);

        cout << string(87, '-') << "\n";
    }

}
