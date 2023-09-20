// Librería para la comunicación I2C y la RTClib
#include <Wire.h>
#include <RTClib.h>

// Declaramos un RTC DS3231
RTC_DS3231 rtc;

void setup () {
 Serial.begin(9600);

 delay(3000);

pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);



 // Comprobamos si tenemos el RTC conectado
 if (! rtc.begin()) {
   Serial.print("REEMPLAZAR BATERIA");
   digitalWrite(4,LOW);
   digitalWrite(3,HIGH);
   while (1);
 }

 digitalWrite(4,HIGH);

 // Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
 // Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  //int horas[6]={7,9,9,10,11,12};
  //int minutos[6]={40,40,50,50,0,0};

}

void loop () {
 DateTime now = rtc.now();
  int i = 0;
  int horarios = 6;
    int horas[6]={7,9,9,10,11,11};
  int minutos[6]={40,40,50,50,0,24};
  String mensajes[6]={"ENTRADA TM","1ER RECREO","FIN 1ER RECREO","2DO RECREO","FIN 2DO RECREO","SALIDA TM"};
    for(i=0;i<horarios;i++) {
      if((horas[i]==now.hour())&&(minutos[i]==now.minute())) {
         Serial.print(mensajes[i]);
          digitalWrite(2,HIGH);
          digitalWrite(5,HIGH);
          delay(20000);
          Serial.print("");
          digitalWrite(2,LOW);
          digitalWrite(5,LOW);
          delay(60000);
      }
    }
   
   delay(10000);
}
