#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <windows.h>
using namespace std;
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
class IOInterface
{
public:
    virtual istream& citeste (istream&)=0;
    virtual ostream& afisare (ostream&)const=0;
};
class Input
{
public:
    static int readInt(const string& prompt)
    {
        int val;
        string input;
        while(true)
        {
            cout<<prompt;
            getline(cin,input);
            try
            {
                val=stoi(input);
                break;
            }
            catch(const invalid_argument&)
            {
                SetColor(4);
                cout<<"The entered value is not an integer. Please try again."<<endl;
                SetColor(7);
            }
        }
        return val;
    }
    static bool readBool(const string& prompt)
    {
        bool val;
        while(true)
        {
            cout<<prompt;
            cin>>val;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                SetColor(4);
                cout<<"\nThe entered value is not 0 or 1. Please try again."<<endl;
                SetColor(7);
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                break;
            }
        }
        return val;
    }
    static double readDouble(const string& prompt)
    {
        double val;
        string input;
        while(true)
        {
            cout<<prompt;
            getline(cin,input);
            try
            {
                val=stod(input);
                break;
            }
            catch(const invalid_argument&)
            {
               SetColor(4);
               cout<<"The entered value is not a number (double). Please try again."<<endl;
               SetColor(7);
            }
        }
        return val;
    }
    static float readFloat(const string& prompt)
    {
        float val;
        string input;
        while(true)
        {
            cout<<prompt;
            getline(cin,input);
            try
            {
                val=stof(input);
                break;
            }
            catch(const invalid_argument&)
            {
                SetColor(4);
               cout<<"The entered value is not a number (float). Please try again."<<endl;
               SetColor(7);
            }
        }
        return val;
    }
    static char readChar(const string& prompt)
    {
        char val;
        string input;
        while(true)
        {
            cout<<prompt;
            getline(cin,input);
            try
            {
                if(input.length()==1)
                {
                    val=input[0];
                    break;
                }
                else
                    throw invalid_argument("");
            }
            catch(const invalid_argument&)
            {
                SetColor(4);
                cout<<"The entered value is not a character. Please try again."<<endl;
                SetColor(7);
            }
        }
        return val;
    }
};
class Utilizator:IOInterface
{
private:
    char* nume;
    int varsta;
    char nivel; //de la a la z
    bool estePremium;
    const int idUtilizator;
    static int idContor;
public:
    Utilizator();//Constructor fara parametrii

    Utilizator(char*,int,char,bool);//Constructor cu toti parametrii

    Utilizator(char*,int,char);//COnstructor cu 3 parametrii

    Utilizator(char*);//COnstructor cu 1 parametrii

    Utilizator(const Utilizator& u);//Constructor de copiere

    Utilizator& operator =(const Utilizator&);//Supraincarcarea operatorului =

    void citesteUtilizator();//functie de citire

    void afiseazaUtilizator();//functie de afisare

    istream& citeste(istream& in)override//Suprascrierea functiei de citire
    {
        char aux[101];
        cout<<"Enter the name: ";
        in.ignore();
        in.getline(aux,101);
        if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(aux)+1];
        strcpy(this->nume,aux);
        cout<<endl;

        this->varsta=Input::readInt("Enter age: ");
        cout<<endl;

        this->nivel=Input::readChar("Enter the experience level from a to z: ");
        while(this->nivel<'a' || this->nivel>'z')
        {
            cout<<"You have entered an incorrect value. Enter a value between a-z: ";
            this->nivel=Input::readChar("");
            cout<<endl;
        }
        cout<<endl;

        this->estePremium=Input::readBool("Is the account premium?");
        cout<<endl;
        return in;
    }

    ostream& afisare(ostream& out)const override//Suprascrierea functiei de afisare
    {
        out<<"The user's name is: "<<this->nume<<endl;
        out<<"The user's age is: "<<this->varsta<<endl;
        out<<"The user's level is: "<<this->nivel<<endl;
        if(this->estePremium==true)
            out<<"The account is premium."<<endl;
        else
            out<<"The account is not premium."<<endl;
        return out;
    }

    friend ostream& operator <<(ostream& out,const Utilizator& u);//Supraincarcarea <<

    friend istream& operator >>(istream& in,Utilizator& u);//Supraincarcarea >>

    Utilizator& operator ++();//obj++

    Utilizator operator ++(int);//++obj

    Utilizator operator +(const Utilizator& u);//obj+obj

    Utilizator operator +(int);//obj+int

    friend Utilizator operator +(int,const Utilizator& j);//int+obj

    bool operator <(const Utilizator& u);//Compararea a 2 obiecte

    bool operator <(char);//Compararea obj-char

    friend bool operator <(char,Utilizator& u);//Comparare char-obj

    bool operator ==(const Utilizator& u);//Supraincarcarea operatorului ==

    //getters
    const char* getNume()const{return this->nume;}
    int getVarsta(){return this->varsta;}
    char getNivel(){return this->nivel;}
    bool getEstePremium(){return this->estePremium;}
    static int getIdContor(){return Utilizator::idContor;}
    const int getIdUtilizator(){return this->idUtilizator;}

    //setters
    void setNume(char* nume){
        if (this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }
    void setVarsta(int varsta){this->varsta=varsta;}
    void setNivel(char nivel){this->nivel=nivel;}
    void setEstePremium(bool estePremium){this->estePremium=estePremium;}

    ~Utilizator()//Destructor
    {
        if(this->nume!=NULL)
        {
            delete[] this->nume;
            this->nume=NULL;
        }
    }
};
int Utilizator::idContor=0;
Utilizator::Utilizator():idUtilizator(idContor++)//Constructor fara parametrii
    {
        this->nume=new char[strlen("Guest")+1];
        strcpy(this->nume,"Guest");
        this->varsta=0;
        this->nivel='a';
        this->estePremium=false;
    }
Utilizator::Utilizator(char* nume,int varsta,char nivel,bool estePremium):idUtilizator(idContor++),varsta(varsta),nivel(nivel),estePremium(estePremium)//Constructor cu toti parametrii
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }
Utilizator::Utilizator(char* nume,int varsta,char nivel):idUtilizator(idContor++),varsta(varsta),nivel(nivel),estePremium(false)//COnstructor cu 3 parametrii
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }
Utilizator::Utilizator(char* nume):idUtilizator(idContor++),varsta(0),nivel('a'),estePremium(false)//Constructor cu 1 parametrii
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);
    }
Utilizator::Utilizator(const Utilizator& u):idUtilizator(idContor)//Constructor de copiere
    {
        this->nume=new char[strlen(u.nume)+1];
        strcpy(this->nume,u.nume);
        this->varsta=u.varsta;
        this->nivel=u.nivel;
        this->estePremium=u.estePremium;
    }
Utilizator& Utilizator::operator =(const Utilizator& u)//Supraincarcarea operatorului =
     {
         if(this!=&u)
         {
             if(this->nume!=NULL)
           {
               delete[] this->nume;
               this->nume=NULL;
           }
        this->nume=new char[strlen(u.nume)+1];
        strcpy(this->nume,u.nume);
        this->varsta=u.varsta;
        this->nivel=u.nivel;
        this->estePremium=u.estePremium;
     }
     return *this;
     }
void Utilizator::citesteUtilizator()//Funcite de citire
    {
        char aux[101];
        cout<<"Enter the name: ";
        cin.ignore();
        cin.getline(aux,101);
        if(this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(aux)+1];
        strcpy(this->nume,aux);
        cout<<endl;

        this->varsta=Input::readInt("Enter age: ");
        cout<<endl;

        this->nivel=Input::readChar("Enter the experience level from a to z: ");
        while(this->nivel<'a' || this->nivel>'z')
        {
            cout<<"You have entered an incorrect value. Enter a value between a-z: ";
            this->nivel=Input::readChar("");
            cout<<endl;
        }
        cout<<endl;

        this->estePremium=Input::readBool("Is the account premium?");
        cout<<endl;
    }
