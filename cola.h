#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <stdexcept>

template<typename tipo>

class cola
{
    private:
        static const size_t CAPACIDAD = 25;
        tipo elementos[CAPACIDAD];
        size_t final;
        size_t inicio;

    public:
        cola<tipo>() : final(CAPACIDAD - 1), inicio(0) {}
        bool vacia();
        bool llena();
        void encolar(tipo elemento);
        void desencolar();
        tipo frente();
};

template<typename tipo>
bool cola<tipo>::vacia(){
    return inicio == (final + 1) % CAPACIDAD;
}

template<typename tipo>
bool cola<tipo>::llena(){
    return inicio == (final + 2) % CAPACIDAD;
}

template<typename tipo>
void cola<tipo>::encolar(tipo elemento){
    if(llena())
        throw std::invalid_argument("Cola Llena");
    final = (final + 1) % CAPACIDAD;
    elementos[final] = elemento;
}

template<typename tipo>
void cola<tipo>::desencolar(){
    if(vacia())
        throw std::invalid_argument("Cola  Vacia");
    inicio = (inicio + 1) % CAPACIDAD;
}

template<typename tipo>
tipo cola<tipo>::frente(){
    if(vacia())
        throw std::invalid_argument("Cola Vacia");
    return elementos[inicio];
}

#endif // COLA_H
