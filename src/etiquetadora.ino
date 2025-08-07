#include <Arduino.h>
//Definicion de pines y variables
int Sensor_Etiqueta = 8;
//ED = Entrada Digital ; SD = Salida Digital

int ED_Start = 2; //Pin de entrada digital para reanudar el proceso cuando es detenido
int ED_Stop = 3; //Pin de entrada digital para detener el proceso
int ED_reset_contador = 5; //Pin de entrada digital para resetear contador de botellas que fueron etiquetadas
int SD_Led_Start = 6; //Pin de salida digital para activar un led que indica que el proceso ha iniciado
int SD_Led_Stop = 7; //Pin de salida digital para activar un led que indica que el proceso ha detenido
int SD_Led_Reset = 9; //Pin de salida digital para activar un led que indica que el contador debe ser reseteado
int SD_Cinta = 10; //Pin de salida digital para activar el rele del pwm que acciona la cinta transportadora
int SD_Etiquetadora = 11; //Pin de salida digital para activar el rele del pwm que acciona el motor de la etiquetadora
int ED_FinalCarrera_Cinta = 12; //si esta presionado quiere decir que una botella ha llegado al final de la cinta transportadora
// para la simulacion se usara un switch.
int ED_Sensor_De_Etiqueta= 13; //Pin de entrada digital que detecta el gap de etiqueta.
int AI_Ultrasonido = A0; //Pin de entrada analogica para el sensor de ultrasonido reemplazado por un final de carrera que tomara una señal DIGITAL
//para simular el conteo de botellas.

//Definicion de variables
int constante_ValorPin_ED_Stop = 0; //Constante para almacenar el valor del pin ED_Stop
void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
    // Configurar pines de entrada y salida
    pinMode(ED_Start, INPUT);
    pinMode(ED_Stop, INPUT); 
    pinMode(ED_reset_contador, INPUT); 
    pinMode(SD_Led_Start, OUTPUT);
    pinMode(SD_Led_Stop, OUTPUT);
    pinMode(SD_Led_Reset, OUTPUT);
    pinMode(SD_Cinta, OUTPUT);
    pinMode(SD_Etiquetadora, OUTPUT);   
    pinMode(ED_FinalCarrera_Cinta, INPUT);
    pinMode(ED_Sensor_De_Etiqueta, INPUT);
    pinMode(AI_Ultrasonido, INPUT);
    Lectura_Valor_De_Entradas();
}

void loop() {
    //Tener en cuenta que STOP arranca en 0 por defecto. Quiere decir que el proceso se ejecuta con normalidad

    if(constante_ValorPin_ED_Stop == LOW) {
        // Iniciar el proceso
        Serial.println("Proceso Iniciado");
    }else{
        // Detener el proceso

        if(digitalRead(ED_Stop) == LOW){ //Si el pin ED_Stop es LOW quiere decir que el boton de paro no esta presionado
            //reanudar el proceso
            constante_ValorPin_ED_Stop = LOW; 
            Serial.println("Proceso Reanudado");
            Funcion_Leds_Start(); //Encender el led de inicio
            //Probar 2 opciones: a) Dejar los contadores con el valor que tenian antes de detenerse
            //b) Resetear los contadores a 0
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
    Serial.print("ED_Start: ");
    Serial.println(digitalRead(ED_Start));
    Serial.print("ED_Stop: ");
    Serial.println(digitalRead(ED_Stop));
    Serial.print("ED_reset_contador: ");
    Serial.println(digitalRead(ED_reset_contador));
    Serial.print("ED_FinalCarrera_Cinta: ");
    Serial.println(digitalRead(ED_FinalCarrera_Cinta));
    Serial.print("ED_Sensor_De_Etiqueta: ");
    Serial.println(digitalRead(ED_Sensor_De_Etiqueta));
    Serial.print("AI_Ultrasonido: ");
    Serial.println(analogRead(AI_Ultrasonido));
}
    
//Funcion_Leds_Stop de funcionamiento y encender los leds de stop:
void Funcion_Stop(){
    digitalWrite(SD_Led_Start, LOW);
    digitalWrite(SD_Led_Reset, LOW);
    digitalWrite(SD_Led_Stop, HIGH);
    digitalWrite(SD_Cinta, LOW);
    digitalWrite(SD_Etiquetadora, LOW);
    constante_ValorPin_ED_Stop = HIGH; //Actualizar el valor del pin ED_Stop a HIGH para indicar que el proceso esta detenido
    Serial.println("Proceso Detenido");
}

//Funcion_Leds_Start
void Funcion_Leds_Start(){
    digitalWrite(SD_Led_Start, HIGH);
    digitalWrite(SD_Led_Reset, LOW);
    digitalWrite(SD_Led_Stop, LOW);
}