void Utilizator::afiseazaUtilizator()//Functie de afisare
    {
        cout<<"The user's name is: "<<nume<<endl;
        cout<<"The user's age is: "<<this->varsta<<endl;
        cout<<"The user's level is: "<<this->nivel<<endl;
        if(this->estePremium==true)
            cout<<"The account is premium."<<endl;
        else
            cout<<"The account is not premium."<<endl;
    }
istream& operator >>(istream& in,Utilizator& u)//Supraincarcarea operatorului >>
    {
        char aux[101];
        cout<<"Enter the name: ";
        in.ignore();
        in.getline(aux,101);
        if(u.nume!=NULL)
            delete[] u.nume;
        u.nume=new char[strlen(aux)+1];
        strcpy(u.nume,aux);
        cout<<endl;

        u.varsta=Input::readInt("Enter age: ");
        cout<<endl;

        u.nivel=Input::readChar("Enter the experience level from a to z: ");
        while(u.nivel<'a' || u.nivel>'z')
        {
            cout<<"You have entered an incorrect value. Enter a value between a-z: ";
            u.nivel=Input::readChar("");
            cout<<endl;
        }
        cout<<endl;

        u.estePremium=Input::readBool("Is the account premium?");
        cout<<endl;
        return in;
    }
ostream& operator <<(ostream& out,const Utilizator& u)//Supraincarcarea operatorului <<
    {
        out<<"The user's name is: "<<u.nume<<endl;
        out<<"The user's age is: "<<u.varsta<<endl;
        out<<"The user's level is: "<<u.nivel<<endl;
        if(u.estePremium==true)
            out<<"The account is premium."<<endl;
        else
            out<<"The account is not premium."<<endl;
        return out;
    }
Utilizator& Utilizator::operator ++()//Supraincarcarea operatorului ++ pre
    {
        this->varsta++;
        this->nivel++;
        return *this;
    }
Utilizator Utilizator::operator ++(int)//Supraincarcarea operatorului ++ post
    {
        Utilizator a(*this);
        this->varsta++;
        this->nivel++;
        return a;
    }
Utilizator Utilizator::operator +(const Utilizator& u)//Supraincarcarea operatorului + obj+obj
{
    Utilizator aux(*this);
    char* concat=new char[strlen(aux.nume)+strlen(u.nume)+2];
    strcpy(concat,aux.nume);
    strcat(concat," ");
    strcat(concat,u.nume);
    delete[] aux.nume;
    aux.nume=concat;
    aux.varsta=aux.varsta+u.varsta;
    if(aux.nivel+(u.nivel-'a'+1)>'z')
        aux.nivel='z';//z este cel mai mare nivel
    else
        aux.nivel=aux.nivel+(u.nivel-'a'+1);
    if(aux.estePremium==true || u.estePremium==true)
        aux.estePremium=true;
    return aux;
}
Utilizator Utilizator::operator +(int i)//Supraincarcarea operatorului + obj+int
{
    Utilizator aux(*this);
    aux.varsta=aux.varsta+i;
    if(aux.nivel+i>'z')
        aux.nivel='z';
    else
        aux.nivel=aux.nivel+i;
    return aux;
}
Utilizator operator +(int i,const Utilizator& u)//Supraincarcarea operatorului int+obj
{
    Utilizator aux(u);
    aux.varsta=aux.varsta+i;
    if(aux.nivel+i>'z')
        aux.nivel='z';
    else
        aux.nivel=aux.nivel+i;
    return aux;
}
bool Utilizator::operator <(const Utilizator& u)//Supraincarcarea operatorului < objobj
{
    return this->nivel<u.nivel;
}

bool Utilizator::operator <(char p)//Supraincarcarea operatorului obj<char
{
    return this->nivel<p;
}

bool operator <(char i,Utilizator& u)//Supraincarcarea operatorului char<obj
{
    return i<u.nivel;
}
bool Utilizator::operator ==(const Utilizator& u)//Supraincarcarea operatorului ==
{
    if(strcmp(this->nume,u.nume)!=0)
        return false;
    if(varsta!=u.varsta)
        return false;
    if(nivel!=u.nivel)
        return false;
    if(estePremium!=u.estePremium)
        return false;
    return true;
}
class Traseu:public IOInterface
{
private:
    char* numeTraseu;
    float distanta;
    int elevatie;
    int calorii;
    int nrSegment;
    float* durataSegment;//se calculeaza pe fiecare kilometru in minute

public:
    Traseu();//Constructor fara parametrii

    Traseu(char*,float,int,int,float*);//Constructor cu toti parametrii

    Traseu(char*,float,int);//Constructor cu cativa(3) parametrii parametru

    Traseu(char*);//Constructor cu un parametru pentru nume

    Traseu(const Traseu& t);//Constructor de copiere

    Traseu& operator =(const Traseu&);//Supraincarcarea operatorului =

    void citesteTraseu();//Functie de citire

    void afiseazaTraseu();//Functie de afisare

    istream& citeste(istream& in)override//Suprascrierea functiei de citire
    {
      char aux[101];
      cout<<"Enter the name of the trail: ";
      in.ignore();
      in.getline(aux,101);
      if(this->numeTraseu!=NULL)
            delete[] this->numeTraseu;
      this->numeTraseu=new char[strlen(aux)+1];
      strcpy(this->numeTraseu,aux);
      cout<<endl;

      this->distanta=Input::readFloat("Enter the distance: ");
      cout<<endl;

      this->elevatie=Input::readInt("Enter the elevation: ");
      cout<<endl;

      this->nrSegment=Input::readInt("Enter the number of segments: ");
      cout<<endl;
      if(this->durataSegment!=NULL)
        delete[] this->durataSegment;
      this->durataSegment=new float[this->nrSegment];
      cout<<"The duration for each segment is:";
      for(int i=0;i<this->nrSegment;i++)
        in>>this->durataSegment[i];
      return in;
    }

    ostream& afisare(ostream& out)const override//Suprascrierea functiei e afisare
    {
        out<<"The name of the trail is: "<<this->numeTraseu<<endl;
        out<<"The distance of the trail is: "<<this->distanta<<endl;
        out<<"The elevation of the trail is: "<<this->elevatie<<endl;
        if(this->calorii!=0)
            out<<"The number of calories burned is: "<<this->calorii<<endl;
        for(int i=0;i<this->nrSegment;i++)
            out<<"The duration for the segment "<<i<<"km-"<<i+1<<"km is "<<this->durataSegment[i]<<" minutes"<<endl;
        return out;
    }

    friend istream& operator >>(istream& in,Traseu& t);//SUpraincarcarea operatorului >>

    friend ostream& operator <<(ostream& out,const Traseu& t);//Supraincarcarea operatorului <<

    float operator[](int);//Supraincarcarea operatorului []

    Traseu operator +(const Traseu& t);//Supraincarcarea operatorului + obj+obj

    Traseu operator +(int);//Supraincarcarea operatorului + obj+int

    friend Traseu operator +(int,const Traseu& t);//Supraincarcarea operatorului + int+obj

    //getters
    const char* getNumeTraseu()const{return this->numeTraseu;}
    float getDistanta(){return this->distanta;}
    int getElevatie(){return this->elevatie;}
    const float* getDurata()const{return this->durataSegment;}
    int getCalorii(){return this->calorii;}

    //setts
    void setNumeTraseu(char* numeTraseu)
    {
        if(this->numeTraseu!=NULL)
            delete[] this->numeTraseu;
        this->numeTraseu=new char[strlen(numeTraseu)+1];
        strcpy(this->numeTraseu,numeTraseu);
    }

    void setDistanta(float distanta){this->distanta=distanta;}
    void setElevatie(int elevatie){this->elevatie=elevatie;}
    void setCalorii(int calorii){this->calorii=calorii;}

    void setDurataSegment(float* durataSegment,int nrSegment)
    {
        if(this->durataSegment!=NULL)
            delete[] this->durataSegment;
        this->durataSegment=new float[nrSegment];
        for(int i=0;i<nrSegment;i++)
            this->durataSegment[i]=durataSegment[i];
    }


