//Made By Mau

//#include <avr/interrupt.h>
#include <SoftwareSerial.h>

//variables
int BotonActual;
int RondasGanadas = 0;
int RondasGanadasEEPROM; //Dirección de memoria
int LED = 9;
int Buzzer = 8;

//comunicación serial con el módulo
SoftwareSerial HC06(12,13);

//_______________________________________________________________________

void setup()
{
  //Configuración base
  	
  	//Comunicación serial.
    Serial.begin(9600); //Puerto serial
  	HC06.begin(9600); //comunicación con el módulo bluetooth
  	delay(1000);
  	HC06.print("AT+NAMEPIANO");
  
  	//Sensores
    pinMode(7, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);

    //leds
  	pinMode(LED, OUTPUT);

    //buzzer
  	pinMode(Buzzer, OUTPUT);
  
    //Configuración  inicial de las luces
  	digitalWrite(LED, LOW);

  //Comunicación serial para el móduglo bluetooth
  HC06.begin(9600);
  
    delay(1000);
}

//_______________________________________________________________________

//lógica de juego
void loop()
{ 

	//botones
  	Serial.print("Entradas:");
    Serial.print(digitalRead(7));
    Serial.print("|");
    Serial.print(digitalRead(6));
    Serial.print("|");
    Serial.print(digitalRead(5));
  	Serial.print("|");
    Serial.println(digitalRead(4));
  
  	//variables
 	  Serial.print("Boton presionado: ");
  	Serial.println(BotonActual);
  
  	//Detección de teclas
	if (digitalRead(7) == 0) {
      
      //Muestreo
      BotonActual = 1;
      digitalWrite(LED, 1);
      
      //enviar el botón presionado por bluetooth
      Serial.println("{\"B4\":1}");
      HC06.println("{\"B4\":1}");
      //delay(100);
   }
  
	if (digitalRead(6) == 0) {
      
      BotonActual = 2;
      digitalWrite(LED, 50);

      //enviar el botón presionado por bluetooth
      Serial.println("{\"B3\":1}");
      HC06.println("{\"B3\":1}");
      //delay(150);
   }
  
	if (digitalRead(5) == 0) {
      
      BotonActual = 3;
      digitalWrite(LED, 127);
      
      //enviar el botón presionado por bluetooth
      Serial.println("{\"B2\":1}");
      HC06.println("{\"B2\":1}");
      //delay(100);
   }
  
 	if (digitalRead(4) == 0) {
      
      BotonActual = 4;
      digitalWrite(LED, HIGH);
      
      //enviar el botón presionado por bluetooth
      Serial.println("{\"B1\":1}");
      HC06.println("{\"B1\":1}");
      //delay(100);
   }

    //indicador de inicio de juego
    	if (digitalRead(3) == 0 || digitalRead(2) == 0) {

      //inicio
      delay(100);
      tone(Buzzer,1000,250);
      delay(250);
      tone(Buzzer,2500,500);

      //secuencia rara de luces
      digitalWrite(LED, HIGH);      delay(100);      digitalWrite(LED, LOW);      delay(100);
      digitalWrite(LED, HIGH);      delay(100);      digitalWrite(LED, LOW);      delay(100);
      digitalWrite(LED, HIGH);      delay(250);      digitalWrite(LED, LOW);      delay(250);
      digitalWrite(LED, HIGH);      delay(250);      digitalWrite(LED, LOW);      delay(250);
      digitalWrite(LED, HIGH);      delay(250);      digitalWrite(LED, LOW);

      //enviar el botón presionado por bluetooth
      Serial.println("Inicio");
      HC06.println("{\"B1\":1}");
      
      delay(100);
   }

      digitalWrite(LED, LOW);
      noTone(Buzzer);
}
