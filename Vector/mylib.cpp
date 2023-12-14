#include "mylib.h"
double ElapsedTime1 = 0, ElapsedTime2 = 0, ElapsedTime3 = 0, ElapsedTime4, SortTime = 0;

std::istream& operator>>(std::istream& is, Studentas& student){
    string Vardas,Pavarde;
    cout <<"Iveskite studento varda ir pavarde: ";
    is >> Vardas >> Pavarde;
    student.setvardas(Vardas);
    student.setpavarde(Pavarde);

    char Pasirinkimas;
    cout << "Pasirinkite kaip ivesite pazymius (M - manualiai, A - automatiskai): ";
    cin >> Pasirinkimas;
    if (Pasirinkimas != 'M' && Pasirinkimas != 'A') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        exit(1);
    }

    if (Pasirinkimas == 'A') {
    char PazymiuPasirinkimas;
    int PazymiuSkaicius;
    cout << "Ar zinote, kiek pazymiu reikia sugeneruot? (T - taip, N - ne) ";
    cin >> PazymiuPasirinkimas;

    if (PazymiuPasirinkimas != 'T' && PazymiuPasirinkimas != 'N') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        exit(1);
    }

    if (PazymiuPasirinkimas == 'T') {
        cout << "Iveskite generuojamu pazymiu skaiciu: ";
        cin >> PazymiuSkaicius;
        if (cin.fail() || PazymiuSkaicius <= 0) {
            cout << "Klaida. Netinkamas ivedimas, programa baigiasi" << endl;
            exit(1);
        }
    } else if (PazymiuPasirinkimas == 'N') {
        PazymiuSkaicius = rand() % 11 + 1;
    }

    for (int j = 0; j < PazymiuSkaicius; j++) {
        int RandPazymis = rand() % 11;
        student.addPazymys(RandPazymis);
    }

    cout << "Sugeneruoti studento pazymiai: ";
    for (int pazymys : student.getPazymiai()) {
        cout << pazymys << " ";
    }
    cout << '\n';
    }
    else if (Pasirinkimas == 'M') {
        cout << "Iveskite pazymiu skaiciu (arba 'q', jei norite ivesti pazymius be apribojimu): ";
    string input;
    int PazymiuSkaicius;
    cin >> input;
    try {
        PazymiuSkaicius = std::stoi(input);
        if (PazymiuSkaicius == 0) {
            throw std::domain_error("Dalyba is nulio neapibrezta.\n");
        }
    } catch (std::invalid_argument&) {
        PazymiuSkaicius = -1;
    } catch (std::exception& e) {
        std::cerr << "Gavome isimti: " << e.what() << endl;
        exit(1);
    }

    if (cin.fail() || PazymiuSkaicius < -1) {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        exit(1);
    }

    if (PazymiuSkaicius == -1) {
        cout << "Iveskite pazymius. Baigti ivedineti pazymius galite suvede 'q'." << endl;
        int Numeris = 1;
        while (true) {
            cout << "Iveskite " << Numeris << " pazymi: ";
            cin >> input;
            int k;
            try {
                k = std::stoi(input);
                if (k < 1 || k > 10) {
                    cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
                    exit(1);
                }
            } catch (std::invalid_argument&) {
                break;
            }

            //Pridedam pazymius
            student.addPazymys(k);
            Numeris++;
        }

        if (Numeris == 1) {
            // Nebuvo pazymiu
            cout << "Dalyba is nulio neapibrezta.\n";
            exit(1);
        }

    } else {
        for (int j = 0; j < PazymiuSkaicius; j++) {
            int k;
            cout << "Iveskite " << j + 1 << " pazymi: ";
            cin >> k;
            if (cin.fail() || k < 1 || k > 10) {
                cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
                exit(1);
            }
            // Pridedam pazymius
            student.addPazymys(k);
        }
    }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Studentas& student) {
    Vidurkis(student);
    Mediana(student);
    os << setw(18) << left << student.Vardas << setw(20) << left << student.Pavarde << setw(18) << student.Vidurkis << &student;
    return os;
}