    ~Traseu()//Destructor
    {
        if(this->numeTraseu!=NULL)
        {
            delete[] this->numeTraseu;
            this->numeTraseu=NULL;
        }
        if(this->durataSegment!=NULL)
        {
            delete[] this->durataSegment;
            this->durataSegment=NULL;
        }
    }
};
Traseu::Traseu()//Constructor fara parametrii
    {
        this->numeTraseu=new char[strlen("Traseul nu are nume")+1];
        strcpy(this->numeTraseu,"Traseul nu are nume");
        this->distanta=0;
        this->elevatie=0;
        this->nrSegment=0;
        this->durataSegment=NULL;
        this->calorii=0;
    }
Traseu::Traseu(char* numeTraseu,float distanta,int elevatie,int nrSegment,float* durata):distanta(distanta),elevatie(elevatie),nrSegment(nrSegment),calorii(0)//Constructor cu toti parametrii
    {
        this->numeTraseu=new char[strlen(numeTraseu)+1];
        strcpy(this->numeTraseu,numeTraseu);

        this->durataSegment=new float[this->nrSegment];
        for(int i=0;i<this->nrSegment;i++)
            this->durataSegment[i]=durataSegment[i];
    }
Traseu::Traseu(char* numeTraseu,float distanta,int elevatie):distanta(distanta),elevatie(elevatie),nrSegment(0),durataSegment(NULL),calorii(0)//Constructor cu cativa(3) parametrii parametru
    {
        this->numeTraseu=new char[strlen(numeTraseu)+1];
        strcpy(this->numeTraseu,numeTraseu);
    }
Traseu::Traseu(char* numeTraseu):distanta(0),elevatie(0),nrSegment(0),durataSegment(NULL),calorii(0)//Constructor cu un parametru pentru nume
    {
        this->numeTraseu=new char[strlen(numeTraseu)+1];
        strcpy(this->numeTraseu,numeTraseu);
    }
Traseu::Traseu(const Traseu& t)//Constructor de copiere
    {
        this->numeTraseu=new char[strlen(t.numeTraseu)+1];
        strcpy(this->numeTraseu,t.numeTraseu);

        this->distanta=t.distanta;
        this->elevatie=t.elevatie;
        this->calorii=t.calorii;

        this->nrSegment=t.nrSegment;
        this->durataSegment=new float[t.nrSegment];
        for(int i=0;i<t.nrSegment;i++)
            this->durataSegment[i]=t.durataSegment[i];
    }
Traseu& Traseu::operator =(const Traseu& t)//Supraincarcarea operatorului =
     {
         if(this!=&t)
         {
             if(this->numeTraseu!=NULL)
           {
               delete[] this->numeTraseu;
               this->numeTraseu=NULL;
           }
           if(this->durataSegment!=NULL)
           {
               delete[] this->durataSegment;
               this->durataSegment=NULL;
           }
            this->numeTraseu=new char[strlen(t.numeTraseu)+1];
            strcpy(this->numeTraseu,t.numeTraseu);
            this->distanta=t.distanta;
            this->elevatie=t.elevatie;
            this->calorii=t.calorii;

            this->nrSegment=t.nrSegment;
            this->durataSegment=new float[t.nrSegment];
            for(int i=0;i<t.nrSegment;i++)
                this->durataSegment[i]=t.durataSegment[i];
     }
     return *this;
     }
void Traseu::citesteTraseu()//Funcite citire
    {
      char aux[101];
      cout<<"Enter the name of the trail: ";
      cin.ignore();
      cin.getline(aux,101);
      if(this->numeTraseu!=NULL)
            delete[] this->numeTraseu;
      this->numeTraseu=new char[strlen(aux)+1];
      strcpy(this->numeTraseu,aux);
      cout<<endl;

      this->distanta=Input::readFloat("Enter the distance: ");
      cout<<endl;

      this->elevatie=Input::readInt("Enter the elevation: ");
      cout<<endl;

      this->nrSegment=Input::readInt("Enter the number of segments: ");
      cout<<endl;
      if(this->durataSegment!=NULL)
        delete[] this->durataSegment;
      this->durataSegment=new float[this->nrSegment];
      cout<<"The duration for each segment is:";
      for(int i=0;i<this->nrSegment;i++)
        cin>>this->durataSegment[i];
    }
void Traseu::afiseazaTraseu()//Functie afisare
    {
        cout<<"The name of the trail is: "<<this->numeTraseu<<endl;
        cout<<"The distance of the trail is: "<<this->distanta<<endl;
        cout<<"The elevation of the trail is: "<<this->elevatie<<endl;
        if(this->calorii!=0)
            cout<<"The number of calories burned is: "<<this->calorii<<endl;
        for(int i=0;i<this->nrSegment;i++)
            cout<<"The duration for the segment "<<i<<"km-"<<i+1<<"km is "<<this->durataSegment[i]<<" minutes"<<endl;
    }
istream& operator >>(istream& in,Traseu& t)////Supraincarcarea operatorului >>
    {
      char aux[101];
      cout<<"Enter the name of the trail: ";
      in.ignore();
      in.getline(aux,101);
      if(t.numeTraseu!=NULL)
            delete[] t.numeTraseu;
      t.numeTraseu=new char[strlen(aux)+1];
      strcpy(t.numeTraseu,aux);
      cout<<endl;

      t.distanta=Input::readFloat("Enter the distance: ");
      cout<<endl;

      t.elevatie=Input::readInt("Enter the elevation: ");
      cout<<endl;

      t.nrSegment=Input::readInt("Enter the number of segments: ");
      cout<<endl;
      if(t.durataSegment!=NULL)
        delete[] t.durataSegment;
      t.durataSegment=new float[t.nrSegment];
      cout<<"The duration for each segment is:";
      for(int i=0;i<t.nrSegment;i++)
        in>>t.durataSegment[i];
      return in;
    }
ostream& operator <<(ostream& out,const Traseu& t)//Supraincarcarea operatorului <<
    {
        out<<"The name of the trail is: "<<t.numeTraseu<<endl;
        out<<"The distance of the trail is: "<<t.distanta<<endl;
        out<<"The elevation of the trail is: "<<t.elevatie<<endl;
        if(t.calorii!=0)
            out<<"The number of calories burned is: "<<t.calorii<<endl;
        for(int i=0;i<t.nrSegment;i++)
            out<<"The duration for the segment "<<i<<"km-"<<i+1<<"km is "<<t.durataSegment[i]<<" minutes"<<endl;
        return out;
    }
float Traseu::operator [](int i)//Supraincarcarea operatorului []
{
    if(i<0 || i>this->nrSegment-1)
        throw runtime_error("Out of range");
    else
        return this->durataSegment[i];
}
Traseu Traseu::operator +(const Traseu& t)//Supraincarcarea operatorului + obj+obj
{
    Traseu aux(*this);
    char* concat=new char[strlen(aux.numeTraseu)+strlen(t.numeTraseu)+2];
    strcpy(concat,aux.numeTraseu);
    strcat(concat," ");
    strcat(concat,t.numeTraseu);
    delete[] aux.numeTraseu;
    aux.numeTraseu=concat;

    aux.distanta=aux.distanta+t.distanta;
    aux.elevatie=aux.elevatie+t.elevatie;
    aux.calorii=aux.calorii+t.calorii;

    int maxNrSegment=max(aux.nrSegment,t.nrSegment);
    float* newDurataSegment=new float[maxNrSegment];
    for(int i=0;i<maxNrSegment;i++)
    {
        newDurataSegment[i]=0;
        if(i<aux.nrSegment)
            newDurataSegment[i]=newDurataSegment[i]+aux.durataSegment[i];
        if(i<t.nrSegment)
            newDurataSegment[i]=newDurataSegment[i]+t.durataSegment[i];
    }
    delete[] aux.durataSegment;
    aux.durataSegment=newDurataSegment;
    aux.nrSegment=maxNrSegment;

    return aux;
}
Traseu Traseu::operator +(int i)//Supraincarcarea operatorului obj+int
{
    Traseu aux(*this);
    aux.distanta=aux.distanta+i;
    aux.elevatie=aux.elevatie+i;
    aux.calorii=aux.calorii+i;
    for(int j=0;j<aux.nrSegment;j++)
        aux.durataSegment[j]=aux.durataSegment[j]+i;
    return aux;
}
Traseu operator +(int i,const Traseu& t)//Supraincarcarea operatorului int+obj
{
    Traseu aux(t);
    aux.distanta=aux.distanta+i;
    aux.elevatie=aux.elevatie+i;
    aux.calorii=aux.calorii+i;
    for(int j=0;j<aux.nrSegment;j++)
        aux.durataSegment[j]=aux.durataSegment[j]+i;
    return aux;
}

