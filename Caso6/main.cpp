// Dylan Stef Torres Walker
//  2018135751

#include "data.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int text_Size = 500;     // Tamaño de texto de entrada ajustable a la cantidad de datos
string line[text_Size];        // Array usado para la carga del txt
const int birds = 20;          // Cantidad de aves (Misma cantidad seleccionada en el JavaScript)

/* Carga del txt en el array 
 *  Input:
 *  Output:
 */
void fileLoader()
{
    int a = 0;

    ifstream myfile("C:/Users/dylan/source/repos/Caso6/data.txt");
    while (!myfile.eof())
    {
        getline(myfile, line[a]);
        a++;

    }
}

/* Funcion principal encargada de multiples secciones del codigo, principal la carga en objetos bird y el paralelismo
 *  Input:
 *  Output: cout con el Ranking y el array de datos para la prueba en JavaScript
 */
int main()
{
    fileLoader();   // Carga del archivo

    DataElement* datos[text_Size];  // Creacion de objetos tipo bird para almancenar cada linea de datos entrante
    string read = "";               // Usado para la asignacion

    for (int i = 0; i < text_Size; i++) {       // For encargado de recorrer cada dato del recuperado del Txt para la carga de datos
        datos[i] = new DataElement();
        read += line[i][0];
        int j = 1;

        if (line[i][1] != ' ') {
            read += line[i][1];
            j++;
        }       // Read line lee el o los dos primeros elementos del string (ID)
        datos[i]->ID = stoi(read);
        j++;
        read = "";

        while (line[i][j] != ' ') {     // Concatena chars hasta encontrar el ' ' ahi se declara el numero tipo double como completo 
            read += line[i][j];
            j++;
        }                               // Adiciona la distancia al objeto
        datos[i]->distancia = stod(read);
        read = "";
        j++;

        while (line[i][j] != ' ') {     // Concatena chars hasta encontrar el ' ' ahi se declara el numero tipo double como completo
            read += line[i][j];
            j++;
        }                               // Adiciona la velocidad al objeto
        datos[i]->velocidad = stod(read);

        read = "";  // Limpia el read
    }

    // Set de variables a utilizar en y post paralelismo
    double MaxDistance1 = 0.0, MaxDistance2 = 0.0, MaxSpeed1 = 0.0, MaxSpeed2 = 0.0;
    double MinDistance1 = 100.0, MinDistance2 = 100.0, MinSpeed1 = 100.0, MinSpeed2 = 100.0;
    int WinerBirds[8] = { 0 };  // Array de Birds ganadores
    DataElement * Ranking[8];   // Valores finales logrados por cada Bird

    int i, j = 0;
    double distancia = 0.0, velocidad = 0.0;

     
    //#pragma omp parallel  for private(i, j, distancia, velocidad) num_threads(4)  
                                                                    // Linea con set de hilos del procesador pero evitado para dejar que el OS decida cuantos usar
    // Inicio de for con paralelismo con las variables privadas para cada thread
    #pragma omp parallel for private(i, j, distancia, velocidad)
    {
        for (i = 0; i < birds; i++) {       // Recorre la lista de Birds
            for (j = 0; j < text_Size; j++) {   // Recorre la lista de objetos para la suma de mayores distancias y velocidades alcanzadas
                if (datos[j]->ID == i) {
                    distancia += datos[j]->distancia;
                    velocidad += datos[j]->velocidad;
                }
            }

            // Top 2 Mayores Distacias logradas 
            if (MaxDistance1 < distancia) {
                MaxDistance2 = MaxDistance1;
                WinerBirds[0] = i;
                MaxDistance1 = distancia;
            }
            if (MaxDistance2 < distancia && MaxDistance1 > distancia) {
                WinerBirds[1] = i;
                MaxDistance2 = distancia;
            }

            // Top 2 Menores Distacias logradas
            if (MinDistance1 > distancia) {
                MinDistance2 = MinDistance1;
                WinerBirds[2] = i;
                MinDistance1 = distancia;
            }
            if (MinDistance2 > distancia && MinDistance1 < distancia) {
                WinerBirds[3] = i;
                MinDistance2 = distancia;
            }

            // Top 2 Mayores Velocidades logradas
            if (MaxSpeed1 < velocidad) {
                MaxSpeed2 = MaxSpeed1;
                WinerBirds[4] = i;
                MaxSpeed1 = velocidad;
            }
            if (MaxSpeed2 < velocidad && MaxSpeed1 > velocidad) {
                WinerBirds[5] = i;
                MaxSpeed2 = velocidad;
            }

            // Top 2 Menores Velocidades logradas
            if (MinSpeed1 > velocidad) {
                MinSpeed2 = MinSpeed1;
                WinerBirds[6] = i;
                MinSpeed1 = velocidad;
            }
            if (MinSpeed2 > velocidad && MinSpeed1 < velocidad) {
                WinerBirds[7] = i;
                MinSpeed2 = velocidad;
            }
        }
    }

    // Set de pragma Critical para los couts finales
    #pragma omp critical
    cout << "Ranking{ \n" <<
        "  MaxDistance1 : " << MaxDistance1 << "   Bird ID : " << WinerBirds[0] << "   Azul;\n" <<
        "  MaxDistance2 : " << MaxDistance2 << "   Bird ID : " << WinerBirds[1] << "   Rojo;\n\n" <<
        "  MinDistance1 : " << MinDistance1 << "   Bird ID : " << WinerBirds[2] << "   Morado;\n" <<
        "  MinDistance2 : " << MinDistance2 << "   Bird ID : " << WinerBirds[3] << "   Cafe;\n\n" <<
        "  MaxSpeed1 : " << MaxSpeed1 << "   Bird ID : " << WinerBirds[4] << "   Verde;\n" <<
        "  MaxSpeed2 : " << MaxSpeed2 << "   Bird ID : " << WinerBirds[5] << "   Amarillo;\n\n" <<
        "  MinSpeed1 : " << MinSpeed1 << "   Bird ID : " << WinerBirds[6] << "   Negro;\n" <<
        "  MinSpeed2 : " << MinSpeed2 << "   Bird ID : " << WinerBirds[7] << "   Celeste;\n" <<
        "}\n\n" << endl;        // Cout con cada Ranking, el ave ganadora y el color asignado a cada ranking

    cout << "[ " << MaxDistance1 << ", " << MaxDistance2 << ", " << MinDistance1 << ", " << MinDistance2 << ", " << 
        MaxSpeed1 << ", " << MaxSpeed2 << ", " << MinSpeed1 << ", " << MinSpeed2 << "];"<< endl;
                                // Cout del array para enviar al JavaScript

}

