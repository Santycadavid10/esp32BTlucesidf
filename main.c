
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <sdkconfig.h>
#include <inttypes.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"
#include "driver/ledc.h"
#include "freertos/timers.h"
#include "sys/time.h"


#define SPP_TAG "SPP_ACCEPTOR_DEMO"
#define SPP_SERVER_NAME "SPP_SERVER"
#define EXAMPLE_DEVICE_NAME "ESP_SPP_ACCEPTOR"
#define SPP_SHOW_DATA 0
#define SPP_SHOW_SPEED 1
#define SPP_SHOW_MODE SPP_SHOW_SPEED    /*Choose show mode: show data or speed*/
#define CONFIG_FREERTOS_HZ 100

int a = 0;
uint16_t receivedValue = 0;
uint8_t pasos = 0;
uint8_t juego = 1;
uint8_t inicio_programa = 0;
int timerId = 1;
int timerId1 = 1;
TimerHandle_t xTimers;
TimerHandle_t x1Timers;
TickType_t myInterval ;
TickType_t myInterval1 ;


static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;
static const bool esp_spp_enable_l2cap_ertm = true;
static struct timeval  time_old;
static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

static char *bda2str(uint8_t * bda, char *str, size_t size){
    if (bda == NULL || str == NULL || size < 18) {
        return NULL;
    }

    uint8_t *p = bda;
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            p[0], p[1], p[2], p[3], p[4], p[5]);
    return str;
}
void inicioescena(void){
receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);//rojo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);//rojo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);//rojo
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//rojo
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);//rojo
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//rojo
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);//rojo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);//azul
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);//azul
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);//azul
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6);//azul
}

typedef void (*TimerCallback)(TimerHandle_t xTimers);

void llamada1(TimerHandle_t xTimers) {
   if (pasos == 0){
         a = a + 1;
       ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, a);//rojo
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);//rojo 
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, a);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde   
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, a);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            if (a == 255){
            pasos = 1;
            } 
        }
   else if (pasos == 1){
        a = a - 1;
       ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, a);//rojo
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);//rojo 
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, a);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde   
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, a);//azul
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);  
        if (a == 0){
            pasos = 2;
        }
    }
   else if (pasos == 2){
        a = a + 1;
       ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, a);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
        if (a == 255){
            pasos = 3;
        }
    }
