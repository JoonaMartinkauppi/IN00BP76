#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

class Opiskelija
{
    private:
        string opiskelijaID;
        string etuNimi;
        string sukuNimi;
        int arvoSana;
    public:
        Opiskelija(string ID, string etu, string suku, int arvo){
            cout<<"Luodaan uusi opiskelija tiedoilla: "<< ID << " " << etu << " " << suku << " " << arvo<<endl;
            opiskelijaID = ID;
            etuNimi = etu;
            sukuNimi = suku;
            arvoSana = arvo;
        };
        ~Opiskelija(){
        }
        string getEtunimi();
        string getSukunimi();
        int getArvosana();
        string getID();
};

string Opiskelija::getEtunimi(){
    return(etuNimi);
}

string Opiskelija::getSukunimi(){
    return(sukuNimi);
}

int Opiskelija::getArvosana(){
    return(arvoSana);
}

string Opiskelija::getID(){
    return(opiskelijaID);
}

void tallennaOpiskelija(){
    string ID, etuN, sukuN;
    int arvoS;
    cout<<"Anna opiskelijalle uniikki ID:"<<endl;
    cin>>ID;
    cout<<"Anna opiskelijan etunimi:"<<endl;
    cin>>etuN;
    cout<<"Anna opiskelijan sukunumi:"<<endl;
    cin>>sukuN;
    Arvo: cout<<"Anna opiskelijan arvosana, 0-5:";
    cin>>arvoS;
    if(cin.fail()){
        string s;
        cout<<"Opiskelijan tallentaminen epäonnistui!"<<endl;
        cin.clear();
        cin>>s;
    }
    else if(arvoS < 0 || arvoS > 5){
        cout<<"Arvosanan tulee olla välillä 0-5!"<<endl;
        goto Arvo;
    }
    else{
        Opiskelija opiskelija(ID, etuN, sukuN, arvoS);
        ofstream rekisteri;
        rekisteri.open("rekisteri.txt", ios_base::app);
        rekisteri << opiskelija.getID() + " ";
        rekisteri << opiskelija.getEtunimi() +" ";
        rekisteri << opiskelija.getSukunimi() +" ";
        rekisteri << opiskelija.getArvosana()<<endl;
        rekisteri.close();
    }   
}
void tulostaOpiskelijat(){
    cout<<"Tulostetaan opiskelijoiden tiedot: "<<endl;
    ifstream rekisteri("rekisteri.txt");
    string rivi;
    while (getline(rekisteri, rivi))
    {
        printf("%s\n", rivi.c_str());
    }
    rekisteri.close();
}

void tulostaOpiskelija(){
    bool olemassa = false;
    string ID;
    cout<<"Anna opiskelijan ID: ";
    cin>>ID;
    ifstream rekisteri("rekisteri.txt");
    string rivi;
    while(getline(rekisteri,rivi)){
        istringstream ss(rivi);
        string sana;
        while(ss >> sana){
            if(sana == ID){
                cout<<"Löytyi opiskelija annetulla ID:llä!"<<endl;
                cout<<"Opiskelijan tiedot:"<<endl;
                printf("%s\n", rivi.c_str());
                olemassa = true;
                break;
            }
        }
    }
    if(!olemassa){
        cout<<"Annetulla ID:llä ei löytynyt opiskelijaa!"<<endl;
    }
}

void poistaOpiskelija(){
    string ID, rivi;
    cout<<"Anna opiskelijan ID: ";
    cin>>ID;
    ifstream rekisteri("rekisteri.txt");
    ofstream rekisteriTemp;
    rekisteriTemp.open("temp.txt");
    while(getline(rekisteri, rivi)){
        istringstream ss(rivi);
        string sana;
        while(ss >> sana){
            if(sana == ID){
                cout<<"Poistetaan opiskelija ID:llä" << sana <<endl;
                goto loppu;
            }
        }
        rekisteriTemp << rivi << endl;
        loppu: continue;
    }
    rekisteri.close();
    rekisteriTemp.close();
    remove("rekisteri.txt");
    rename("temp.txt", "rekisteri.txt");
}

void arvosanaKA(){
    int as;
    double keskiarvo = 0;
    int maara = 0;
    cout<<"Tulostetaan arvosanojen keskiarvo: ";
    ifstream rekisteri("rekisteri.txt");
    string rivi;
    while (getline(rekisteri, rivi))
    {
        string arvosana = rivi.substr(rivi.length()-1);
        as = stoi(arvosana);
        keskiarvo += as;
        maara++;
    }
    keskiarvo = keskiarvo / maara;
    rekisteri.close();
    cout<<keskiarvo<<endl;
}

void kaikkiArvosanat(){
    cout<<"Tulostetaan kaikki arvosanat: "<<endl;
    ifstream rekisteri("rekisteri.txt");
    string rivi;
    while (getline(rekisteri, rivi))
    {
        string arvosana = rivi.substr(rivi.length()-1);
        cout<<arvosana<<endl;
    }
    rekisteri.close();
}

void annettuArvosana(int as){
    cout<<"Tulostetaan opiskelijat annetulla arvosanalla:"<<endl;
    ifstream rekisteri("rekisteri.txt");
    string rivi;
    while (getline(rekisteri, rivi))
    {
        string arvosana = rivi.substr(rivi.length()-1);
        int arvosanaInt = stoi(arvosana);
        if(arvosanaInt == as){
            cout<<rivi<<endl;
        }
    }
    rekisteri.close();
}


int main()
{
    cout<<"Tervetuloa Tenttirekisteriohjelmaan"<<endl;
    bool b = true;
    // Päävalikko:
    while (b)
    {
        int valinta;
        cout<<"\nValitse 1 lisääksesi opiskelijan"<<endl;
        cout<<"Valitse 2 poistaaksesi opiskelijan"<<endl;
        cout<<"Valitse 3 tulostaaksesi yhden opiskelijan tiedot"<<endl;
        cout<<"Valitse 4 tulostaaksesi kaikkien opiskelijoiden tiedot"<<endl;
        cout<<"Valitse 5 tulostaaksesi arvosanojen keskiarvon"<<endl;
        cout<<"Valitse 6 tulostaaksesi kaikki arvosanat"<<endl;
        cout<<"Valitse 7 tulostaaksesi tietyn arvosanan opiskelijat"<<endl;
        cout<<"Lopettaaksesi valitse 8"<<endl;
        cout<<"Valinta: ";
        cin>>valinta;
        if(cin.fail()){
            string s;
            cout<<"Väärä syöte, yritä uudelleen."<<endl;
            cin.clear();
            cin>>s;
            continue;
        }
        switch (valinta)
        {
        case 1:
            tallennaOpiskelija();
            break;
        case 2:
            poistaOpiskelija();
            break;
        case 3:
            tulostaOpiskelija();
            break;
        case 4:
            tulostaOpiskelijat();
            break;
        case 5:
            arvosanaKA();
            break;
        case 6:
            kaikkiArvosanat();
            break;
        case 7:
            int as;
            cout<<"Anna haettava arvosana: ";
            cin>>as;
            annettuArvosana(as);
            break;
        case 8:
            b = false;
            break;
        default:
            cout<<"Väärä syöte, yritä uudelleen."<<endl;
            break;
        }
    }
    return 0;
}
