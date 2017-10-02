///////////////////
// PINES MOTORES //
///////////////////
#define MOTOR_IZQUIERDO_ADELANTE PB12
#define MOTOR_IZQUIERDO_ATRAS PB13
#define MOTOR_IZQUIERDO_PWM PB1
#define MOTOR_DERECHO_ADELANTE PB14
#define MOTOR_DERECHO_ATRAS PB15
#define MOTOR_DERECHO_PWM PA8
#define MOTOR_RUN PB10
#define MOTOR_DERECHO_ENCODER PB11
#define MOTOR_IZQUIERDO_ENCODER PB9
#define MOTOR_VENTILADOR PB8

//////////////////
// PINES SWITCH //
//////////////////
#define SW_1 PA11
#define SW_2 PA12

//////////////////
// PINES BTN/LED //
//////////////////
#define BTN PB5
#define LED PB0

////////////////////
// PINES SENSORES //
////////////////////
#define SENSOR_1 PA6
#define SENSOR_2 PA5
#define SENSOR_3 PA4
#define SENSOR_4 PA3
#define SENSOR_5 PA2
#define SENSOR_6 PA1
#define SENSOR_7 PA0
#define SENSOR_IZQUIERDO_XSLEEP PA15
#define SENSOR_FRONTAL_XSLEEP PB4
#define SENSOR_DERECHO_XSLEEP PB3

//////////////////
// SENSORES I2C //
//////////////////
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor_izquierdo, sensor_frontal, sensor_derecho;

//////////////////////
// SENSORES QRE1113 //
//////////////////////
const short NUM_SENSORS =  7;
short sensorPins[] = {SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7};

////////////////////////
//VARIABLES TEST PINS //
////////////////////////
const int debug_time = 500;
bool led_state = false;

volatile long ticks_derecho = 0;
volatile long ticks_izquierdo = 0;

void setup() {
  // Inicializa todos los componentes
  init_all();

  delay(2000);
}

void loop() {
  if(millis()%debug_time==0){
    // Sensores láser
    Serial.println("VL53L0X:");
    Serial.print(sensor_izquierdo.readRangeSingleMillimeters());
    Serial.println("\t");
    Serial.print(sensor_frontal.readRangeSingleMillimeters());
    Serial.println("\t");
    Serial.print(sensor_derecho.readRangeSingleMillimeters());
    Serial.print("\n\n");

    // // Sensores IR
    Serial.println("QRE1113:");
    for (byte sensor = 0; sensor < NUM_SENSORS; sensor++) {
      Serial.print(analogRead(sensorPins[sensor]));
      if(sensor != (NUM_SENSORS-1)){
        Serial.println("\t");
      }
    }
    Serial.print("\n\n");

    // Estado de botón y swtich
    Serial.print("BTN: ");
    Serial.println(digitalRead(BTN));
    Serial.print("SW_1: ");
    Serial.println(digitalRead(SW_1));
    Serial.print("SW_2: ");
    Serial.println(digitalRead(SW_2));
    Serial.print("\n");


    // Estado de botón y swtich
    Serial.print("ENC IZ: ");
    Serial.println(ticks_izquierdo);
    Serial.print("ENC DE: ");
    Serial.println(ticks_derecho);

    // Cambio estado led;
    led_state = !led_state;
    digitalWrite(LED, led_state);

    Serial.println("============================================================");
  }
}


void encoder_derecho(){
  ticks_derecho++;
}

void encoder_izquierdo(){
  ticks_izquierdo++;
}
