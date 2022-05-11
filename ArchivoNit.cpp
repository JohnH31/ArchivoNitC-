#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
//#define nombreArchivo "prueba1.csv" //Se puede cambiar aqui el csv que se desee probar 
using namespace std;
void vista();

//Clase organizadora busca el dato lo sepra por nodo y va almacenando informacion 
class Nodo{
    public:
    long nit;
    string fecha;
    double total;
    friend ostream& operator<<(ostream& ost, const Nodo& nod);
    };

    ostream& operator<<(ostream& ost, const Nodo& nodo)
    {
       ost << "nit: " << nodo.nit << ", fecha: " << nodo.fecha << ", total: " << nodo.total;
    }

//vista genera de todo el proceso desde la lectura del csv hasta el despacho 
//para poder ser dividio tanto los costos como los nit repetidos, usando map y vectores 
    void vista()
       {
        string nombreArchivo;
        cout <<"Indique el nombre del archivo: ";
        cin >> nombreArchivo;
        float acumulado;
        float fin;
        int num = 0;
        string nombre;
        char delimitador = ',';
        ifstream archivo(nombreArchivo);
        string linea;
        vector<Nodo *> nodosCSV;
        map<long, double> sumas;
        map<long, double>::iterator buscaSumas;
        while (getline(archivo, linea)) {
        stringstream stream(linea);
        string dato;
        Nodo *presente = new Nodo();
        for (int inicio = 0; getline(stream, dato, delimitador); inicio++) {
            switch(inicio) {
                case 0:
                    presente->nit = stol(dato);
                break;
                case 1:
                    presente->fecha = dato;
                break;
                case 2:
                    presente->total = stod(dato);
                break;
            }
       }

       nodosCSV.push_back(presente);
       buscaSumas = sumas.find(presente->nit);

       if (buscaSumas == sumas.end()) {
        sumas.insert(pair<long, double>(presente->nit, presente->total));
       }
       else
         {
         buscaSumas->second += presente->total;
         
        }
       }

       //IMPRIMIR TODOS LOS DATOS SEGUN LO SOLICITADO
       cout << "\n";
       cout << "No. " << "NIT " << "        Total Vendido" << endl;

       for (map<long, double>::iterator i = sumas.begin(); i != sumas.end(); i++) {  
           num++;  
        cout<< num<< "   " << i->first << "    " << i->second << endl;
        acumulado = i->second;
        fin = acumulado + fin;
     }
     cout << "    " << "    " << "  --------------" << endl;
     cout << "Sumatoria Nits: " << fin << endl;
    }

//El menu principal para su funcionamiento 
int main()
{
    vista();
    return 0;
}