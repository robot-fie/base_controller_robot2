#include <iostream>
#include <math.h>

# define PI 3.14159265358979323846  /* pi */

#include "MovimientoDiscreto.hpp"

using namespace std;

//Inicializo la variable estatica
Movimiento MovimientoDiscreto::array[12] = {{-0.05, 0.05},   //0 Giro en el lugar Izquierda
                                            {0.05,  0},       //1 Amortiguacion Giro Derecha
                                            {0.1,   0.05},    //2 Giro Suave Derecha
                                            {0.1,   0.1},     //3 Avance Frontal
                                            {0.05,  0.1},     //4 Giro Suave Izquierda
                                            {0,     0.05},    //5 Amortiguacion Giro Izquierda
                                            {0.05,  -0.05},    //6 Giro en el lugar derecha
                                            {-0.05, 0},       //7 Amortiguacion giro Atras Derecha
                                            {-0.1,  -0.05},    //8 Giro Suave atras Derecha
                                            {-0.1,  -0.1},    //9 Retroceso
                                            {-0.05, -0.1},    //10 Giro Suave atras izquierda
                                            {0,     -0.05}};  //11 Amortiguacion giro atras izquierda

//Constructor de la clase
MovimientoDiscreto::MovimientoDiscreto() {
    MovimientoDiscreto::rueda.izquierda = 0.0;
    MovimientoDiscreto::rueda.derecha = 0.0;
}

//Getter
const Movimiento &MovimientoDiscreto::getRueda() const {
    return rueda;
}

/**
 * Setter del atributo de clase rueda,
 * @param rueda struc Movimiento, con valores float para rueda izquierda y derecha
 */
void MovimientoDiscreto::setRueda(Movimiento rueda) {
    if (rueda.izquierda >= -1 && rueda.izquierda <= 1) {
        MovimientoDiscreto::rueda.izquierda = rueda.izquierda;
    } else {
        cout << "Valores fuera de rango, se establece por defecto en 0" << endl;
        MovimientoDiscreto::rueda.izquierda = 0;
    }

    if (rueda.derecha >= -1 && rueda.derecha <= 1) {
        MovimientoDiscreto::rueda.derecha = rueda.derecha;
    } else {
        cout << "Valores fuera de rango, se establece por defecto en 0" << endl;
        MovimientoDiscreto::rueda.derecha = 0;
    }
}

/**
 * Funcion que calcula el ángulo en radianes, lo corrige por cuadrante y lo transforma a grados. Necesita de la
 * constante PI
 * @param x float que es homologo al eje y
 * @param z float que es homologo al eje x
 * @return float con el angulo en grados.
 */
float MovimientoDiscreto::calcularAngulo(float x, float z) {

    if (x >= 0 && z <= 0) { //Primer Cuadrante
        return (float) (atan2(abs(x), abs(z)) / (PI / 180));
    } else if (x >= 0 && z >= 0) { //Segundo Cuadrante
        return (float) ((PI - atan2(abs(x), abs(z))) / (PI / 180));
    } else if ((x <= 0 && z >= 0)) { //Tercer Cuadrante
        return (float) (((atan2(abs(x), abs(z)) + PI)) / (PI / 180));
    } else if (x <= 0 && z <= 0) { //Cuarto Cuadrane
        return (float) (((2 * PI) - atan2(abs(x), abs(z))) / (PI / 180));
    } else {
        return 0;
    }
}

/**
 * Funcion que recibe como parametros los dos ejes del Joystick y devuelve el modulo con precicion de 0.1.
 * @param x float que es homologo al eje y
 * @param z float que es homologo al eje x
 * @return float con el modulo con dominio entre 0 y 1.
 */
float MovimientoDiscreto::calcularModulo(float x, float z) {
    float modulo;
    //Calculo el modulo con pitagoras
    modulo = (float) sqrt(pow(x, 2) + pow(z, 2));
    //Redondeo el valor del modulo
    modulo *= 10;
    modulo = round(modulo);
    return modulo / 10;
}

/**
 * Funcion que calcula dado un angulo y el modulo, el movimiento para ruedas diferenciales.
 * @param angulo
 * @param modulo
 * @return struct movimiento con los valores float rueda izquierda y derecha
 */

