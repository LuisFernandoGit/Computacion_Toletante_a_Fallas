#ifndef TIEMPOS_H
#define TIEMPOS_H


class tiempos
{
    public:
        int llegada;        //Tiempo en el que el proceso llega a "Listo".
        int finalizacion;   //Tiempo en el que el proceso termina.
        int retorno;        //Tiempo en el que el proceso estuvo en memoria.
        int respuesta = -1; //Tiempo en el que el programa tardo en despachar 
                            //al proceso por primera vez.
        int espera;         //Tiempo en el que el proceso no estuvo en ejecución.
        int servicio;       //Tiempo en el que el proceso estuvo en ejecución.
        tiempos();  
};

#endif // TIEMPOS_H