//Rusiavimo funkcija
bool Rusiavimas(const Studentas& a, const Studentas& b) {

    string strA = a.vardas();
    string strB = b.vardas();

    if(strA == strB) { // Jeigu vardai vienodi, palyginam pagal pavarde
         strA = a.pavarde();
         strB = b.pavarde();
    }

    size_t i = 0, j = 0;
    while (i < strA.size() && j < strB.size()) {
        if (isdigit(strA[i]) && isdigit(strB[j])) {
            int numA = 0, numB = 0;
            while (i < strA.size() && isdigit(strA[i])) {
                numA = numA * 10 + (strA[i] - '0');
                i++;
            }
            while (j < strB.size() && isdigit(strB[j])) {
                numB = numB * 10 + (strB[j] - '0');
                j++;
            }
            if (numA != numB)
                return numA < numB;
        }
        else {
            if (strA[i] != strB[j])
                return strA[i] < strB[j];
            i++;
            j++;
        }
    }
    return strA.size() < strB.size();
}

// Rusiavimas tik pagal varda
bool compareByName(const Studentas& a, const Studentas& b) {
    string strA = a.vardas();
    string strB = b.vardas();
    size_t i = 0, j = 0;
    while (i < strA.size() && j < strB.size()) {
        if (isdigit(strA[i]) && isdigit(strB[j])) {
            int numA = 0, numB = 0;
            while (i < strA.size() && isdigit(strA[i])) {
                numA = numA * 10 + (strA[i] - '0');
                i++;
            }
            while (j < strB.size() && isdigit(strB[j])) {
                numB = numB * 10 + (strB[j] - '0');
                j++;
            }
            if (numA != numB)
                return numA < numB;
        }
        else {
            if (strA[i] != strB[j])
                return strA[i] < strB[j];
            i++;
            j++;
        }
    }
    return strA.size() < strB.size();
}

// Rusiavimas tik pagal pavarde
bool compareBySurname(const Studentas& a, const Studentas& b) {
    string strA = a.pavarde();
    string strB = b.pavarde();
    size_t i = 0, j = 0;
    while (i < strA.size() && j < strB.size()) {
        if (isdigit(strA[i]) && isdigit(strB[j])) {
            int numA = 0, numB = 0;
            while (i < strA.size() && isdigit(strA[i])) {
                numA = numA * 10 + (strA[i] - '0');
                i++;
            }
            while (j < strB.size() && isdigit(strB[j])) {
                numB = numB * 10 + (strB[j] - '0');
                j++;
            }
            if (numA != numB)
                return numA < numB;
        }
        else {
            if (strA[i] != strB[j])
                return strA[i] < strB[j];
            i++;
            j++;
        }
    }
    return strA.size() < strB.size();
}

// Rusiavimas pagal vidurki
bool compareByGrade(const Studentas& a, const Studentas& b) {
    return a.vidurkis() < b.vidurkis();
}

