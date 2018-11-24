#include "gyro_ctrl.h"

#include "ev3.h"
#include "brick.h"
#include "ev3_sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

gyro_t* create_gyro(){

    if(ev3_sensor_init() == -1) {
        printf("No sensors found\n");
        return NULL;
    }


    gyro_t * newGyro = malloc(sizeof(gyro_t));
    if(ev3_search_sensor(LEGO_EV3_GYRO,&(newGyro->sn),0)){
        printf("Gyro-Sensor was found\n");
    

        set_sensor_mode_inx(newGyro->sn, GYRO_GYRO_ANG);

        newGyro->start_deg = 0;
        newGyro->start_deg = read_degree(newGyro);

        printf("start deg =%d\n", newGyro->start_deg);
        
        return newGyro;

    }

    

    return NULL;
}

void gyro_reset(gyro_t* gyro) {
    if(gyro == NULL) return;
    gyro->start_deg = 0;
    gyro->start_deg = read_degree(gyro);
}

void remove_gyro(gyro_t *gyro){
    if(gyro != NULL){
        free(gyro);
    }
}

int read_degree(gyro_t *gyro){
    if(gyro==NULL)return 0;

    int value = 0;
    get_sensor_value(0, gyro->sn, &value);
    return value - gyro->start_deg;
}