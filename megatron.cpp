#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    string relacion;
    cout << "Nombre de la relacion: ";
    cin >> relacion;
    string esquema = "C:\\megatron\\esquema.txt";
    string dataPath = "C:\\megatron\\" + relacion + ".txt";

    vector<string> nombresParametros;
    bool fileExists = false;

    ifstream verificarParams(esquema);
    if (verificarParams.good()){
        string findrelacion;
        while (getline(verificarParams, findrelacion))
        {
            stringstream ss(findrelacion);
            string newnamerelacion;
            getline(ss, newnamerelacion, '#');
            if (newnamerelacion == relacion)
            {
                fileExists = true;
                cout << "Agregando nueva tupla a la relacion existente ->" << endl;
                string parametro;
                while (getline(ss, parametro, '#')) {
                    nombresParametros.push_back(parametro);
                }
                break;
            }
            

        }
        
        
    }
    verificarParams.close();

    int cantidad;
    if (!fileExists) {
        cout << "Cuantos parametros tendra la relacion?: ";
        cin >> cantidad;
        
        cout << "Ingresa los nombres de los parametros:" << endl;
        for (int i = 0; i < cantidad; i++) {
            string newparametro;
            cout << "Parametro " << (i+1) << ": ";
            cin >> newparametro;
            nombresParametros.push_back(newparametro);
            
        }
        ofstream archivoParams(esquema, ios::app);
        if (archivoParams.is_open()) {
            cout << "Archivo de parametros creado exitosamente en: " << esquema << endl;
            archivoParams << relacion +"#";
            for (int i = 0; i < nombresParametros.size(); i++) {
                archivoParams << nombresParametros[i];
                if (i < nombresParametros.size() - 1) {
                    
                    archivoParams << "#";
                }
            }
            //cout<<endl;
            archivoParams<<endl;
            archivoParams.close();
        } else {
            cout << "No se pudo crear el archivo de parametros." << endl;
            return 1;
        }
    }
    ofstream archivo(dataPath, fileExists ? ios::app : ios::out);
    if (archivo.is_open()) {
        cout << "Archivo de datos " << (fileExists ? "abierto" : "creado") << " exitosamente en: " << dataPath << endl;
    } else {
        cout << "No se pudo crear/abrir el archivo de datos." << endl;
        return 1;
    }
    vector<string> RegisParametros;
    cout << "\nIngresa los registros para cada parametro:" << endl;
    for (int i = 0; i < nombresParametros.size(); i++) {
        string valor;
        cout << nombresParametros[i] << ": ";
        cin >> valor;
        RegisParametros.push_back(valor);
    }
    for (int i = 0; i < RegisParametros.size(); i++) {
        archivo << RegisParametros[i];
        if (i < RegisParametros.size() - 1) {
            archivo << "#";
        }
    }
    archivo << endl;
    archivo.close();
    
    cout << "Tupla agregada exitosamente." << endl;
    return 0;
}