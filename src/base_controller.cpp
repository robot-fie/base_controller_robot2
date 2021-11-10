#include "../include/base_controller.hpp"
#include "../include/MovimientoDiscreto.hpp"

BaseController::BaseController() {
    // Manejador del Nodo
    n = ros::NodeHandle();
    // Instancia privada solamente para acceder a los parametros
    private_n = ros::NodeHandle("~");
    // Inicializacion de las subscripciones
    twist = n.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &BaseController::twistMsgCallback, this);
    //------------>
    movimiento = MovimientoDiscreto();
    // Inicializacion de las publicaciones
    tracksNode =  n.advertise<motors_panda::Motors>("tracks_duty_cycle", 10);
}

void BaseController::twistMsgCallback(const geometry_msgs::Twist::ConstPtr& msg){
    // Tomo la magnitud del vector velocidad
    const double x = msg->linear.x;
    // Tomo la varicion en azimut del vector velocidad 
    const double z = msg->angular.z;
    motorDriver(x,z);
}


void BaseController::motorDriver(const double x, const double z){
    motors_panda::Motors motorMsg;
    movimiento.realizarMovimientoDiscreto((float)x,(float)z);
    motorMsg.data_l = movimiento.getRueda().izquierda;
    motorMsg.data_r = movimiento.getRueda().derecha;
    tracksNode.publish(motorMsg);
}

int main(int argc, char **argv) {
    ros::init(argc,argv,"base_controller");
    BaseController BC = BaseController();
    ros::spin();
    return 0;
}
