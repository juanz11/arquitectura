//Juan Zamora CI: 20313463
//LFU

#include <iostream>
#include <string>    
#include <cmath>       
#include <algorithm>   
#include <bitset>      
#include <iomanip>      
#include <list>        

#define NUMBITS 16    
using namespace std;


void associative(list<pair<int, int>> & listaAux){  
    list<pair<int, int>> :: iterator aux01, aux02;
    bool ant,pro;
    
    if (listaAux.size() > 1) {
        aux01 = listaAux.begin();

            aux02 = next(aux01);
          
                if ((*aux01).second < (*aux02).second){
                    (*aux01).swap(*aux02);
                }
                aux02++;
            
            aux01++;
        
    };
};


pair<int, int> searcMf(list<pair<int, int>> listaAux){
    list<pair<int, int>> :: iterator datoInd;
    pair<int, int> parMin = make_pair(999999999, 999999999);

    for(datoInd = listaAux.begin(); datoInd != listaAux.end(); datoInd++){
        if (parMin.second > (* datoInd).second) {
            parMin = (*datoInd);
        }
    }

    return parMin;
};


void ordlist(list<pair<int, int>> & listaAux){  //ordenamiento de lista
    list<pair<int, int>> :: iterator aux01, aux02;

    if (listaAux.size() > 1) {
        aux01 = listaAux.begin();

        while (aux01 != prev(listaAux.end())) {
            aux02 = next(aux01);
            while (aux02 != listaAux.end()){
                if ((*aux01).second < (*aux02).second){
                    (*aux01).swap(*aux02);
                }
                aux02++;
            }
            aux01++;
        }
    };
};


void cacheDirectaLRU(list<int> listaDir, int capacidadCache) {

    list<int> :: iterator indiceDir, datoInd;
    list<int> listaCache, listaAux;

  
    int bitsIndice = log10(capacidadCache) / log10(2);
    int bitsEtiqueta = NUMBITS - bitsIndice;
    int tasaAciertos = 0, tasaFallos = 0;
    bool huboHit;

    cout << "\n" << setw(20) << " A Direccion:" << setw(20) << "Hit?:" << setw(20) << "Contenido de Ahora:";
    for (indiceDir = listaDir.begin(); indiceDir != listaDir.end(); indiceDir++) {
        bitset<NUMBITS> binarioAux = * indiceDir;
        huboHit = false;

        for (datoInd = listaAux.begin(); datoInd != listaAux.end() && !huboHit; datoInd++) {
            if(* indiceDir == * datoInd) huboHit = true;

        };

        string etiqueta = binarioAux.to_string().substr(0, bitsEtiqueta);
        string indice = binarioAux.to_string().substr(bitsEtiqueta);
        string direccion = etiqueta + " " + indice;

        if (!huboHit) {
            if (listaAux.size() < capacidadCache) {
                listaCache.push_back(* indiceDir);

            } else {
                datoInd = find(listaCache.begin(), listaCache.end(), listaAux.front());
                (* datoInd) = (* indiceDir);
                listaAux.pop_front();
            }

            listaAux.push_back(* indiceDir);
            tasaFallos++;

            cout << "\n" << setw(20) << direccion << setw(20) << "FALLO" << setw(20) << * indiceDir;
        } else {
            listaAux.remove(* indiceDir);
            listaAux.push_back(* indiceDir);
            tasaAciertos++;

            cout << "\n" << setw(20) << direccion << setw(20) << "Hit" << setw(20) << * indiceDir;
        };
    };
};