//Vidurkio Skaciavimas
void Vidurkis(Studentas& Laikinas) {
    float PazymiuVidurkis = 0.0;
    for (int j = 0; j < Laikinas.pazymiai().size(); j++) {
        PazymiuVidurkis += Laikinas.pazymiai()[j];
    }
    if (!Laikinas.pazymiai().empty()) {
        PazymiuVidurkis /= Laikinas.pazymiai().size();
    }
    Laikinas.setvidurkis(0.4 * PazymiuVidurkis + 0.6 * Laikinas.egzaminas());
}
//Medianos Skaiciavimas
void Mediana(Studentas& Laikinas) {
    Laikinas.sortPazymiai();
    vector<int> pazymiai = Laikinas.pazymiai();
    int vidut = pazymiai.size() / 2;
    if (pazymiai.size() % 2 == 0) {
        Laikinas.setmediana((pazymiai[vidut - 1] + pazymiai[vidut]) / 2.0);
    } else {
        Laikinas.setmediana(pazymiai[vidut]);
    }
}
//Duomenu nuskaitymas is failo(Pavadinimus rasyt su .txt, pvz. studentai10000.txt)
void FailoSkaitymas(vector<Studentas>& Grupe) {
    string inputFileName;
    cout << "Jusu aplankale esantis teksto failas: " << endl;
    system("dir *.txt");
    cout << "Iveskite failo pavadinima: ";
    cin >> inputFileName;
    ifstream inputFile(inputFileName);

    auto start = std::chrono::high_resolution_clock::now();
    if (!inputFile.is_open()) {
        cout << "Nepavyko atidaryti faila: " << inputFileName << endl;
        exit(1);
    }

    Studentas Laikinas;
    string line;
    getline(inputFile, line); // Ignoruojam header linija
    while (getline(inputFile, line)) {
        istringstream iss(line);
        iss >> inputFileName;
        Laikinas.setvardas(inputFileName);
        iss >> inputFileName;
        Laikinas.setpavarde(inputFileName);

        vector<int> pazymiai;
        string value;
        while (iss >> value) {
            if (all_of(value.begin(), value.end(), ::isdigit)) {
                int pazymys = std::stoi(value);
                pazymiai.push_back(pazymys);
            }
        }

        if (!pazymiai.empty()) {
            Laikinas.setegzaminas(pazymiai.back());
            pazymiai.pop_back();
            Laikinas.setpazymiai(pazymiai);
        } else {
            continue;
        }

        // Skaiciavimas
        Vidurkis(Laikinas);
        Mediana(Laikinas);

        Grupe.push_back(Laikinas);
        pazymiai.clear();
    }
    inputFile.close();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = finish - start;
    ElapsedTime1 = elapsed1.count();
    cout << "Failo nuskaitymo laikas: " << elapsed1.count() << " sekundziu" << endl;
}
//Failo funkcija, kuriame bus rezultatai(Failo pavadinima rasyt su .txt, pvz. rezultatai.txt)
void RezultatoFailas(ofstream& outputFile) {
    string outputFileName;
    cout << "Iveskite rezultatu failo pavadinima: ";
    cin >> outputFileName;

    outputFile.open(outputFileName);

    if (!outputFile.is_open()) {
        cout << "Nepavyko atidaryti rezultatu faila: " << outputFileName << endl;
        exit(1);
    }
}
//Egzamino pazymio ivedimo funkcija
void EgzaminoPazymis(Studentas& Laikinas) {
    char Pasirinkimas;
    cout << "Pasirinkite kaip ivesite egzamino pazymi (M - manualiai, A - automatiskai): ";
    cin >> Pasirinkimas;

    if (Pasirinkimas != 'M' && Pasirinkimas != 'A') {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
        exit(1);
    }

    int Egzaminas;
    if (Pasirinkimas == 'A') {
        Egzaminas = rand() % 11;
        Laikinas.setegzaminas(Egzaminas);
        cout << "Sugeneruotas egzamino pazymis: " << Egzaminas << '\n';
    } else if (Pasirinkimas == 'M') {
        cout << "Iveskite egzamino pazymi: ";
        cin >> Egzaminas;
        if (cin.fail() || Egzaminas < 0 || Egzaminas > 10) {
            cout << "Klaida. Netinkamas ivedimas, programa baigiasi" << endl;
            exit(1);
        } else {
            Laikinas.setegzaminas(Egzaminas);
        }
    }
}
//Studentu skaiciu ir ivedimo budo funkcija
void StudentuInfo(Studentas& Laikinas, vector<Studentas>& Grupe) {
    int StudentuSkaicius;
    cout << "Iveskite studentu skaiciu: ";
        cin >> StudentuSkaicius;
        if (cin.fail() || StudentuSkaicius <= 0) {
            cout << "Klaida. Netinkamas ivedimas, programa baigiasi." << endl;
            exit(1);
        }

        srand(time(0));

        for (int i = 0; i < StudentuSkaicius; i++) {
            cin >> Laikinas;
            EgzaminoPazymis(Laikinas);
            // Nustatom vidurki arba mediana
            Vidurkis(Laikinas);
            Mediana(Laikinas);

            // Pridedam studenta
            Grupe.push_back(Laikinas);

            // Clearinam studentu pazymius pries pereinant prie kito studento
            Laikinas.setpazymiai({});
        }
}

