// Librería para la comunicación I2C y la RTClib
#include <Wire.h>
#include <RTClib.h>

// Declaramos un RTC DS3231
RTC_DS3231 rtc;

#define RELAY 2
#define LED_PILA 3
#define ZUMBADOR 4
#define LED_TIMBRE 5
#define PANICO 6


void setup () {
    Serial.begin(9600);

    delay(3000);

    pinMode(RELAY,OUTPUT);
    pinMode(LED_PILA,OUTPUT);
    pinMode(ZUMBADOR,OUTPUT);
    pinMode(LED_TIMBRE,OUTPUT);
    pinMode(PANICO,INPUT);


    // Comprobamos si tenemos el RTC conectado
    if (! rtc.begin()) {
      reemplazarPila();

    }


 // Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
 // Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}

void loop () {
    DateTime now = rtc.now();

    String horario = String(now.hour(), DEC) + ":" + String(now.minute(),DEC);
    
    //*******ESTO ES POR SI NO ANDA EL RELOJ*******
    if(!now.isValid()) {
      Serial.println("FALLA EN MODULO RTC");
      tone(ZUMBADOR, 880);
      delay(100);
      noTone(ZUMBADOR);

    }
    //*********************************************

    //**********TURNO MAÑANA FRENTE**********
    if(horario=="16:58"){
        Serial.println("HORARIO DE PRUEBA");
        tocarTimbre();
    }
              
    //******************************************
    delay(10000);
}

void tocarTimbre() {

    digitalWrite(RELAY,HIGH);
    digitalWrite(LED_TIMBRE,HIGH);
    tone(ZUMBADOR, 880);
    delay(500);
    noTone(ZUMBADOR);
    delay(29500);
    digitalWrite(RELAY,LOW);
    digitalWrite(LED_TIMBRE,LOW);
    noTone(ZUMBADOR);
    delay(40000);

}

void reemplazarPila() {
  digitalWrite(LED_PILA,HIGH);
  Serial.println("REEMPLAZAR PILA");
  while(1) {
      tone(ZUMBADOR, 880);
      delay(250);
      noTone(ZUMBADOR);
      delay(250);

  }

}

