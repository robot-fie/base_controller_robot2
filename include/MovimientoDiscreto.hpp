
#ifndef CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H
#define CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H


#include <ostream>

struct Movimiento {
    double izquierda;
    double derecha;
};

class MovimientoDiscreto {

private:
    Movimiento rueda;
    
    static Movimiento array[12];

    //Funciones de utileria
    double calcularAngulo(double x, double z);

    double calcularModulo(double x, double z);

    Movimiento devolverMovimientoDiscretizado(double angulo, double modulo);

public:

    MovimientoDiscreto();

    const Movimiento &getRueda() const;

    void setRueda(Movimiento rueda);

    void realizarMovimientoDiscreto(double x, double z);


};


#endif //CONVERSIONAMOVIMIENTODISCRETO_MOVIMIENTODISCRETO_H
