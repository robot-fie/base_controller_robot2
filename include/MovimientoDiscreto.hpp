
#ifndef CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H
#define CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H


#include <ostream>

struct Movimiento {
    float izquierda;
    float derecha;
};

class MovimientoDiscreto {

private:
    Movimiento rueda;
    
    static Movimiento array[12];

    //Funciones de utileria
    float calcularAngulo(float x, float z);

    float calcularModulo(float x, float z);

    Movimiento devolverMovimientoDiscretizado(float angulo, float modulo);

public:

    MovimientoDiscreto();

    const Movimiento &getRueda() const;

    void setRueda(Movimiento rueda);

    void realizarMovimientoDiscreto(float x, float z);


};


#endif //CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H
