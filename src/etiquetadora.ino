#include <Arduino.h>
//Definicion de pines

//ED = Entrada Digital ; SD = Salida Digital
int ED_Start = 2; //Pin de entrada digital para reanudar el proceso cuando es detenido
int ED_Stop = 3; //Pin de entrada digital para detener el proceso
int SD_Rele_Cinta = 4; //Pin de salida digital para activar el rele del pwm que acciona la cinta transportadora
int SD_Rele_Etiquetadora = 5; //Pin de salida digital para activar el rele del pwm que acciona el motor de la etiquetadora
int SD_Led_Start = 6; //Pin de salida digital para activar un led que indica que el proceso ha iniciado
int SD_Led_Stop = 7; //Pin de salida digital para activar un led que indica que el proceso ha detenido
//pines de LED van directamente a mostrarse por interfaz web. Por ahora los dejamos hasta configurar la interfaz
int ED_Sensor_De_Etiqueta= 8; //Pin de entrada digital que detecta el gap de etiqueta.

//Error el ultrasonido utiliza 2 pines digitales, uno para trigger y otro para echo.
//Quedarian 6 pines digitales libres que corresponden a 3 sensores de ultrasonido. 
//Para la simulación se usara S1 con sensor ultrasonido, S2 y S3 seran pulsadores.
//Donde SU1 = Sensor Ultrasonido 1 encargado de detectar presencia de la botella y sera utilizado para permitir el despegue de la primer etiqueta, SU2 = Sensor Ultrasonido 2, 
//SU3 = Sensor Ultrasonido 3 utilizado para determinar cuando la botella fue etiquetada y además evitar la acumulacion de botellas en la cinta transportadora.

int SensorUS_S1 = 9; //Pin de entrada digital para el boton que representa S1
int SensorUS_S2 = 10; //Pin de entrada digital para el boton que representa S2
int SensorUS_S3 = 11; //Pin de entrada digital para el boton que representa S3


//Protocolo de comunicacion HTTP y Asincronico
//Se deberá coordinar esp32 con django y django con el frotend actuando django de intermediario.
//1. Se hará una prueba, creando un programa  en el que se determine si la esp32 esta conectada o no.
//2. Se creara un programa que permita enviar datos desde la esp32 a django y viceversa.



//Definicion de variables
int constante_ValorPin_ED_Stop = 0; //Constante para almacenar el valor del pin ED_Stop
void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    // Configurar pines de entrada y salida
    pinMode(ED_Start, INPUT);
    pinMode(ED_Stop, INPUT); 
    pinMode(SD_Led_Start, OUTPUT);
    pinMode(SD_Led_Stop, OUTPUT);
    pinMode(SD_Rele_Cinta, OUTPUT);
    pinMode(SD_Rele_Etiquetadora, OUTPUT);
    pinMode(ED_Sensor_De_Etiqueta, INPUT);
    pinMode(SensorUS_S1, INPUT);
    pinMode(SensorUS_S2, INPUT);
    pinMode(SensorUS_S3, INPUT);
    Lectura_Valor_De_Entradas();
    
}

void loop() {
    //Tener en cuenta que STOP arranca en 0 por defecto. Quiere decir que el proceso se ejecuta con normalidad

    if(constante_ValorPin_ED_Stop == LOW && digitalRead(ED_Stop) == LOW){
        // Iniciar el proceso
        delay(2000); // Esperar .1 segundo antes de iniciar el proceso
        Serial.println("Proceso Iniciado");
        Lectura_Valor_De_Entradas();
        Funcion_Start();
    }else{
        // Detener el proceso

        if(digitalRead(ED_Stop) == LOW && digitalRead(ED_Start) == HIGH){ //Si el pin ED_Stop es LOW quiere decir que el boton de paro no esta presionado
            //reanudar el proceso
            constante_ValorPin_ED_Stop = LOW; 
            Serial.println("Proceso Reanudado");
            Funcion_Start(); //Encender el led de inicio
            digitalWrite(SD_Rele_Cinta, HIGH); //Encender la cinta transportadora

            if(SensorUS_S1 == HIGH){
                // Si S1 está activo, permitir el despegue de la etiqueta
                //encendemos el motor de la etiquetadora HASTA que detecta el GAP de la etiqueta
                while(ED_Sensor_De_Etiqueta == HIGH) { //mientras sea HIGH quiere decir que esta detectando la etiqueta.
                    digitalWrite(SD_Rele_Etiquetadora, HIGH); //Encender el motor de la etiquetadora
                }
            }
        }else{
            //Si el pin ED_Stop es HIGH quiere decir que el boton de paro esta presionado
            //Detener el proceso
            Funcion_Stop();
        }

    }
}

//Funcion_Lectura_Valor_De_Entradas para conocer el estado inicial de las entradas digitales y analogicas
//y mostrarlo por el puerto serie
void Lectura_Valor_De_Entradas(){
    Serial.println("Estado Inicial de las Entradas:");
    //Las lecturas de ED_Start y ED_Stop van a trabajar en conjunto a la interfaz web, permitiando al usuario
    //iniciar o terminar el proceso de manera fisica o por software.
    Serial.print("ED_Start: ");
    Serial.println(digitalRead(ED_Start));
    Serial.print("ED_Stop: ");
    Serial.println(digitalRead(ED_Stop));
    Serial.print("ED_Sensor_De_Etiqueta: ");
    Serial.println(digitalRead(ED_Sensor_De_Etiqueta));
}
    
//Funcion_Leds_Stop de funcionamiento y encender los leds de stop:
void Funcion_Stop(){
    //Los leds start y stop se deberian ver reflejados en la interfaz web
    digitalWrite(SD_Led_Start, LOW);
    digitalWrite(SD_Led_Stop, HIGH);
    digitalWrite(SD_Rele_Cinta, LOW);
    digitalWrite(SD_Rele_Etiquetadora, LOW);
    constante_ValorPin_ED_Stop = HIGH; //Actualizar el valor del pin ED_Stop a HIGH para indicar que el proceso esta detenido
    Serial.println("Proceso Detenido");
}

//Funcion_Leds_Start
void Funcion_Start(){
    digitalWrite(SD_Led_Start, HIGH);
    digitalWrite(SD_Led_Stop, LOW);

}