void cacheDirectaLFU(list<int> listaDir, int capacidadCache) {
   
    list<int> :: iterator indiceDir;
    list<int> listaCache;

    list<pair<int, int>> :: iterator datoInd, datoInd02;
    list<pair<int, int>> listaAux;

    int bitsIndice = log10(capacidadCache) / log10(2);
    int bitsEtiqueta = NUMBITS - bitsIndice;
    int tasaAciertos = 0, tasaFallos = 0;
    bool huboHit, encontrado;

    cout << "\n" << setw(20) << "Direccion:" << setw(20) << "Hit?:" << setw(20) << "Contenido Ahora:";
    for (indiceDir = listaDir.begin(); indiceDir != listaDir.end(); indiceDir++) {
        bitset<NUMBITS> binarioAux = * indiceDir;
        huboHit = false;

        cout << "\n\n   * A Direccion: " << * indiceDir;
        for (datoInd = listaAux.begin(); datoInd != listaAux.end() && !huboHit; datoInd++) {
            if(* indiceDir == (* datoInd).first){
                cout << " - Hit";
                (*datoInd).second++;
                huboHit = true;
            }
        };

        string etiqueta = binarioAux.to_string().substr(0, bitsEtiqueta);
        string indice = binarioAux.to_string().substr(bitsEtiqueta);
        string direccion = etiqueta + " " + indice;

        for (datoInd = listaAux.begin(); datoInd != listaAux.end() && !huboHit; datoInd++) {
            cout << "\n * " << (* datoInd).first << " - " << (* datoInd).second;
        };

        if (!huboHit) {
            if (listaAux.size() < capacidadCache) {
                pair<int, int> pairAux = make_pair(* indiceDir, 0);

                listaCache.push_back(* indiceDir);
                listaAux.push_back(pairAux);
            } else {
                ordlist(listaAux);

                encontrado = false;

                for(datoInd02 = listaAux.begin(); datoInd02 != listaAux.end(); datoInd02++){
                    if((* datoInd02).second == 0){
                        break;
                    }
                }

                cout << "\n Dato: " << (*datoInd02).first << " - " << (*datoInd02).second << "\n";

               
            }
            cout << " - FALLO";
        } else {
            
        }
    };

    for (datoInd = listaAux.begin(); datoInd != listaAux.end() && !huboHit; datoInd++) {
            cout << "\n * " << (* datoInd).first << " - " << (* datoInd).second;
    };
};




void reemplazoLFU (list<int> listaDir, int capacidadCache) {
    list<int> :: iterator indiceDir;
    list<int> listaCache;
    list<pair<int, int>> :: iterator datoInd, datoInd02;
    list<pair<int, int>> listaAux;

    int bitsIndice = log10(capacidadCache) / log10(2);
    int bitsEtiqueta = NUMBITS - bitsIndice;
    int tasaAciertos = 0, tasaFallos = 0;
    bool huboHit, encontrado;

    for (indiceDir = listaDir.begin(); indiceDir != listaDir.end(); indiceDir++) {
        bitset<NUMBITS> valorBinario = * indiceDir;
        huboHit = false;

        cout << "\n\n   * Con Direccion: " << * indiceDir;
        for (datoInd = listaAux.begin(); datoInd != listaAux.end() && !huboHit; datoInd++) {
            if (* indiceDir == (* datoInd).first){
                (* datoInd).second++;
                huboHit = true;
            };
        };

        cout << "\n Estado en Cache :";
        for (datoInd02 = listaAux.begin(); datoInd02 != listaAux.end() && !huboHit; datoInd02++) {
            cout << "\n * " << (* datoInd02).first << " - " << (* datoInd02).second;
        };

        if (!huboHit) {
            pair<int, int> datoAux = make_pair(* indiceDir, 0);
            if (listaAux.size() < capacidadCache) {
                listaCache.push_back(* indiceDir);
                listaAux.push_back(datoAux);

            } else {
                pair<int, int> menosLlamado = searcMf(listaAux);

                cout << "\n * El par de menor frecuencia es " << menosLlamado.first << " con " << menosLlamado.second << " frecuencias";
                cout << "\n * El resultado " << menosLlamado.first << " fue reemplazado por " << datoAux.first;

                listaAux.remove(menosLlamado);
                listaAux.push_back(datoAux);
            }
        }
    };
};

//principal 

int main() {
    list<int> listaDiret;


    int cantLinea, tamCache, austVar,  dirAux;
    bool bandera,bandEmpl, dataRemplazo;

   
    cin >> tamCache;
    cin.ignore(256, '\n');
    cin >> bandEmpl;
    cin.ignore(256, '\n');
    cin >> cantLinea;
    cin.ignore(256, '\n');
    cin >> dataRemplazo;
    cin.ignore(256, '\n');




    while(cin >> dirAux) {
        cin.ignore(256, '\n');

        listaDiret.push_back(dirAux);
    };

    int numLineas = tamCache / cantLinea;



    cout << "\n\n Lista Generada:";
    for(list<int> :: iterator aux = listaDiret.begin(); aux != listaDiret.end(); aux++){
        cout << " " << *aux;
    }
    cout << "\n";

    if (!bandEmpl) {
        if (!dataRemplazo) {
            
            cacheDirectaLRU(listaDiret, numLineas);
        } else {
            

            reemplazoLFU(listaDiret, numLineas);
        };
    } else {
        if (!dataRemplazo) {
            
        } else {
            
        };
    };
};
