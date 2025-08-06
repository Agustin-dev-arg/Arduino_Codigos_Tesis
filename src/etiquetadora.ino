#include <Arduino.h>
//Definicion de pines y variables
int Sensor_Etiqueta = 8;
//ED = Entrada Digital ; SD = Salida Digital

int ED_Start = 2; //Pin de entrada digital para iniciar el proceso
int ED_Stop = 3; //Pin de entrada digital para detener el proceso
int ED_Emergencia = 4; //Pin de entrada digital para detener el proceso en caso de emergencia
int ED_reset_contador = 5; //Pin de entrada digital para resetear contador de botellas que fueron etiquetadas
int SD_Led_Start = 6; //Pin de salida digital para activar un led que indica que el proceso ha iniciado
int SD_Led_Stop = 7; //Pin de salida digital para activar un led que indica que el proceso ha detenido
int SD_Led_Emergencia = 8; //Pin de salida digital para activar un led que indica que el proceso ha detenido por emergencia
int SD_Led_Reset = 9; //Pin de salida digital para activar un led que indica que el contador debe ser reseteado
int SD_Cinta = 10; //Pin de salida digital para activar el rele del pwm que acciona la cinta transportadora
int SD_Etiquetadora = 11; //Pin de salida digital para activar el rele del pwm que acciona el motor de la etiquetadora
int ED_FinalCarrera_Cinta = 12; //si esta presionado quiere decir que una botella ha llegado al final de la cinta transportadora
// para la simulacion se usara un switch.
int ED_Sensor_De_Etiqueta= 13; //Pin de entrada digital que detecta el gap de etiqueta.
int AI_Ultrasonido = A0; //Pin de entrada analogica para el sensor de ultrasonido reemplazado por un final de carrera que tomara una señal DIGITAL
//para simular el conteo de botellas.


void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    // Configurar pines de entrada y salida
    pinMode(ED_Start, INPUT);
    pinMode(ED_Stop, INPUT); 
    pinMode(ED_Emergencia, INPUT); 
    pinMode(ED_reset_contador, INPUT); 
    pinMode(SD_Led_Start, OUTPUT);
    pinMode(SD_Led_Stop, OUTPUT);
    pinMode(SD_Led_Emergencia, OUTPUT);
    pinMode(SD_Led_Reset, OUTPUT);
    pinMode(SD_Cinta, OUTPUT);
    pinMode(SD_Etiquetadora, OUTPUT);   
    pinMode(ED_FinalCarrera_Cinta, INPUT);
    pinMode(ED_Sensor_De_Etiqueta, INPUT);
    pinMode(AI_Ultrasonido, INPUT);
}

void loop() {

}
