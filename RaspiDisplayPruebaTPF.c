#include "disdrv.h"
#include "termlib.h"

char raspimenu [16][16] = {     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} , // He aqui el menu principal de la raspi hardcodeado
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,1,1,1,0,1,0,0,1,1,1,0,1,0,1,0} ,
                                {0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0} ,
                                {0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0} ,
                                {0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,0} ,
                                {0,1,0,0,0,1,1,0,1,0,1,0,0,1,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
                };

void actualizarDisplay(char matriz[16][16] ); //ESTA FUNCION CONTROLA EL BUFFER  DEL DISPLAY A PARTIR DE LA MATRIZ DADA
// SI EL ELEMENTO EN LA MATRIZ VALE 0, SE APAGA EL LED CORRESPONDIENTE Y
// SI VALE 1 SE LO PRENDE
// EN CUALQUIER OTRO CASO, SE LO DEJA IGUAL QUE ANTES

int main (void){

    disp_init();				//inicializa el display
    disp_clear();				//limpia todo el display
    actualizarDisplay(raspimenu);
    disp_update();							//ahora lo vemos en el display
    return 0;
}

void actualizarDisplay(char matriz [16][16] ){

    dcoord_t myPoint = {};		//inicializa myPoint en (0,0). Recordemos que está arriba a la izquierda.
    int y,x;
    for (x = DISP_MIN; x <= DISP_MAX_Y; x++)	//para cada coordenada en y...
    {
        for ( y = DISP_MIN; y <= DISP_MAX_X ; y++)	//para cada coordenada en x...
        {
            myPoint.x = y;
            myPoint.y = x;
            if (matriz[x][y] == 1) {
                disp_write(myPoint, D_ON);                //prende el LED en el buffer
            }
            else if (matriz[x][y] == 0){
                disp_write(myPoint, D_OFF);                //prende el LED en el buffer
            }
        }
    }
}
