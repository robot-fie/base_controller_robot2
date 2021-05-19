#include "../include/base_controller.hpp"

BaseController::BaseController() {
    // Manejador del Nodo
    n = ros::NodeHandle();
    // Instancia privada solamente para acceder a los parametros
    private_n = ros::NodeHandle("~");
    // Inicializacion de las subscripciones
    twist = n.subscribe<geometry_msgs::Twist>("cmd_vel", 10, &BaseController::twistMsgCallback, this);


    // Inicializacion de las publicaciones
    tracksNode =  n.advertise<std_msgs::Float64>("commands/motor/duty_cycle", 10);

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
    // aca mandamos los mensajes a el driver de las ruedas
    
}

int main(int argc, char **argv) {
    ros::init(argc,argv,"base_controller");
    BaseController BC = BaseController();
    ros::spin();
    return 0;
}