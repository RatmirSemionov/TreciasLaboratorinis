#include "mylib.h"

int main() {
    //Studento klases objekto kurimas
    Studentas obj1;
    obj1.setvardas("Michael");
    obj1.setpavarde("Sanchez");
    obj1.addPazymys(5);
    obj1.addPazymys(7);
    obj1.addPazymys(9);
    obj1.addPazymys(10);
    obj1.setegzaminas(8);

    Studentas obj2 = obj1;
    Studentas obj3;
    obj3 = obj1;

    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout<<"Informacija apie obj1 tokia: "<<obj1<<endl;
    cout<<"Informacija apie obj2 tokia: "<<obj2<<endl;
    cout<<"Informacija apie obj3 tokia: "<<obj3<<endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    //Patikrinimas, ar Zmogus klases objektas gali but sukurtas
    //Zmogus zmog("Nicholas", "Cage");

    Studentas Laikinas;
    vector<Studentas> Grupe;
    char Pasirinktas;
    char Pasirinkimas2;
    string inputFileName;
    string outputFileName;
    ofstream outputFile;
    char FailoGeneravimas;
    char Padalinimas;
    //Ar norim sugeneruot faila, arba jau turim.
    cout << "Ar norite sugeneruot studentu faila arba naudot sugeneruota? (T - taip, N - ne, J - jau turim faila): ";
    cin >> FailoGeneravimas;
    if (FailoGeneravimas != 'T' && FailoGeneravimas != 'N' && FailoGeneravimas != 'J') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        exit(1);
    }
    if (FailoGeneravimas == 'J') {
        vector<Studentas> BelowFive;
        vector<Studentas> AboveFive;
        FailoSkaitymas(Grupe);
        KategorizuotiStudentus(Grupe, BelowFive, AboveFive);
        KategorijuFailai(Grupe, BelowFive, AboveFive);
    }
    if (FailoGeneravimas == 'T') {
        int studentCount;
        int gradeCount;
        string filename;
        cout << "Iveskite kiek studentu duomenis norite sugeneruoti: ";
        cin >> studentCount;
        if (cin.fail() || studentCount < 1) {
            cout << "Klaida. Netinkamas ivedimas, programa baigiasi";
            exit(1);
        }
        cout << "Iveskite kiek namu darbu pazymiu turi studentai: ";
        cin >> gradeCount;
        if (cin.fail() || gradeCount < 1) {
            cout << "Klaida. Netinkamas ivedimas, programa baigiasi";
            exit(1);
        }
        cout << "Iveskite failo pavadinima i kuri norite sugeneruoti duomenis: ";
        cin >> filename;
        SukurtiStudentoFaila(studentCount, gradeCount, filename);
        cout << "Studentu duomenis sugeneruoti i faila " << filename << endl;
        cout << "Ar norite padalinti studentus i dvi kategorijas?(Vargsiukai, Galvociai) - (T - taip, N - ne): ";
        cin >> Padalinimas;
        if (Padalinimas == 'T') {
            vector<Studentas> BelowFive;
            vector<Studentas> AboveFive;
            FailoSkaitymas(Grupe);
            KategorizuotiStudentus(Grupe, BelowFive, AboveFive);
            KategorijuFailai(Grupe, BelowFive, AboveFive);
        }
        else {
        cout << "Programa baigiasi, darbas atliktas" << endl;
        exit(1);
        }
    }
    else if (FailoGeneravimas == 'N') {
    //Kaip gausim duomenis
    cout << "Kaip norite ivesti duomenis? (M - manualiai, F - is failo): ";
    cin >> Pasirinkimas2;
    if (Pasirinkimas2 != 'M' && Pasirinkimas2 != 'F') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        return 1;
    }
    //Nuskaitymas is failo
    if (Pasirinkimas2 == 'F') {
        FailoSkaitymas(Grupe);
        RezultatoFailas(outputFile);
    //Manualus ivedimas
    } else if (Pasirinkimas2 == 'M') {
        StudentuInfo(Laikinas, Grupe);
    }

    // Studentu rusiavimas
    sort(Grupe.begin(), Grupe.end(), Rusiavimas);

    std::ostream &output = (Pasirinkimas2 == 'F') ? outputFile : cout;
    //Pasirinkimas ka apskaiciuot
    cout << "Apskaciuoti Vidurki (V) arba Mediana (M)? -> ";
    cin >> Pasirinktas;
    if (Pasirinktas != 'V' && Pasirinktas != 'M') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi" << endl;
        return 1;
    }
    output << "----------------------------------------------------------------------" << endl;
    output << setw(17) << left << "Vardas " << setw(15) << left << " Pavarde " << setw(20) << (Pasirinktas == 'V' ? " Galutinis (Vid.) " : " Galutinis (Med.) ") << "Adresas atmintyje" << endl;
    output << "----------------------------------------------------------------------" << endl;
    output << std::fixed << std::setprecision(2);
    for (auto &a : Grupe) {
        output << setw(18) << left << a.vardas() << setw(20) << left << a.pavarde() << setw(18) << (Pasirinktas == 'V' ? a.vidurkis() : a.mediana()) << &a << endl;
    }
    }
}
