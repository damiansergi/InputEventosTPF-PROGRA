#include "joydrv.h"
#include "termlib.h"
#include "IOEvents.h"

static char inputBuffer [MAXIMOEVENTOSBUFFER] = {0}; //He aqui el buffer de eventos

void * InputEvent(void *) {
    jcoord_t myCoords;      //He aqui las coordenadas del joystick
    joy_init();                //inicializo el joystick
    char ultimoEvento = VACIO;
    char ultimoEventoBoton = VACIO;
    while (1) { //ACA SERIA MEJOR SETEARLO CON EL TIMER, O PONER UN DELAY EN EL CODIGO
        joy_update();                            //primero actualizo las coordenadas medidas
        myCoords = joy_get_coord();                //luego las guardo en myCoords
        if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y <= LIMITEMOVDEPALANCA && myCoords.y >= -LIMITEMOVDEPALANCA) ) { //se mueve hacia la derecha
            if (ultimoEvento != UPDERECHA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNDERECHA);
                ultimoEvento = UPDERECHA;
            }
        }
        else if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo a la derecha
            if (ultimoEvento != UPABAJODERECHA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNABAJODERECHA);
                ultimoEvento = (UPABAJODERECHA);
            }
        }
        else if ((myCoords.x >= -LIMITEMOVDEPALANCA && myCoords.x <= LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo
            if (ultimoEvento != UPABAJO) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNABAJO);
                ultimoEvento = (UPABAJO);
            }
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo a la izquierda
            if (ultimoEvento != UPABAJOIZQUIERDA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNABAJOIZQUIERDA);
                ultimoEvento = (UPABAJOIZQUIERDA);
            }
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y >= -LIMITEMOVDEPALANCA && myCoords.y <= LIMITEMOVDEPALANCA)) { //se mueve hacia la izq
            if (ultimoEvento != UPIZQUIERDA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNIZQUIERDA);
                ultimoEvento = (UPIZQUIERDA);
            }
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { //se mueve hacia arriba a la izquierda
            if (ultimoEvento != UPARRIBAIZQUIERDA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNARRIBAIZQUIERDA);
                ultimoEvento = (UPARRIBAIZQUIERDA);
            }
        }
        else if ((myCoords.x >= -LIMITEMOVDEPALANCA && myCoords.x <= LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { //se mueve hacia arriba
            if (ultimoEvento != UPARRIBA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNARRIBA);
                ultimoEvento = (UPARRIBA);
            }
        }
        else if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { // se mueve hacia arriba a la derecha
            if (ultimoEvento != UPDERECHA) {
                storeInputEvent(ultimoEvento);
                storeInputEvent(DOWNDERECHA);
                ultimoEvento = (UPDERECHA);
            }
        }
        else{   //Si el joystick no indica nada, guardare eso tambien para evitar problemas debido a la circularidad del buffer
            if (ultimoEvento != NOHAYMOVIMIENTO) {
                storeInputEvent(ultimoEvento);
                ultimoEvento = (NOHAYMOVIMIENTO);
            }
        }

        //Checkeo si se presiono el boton del switch

        if ( joy_get_switch() == J_PRESS){
            if (ultimoEventoBoton != DOWNBOTON) {

                storeInputEvent(DOWNBOTON);
                ultimoEventoBoton = DOWNBOTON;
            }
        }
        else if ( joy_get_switch() == J_NOPRESS ){
            if (ultimoEventoBoton != UPBOTON) {

                storeInputEvent(UPBOTON);
                ultimoEventoBoton = UPBOTON;
            }
    }
}

char getInputEvent (void){
    static int i = 0;
    char salida;
    if (i >= MAXIMOEVENTOSBUFFER){

        i = 0;
        salida = inputBuffer[i];
        inputBuffer[i] = VACIO;
        i++;
    }
    else{

        salida = inputBuffer[i];
        inputBuffer[i] = VACIO;
        i++;
    }

    return salida;
}
void storeInputEvent (char evento){
    static int i = 0;
    if (i >= MAXIMOEVENTOSBUFFER){

        i = 0;
        inputBuffer[++i] = evento;
    }
    else{

        inputBuffer[i] = evento;
        i++;
    }
}

int esBufferVacio (void){
    int salida = 1; //asumo que el buffer esta vacio hasta que encuentre un evento
    int i;

    for (i = 0; i< MAXIMOEVENTOSBUFFER; i++){

        if (inputBuffer[i] != VACIO){

            salida = 0;
        }
    }
    return salida;
}