Movimiento MovimientoDiscreto::devolverMovimientoDiscretizado(float angulo, float modulo) {

    Movimiento rueda = {0, 0};

    //Movimientos hacia adelante

    if (angulo >= 67.5 && angulo <= 112.5) { //Movimiento frontal
        rueda.izquierda = (modulo * array[3].izquierda) * 10;
        rueda.derecha = (modulo * array[3].derecha) * 10;
        return rueda;

    } else if (angulo >= 27.5 && angulo <= 67.5) { //Giro suave derecha
        rueda.izquierda = (modulo * array[2].izquierda) * 10;
        rueda.derecha = (modulo * array[2].derecha) * 10;
        return rueda;

    } else if (angulo >= 112.5 && angulo <= 152.5) {//Giro Suave Izquirda
        rueda.izquierda = (modulo * array[4].izquierda) * 10;
        rueda.derecha = (modulo * array[4].derecha) * 10;
        return rueda;

    } else if (angulo >= 17.5 && angulo <= 27.5) { //Giro Amortiguado Derecha
        rueda.izquierda = (modulo * array[1].izquierda) * 10;
        rueda.derecha = (modulo * array[1].derecha) * 10;
        return rueda;

    } else if (angulo >= 152.5 && angulo <= 162.5) { //Giro Amortiguado Izquierda
        rueda.izquierda = (modulo * array[5].izquierda) * 10;
        rueda.derecha = (modulo * array[5].derecha) * 10;
        return rueda;

    } else if ((angulo >= 342.5 && angulo <= 360) || (angulo >= 0 && angulo <= 17.5)) { //Giro en el lugar derecha
        rueda.izquierda = (modulo * array[6].izquierda) * 10;
        rueda.derecha = (modulo * array[6].derecha) * 10;
        return rueda;

    } else if (angulo >= 152.5 && angulo <= 197.5) { //Giro en el lugar izquierda
        rueda.izquierda = (modulo * array[0].izquierda) * 10;
        rueda.derecha = (modulo * array[0].derecha) * 10;
        return rueda;

        //Movimientos hacia atras
    } else if (angulo >= 332.5 && angulo <= 342.5) { //Amortiguacion giro atras derecha
        rueda.izquierda = (modulo * array[7].izquierda) * 10;
        rueda.derecha = (modulo * array[7].derecha) * 10;
        return rueda;
    } else if (angulo >= 197.5 && angulo <= 207.5) { //Amortiguacion giro atras IZQUIERDA
        rueda.izquierda = (modulo * array[11].izquierda) * 10;
        rueda.derecha = (modulo * array[11].derecha) * 10;
        return rueda;
    } else if (angulo >= 292.5 && angulo <= 332.5) { //Giro Suave atras derecha
        rueda.izquierda = (modulo * array[8].izquierda) * 10;
        rueda.derecha = (modulo * array[8].derecha) * 10;
        return rueda;
    } else if (angulo >= 207.5 && angulo <= 247.5) { //Giro Suvae atras izquierda
        rueda.izquierda = (modulo * array[10].izquierda) * 10;
        rueda.derecha = (modulo * array[10].derecha) * 10;
        return rueda;
    } else if (angulo >= 247.5 && angulo <= 292.5) { //Retroceso
        rueda.izquierda = (modulo * array[9].izquierda) * 10;
        rueda.derecha = (modulo * array[9].derecha) * 10;
        return rueda;
    }
    return rueda;
}

/**
 * Funcion que realiza el movmiento discreto, actualizando los atributos del objeto.
 * @param x
 * @param z
 */
void MovimientoDiscreto::realizarMovimientoDiscreto(float x, float z) {
    //Primero determino el angulo de movimiento.
    float angulo = MovimientoDiscreto::calcularAngulo(x, z);
    //Segundo determino la magnitud del movimiento.
    float modulo = MovimientoDiscreto::calcularModulo(x, z);
    //Calculo el movimiento discreto y seteo el atributo de clase "rueda"
    MovimientoDiscreto::setRueda(devolverMovimientoDiscretizado(angulo, modulo));
}