else if (pasos == 3){
        a = a - 1;
       ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, a);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
        if (a == 0){
            pasos = 4;
            a = 255;
        }
    }
 else if (pasos == 4){
        a = a - 1;
      ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, a);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde 
        if (a == 0){
            pasos = 5;
            a = 255;
        }
    }
 else if (pasos == 5){
        a = a - 1;
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, a);//rojo
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);//rojo  
        if (a == 0){
            pasos = 0;
        }
    }       
}
void llamada2(TimerHandle_t xTimers) {
     receivedValue = 225;
   if (pasos == 0){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 1; }
    else if(pasos == 1){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 2; }
    else if(pasos == 2){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 3; }
    else if(pasos == 3){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 4; }
    else if(pasos == 4){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 5; }
    else if(pasos == 5){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 6; }
    else if(pasos == 6){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 7; }
    else if(pasos == 7){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 8; }
    else if(pasos == 8){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 9; }
    else if(pasos == 9){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 10; }
    else if(pasos == 10){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 11; }
        else if(pasos == 11){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
            
    pasos = 12; }
    else if(pasos == 12){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 13; }
    else if(pasos == 13){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 14; }
    else if(pasos == 14){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 15; }
    else if(pasos == 15){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 16; }
    else if(pasos == 16){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 17; }
        else if(pasos == 17){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
            
    pasos = 0; }

}
void llamada3(TimerHandle_t xTimers) { 
    if(pasos == 0){
    receivedValue = receivedValue +1;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
        if(receivedValue == 255){
            pasos = 1;
            receivedValue = 0;
        }
    }else if(pasos == 1){
    receivedValue = receivedValue +1;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
        if(receivedValue == 255){
            pasos = 2;
            receivedValue = 0;
        }
    }else if(pasos == 2){
    receivedValue = receivedValue +1;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        if(receivedValue == 255){
            pasos = 3;
            receivedValue = 0;
        }
    }else if(pasos == 3){
    receivedValue = receivedValue +1;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
        if(receivedValue == 255){
            pasos = 4;
            receivedValue = 0;
        }
    }else if(pasos == 4){
    receivedValue = receivedValue +1;
       ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6);
        if(receivedValue == 255){
            pasos = 5;            
        }
    }else if(pasos == 5){
    receivedValue = receivedValue -1;
       ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6);
        if(receivedValue == 0){
            pasos = 6;
            receivedValue = 255;
        }
    }else if(pasos == 6){
    receivedValue = receivedValue -1;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);
        if(receivedValue == 0){
            pasos = 7;
            receivedValue = 255;
        }
    }else if(pasos == 7){
    receivedValue = receivedValue -1;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        if(receivedValue == 0){
            pasos = 8;
            receivedValue = 255;
        }
    }else if(pasos == 8){
    receivedValue = receivedValue -1;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
        if(receivedValue == 0){
            pasos = 9;
            receivedValue = 255;
        }
    }else if(pasos == 9){
    receivedValue = receivedValue -1;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
        if(receivedValue == 0){
            pasos = 0;
            receivedValue = 0;
        }
    }
}
void llamada4(TimerHandle_t xTimers) { 
    if(receivedValue <= 255 && pasos == 0){
        receivedValue = receivedValue+1;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5);//verde} 
            if(receivedValue == 256){
                pasos = 1;
            }
    }
 else if(receivedValue > 0 && pasos == 1){
    receivedValue = receivedValue - 1;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5);//verde
            if(receivedValue == 0){
                pasos = 0;
            }         
 }
}
void llamada5(TimerHandle_t xTimers) {
}


void llamade1(TimerHandle_t xTimers){}
void llamade2(TimerHandle_t xTimers) {
     receivedValue = 225;
   if (pasos == 0){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 1; }
    else if(pasos == 1){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 2; }
    else if(pasos == 2){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 3; }
    else if(pasos == 3){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 4; }
    else if(pasos == 4){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 5; }
    else if(pasos == 5){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 6; }
    else if(pasos == 6){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 7; }
    else if(pasos == 7){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 8; }
    else if(pasos == 8){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 9; }
    else if(pasos == 9){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 10; }
    else if(pasos == 10){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 11; }
        else if(pasos == 11){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
            
    pasos = 12; }
    else if(pasos == 12){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
    pasos = 13; }
    else if(pasos == 13){ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
    pasos = 14; }
    else if(pasos == 14){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    pasos = 15; }
    else if(pasos == 15){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    pasos = 16; }
    else if(pasos == 16){ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    pasos = 17; }
        else if(pasos == 17){
    receivedValue = 0;
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);
            
    pasos = 0; }
}
void llamade3(TimerHandle_t xTimers){}
void llamade4(TimerHandle_t xTimers){}
void llamade5(TimerHandle_t xTimers){}


esp_err_t set_timer(int escena1, TickType_t MyInterval){
        TimerCallback function;

    if (escena1 == 1) {
        function = llamada1;
    } else if (escena1 == 2) {
        function = llamada2;
    } else if (escena1 == 3) {
        function = llamada3;
    }else if (escena1 == 4) {
        function = llamada4;   
     }else if (escena1 == 5) {
        function = llamada5;   
     }else {
        // Valor de x inválido, manejar el error según sea necesario
        return ESP_ERR_INVALID_ARG;
    }

    xTimers = xTimerCreate("Timer",       // Just a text name, not used by the kernel.
                          (pdMS_TO_TICKS(MyInterval)),   // The timer period in ticks.
                           pdTRUE,        // The timers will auto-reload themselves when they expire.
                           ( void * )timerId,  // Assign each timer a unique id equal to its array index.
                            function // Each timer calls the same callback when it expires.
                                   );
 
          if( xTimers == NULL )
          {
              // The timer was not created.
          }
          else
          {
            xTimerStart(xTimers, 0);
          }
    return ESP_OK;
 }

