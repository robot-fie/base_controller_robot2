#include "../include/base_controller.hpp"

BaseController::BaseController() {
    // Manejador del Nodo
    n = ros::NodeHandle();
    // Instancia privada solamente para acceder a los parametros
    private_n = ros::NodeHandle("~");
    // Inicializacion de las subscripciones
    twist = n.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &BaseController::twistMsgCallback, this);


    // Inicializacion de las publicaciones
    tracksNode =  n.advertise<motors_panda::Motors>("commands/motor/duty_cycle", 10);

    // Inicializacion de las variables de estado
    this->tracksNode.data = 0.0;
}

void BaseController::twistMsgCallback(const geometry_msgs::Twist::ConstPtr& msg){
    // Tomo la magnitud del vector velocidad
    const double x = msg->linear.x;
    // Tomo la varicion en azimut del vector velocidad 
    const double z = msg->angular.z;
    // Teniendo los datos del Joystick llamamos a motor driver a ver que hacemos.
    // De esta manera solo se impacta en los motores si realmente hay ordenes
    motorDriver(x,z);
}


void BaseController::motorDriver(const double x, const double z){
    motorMsg.data_l = modulus(x, z) * sgn(z);
    motorMsg.data_r = modulus(x, z) * sgn(z) * -1.0;
    tracksNode.publish(motorMsg);
    // aca mandamos los mensajes a el driver de las ruedas
    /* double fast_track;
    double slow_track;
    fast_track = std::abs(x)
    slow_track = std::abs(x * (1 - std::abs(z)))
    motors_panda::Motors motorMsg;
    if(z == 0.0) {
        motorMsg.data_l = fast_track;
        motorMsg.data_r = fast_track;
        tracksNode.publish(motorMsg);
    } else if (z < 0.0) {
        motorMsg.data_l = slow_track;
        motorMsg.data_r = fast_track;
        tracksNode.publish(motorMsg);
    } else if (z > 0.0) {
        motorMsg.data_l = fast_track;
        motorMsg.data_r = slow_track;
        tracksNode.publish(motorMsg);
    } */
}

int main(int argc, char **argv) {
    ros::init(argc,argv,"base_controller");
    BaseController BC = BaseController();
    ros::spin();
    return 0;
}