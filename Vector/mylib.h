#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cctype>
#include <ios>
#include <chrono>

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
using std::setw;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::left;
using std::to_string;

class Zmogus {
protected:
    string Vardas, Pavarde;

public:
    Zmogus(const string& vardas, const string& pavarde) :
        Vardas(vardas), Pavarde(pavarde) {}

    virtual ~Zmogus() {}

    //Geteriai
    virtual inline string vardas() const { return Vardas; }
    virtual inline string pavarde() const { return Pavarde; }

    //Setteriai
    virtual void setvardas(const string& v) { Vardas = v; }
    virtual void setpavarde(const string& p) { Pavarde = p; }
    virtual void informacija() const = 0;
};

class Studentas : public Zmogus {
private:
    // Realizacija
    vector<int> Pazymiai;
    int Egzaminas;
    float Vidurkis;
    double Mediana;

public:
    // Interfeisas
    Studentas() : Zmogus("", ""), Egzaminas(0), Vidurkis(0), Mediana(0) {}
    Studentas(const string& vardas, const string& pavarde, const vector<int>& pazymiai,
              int egzaminas, float vidurkis, double mediana) :
        Zmogus(vardas, pavarde), Pazymiai(pazymiai), Egzaminas(egzaminas), Vidurkis(vidurkis), Mediana(mediana) {}
     void informacija() const override {};
    ~Studentas() { Pazymiai.clear(); }

    // Copy konstruktorius
    Studentas(const Studentas& other) : Zmogus(other.Vardas, other.Pavarde) {
        Pazymiai = other.Pazymiai;
        Egzaminas = other.Egzaminas;
        Vidurkis = other.Vidurkis;
        Mediana = other.Mediana;
    }

    // Copy Assignment operatorius
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            Pazymiai = other.Pazymiai;
            Egzaminas = other.Egzaminas;
            Vidurkis = other.Vidurkis;
            Mediana = other.Mediana;
        }
        return *this;
    }
    //Ivedimo operatorius
    friend std::istream& operator>>(std::istream& is, Studentas& student);

    //Isvedimo operatorius
    friend std::ostream& operator<<(std::ostream& os, Studentas& student);

    // Get'eriai
    inline string vardas() const { return Vardas; }
    inline string pavarde() const { return Pavarde; }
    inline float vidurkis() const { return Vidurkis; }
    inline double mediana() const { return Mediana; }
    vector<int> pazymiai() const { return Pazymiai; }
    int egzaminas() const { return Egzaminas; }

    // Set'eriai
    void setvardas(const string& v) { Vardas = v; }
    void setpavarde(const string& p) { Pavarde = p; }
    void setpazymiai(const vector<int>& p) { Pazymiai = p; }
    void setegzaminas(int e) { Egzaminas = e; }
    void setvidurkis(float v) { Vidurkis = v; }
    void setmediana(double m) { Mediana = m; }

    void sortPazymiai() {
        sort(Pazymiai.begin(), Pazymiai.end());
    }
    void addPazymys(int pazymys) {
        Pazymiai.push_back(pazymys);
    }

    vector<int> getPazymiai() const {
        return Pazymiai;
    }
};

bool Rusiavimas(const Studentas& a, const Studentas& b);
bool compareByName(const Studentas& a, const Studentas& b);
bool compareBySurname(const Studentas& a, const Studentas& b);
bool compareByGrade(const Studentas& a, const Studentas& b);
void Vidurkis(Studentas& Laikinas);
void Mediana(Studentas& Laikinas);
void FailoSkaitymas(vector<Studentas>& Grupe);
void RezultatoFailas(ofstream& outputFile);
void EgzaminoPazymis(Studentas& Laikinas);
void PazymiuGeneravimas(Studentas& Laikinas);
void PazymiuIvedimas(Studentas& Laikinas);
void StudentuInfo(Studentas& Laikinas, vector<Studentas>& Grupe);
void SukurtiStudentoFaila(int studentCount, int gradeCount, const string& filename);
void KategorizuotiStudentus(vector<Studentas>& Grupe, vector<Studentas>& BelowFive, vector<Studentas>& AboveFive);
void KategorijuFailai(const vector<Studentas>& Grupe, const vector<Studentas>& BelowFive, const vector<Studentas>& AboveFive);
#endif // MYLIB_H_INCLUDED
