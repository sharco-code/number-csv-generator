#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

//Funcion que rellena los espacios sobrantes con 0 (en este caso)
string to_zero_lead(const int value, const unsigned precision) {
     ostringstream oss;
     oss << setw(precision) << setfill('0') << value;
     return oss.str();
}

int main() {
    
    int number = 1;                //Este es el numero de telefono que se va a ir registrando y va a ir cambiando en el bucle

    string syntaxis = "Name,Given Name,Additional Name,Family Name,Yomi Name,Given Name Yomi,Additional Name Yomi,Family Name Yomi,Name Prefix,Name Suffix,Initials,Nickname,Short Name,Maiden Name,Birthday,Gender,Location,Billing Information,Directory Server,Mileage,Occupation,Hobby,Sensitivity,Priority,Subject,Notes,Group Membership,Phone 1 - Type,Phone 1 - Value\n";       //Esto almacenara la syntaxis que se guardara en el archivo
    
    //------Intoduce las partes entre las que dividir el archivo-----------
    cout << "Partes:";
    int user_input;
    cin >> user_input;

    int division = 1000000 / user_input;
    int div_rem = division;             //remanente para mas adelante
    //-------Intoduce el prefijo de el numero [3 numeros]------------------
    cout << "Prefijo [3 numeros]:";
    int prefix;
    cin >> prefix;
    //---------------------------------------------------------------------

    //Variables que se utilizan dentro del loop
    int count = 1;         //Esta cuenta es para asignar un numero al crear los archivos
    string archivo;        //El nombre de el archivo


    //Este bucle es el que divide en partes el archivo
    while (0 < user_input) {

        cout<<"[info] Creando archivo "<<count<<endl;              //LOG
        archivo = "archivo" + to_zero_lead(count, 3) + ".csv";     //Asigna el nombre al archivo

        fstream fs (archivo, fstream::in | fstream::out | fstream::trunc);

        //Este bucle va registrando los numeros en el archivo
        while(number < division) {
            string number_turned = to_zero_lead(prefix, 3) + to_zero_lead(number, 6);      //Ajusta el numero a para que tenga 6 dijitos

            //Añade la sintaxis del .csv
            syntaxis += number_turned + "," + number_turned + ",,,,,,,,,,,,,,,,,,,,,,,,,* My Contacts,Mobile," + number_turned + "\n";
            
            //Cada 10000 numeros guarda el archivo
            if(!(number % 10000)) {
                cout<<" - Registrando: "<<number_turned<<endl;      //LOG 
                fs << syntaxis;
                fs.flush();
                syntaxis.clear();
            }
            number++;
        }
        //Guarda, cierra y limpia el string

        fs << syntaxis;
        fs.flush();
        fs.close();
        syntaxis.clear();

        cout<<"[info] Archivo "<<count<<" completado"<<endl;      //LOG 

        division = division + div_rem;

        //Variables para el siguiente loop
        count++;
        user_input--;
    }


    return 0;
}
