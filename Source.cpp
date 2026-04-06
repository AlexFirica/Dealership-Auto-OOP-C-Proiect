#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ofstream out("fisier.txt", ios::app);

class Car 
{
protected:
    string marca;
    string model;
    int an;
    float pret;

public:

    Car(string marca = "", string model = "", int an = 0, float pret = 0) {
        this->marca = marca;
        this->model = model;
        this->an = an;
        this->pret = pret;
    }

    string getMarca() 
    { 
        return marca; 
    }
    string getModel()  
    {
        return model; 
    }
    int getAn() 
    {
        return an; 
    }
    float getPret() 
    {
        return pret; 
    }

    void setMarca(string& marca) 
    {
        this->marca = marca; 
    }
    void setModel(string& model) 
    { 
        this->model = model;
    }
    void setAn(int& an)
    {
        this->an = an;
    }
    void setPret(float& pret) 
    { 
        this->pret = pret; 
    }

    virtual void afisare() 
    {
        cout << marca << " " << model << " (" << an << ") - Pret: " << pret << " euro\n";
    }

    virtual float calculeazaPretFinal() 
    {
        float *pretFinal = &pret;
        char r;

        cout << "Garantie extinsa? (y/n): ";
        cin >> r;
        if (r == 'y') *pretFinal += 500;

        cout << "Pachet premium? (y/n): ";
        cin >> r;
        if (r == 'y') *pretFinal += 1500;

        return *pretFinal;
    }

    Car& operator=(const Car& other) 
    {
        if (this != &other) 
        {
            marca = other.marca;
            model = other.model;
            an = other.an;
            pret = other.pret;
        }
        return *this;
    }

    Car operator+(float extra) 
    {
        Car copie = *this;
        copie.pret += extra;
        return copie;
    }

    virtual void salveaza(ofstream& out) 
    {
        out << marca << " "<< model << " "<< an << " "<< pret << "\n";
    }

    virtual ~Car() {}
};

class MasinaElectrica : public Car 
{
private:
    int autonomie;

public:
    MasinaElectrica(string marca = "", string model = "", int an = 0, float pret = 0, int autonomie = 0): Car(marca, model, an, pret) 
    {
        this->autonomie = autonomie;
    }

    int getAutonomie() { return autonomie; }
    void setAutonomie(int a) { autonomie = a; }

    void afisare() override 
    {
        Car::afisare();
        cout << "Autonomie: " << autonomie << " km\n";
    }

    float calculeazaPretFinal() override
    {
        float pretFinal = pret;
        char r;

        cout << "Statie incarcare? (y/n): ";
        cin >> r;
        if (r == 'y') pretFinal += 1000;

        return pretFinal;
    }

    void salveaza(ofstream& out) override 
    {
        out << marca << " "<< model << " "<< pret << " "<< autonomie << "\n";
    }
};

class Dealership 
{
private:
    vector<Car*> masini;

public:
    void adaugaMasina(Car* m)
    {
        masini.push_back(m);
    }

    void afiseazaMasini() 
    {
        for (int i = 0; i < masini.size(); i++)
        {
            cout << i << ". ";
            masini[i]->afisare();
        }
    }

    void cumparaMasina()
    {
        int index;
        cout << "Alegeti indexul masinii: ";
        cin >> index;
        if (index >=0 && index < masini.size())
        {
            float pretFinal = masini[index]->calculeazaPretFinal();
            cout << "Pret final: " << pretFinal << " euro\n";
        }
        else cout << "Index invalid!\n";
    }
    
    void setGetMasina()
    {
        int index;
        cout << "Alegeti indexul masinii: ";
        do
        {
            cin >> index;
        } while (index < 0 || index > masini.size());
        
        if (index >= 0 && index < masini.size())
        {
            int opt;
            do
            {
                cout << "\n1. Seteaza\n2. Obtine\n0.Iesire in meniul principal\n";
                cin >> opt;
                string marca;
                string model;
                int an;
                float pret;
                if (opt == 1)
                {
                    cout << "Marca: "; cin >> marca;
                    cout << "Model: "; cin >> model;
                    cout << "An: "; cin >> an;
                    cout << "Pret: "; cin >> pret;
                    masini[index]->setMarca(marca);
                    masini[index]->setModel(model);
                    masini[index]->setAn(an);
                    masini[index]->setPret(pret);
                    cout << "\tDate introduse cu succes!\n";
                }
                else if (opt == 2)
                {
                    string r;
                    cout << "Ce vrei sa obtii despre aceasta masina? (marca/model/an/pret): ";
                    cin >> r;
                    if (r=="marca")
                    {
                        cout<<masini[index]->getMarca();
                        return;
                    }
                    if (r=="model")
                    {
                        cout<<masini[index]->getModel();
                        return;
                    }
                    if (r=="an")
                    {
                        cout<<masini[index]->getAn();
                        return;
                    }
                    if (r=="pret")
                    {
                        cout<<masini[index]->getPret();
                        return;
                    }
                }
                else if (opt==0)
                {
                    cout << "Iesire!";
                }
                else cout << "Alege o optiune!\n";
            }while (opt != 0);
            
        }
        else cout << "Index invalid!\n";
    }

    void salveazaFisier(string numeFisier) 
    {
        ofstream out(numeFisier,ios::app);

        for (auto m : masini) {
            m->salveaza(out);
        }
        out.close();
        cout << "S-a salvat in fisier!\n";
    }

    ~Dealership() 
    {
        for (auto m : masini)
            delete m;
    }
};

int main() 
{
    Dealership d;

    Car c1("Dacia", "Logan", 2000, 4000);
    Car c2 = c1+500;
   
    d.adaugaMasina(new Car(c2));
    d.adaugaMasina(new Car("BMW", "X5", 2020, 30000));
    d.adaugaMasina(new Car("Audi", "A8", 2015, 29000));
    d.adaugaMasina(new Car("Audi", "S5", 2013, 25000));
    d.adaugaMasina(new Car("Mercedes Benz", "S63 AMG", 2021, 45000));
    d.adaugaMasina(new Car("Porsche", "911 GT3RS", 2024, 213000));
    d.adaugaMasina(new MasinaElectrica("Tesla", "Model 3", 2022, 40000, 450));
    d.adaugaMasina(new MasinaElectrica("Audi", "Q4 E-TRON 3", 2021, 23000, 280));
    d.adaugaMasina(new MasinaElectrica("BMW", "330e F30", 2016, 20000, 40));

    int opt;
    cout << "\t~~~ Bine ati venit la Dealership Firicel! ~~~\n";
    do 
    {
        cout << "\n1. Afisare\n2. Adaugare\n3. Cumparare\n4. Salvare\n5. Setare / Obtinere Date\n0. Exit\nAlege o optiune:";
        cin >> opt;
        cout << '\n';

        if (opt == 1)
        {
            d.afiseazaMasini();
        }
        else if (opt == 2)
        {
            string marca, model;
            int an;
            float pret;

            cout << "Marca: "; cin >> marca;
            cout << "Model: "; cin >> model;
            cout << "An: "; cin >> an;
            cout << "Pret: "; cin >> pret;

            d.adaugaMasina(new Car(marca, model, an, pret));
        }
        else if (opt == 3)
        {
            d.cumparaMasina();
        }
        else if (opt == 4)
        {
            d.salveazaFisier("fisier.txt");
        }
        else if (opt == 5)
        {
            d.setGetMasina();
        }
        else if (opt == 0)
            cout << "Iti multumim pentru vizita.La revedere!";
    }while (opt != 0);

    return 0;
}