esp_err_t set_timer1(int escena2, TickType_t MyInterval1){
        TimerCallback function;

    if (escena2 == 1) {
        function = llamade1;
    } else if (escena2 == 2) {
        function = llamade2;
    } else if (escena2 == 3) {
        function = llamade3;
    }else if (escena2 == 4) {
        function = llamade4;   
     }else if (escena2 == 5) {
        function = llamade5;   
     }else {
        // Valor de x inválido, manejar el error según sea necesario
        return ESP_ERR_INVALID_ARG;
    }
    
    x1Timers = xTimerCreate("Timer",       // Just a text name, not used by the kernel.
                          (pdMS_TO_TICKS(MyInterval1)),   // The timer period in ticks.
                           pdTRUE,        // The timers will auto-reload themselves when they expire.
                           ( void * )timerId1,  // Assign each timer a unique id equal to its array index.
                            function // Each timer calls the same callback when it expires.
                                   );
 
          if( x1Timers == NULL )
          {
              // The timer was not created.
          }
          else
          {
            xTimerStart(x1Timers, 0);
          }
    return ESP_OK;
 }


esp_err_t set_pwm(void){
// Configurar el temporizador para high LEDC
ledc_timer_config_t ledc_timerH = {
        .duty_resolution = LEDC_TIMER_8_BIT, // Resolución de 8 bits
        .freq_hz = 5000, // Frecuencia de 5000 Hz
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timerH);

// Configurar el temporizador para low LEDC
    ledc_timer_config_t ledc_timerL = {
        .duty_resolution = LEDC_TIMER_8_BIT, // Resolución de 8 bits
        .freq_hz = 5000, // Frecuencia de 5000 Hz
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_1
    };
    ledc_timer_config(&ledc_timerL);
    
 // color rojo canal 1
    ledc_channel_config_t channelconfigR0 = {
        .gpio_num = 2,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigR0); 

 // color verde canal 1
    ledc_channel_config_t channelconfigG0 = {
        .gpio_num = 4,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigG0);

 // color azul canal 1
    ledc_channel_config_t channelconfigB0 = {
        .gpio_num = 16,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigB0);

// color rojo canal 2
    ledc_channel_config_t channelconfigR1 = {
        .gpio_num = 17,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_3,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigR1);

 // color verde canal 2
    ledc_channel_config_t channelconfigG1 = {
        .gpio_num = 5,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_4,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigG1);

// color azul canal 2
    ledc_channel_config_t channelconfigB1 = {
        .gpio_num = 23,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_5,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigB1);

// color rojo canal 3
    ledc_channel_config_t channelconfigR2 = {
        .gpio_num = 22,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_6,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigR2);

// color verde canal 3
     ledc_channel_config_t channelconfigG2 = {
        .gpio_num = 19,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_7,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigG2);

// color azul canal 3
    ledc_channel_config_t channelconfigB2 = {
        .gpio_num = 18,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigB2);

// color rojo canal 4
    ledc_channel_config_t channelconfigR3 = {
        .gpio_num = 32,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigR3);

// color verde canal 4
    ledc_channel_config_t channelconfigG3 = {
        .gpio_num = 33,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigG3);

// color azul canal 4
    ledc_channel_config_t channelconfigB3 = {
        .gpio_num = 25,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_3,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigB3);

// color rojo canal 5
ledc_channel_config_t channelconfigR4 = {
        .gpio_num = 26,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_4,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigR4);

// color verde canal 5
    ledc_channel_config_t channelconfigG4 = {
        .gpio_num = 14,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_5,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigG4);

// color azul canal 5
    ledc_channel_config_t channelconfigB4 = {
        .gpio_num = 10,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_6,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
    };
    ledc_channel_config(&channelconfigB4);

    return ESP_OK;
}