class PctInteres:IOInterface
{
protected:
    char* numePct;
    string descrierePct;
    double x_coord;
    double y_coord;
public:

    virtual void f()=0;

    PctInteres();//Constructor fara parametrii

    PctInteres(char*,string,double,double);//Constructor cu toti parametrii

    PctInteres(char*,string);//Constructor cu 2 parametrii

    PctInteres(char*);//Constructor cu un parametru

    PctInteres(const PctInteres& p);//Constructor de copiere

    PctInteres& operator =(const PctInteres&);//Supraincarcarea operatorului =

    void citestePctInteres();//Functie citire

    void afiseazaPctInteres();//Functie afisare

    friend istream& operator >>(istream& in,PctInteres& p);//Supraincarcarea operatorului >>

    friend ostream& operator <<(ostream& out,const PctInteres& p);//Supraincarcarea operatorului <<

    istream& citeste(istream& in)override//Suprascrierea functiei de citire
    {
        char aux[101];
        cout<<"Enter the name of the point: ";
        in.ignore();
        in.getline(aux,101);
        if(this->numePct!=NULL)
            delete[] this->numePct;
        this->numePct=new char[strlen(aux)+1];
        strcpy(this->numePct,aux);
        cout<<endl;

        cout<<"Enter the description of the point: ";
        getline(in,this->descrierePct);
        cout<<endl;

        this->x_coord=Input::readDouble("Enter the x coordinates: ");
        cout<<endl;

        this->y_coord=Input::readDouble("Enter the y coordinates: ");
        cout<<endl;
        return in;
    }

    ostream& afisare(ostream& out)const override//Suprascrierea functiei de afisare
    {
        cout<<"The name of the point is: "<<this->numePct<<endl;
        cout<<"Point description: "<<this->descrierePct<<endl;
        cout<<"The geographical coordinates of the point are: ";
        if(this->x_coord>0)
            cout<<this->x_coord<<" degrees E,";
        else if(this->x_coord<0)
            cout<<this->x_coord<<" degrees W,";
        else
            cout<<this->x_coord<<" degrees=Greenwich Meridian,";
        if(this->y_coord>0)
            cout<<this->y_coord<<" degrees N"<<endl;
        else if(this->y_coord<0)
            cout<<this->y_coord<<" degrees S"<<endl;
        else
            cout<<this->y_coord<<" degrees=Equator"<<endl;
        return out;
    }
    //getters
    const char* getNumePct()const{return this->numePct;}
    string getDescrierePct(){return this->descrierePct;}
    double getX_coord(){return this->x_coord;}
    double getY_coord(){return this->y_coord;}

    //setters
    void setNumePct(char* numePct)
    {
        if(this->numePct!=NULL)
            delete[] this->numePct;
        this->numePct=new char[strlen(numePct)+1];
        strcpy(this->numePct,numePct);
    }
    void setDescrierePct(string descrierePct){this->descrierePct=descrierePct;}
    void setX_coord(double x_coord){this->x_coord=x_coord;}
    void setY_coord(double y_coord){this->y_coord=y_coord;}

    virtual ~PctInteres()//Destructor
    {
        if(this->numePct!=NULL)
        {
            delete[] this->numePct;
            this->numePct=NULL;
        }
    }
};
PctInteres::PctInteres()//Constructor fara parametrii
    {
        this->numePct=new char[strlen("Punct fara nume")+1];
        strcpy(this->numePct,"Punct fara nume");
        this->descrierePct="";
        this->x_coord=0;
        this->y_coord=0;
    }
PctInteres::PctInteres(char* numePct,string descrierePct,double x_coord,double y_coord):descrierePct(descrierePct),x_coord(x_coord),y_coord(y_coord)//Constructor cu toti parametrii
    {
        this->numePct=new char[strlen(numePct)+1];
        strcpy(this->numePct,numePct);
    }
PctInteres::PctInteres(char* numePct,string descrierePct):descrierePct(descrierePct),x_coord(0),y_coord(0)//Constructor cu 2 parametrii
    {
        this->numePct=new char[strlen(numePct)+1];
        strcpy(this->numePct,numePct);
    }
PctInteres::PctInteres(char* numePct):descrierePct(""),x_coord(0),y_coord(0)//Constructor cu un parametru
    {
        this->numePct=new char[strlen(numePct)+1];
        strcpy(this->numePct,numePct);
    }
PctInteres::PctInteres(const PctInteres& p)//Constructor de copiere
    {
        this->numePct=new char[strlen(p.numePct)+1];
        strcpy(this->numePct,p.numePct);
        this->descrierePct=p.descrierePct;
        this->x_coord=p.x_coord;
        this->y_coord=p.y_coord;
    }
PctInteres& PctInteres::operator =(const PctInteres& p)//Supraincarcarea operatorului =
     {
         if(this!=&p)
         {
             if(this->numePct!=NULL)
           {
               delete[] this->numePct;
               this->numePct=NULL;
           }
            this->numePct=new char[strlen(p.numePct)+1];
            strcpy(this->numePct,p.numePct);
            this->descrierePct=p.descrierePct;
            this->x_coord=p.x_coord;
            this->y_coord=p.y_coord;
         }
         return *this;
     }

void PctInteres::citestePctInteres()//Functie citire
    {
        char aux[101];
        cout<<"Enter the name of the point: ";
        cin.ignore();
        cin.getline(aux,101);
        if(this->numePct!=NULL)
            delete[] this->numePct;
        this->numePct=new char[strlen(aux)+1];
        strcpy(this->numePct,aux);
        cout<<endl;

        cout<<"Enter the description of the point: ";
        getline(cin,this->descrierePct);
        cout<<endl;

        this->x_coord=Input::readDouble("Enter the x coordinates: ");
        cout<<endl;

        this->y_coord=Input::readDouble("Enter the y coordinates: ");
        cout<<endl;
    }

void PctInteres::afiseazaPctInteres()//Funcite afisare
    {
        cout<<"The name of the point is: "<<this->numePct<<endl;
        cout<<"Point description: "<<this->descrierePct<<endl;
        cout<<"The geographical coordinates of the point are: ";
        if(this->x_coord>0)
            cout<<this->x_coord<<" degrees E,";
        else if(this->x_coord<0)
            cout<<this->x_coord<<" degrees W,";
        else
            cout<<this->x_coord<<" degrees=Greenwich Meridian,";
        if(this->y_coord>0)
            cout<<this->y_coord<<" degrees N"<<endl;
        else if(this->y_coord<0)
            cout<<this->y_coord<<" degrees S"<<endl;
        else
            cout<<this->y_coord<<" degrees=Equator"<<endl;
    }
istream& operator >>(istream& in,PctInteres* p)//Supraincarcarea operatorului >>
    {
        if(p!=nullptr)
            p->citeste(in);
        else
            cout<<"The pointer is NULL"<<endl;
        return in;
    }
ostream& operator <<(ostream& out,const PctInteres* p)//Supraincarcarea operatorului <<
    {
        if(p!=nullptr)
            p->afisare(out);
        else
            cout<<"The pointer is NULL"<<endl;
        return out;
    }
class NaturalPct:virtual public PctInteres
{
protected:
    string ecosystemType;
    bool isProtectedArea;
    vector <string> wildlife;
public:
    NaturalPct():ecosystemType(""),isProtectedArea(false){}

