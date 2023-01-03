#include "mylib.h"

class Zmogus {
protected:
    string vardas_; //Vardas
    string pavarde_; //Pavarde
public:
    virtual void setVardas(string vardas) = 0;
    virtual void setPavarde(string pavarde) = 0;
    inline string getVardas() const { return vardas_; } // get'eriai, inline
    inline string getPavarde() const { return pavarde_; } // get'eriai, inline
    
    Zmogus()
    {
        vardas_ = "";
        pavarde_ = "";
    }

};


class Studentas : public Zmogus {
public:
    string vardas_; //Studento vardas
    string pavarde_; //Studento pavarde
    int n_; //Namu darbu kiekis
    vector<int> paz_; //Namu darbu pazymiai
    int egz_; //Egzamino pazymys
    double vidurkis_; //Pazymiu vidurkis
    double mediana_; //Pazymiu mediana
    int sum_; //Pazymiu suma


    Studentas() : egz_(0) { }  // default konstruktorius
    Studentas(std::istream& is);
    inline string getVardas() const { return vardas_; } // get'eriai, inline
    void setVardas(string vardas) { vardas_ = vardas; }
    inline string getPavarde() const { return pavarde_; } // get'eriai, inline
    void setPavarde(string pavarde) { pavarde_ = pavarde; }
    double getPaz(int i) const { return paz_.at(i); }
    void setPaz(int nd, int index) { paz_[index] = nd; }
    void addPaz(int nd) {
        paz_.reserve(paz_.size() + 1);
        paz_.push_back(nd);
    }
    void clearPaz() { paz_.clear(); }
    inline int getPazSize() { return paz_.size(); }
    void sortPaz() { sort(paz_.begin(), paz_.end()); }

    inline int getEgz() const { return egz_; }
    void setEgz(int egz) { egz_ = egz; }

    inline double getVidurkis() const { return vidurkis_; }
    void setVidurkis(double vidurkis) { vidurkis_ = vidurkis; }

    inline double getMediana() const { return mediana_; }
    void setMediana(double mediana) { mediana_ = mediana; }

    // I. Destructor
    ~Studentas() {
        paz_.clear();
    }

    // II. Copy constructor
    Studentas(const Studentas& other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        n_ = other.n_;
        paz_ = other.paz_;
        egz_ = other.egz_;
        vidurkis_ = other.vidurkis_;
        mediana_ = other.mediana_;
        sum_ = other.sum_;
    }

    // III. Copy assignment operator
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            n_ = other.n_;
            paz_ = other.paz_;
            egz_ = other.egz_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
            sum_ = other.sum_;
        }
        return *this;
    }
};