static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
    char bda_str[18] = {0};

    switch (event) {
    case ESP_SPP_INIT_EVT:
        if (param->init.status == ESP_SPP_SUCCESS) {
            ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
            esp_spp_start_srv(sec_mask, role_slave, 0, SPP_SERVER_NAME);
        } else {
            ESP_LOGE(SPP_TAG, "ESP_SPP_INIT_EVT status:%d", param->init.status);
        }
        break;
    case ESP_SPP_DISCOVERY_COMP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT");
        break;
    case ESP_SPP_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
        break;
    case ESP_SPP_CLOSE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT status:%d handle:%"PRIu32" close_by_remote:%d", param->close.status,
                 param->close.handle, param->close.async);
        break;
    case ESP_SPP_START_EVT:
        if (param->start.status == ESP_SPP_SUCCESS) {
            ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT handle:%"PRIu32" sec_id:%d scn:%d", param->start.handle, param->start.sec_id,
                     param->start.scn);
            esp_bt_dev_set_device_name(EXAMPLE_DEVICE_NAME);
            esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        } else {
            ESP_LOGE(SPP_TAG, "ESP_SPP_START_EVT status:%d", param->start.status);
        }
        break;
    case ESP_SPP_CL_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
        break;
    case ESP_SPP_DATA_IND_EVT: // entra evento por bt
        int i = 0;// variable para convertir array
        if (i < param->data_ind.len) { //convierto arrays de 2 bits en unnumero entero
            if (param->data_ind.len - i >= 2) {
            // Reconstruir número de 2 bytes
                receivedValue = (param->data_ind.data[i+1] << 8) | param->data_ind.data[i];
                i += 2; // Incrementar el índice en 2 para saltar al siguiente par de bytes
        } else {
            // Número de 1 byte
            receivedValue = param->data_ind.data[i];
            i++; // Incrementar el índice en 1 para saltar al siguiente byte
        }
    }