    NaturalPct(char* numePct,string descrierePct,double x_coord,double y_coord,string ecosystemType,bool isProtectedArea,vector<string> wildlife):PctInteres(numePct,descrierePct,x_coord,y_coord),ecosystemType(ecosystemType),isProtectedArea(isProtectedArea),wildlife(wildlife){}

    NaturalPct(const NaturalPct& n):PctInteres(n),ecosystemType(n.ecosystemType),isProtectedArea(n.isProtectedArea),wildlife(n.wildlife){}

    NaturalPct& operator =(const NaturalPct& n)
    {
        if(this!=&n)
        {
            PctInteres::operator=(n);
            ecosystemType=n.ecosystemType;
            isProtectedArea=n.isProtectedArea;
            wildlife=n.wildlife;
        }
        return *this;
    }
    //getters
    string getEcosystemType(){return ecosystemType;}
    bool getIsProtectedArea(){return isProtectedArea;}
    const vector<string>& getWildLife()const{return wildlife;}

    istream& citeste(istream& in)override
    {
        PctInteres::citeste(in);

        cout<<"Enter ecosystem type: ";
        getline(in,ecosystemType);

        isProtectedArea=Input::readBool("Is it in a protected area? (1 for yes, 0 for no): ");

        int wildlifeCount;
        wildlifeCount=Input::readInt("Enter number of wildlife types: ");
        wildlife.clear();
        string wild;
        for(int i=0;i<wildlifeCount;i++)
        {
            cout<<"Enter wildlife type nr"<<(i+1)<<": ";
            getline(in,wild);
            wildlife.push_back(wild);
        }
        cout<<endl;
        return in;
    }
    ostream& afisare(ostream& out)const override
    {
        PctInteres::afisare(out);
        out<<"Ecosystem type: "<<ecosystemType<<endl;
        if(isProtectedArea==true)
            out<<"The area is protected"<<endl;
        else
            out<<"The area is not protected"<<endl;
        out<<"Wildlife: ";
        for(const auto&w:wildlife)//afisam elementele din vector fara a le mai face o copie
        {
            out<<w<<", ";
        }
        out<<endl;
        return out;
    }
    friend istream& operator >>(istream& in,NaturalPct* obj)
    {
        if(obj!=nullptr)
        {
            obj->citeste(in);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return in;
    }
    friend ostream& operator <<(ostream& out,const NaturalPct* obj)
    {
        if(obj!=nullptr)
        {
            obj->afisare(out);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return out;
    }
    void f()override{}
    ~NaturalPct(){}
};
class ManMadePct:virtual public PctInteres
{
protected:
    int yearEstablished;
    string historicalSignificance;
    bool isTouristAttraction;
public:
    ManMadePct():yearEstablished(0),historicalSignificance(""),isTouristAttraction(false){}

    ManMadePct(char* numePct,string descrierePct,double x_coord,double y_coord,int yearEstablished,string historicalSignificance,bool isTouristAttraction):PctInteres(numePct,descrierePct,x_coord,y_coord),yearEstablished(yearEstablished),historicalSignificance(historicalSignificance),isTouristAttraction(isTouristAttraction){}

    ManMadePct(const ManMadePct& m):PctInteres(m),yearEstablished(m.yearEstablished),historicalSignificance(m.historicalSignificance),isTouristAttraction(m.isTouristAttraction){}

    ManMadePct& operator =(const ManMadePct& m)
    {
        if(this!=&m)
        {
            PctInteres::operator=(m);
            yearEstablished=m.yearEstablished;
            historicalSignificance=m.historicalSignificance;
            isTouristAttraction=m.isTouristAttraction;
        }
        return *this;
    }
    istream& citeste(istream& in)override
    {
        PctInteres::citeste(in);
        yearEstablished=Input::readInt("Enter the year established: ");

        cout<<"Enter historical significance: ";
        getline(in,historicalSignificance);

        isTouristAttraction=Input::readBool("Is it a tourist attraction? (1 for yes, 0 for no): ");

        return in;
    }
    ostream& afisare(ostream& out)const override
    {
        PctInteres::afisare(out);
        out<<"Year established: "<<yearEstablished<<endl;
        out<<"Historical significance: "<<historicalSignificance<<endl;
        if(isTouristAttraction==true)
            out<<"It is a tourist attraction"<<endl;
        else
            out<<"It is not a tourist attraction"<<endl;
        return out;
    }
    friend istream& operator >>(istream& in,ManMadePct* obj)
    {
        if(obj!=nullptr)
        {
            obj->citeste(in);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return in;
    }
    friend ostream& operator >>(ostream& out,const ManMadePct* obj)
    {
        if(obj!=nullptr)
        {
            obj->afisare(out);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return out;
    }
    void f()override{}
    ~ManMadePct()override{}
};
class MixedPct:public NaturalPct,public ManMadePct
{
protected:
    int visitorCount;
    string uniqueFeatures;
public:
    MixedPct():visitorCount(0),uniqueFeatures(""){}

    MixedPct(char* numePct,string descrierePct,double x_coord,double y_coord,string ecosystemType,bool isProtectedArea,const vector<string>& wildlife,int yearEstablished,string historicalSignificance,bool isTouristAttraction,int visitorCount,string uniqueFeatures):PctInteres(numePct,descrierePct,x_coord,y_coord),NaturalPct(numePct,descrierePct,x_coord,y_coord,ecosystemType,isProtectedArea,wildlife),ManMadePct(numePct,descrierePct,x_coord,y_coord,yearEstablished,historicalSignificance,isTouristAttraction),visitorCount(visitorCount),uniqueFeatures(uniqueFeatures){}

    MixedPct(const MixedPct& m):PctInteres(m),NaturalPct(m),ManMadePct(m),visitorCount(m.visitorCount),uniqueFeatures(m.uniqueFeatures){}

    MixedPct& operator =(const MixedPct& m)
    {
        if(this!=&m)
        {
            NaturalPct::operator=(m);

            yearEstablished=m.yearEstablished;
            historicalSignificance=m.historicalSignificance;
            isTouristAttraction=m.isTouristAttraction;

            visitorCount=m.visitorCount;
            uniqueFeatures=m.uniqueFeatures;
        }
        return *this;
    }
    istream& citeste(istream& in)override
    {
        NaturalPct::citeste(in);

        yearEstablished=Input::readInt("Enter the year established: ");

        cout<<"Enter historical significance: ";
        getline(in,historicalSignificance);

        isTouristAttraction=Input::readBool("Is it a tourist attraction? (1 for yes, 0 for no): ");

        visitorCount=Input::readInt("Enter visitor count: ");

        cout<<"Enter unique features: ";
        getline(in,uniqueFeatures);
        return in;
    }

    ostream& afisare(ostream& out)const override
    {
        NaturalPct::afisare(out);

        out<<"Year established: "<<yearEstablished<<endl;
        out<<"Historical significance: "<<historicalSignificance<<endl;
        if(isTouristAttraction==true)
            out<<"It is a tourist attraction"<<endl;
        else
            out<<"It is not a tourist attraction"<<endl;;

        out<<"Visitor count: "<<visitorCount<<endl;
        out<<"Unique Features: "<<uniqueFeatures<<endl;
        return out;
    }
    friend istream& operator >>(istream& in,MixedPct* obj)
    {
        if(obj!=nullptr)
        {
            obj->citeste(in);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return in;
    }
    friend ostream& operator <<(ostream& out,const MixedPct* obj)
    {
        if(obj!=nullptr)
        {
            obj->afisare(out);
        }
        else
            cout<<"The pointer is NULL"<<endl;
        return out;
    }
    void f()override{}
    ~MixedPct(){}
};
class Notite:IOInterface
{
private:
    string descriere;
    string dataCreare;
    int nota;//1-10
    bool publica;
public:
    Notite();//Constructor fara parametrii

    Notite(string,string,int,bool);//Constructor cu toti parametrii

    Notite(string,string);//Constructor cu 2 parametrii

    Notite(string);//Constructor cu 1 parametru

    Notite(const Notite& n);//Constructor de copiere

    Notite& operator =(const Notite&);//Supraincarcarea operatorului =

    void citesteNotite();//Functie citire

    void afiseazaNotite();//Functie afisare

    istream& citeste(istream& in)override//Suprascrierea functiei de citire
    {
        cout<<"Note description: ";
        in.ignore();
        getline(in,this->descriere);
        cout<<endl;

        cout<<"Enter the date of creation of the note: ";
        in.ignore();
        getline(in,this->dataCreare);
        cout<<endl;

        this->nota=Input::readInt("Give a rating to the trail: ");
        while(this->nota<1 || this->nota>10)
        {   cout<<"You have entered an incorrect value. Enter a value in the range 1-10: ";
            this->nota=Input::readInt("");
            cout<<endl;
        }

        this->publica=Input::readBool("Do you want to make this note public? ");
        cout<<endl;
        return in;
    }

    ostream& afisare(ostream& out)const override//SUprascrierea functiei de afisare
    {
        out<<"Description: "<<this->descriere<<endl;
        out<<"The date of creation of the note is: "<<this->dataCreare<<endl;
        out<<"The rating given to the trail is: "<<this->nota<<endl;
        if(this->publica==1)
            out<<"The note is public.";
        else
            out<<"The note is not public.";
        return out;
    }

    friend istream& operator >>(istream& in,Notite& n);//Supraincarcarea operatorului >>

    friend ostream& operator <<(ostream& out,const Notite& n);//Supraincarcarea operatorului <<


    //getter
    string getDescriere(){return this->descriere;}
    string getDataCreare(){return this->dataCreare;}
    int getNota(){return this->nota;}
    bool getPublica(){return this->publica;}

    //setter
    void setDescriere(string descriere){this->descriere=descriere;}
    void setDataCreare(string dataCreare){this->dataCreare=dataCreare;}
    void setNota(int nota){this->nota=nota;}
    void setPublica(bool publica){this->publica=publica;}
    ~Notite()//Destructor
    {
        //nu avem ce sa stergem
    }
};
Notite::Notite()//Constructor fara parametrii
    {
        this->descriere="";
        this->dataCreare="dd/mm/yyyy";
        this->nota=0;
        this->publica=false;
    }
Notite::Notite(string descriere,string dataCreare,int nota,bool publica):descriere(descriere),dataCreare(dataCreare),nota(nota),publica(publica){}//Constructor cu toti parametrii

Notite::Notite(string descriere,string dataCreare):descriere(descriere),dataCreare(dataCreare),publica(false){}//Constructor cu 2 parametrii

Notite::Notite(string descriere):descriere(descriere),dataCreare("dd/mm/yyyy"),nota(0),publica(false){}//Constructor cu 1 parametru

Notite::Notite(const Notite& n)//Constructor de copiere
    {
        this->descriere=n.descriere;
        this->dataCreare=n.dataCreare;
        this->nota=n.nota;
        this->publica=n.publica;
    }
void Notite::citesteNotite()//Functie citire
    {
        cout<<"Note description: ";
        cin.ignore();
        getline(cin,this->descriere);
        cout<<endl;

        cout<<"Enter the date of creation of the note: ";
        cin.ignore();
        getline(cin,this->dataCreare);
        cout<<endl;

        this->nota=Input::readInt("Give a rating to the trail: ");
        while(this->nota<1 || this->nota>10)
        {   cout<<"You have entered an incorrect value. Enter a value in the range 1-10: ";
            this->nota=Input::readInt("");
            cout<<endl;
        }

        this->publica=Input::readBool("Do you want to make this note public? ");
        cout<<endl;
    }
void Notite::afiseazaNotite()//Functie afisare
    {
        cout<<"Description: "<<this->descriere<<endl;
        cout<<"The date of creation of the note is: "<<this->dataCreare<<endl;
        cout<<"The rating given to the trail is: "<<this->nota<<endl;
        if(this->publica==1)
            cout<<"The note is public.";
        else
            cout<<"The note is not public.";
    }
istream& operator >>(istream& in,Notite& n)//Supraincarcarea operatorului >>
    {
        cout<<"Note description: ";
        in.ignore();
        getline(in,n.descriere);
        cout<<endl;

        cout<<"Enter the date of creation of the note: ";
        in.ignore();
        getline(in,n.dataCreare);
        cout<<endl;

        n.nota=Input::readInt("Give a rating to the trail: ");
        while(n.nota<1 || n.nota>10)
        {   cout<<"You have entered an incorrect value. Enter a value in the range 1-10: ";
            n.nota=Input::readInt("");
            cout<<endl;
        }

        n.publica=Input::readBool("Do you want to make this note public? ");
        cout<<endl;
        return in;
    }
ostream& operator <<(ostream& out,const Notite& n)//Supraincarcarea operatorului <<
    {
        out<<"Description: "<<n.descriere<<endl;
        out<<"The date of creation of the note is: "<<n.dataCreare<<endl;
        out<<"The rating given to the trail is: "<<n.nota<<endl;
        if(n.publica==1)
            out<<"The note is public.";
        else
            out<<"The note is not public.";
        return out;
    }
Notite& Notite::operator =(const Notite& n)//Supraincarcarea operatorului =
     {
        if(this!=&n)
        {
            this->descriere=n.descriere;
            this->dataCreare=n.dataCreare;
            this->publica=n.publica;
        }
        return *this;
}
class MeniuSingleton
{
private:
    static MeniuSingleton *ptr;
    MeniuSingleton(){}

public:
    MeniuSingleton(const MeniuSingleton&)=delete;
    MeniuSingleton& operator =(const MeniuSingleton&)=delete;
    static MeniuSingleton *getInstance()
    {
        if(!ptr)
            ptr=new MeniuSingleton();
        return ptr;
    }
    static void destroy()
    {
        if(ptr!=nullptr)
        {
            delete ptr;
            ptr=nullptr;
        }
    }
    void meniu()
    {
    vector <Utilizator> listaUtilizatori;
    vector <Traseu> listaTrasee;
    vector <PctInteres*> listaPctInteres;
    vector <Notite> listaNotite;
    bool stop=false;
    int comanda;
    cout<<"Welcome to my OOP project"<<endl;
    cout<<"\n\n";
    cout<<"  ALL TRAILS"<<endl;
    cout<<"\n\nA Console-bases aplication"<<endl;
    cout<<"\n";
    system("pause");
    system("cls");
    while(stop!=true)
    {
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"!!                                                !!"<<endl;
        cout<<"!! Press 1 to work with the User class            !!" << endl;
        cout<<"!! Press 2 to work with the Trail class           !!" << endl;
        cout<<"!! Press 3 to work with the Interest Point class  !!" << endl;
        cout<<"!! Press 4 to work with the Notes class           !!" << endl;
        cout<<"!! Press 5 to exit the program                    !!" << endl;
        cout<<"!!                                                !!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        comanda=Input::readInt("");
        switch(comanda)
        {
        case 1:
            {
                system("cls");
                cout << "Press 1 to read user data from the keyboard" << endl;
                cout << "Press 2 to display user data" << endl;
                cout << "Press 3 if you want to update a user" << endl;
                cout << "Press 4 if you want to delete a user" << endl;
                cout << "Press 5 if you want to filter by level" << endl << endl << endl;
                cout << "*Press any other key to go back*" << endl;
                comanda=Input::readInt("");
                switch(comanda)
                {
                case 1:
                    {
                        system("cls");
                        Utilizator a;
                        cin>>a;
                        listaUtilizatori.push_back(a);
                        system("cls");
                        break;
                    }
                case 2:
                    {
                        system("cls");
                        cout<<"User data are:"<<endl;
                        for(int i=0;i<listaUtilizatori.size();i++)
                        {
                            cout<<listaUtilizatori[i];
                            cout<<endl;
                        }
                        break;
                    }
                case 3:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which user do you want to update:");
                        if(aux>0 && aux<=listaUtilizatori.size())
                        {
                            cout<<"Enter the new data for the user "<<aux<<" :"<<endl;
                            Utilizator update;
                            update.citeste(cin);
                            listaUtilizatori[aux-1]=update;
                            SetColor(2);
                            system("cls");
                            cout<<"User "<<aux<<" has been successfully updated"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"There is NO user with the number "<<aux<<endl;
                            SetColor(7);
                            }
                        break;
                    }
                case 4:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which user do you want to delete: ");
                        if(aux>0 && aux<=listaUtilizatori.size())
                        {
                            listaUtilizatori.erase(listaUtilizatori.begin()+aux-1);
                            SetColor(2);
                            system("cls");
                            cout<<"User "<<aux<<" was successfully deleted"<<endl;
                            SetColor(7);
                        }
                        else
                        {
                            SetColor(4);
                            system("cls");
                            cout<<"There is NO user with the number "<<aux<<endl;
                            SetColor(7);
                        }

                        break;
                    }
                case 5:
                    {
                        system("cls");
                        char nivel;
                        bool ok=1;
                        nivel=Input::readChar("What level do you want to search for: ");
                        while(nivel<'a' || nivel>'z')
                        {
                            cout<<"You have entered an incorrect value. Enter a value between a-z: ";
                            nivel=Input::readChar("");
                            cout<<endl;
                        }
                        for(int i=0;i<=listaUtilizatori.size();i++)
                            if(listaUtilizatori[i].getNivel()==nivel)
                            {
                                ok=0;
                                listaUtilizatori[i].afisare(cout);
                                cout<<endl;
                            }
                        if(ok==1)
                        {
                            SetColor(4);
                            system("cls");
                            cout<<"There are no users this this livel"<<endl;
                            SetColor(7);
                        }

                    }
                default:
                    {
                        system("cls");
                        break;
                    }
                }
                break;
            }
        case 2:
            {
                system("cls");
                cout<<"Press 1 to read trail data from the keyboard"<<endl;
                cout<<"Press 2 to display the list of trails"<<endl;
                cout<<"Press 3 to update a trail"<<endl;
                cout<<"Press 4 to delete a trail"<<endl;
                cout<<"Press 5 to calculate the number of calories burned"<<endl<<endl << endl;
                cout<<"*Press any other key to go back*"<<endl;
                comanda=Input::readInt("");
                switch(comanda)
                {
                case 1:
                    {
                        system("cls");
                        Traseu a;
                        cin>>a;
                        listaTrasee.push_back(a);
                        system("cls");
                        break;
                    }
                case 2:
                    {
                        system("cls");
                        cout<<"The dates of the Trails are:"<<endl;
                        for(int i=0;i<listaTrasee.size();i++)
                        {
                            listaTrasee[i].afisare(cout);
                            cout<<endl;
                        }
                        break;
                    }
                case 3:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which trail do you want to update: ");
                        if(aux>0 && aux<=listaTrasee.size())
                        {
                            cout<<"Enter the new data for the trail "<<aux<<" :"<<endl;
                            Traseu update;
                            update.citeste(cin);
                            listaTrasee[aux-1]=update;
                            SetColor(2);
                            system("cls");
                            cout<<"Trail "<<aux<<" has been successfully updated"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Trail number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);
                            }
                        break;
                    }
                case 4:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Ce trail vreti sa stergeti: ");
                        if(aux>0 && aux<=listaTrasee.size())
                        {
                            listaTrasee.erase(listaTrasee.begin()+aux-1);
                            SetColor(2);
                            system("cls");
                            cout<<"Trail "<<aux<<" was successfully deleted"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Trail number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);}
                        break;
                    }
                case 5:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("For which trail do you want to calculate calories?");
                        if(aux>0 && aux<=listaTrasee.size())
                        {
                            listaTrasee[aux-1].setCalorii(listaTrasee[aux-1].getDistanta()*90);
                            SetColor(2);
                            system("cls");
                            cout<<"Calories have been calculated"<<endl;
                            SetColor(7);
                        }
                        else
                        {
                            SetColor(4);
                            system("cls");
                            cout<<"Trail number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);
                        }

                        break;
                    }
                default:
                    {
                        system("cls");
                        break;
                    }
                }
                break;
            }
        case 3:
            {
                system("cls");
                cout << "Press 1 to read data of an interest point from the keyboard" << endl;
                cout << "Press 2 to display the list of interest points" << endl;
                cout << "Press 3 to update an interest point" << endl;
                cout << "Press 4 to delete an interest point" << endl;
                cout << "Press 5 to find the closest point to a set of coordinates" << endl;
                cout << "Press 6 to calculate the health of the ecosystem" << endl;
                cout << "*Press any other key to go back*" << endl;
                comanda=Input::readInt("");
                switch(comanda)
                {
                case 1:
                    {
                        system("cls");
                        cout << "Press 1 to add a natural point" << endl;
                        cout << "Press 2 to add a man-made point" << endl;
                        cout << "Press 3 to add a mixed point" << endl << endl << endl;
                        cout << "*Press any other key to go back*" << endl;
                        cin>>comanda;
                        switch(comanda)
                        {
                        case 1:
                            {
                                system("cls");
                                PctInteres *a=new NaturalPct();
                                cin>>a;
                                listaPctInteres.push_back(a);
                                system("cls");
                                break;
                            }
                        case 2:
                            {
                                system("cls");
                                PctInteres *a=new ManMadePct();
                                cin>>a;
                                listaPctInteres.push_back(a);
                                system("cls");
                                break;
                            }
                        case 3:
                            {
                                system("cls");
                                PctInteres *a=new MixedPct();
                                cin>>a;
                                listaPctInteres.push_back(a);
                                system("cls");
                                break;
                            }
                        default:
                            {
                                cin.ignore();
                                system("cls");
                                break;
                            }
                        }
                    break;
                    }
                case 2:
                    {
                        system("cls");
                        cout<<"Press 1 to display the entire list of points"<<endl;
                        cout<<"Press 2 to display only natural points"<<endl;
                        cout<<"Press 3 to display only man-made points"<<endl;
                        cout<<"Press 4 to display only mixed points"<<endl;
                        cout<<"*Press any other key to go back*"<<endl;
                        comanda=Input::readInt("");
                        switch(comanda)
                        {
                        case 1:
                            {
                                system("cls");
                                cout<<"The points of interest data are:"<<endl;
                                for(int i=0;i<listaPctInteres.size();i++)
                                {
                                    cout<<listaPctInteres[i];
                                    cout<<endl;
                                }
                                break;
                            }
                        case 2:
                            {
                                system("cls");
                                cout<<"The data of the natural points are:"<<endl;
                                for(int i=0;i<listaPctInteres.size();i++)
                                {
                                    if(typeid(*listaPctInteres[i])==typeid(NaturalPct))
                                    {
                                        cout<<listaPctInteres[i];
                                        cout<<endl;
                                    }
                                }
                                break;
                            }
                        case 3:
                            {
                                system("cls");
                                cout<<"The data of the man-made points are:"<<endl;
                                for(int i=0;i<listaPctInteres.size();i++)
                                {
                                    if(typeid(*listaPctInteres[i])==typeid(ManMadePct))
                                    {
                                        cout<<listaPctInteres[i];
                                        cout<<endl;
                                    }
                                }
                                break;
                            }
                        case 4:
                            {
                                system("cls");
                                cout<<"The mixed points data are:"<<endl;
                                for(int i=0;i<listaPctInteres.size();i++)
                                {
                                    if(typeid(*listaPctInteres[i])==typeid(MixedPct))
                                    {
                                        cout<<listaPctInteres[i];
                                        cout<<endl;
                                    }
                                }
                                break;
                            }
                        default:
                            {
                                system("cls");
                                break;
                            }
                        }
                    break;
                    }
                case 3:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("What point do you want to update: ");
                        if(aux>0 && aux<=listaPctInteres.size())
                        {
                            cout<<"Enter the new data for the point "<<aux<<" :"<<endl;
                            listaPctInteres[aux-1]->citeste(cin);
                            SetColor(2);
                            system("cls");
                            cout<<"Point "<<aux<<" has been successfully updated"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Point number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);}
                        break;
                    }
                case 4:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which point do you want to delete: ");
                        if(aux>0 && aux<=listaPctInteres.size())
                        {
                            if(listaPctInteres[aux-1]!=nullptr)
                            {
                                delete listaPctInteres[aux-1];
                                listaPctInteres.erase(listaPctInteres.begin()+aux-1);
                                SetColor(2);
                                system("cls");
                                cout<<"Point "<<aux<<" was successfully deleted"<<endl;
                                SetColor(7);
                            }
                            else
                                {SetColor(4);
                                system("cls");
                                cout<<"Poiunter is NULL"<<endl;
                                SetColor(7);}
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Point number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);}
                        break;
                    }
                case 5:
                    {
                        system("cls");
                        double x,y;
                        x=Input::readDouble("Enter the x coordinates: ");
                        y=Input::readDouble("Enter the y coordinates: ");
                        vector<int> index;
                        double distmin=1e9;
                        for(int i=0;i<listaPctInteres.size();i++)
                        {
                            double dist=sqrt(pow(listaPctInteres[i]->getX_coord()-x,2)+pow(listaPctInteres[i]->getY_coord()-y,2));
                            if(dist<distmin)
                            {
                                distmin=dist;
                                index.clear();
                                index.push_back(i);
                            }
                            else if(dist==distmin)
                            {
                                index.push_back(i);
                            }
                        }
                        if(!index.empty())
                            {cout<<"The nearest points of interest to coordinates x:"<<x<<" and y:"<<y<<" are:"<<endl;
                             for(int i:index)
                             {
                                 cout<<listaPctInteres[i];
                             }

                            }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"There are no points in the list!"<<endl;
                            SetColor(7);
                            }
                        break;
                    }
                case 6:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("For which point do you want to know the health of the ecosystem (only for natural or mixed points): ");
                        if(aux>0 && aux<=listaPctInteres.size())
                        {
                            if(typeid(*listaPctInteres[aux-1])==typeid(NaturalPct))
                            {
                                double healthScore=0.0;
                                NaturalPct* naturalPoint=dynamic_cast<NaturalPct*>(listaPctInteres[aux-1]);//Functiile se apeleaza din instanta nu din obiect de aceea trebuie facut dynamic_cast(facem downcasting)
                                string ecosystemType=naturalPoint->getEcosystemType();
                                bool isProtectedArea=naturalPoint->getIsProtectedArea();
                                int speciesCount=naturalPoint->getWildLife().size();
                                healthScore+=speciesCount*0.5;
                                if(isProtectedArea)
                                {
                                    healthScore+=10;
                                }
                                system("cls");
                                cout<<"The health score of the ecosystem is: "<<healthScore<<endl;
                            }
                            else
                            if(typeid(*listaPctInteres[aux-1])==typeid(MixedPct))
                            {
                                double healthScore=0.0;
                                MixedPct* mixedPoint=dynamic_cast<MixedPct*>(listaPctInteres[aux-1]);//Functiile se apeleaza din instanta nu din obiect de aceea trebuie facut dynamic_cast(facem downcasting)
                                string ecosystemType=mixedPoint->getEcosystemType();
                                bool isProtectedArea=mixedPoint->getIsProtectedArea();
                                int speciesCount=mixedPoint->getWildLife().size();
                                healthScore+=speciesCount*0.5;
                                if(isProtectedArea==true)
                                {
                                    healthScore+=10;
                                }
                                system("cls");
                                SetColor(2);
                                cout<<"The health score of the ecosystem is: "<<healthScore<<endl;
                                SetColor(7);
                            }
                            else
                            {   SetColor(4);
                                system("cls");
                                cout<<"The chosen point is not natural or mixed"<<endl;
                                SetColor(7);
                            }

                        }
                        else
                        {
                            SetColor(4);
                            system("cls");
                            cout<<"There is no point with the number: "<<aux<<endl;
                            SetColor(7);
                        }
                        break;
                    }
                default:
                    {
                        break;
                    }
                }
                break;
            }
        case 4:
            {
                system("cls");
                cout << "Press 1 to read note data from the keyboard" << endl;
                cout << "Press 2 to display the list of notes" << endl;
                cout << "Press 3 to update a note" << endl;
                cout << "Press 4 to delete a note" << endl;
                cout << "Press 5 to filter notes by rating" << endl << endl << endl;
                cout << "*Press any other key to go back*" << endl;
                comanda=Input::readInt("");
                switch(comanda)
                {
                case 1:
                    {
                        system("cls");
                        Notite a;
                        a.citeste(cin);
                        listaNotite.push_back(a);
                        system("cls");
                        break;
                    }
                case 2:
                    {
                        system("cls");
                        cout<<"The data of the note are::"<<endl;
                        for(int i=0;i<listaNotite.size();i++)
                        {
                            listaNotite[i].afisare(cout);
                            cout<<endl;
                        }
                        break;
                    }
                case 3:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which note do you want to update: ");
                        if(aux>0 && aux<=listaNotite.size())
                        {
                            cout<<"Enter the new data for the note "<<aux<<" :"<<endl;
                            Notite update;
                            update.citeste(cin);
                            listaNotite[aux-1]=update;
                            SetColor(2);
                            system("cls");
                            cout<<"Note "<<aux<<" was successfully updated"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Note number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);}
                        break;
                    }
                case 4:
                    {
                        system("cls");
                        int aux;
                        aux=Input::readInt("Which note do you want to delete: ");
                        if(aux>0 && aux<=listaNotite.size())
                        {
                            listaNotite.erase(listaNotite.begin()+aux-1);
                            SetColor(2);
                            system("cls");
                            cout<<"Note "<<aux<<" it was successfully deleted"<<endl;
                            SetColor(7);
                        }
                        else
                            {SetColor(4);
                            system("cls");
                            cout<<"Note number "<<aux<<" doesn't exist"<<endl;
                            SetColor(7);}
                        break;
                    }
                case 5:
                    {
                        system("cls");
                        int notamin;
                        notamin=Input::readInt("Enter the minimum value for the grade: ");
                        while(notamin<0 || notamin>10)
                        {
                            notamin=Input::readInt("Please enter a number between 1 and 10:");
                        }
                        int notamax;
                        notamax=Input::readInt("Enter the maximum value for the grade: ");
                        while(notamax<notamin || notamax>10)
                        {
                            cout<<"Please enter a number between "<<notamin<<" and 10:";
                            notamax=Input::readInt("");
                        }
                        if(notamin==notamax)
                            cout<<"Notes with a the rating "<<notamin<<" are:"<<endl<<endl;
                        else
                            cout<<"Notes with a rating between "<<notamin<<" and "<<notamax<<" are:"<<endl<<endl;
                        for(int i=0;i<listaNotite.size();i++)
                           if(listaNotite[i].getNota()>=notamin && listaNotite[i].getNota()<=notamax)
                                {
                                    listaNotite[i].afisare(cout);
                                    cout<<endl<<endl;
                                }
                        break;
                    }
                default:
                    {
                        system("cls");
                        break;
                    }
                }
                break;
            }
                case 5:
                    {
                        system("cls");
                        cout<<"Exiting the program..."<<endl;
                        stop=true;
                        break;
                    }
        default:
            {
                break;
            }
        }
    }
    for(PctInteres* pointer:listaPctInteres)
    {
        if(pointer!=nullptr)
        {
            delete pointer;//Stergem pointeri(destructor), dealocam memorie
        }
    }
    listaPctInteres.clear();//Curatam vectorul
    }
};
MeniuSingleton* MeniuSingleton::ptr=0;
int main()
{
    MeniuSingleton *meniulMeu=MeniuSingleton::getInstance();
    meniulMeu->meniu();
    MeniuSingleton::destroy();
    return 0;
}
