#ifndef PROCESO_H
#define PROCESO_H
#include <iostream>
#include <tiempos.h>
using namespace std;


class Proceso
{
public:
    float resultado = 0; //Resultado de la operación realizada.
    int op1 = 0;         //Operando izquierdo de la operación.
    int op2 = 0;         //Operando derecho de la operación.
    int op = 0;          //Cada operación tendrá asignada un valor numérico, por ejemplo 1 = suma.
    int tiempo = 10;     //Tiempo Máximo Estimado del proceso.
    int id = 0;          //Identificado del proceso, será autoincrementable.
    int tt = 0;          //Tiempo Transcurrido en ejecución.
    int ttb = 0;         //Tiempo Transcurrido en bloqueado.

    Tiempos t;           //Objeto donde se guardarán los tiempos del proceso.
    Proceso();
};

#endif // PROCESO_H