if(receivedValue < 256){

        if(juego == 1){
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);//rojo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);//rojo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);//rojo
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);//rojo
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//rojo
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);//rojo
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//rojo
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_4);//rojo
            juego = 10;
            printf("%d", receivedValue  );
            printf("rojo\n");
        }
        else if(juego == 2){
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);//verde
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7, receivedValue);//verde
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_7);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);//verde
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_5);//verde
            juego = 20;
            printf("%d", receivedValue  );
            printf("verde\n");
        }
        else if(juego == 3){
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, receivedValue);//azul
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);//azul
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, receivedValue);//azul
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_3);//azul
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6, receivedValue);//azul
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_6);//azul
            
            printf("%d", receivedValue  );
            printf("azul\n");
            juego = 1;
        }
        if(juego == 10){juego = 2;}
        if(juego == 20){juego = 3;}
    }

  else if(receivedValue == 301){
   if(xTimers != NULL) {
    xTimerStop(xTimers, 0);
    xTimerDelete(xTimers, 0);
    } 
    inicioescena();
    myInterval = 20;
    pasos = 0;
    a = 0;
    set_timer(1, myInterval);       
  }
  else if(receivedValue == 302){
   if(xTimers != NULL) {
    xTimerStop(xTimers, 0);
    xTimerDelete(xTimers, 0);
    } 
    inicioescena();
    myInterval = 1000;
    pasos = 0;
    set_timer(2, myInterval);     
  }
  else if(receivedValue == 303){
   if(xTimers != NULL) {
    xTimerStop(xTimers, 0);
    xTimerDelete(xTimers, 0);
    } 
    pasos = 0;
   inicioescena();
    myInterval = 20;
    set_timer(3, myInterval);     
  }
  else if(receivedValue == 304){
        if(xTimers != NULL) {
    xTimerStop(xTimers, 0);
    xTimerDelete(xTimers, 0);
    }
    if(x1Timers != NULL) {
    xTimerStop(x1Timers, 0);
    xTimerDelete(x1Timers, 0);
    }
    inicioescena();
    pasos = 0;
    receivedValue = 0;
    myInterval = 100;
    myInterval1 = 1000;
    set_timer(4, myInterval); 
    set_timer1(2, myInterval1);
    
  }else if(receivedValue == 305){
    printf("holaa");
  }
        break;
    case ESP_SPP_CONG_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT");
        break;
    case ESP_SPP_WRITE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT");
        break;
    case ESP_SPP_SRV_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT status:%d handle:%"PRIu32", rem_bda:[%s]", param->srv_open.status,
                 param->srv_open.handle, bda2str(param->srv_open.rem_bda, bda_str, sizeof(bda_str)));
        gettimeofday(&time_old, NULL);
        break;
    case ESP_SPP_SRV_STOP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_STOP_EVT");
        break;
    case ESP_SPP_UNINIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_UNINIT_EVT");
        break;
    default:
        break;
    }
}

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param){
    char bda_str[18] = {0};

    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT:{
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(SPP_TAG, "authentication success: %s bda:[%s]", param->auth_cmpl.device_name,
                     bda2str(param->auth_cmpl.bda, bda_str, sizeof(bda_str)));
        } else {
            ESP_LOGE(SPP_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }
    case ESP_BT_GAP_PIN_REQ_EVT:{
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
        if (param->pin_req.min_16_digit) {
            ESP_LOGI(SPP_TAG, "Input pin code: 0000 0000 0000 0000");
            esp_bt_pin_code_t pin_code = {0};
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code);
        } else {
            ESP_LOGI(SPP_TAG, "Input pin code: 1234");
            esp_bt_pin_code_t pin_code;
            pin_code[0] = '1';
            pin_code[1] = '2';
            pin_code[2] = '3';
            pin_code[3] = '4';
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
        }
        break;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %"PRIu32, param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%"PRIu32, param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    case ESP_BT_GAP_MODE_CHG_EVT:
        ESP_LOGI(SPP_TAG, "ESP_BT_GAP_MODE_CHG_EVT mode:%d bda:[%s]", param->mode_chg.mode,
                 bda2str(param->mode_chg.bda, bda_str, sizeof(bda_str)));
        break;

    default: {
        ESP_LOGI(SPP_TAG, "event: %d", event);
        break;
    }
    }
    return;
}

void app_main(void){
    if(inicio_programa == 0){
    set_pwm();
    inicio_programa = 1;
    myInterval = 10;
    set_timer(1, myInterval);
    }
    char bda_str[18] = {0};
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s gap register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    esp_spp_cfg_t bt_spp_cfg = {
        .mode = esp_spp_mode,
        .enable_l2cap_ertm = esp_spp_enable_l2cap_ertm,
        .tx_buffer_size = 0, /* Only used for ESP_SPP_MODE_VFS mode */
    };
    if ((ret = esp_spp_enhanced_init(&bt_spp_cfg)) != ESP_OK) {
        ESP_LOGE(SPP_TAG, "%s spp init failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    /* Set default parameters for Secure Simple Pairing */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
#endif

    /*
     * Set default parameters for Legacy Pairing
     * Use variable pin, input pin code when pairing
     */
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_VARIABLE;
    esp_bt_pin_code_t pin_code;
    esp_bt_gap_set_pin(pin_type, 0, pin_code);

    ESP_LOGI(SPP_TAG, "Own address:[%s]", bda2str((uint8_t *)esp_bt_dev_get_address(), bda_str, sizeof(bda_str)));
}
