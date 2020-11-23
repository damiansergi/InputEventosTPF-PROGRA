#include <stdio.h>
#include "joydrv.h"
#include "termlib.h"
#include "IOEvents.h"

static char inputBuffer [MAXIMOEVENTOSBUFFER] = {0}; //He aqui el buffer de eventos

static void storeInputEvent (char evento);

void InputEvent(void) {
    jcoord_t myCoords;      //He aqui las coordenadas del joystick
    joy_init();                //inicializo el joystick
    while (1) { //ACA SERIA MEJOR SETEARLO CON EL TIMER, O PONER UN DELAY EN EL CODIGO
        joy_update();                            //primero actualizo las coordenadas medidas
        myCoords = joy_get_coord();                //luego las guardo en myCoords
        if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y <= LIMITEMOVDEPALANCA && myCoords.y >= -LIMITEMOVDEPALANCA)  ) { //se mueve hacia la derecha

            storeInputEvent(DERECHA);
        }
        else if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo a la derecha

            storeInputEvent(ABAJODERECHA);
        }
        else if ((myCoords.x >= -LIMITEMOVDEPALANCA && myCoords.x <= LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo

            storeInputEvent(ABAJO);
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y <= -LIMITEMOVDEPALANCA)) { //se mueve hacia abajo a la izquierda

            storeInputEvent(ABAJOIZQUIERDA);
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y >= -LIMITEMOVDEPALANCA && myCoords.y <= LIMITEMOVDEPALANCA)) { //se mueve hacia la izq

            storeInputEvent(IZQUIERDA);
        }
        else if ((myCoords.x <= -LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { //se mueve hacia arriba a la izquierda

            storeInputEvent(ARRIBAIZQUIERDA);
        }
        else if ((myCoords.x >= -LIMITEMOVDEPALANCA && myCoords.x <= LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { //se mueve hacia arriba

            storeInputEvent(ARRIBA);
        }
        else if ((myCoords.x >= LIMITEMOVDEPALANCA) && (myCoords.y >= LIMITEMOVDEPALANCA)) { // se mueve hacia arriba a la derecha

            storeInputEvent(ARRIBADERECHA);
        }

        //Checkeo si se presiono el boton del switch

        if ( joy_get_switch() == J_PRESS){

            storeInputEvent(BOTON);
        }
    }
}

char getInputEvent (void){
    static int i = 0;
    char salida;
    if (i >= MAXIMOEVENTOSBUFFER){

        i = 0;
        salida = inputBuffer[0];
    }
    else{

        salida = inputBuffer[++i];
    }

    return salida;
}
static void storeInputEvent (char evento){
    static int i = 0;
    if (i >= MAXIMOEVENTOSBUFFER){

        i = 0;
        inputBuffer[0] = evento;
    }
    else{

        inputBuffer[i] = evento;
        i++;
    }
}