void SukurtiStudentoFaila(int studentCount, int gradeCount, const string& filename) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        exit(1);
    }

    Studentas Laikinas;
    srand(time(NULL));

    file << std::left << std::setw(22) << "Vardas"
                      << std::setw(22) << "Pavarde";

    for (int i = 1; i <= gradeCount; i++)
        file << std::setw(10) << "ND" + std::to_string(i);

    file << std::setw(10) << "Egz." << "\n";

    for (int i = 0; i < studentCount; i++) {
        Laikinas.setvardas("Vardas" + std::to_string(i+1));
        Laikinas.setpavarde("Pavarde" + std::to_string(i+1));

        for (int j = 0; j < gradeCount; j++)
            Laikinas.addPazymys(rand()%11);

        Laikinas.setegzaminas(rand()%11);

        file << std::left << std::setw(22) << Laikinas.vardas()
                          << std::setw(22) << Laikinas.pavarde();

        for (int grade : Laikinas.getPazymiai())
            file << std::setw(10) << grade;

        file << std::setw(10) << Laikinas.egzaminas() << "\n";

        Laikinas.setpazymiai({});
    }

    file.close();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << "Failo kurimo laikas: " << elapsed.count() << " sekundziu" << endl;
}

void KategorizuotiStudentus(vector<Studentas>& Grupe, vector<Studentas>& BelowFive, vector<Studentas>& AboveFive) {
    int strategija;
    char option;
    cout << "Pasirinkite rusiavimo metoda: (W - varda, P - pavarde, V - vidurki, N - nerusiuot): ";
    cin >> option;
    cout << "Pasirinkite padalinimo i kategorijas strategija (1, 2 arba 3): ";
    cin >> strategija;
    if (strategija != 1 && strategija != 2 && strategija != 3) {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi" << endl;
        exit(1);
    }
    auto start1 = std::chrono::high_resolution_clock::now();
    if (strategija == 1) {
        for (auto& a : Grupe) {
            if(a.vidurkis() < 5.0){
                BelowFive.push_back(a);
            } else {
                AboveFive.push_back(a);
            }
        }
    }
    else if (strategija == 2) {
        // Atbuline eiga
        sort(Grupe.rbegin(), Grupe.rend(), [](const Studentas& a, const Studentas& b) {
            return a.vidurkis() < b.vidurkis();
        });

        // Naudojam pop istrinimui is Grupe konteinerio
        while (!Grupe.empty() && Grupe.back().vidurkis() < 5.0) {
            BelowFive.push_back(Grupe.back());
            Grupe.pop_back();
        }
    }
    else if (strategija == 3) {
        BelowFive.reserve(Grupe.size());
        AboveFive.reserve(Grupe.size());

        std::partition_copy(Grupe.begin(), Grupe.end(), std::back_inserter(BelowFive), std::back_inserter(AboveFive), [](const auto& a) {
            return a.vidurkis() < 5.0;
        });
    }
    auto finish1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = finish1 - start1;
    ElapsedTime2 = elapsed2.count();
    cout << "Studentu dalinimas i kategorijas uztruko: " << elapsed2.count() << " sekundziu" << endl;

    auto start = std::chrono::high_resolution_clock::now();
    if (strategija == 1 || strategija == 3) {
    switch (option) {
        case 'W':
            sort(BelowFive.begin(), BelowFive.end(), compareByName);
            sort(AboveFive.begin(), AboveFive.end(), compareByName);
            break;
        case 'P':
            sort(BelowFive.begin(), BelowFive.end(), compareBySurname);
            sort(AboveFive.begin(), AboveFive.end(), compareBySurname);
            break;
        case 'V':
            sort(BelowFive.begin(), BelowFive.end(), compareByGrade);
            sort(AboveFive.begin(), AboveFive.end(), compareByGrade);
            break;
        case 'N':
            break;
        default:
            cout << "Netinkamas ivedimas. Programa baigiasi." << endl;
            exit(1);
    }
    }
    else if (strategija == 2) {
        switch (option) {
        case 'W':
            sort(BelowFive.begin(), BelowFive.end(), compareByName);
            sort(Grupe.begin(), Grupe.end(), compareByName);
            break;
        case 'P':
            sort(BelowFive.begin(), BelowFive.end(), compareBySurname);
            sort(Grupe.begin(), Grupe.end(), compareBySurname);
            break;
        case 'V':
            sort(BelowFive.begin(), BelowFive.end(), compareByGrade);
            sort(Grupe.begin(), Grupe.end(), compareByGrade);
            break;
        case 'N':
            break;
        default:
            cout << "Netinkamas ivedimas. Programa baigiasi." << endl;
            exit(1);
    }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapseds = finish - start;
    SortTime = elapseds.count();
    cout << "Studentu rusiavimas pagal parametra uztruko: " << elapseds.count() << " sekundziu" << endl;
}

void KategorijuFailai(const vector<Studentas>& Grupe, const vector<Studentas>& BelowFive, const vector<Studentas>& AboveFive) {
    string fileBelowFive, fileAboveFive;
    int strategy;
    cout << "Pagal kuri strategija norite ivesti duomenis i failus? (1, 2 arba 3): ";
    cin >> strategy;
    cout << "Iveskite rezultato failo pavadinima studentams su galutini vidurki < 5: ";
    cin >> fileBelowFive;
    cout << "Iveskite rezultato failo pavadinima studentams su galutini vidurki >= 5: ";
    cin >> fileAboveFive;

    ofstream BelowFiveFile(fileBelowFive);
    ofstream AboveFiveFile(fileAboveFive);

    if (strategy != 1 && strategy != 2 && strategy != 3) {
        cout << "Klaida. Netinkamas ivedimas, programa baigiasi" << endl;
        exit(1);
    }

    if (!BelowFiveFile.is_open() || !AboveFiveFile.is_open()) {
        cout << "Nepavyko atidaryti failo: " << (BelowFiveFile.is_open() ? fileAboveFive : fileBelowFive) << endl;
        exit(1);
    }
    auto start1 = std::chrono::high_resolution_clock::now();
    // Output rezultatas
    BelowFiveFile << "-------------------------------------------------\n";
    BelowFiveFile << std::left << std::setw(17) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(15) << "Galutinis (Vid.)" << "\n";
    BelowFiveFile << "-------------------------------------------------\n";

    // Duomenys rasomos studentams su vidurki < 5
    for(const auto& a : BelowFive){
        BelowFiveFile << std::fixed << std::setprecision(2) << std::left << std::setw(17) << a.vardas()
                              << std::setw(20) << a.pavarde()
                              << std::setw(15) << a.vidurkis()
                              << "\n";
    }

    auto finish1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed3 = finish1 - start1;
    ElapsedTime3 = elapsed3.count();


    auto start = std::chrono::high_resolution_clock::now();
    // Output rezultatas
    AboveFiveFile << "-------------------------------------------------\n";
    AboveFiveFile << std::left << std::setw(17) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(15) << "Galutinis (Vid.)" << "\n";
    AboveFiveFile << "-------------------------------------------------\n";

    // Duomenys rasomos studentams su vidurki >= 5
    if (strategy == 1 || strategy == 3) {
    for(const auto& a : AboveFive){
        AboveFiveFile << std::fixed << std::setprecision(2) << std::left << std::setw(17) << a.vardas()
                            << std::setw(20) << a.pavarde()
                            << std::setw(15) << a.vidurkis()
                            << "\n";
    }
    }
    else if (strategy == 2) {
    for(const auto& a : Grupe){
        AboveFiveFile << std::fixed << std::setprecision(2) << std::left << std::setw(17) << a.vardas()
                            << std::setw(20) << a.pavarde()
                            << std::setw(15) << a.vidurkis()
                            << "\n";
    }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed4 = finish - start;
    ElapsedTime4 = elapsed4.count();

    BelowFiveFile.close();
    AboveFiveFile.close();
    cout << "Galutiniai matavimo rezultatai: " << endl;
    cout << "Failo nuskaitymo laikas: " << ElapsedTime1 << " sekundziu" << endl;
    cout << "Studentu rusiavimas pagal parametra uztruko: " << SortTime << " sekundziu" << endl;
    cout << "Studentu dalinimas i kategorijas uztruko: " << ElapsedTime2 << " sekundziu" << endl;
    cout << "Studentu irasymas vargsiuku faila: " << ElapsedTime3 << " sekundziu" << endl;
    cout << "Studentu irasymas galvociu faila: " << ElapsedTime4 << " sekundziu" << endl;
    double totalElapsed = ElapsedTime1 + ElapsedTime2 + ElapsedTime3 + ElapsedTime4;
    cout << "Bendras matavimo laikas: " << std::setprecision(15) << totalElapsed << " sekundziu" << endl;
}
