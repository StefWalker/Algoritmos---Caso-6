#pragma once

#include <iostream>
#include <string>

using namespace std;

/* Struct para el almacenamiento de datos
 *	Principalmente generado para la permanencia de datos individuales
 */
struct DataElement {
	int ID;				// ID del Bird
	double distancia;	// Distancia generada en lapso de tiempo
	double velocidad;	// Velocidad generada en lapso de tiempo

	DataElement() {
		this->ID = 0;
		this->distancia = 0;
		this->velocidad = 0;
	}
};