//#include <AsyncTCP.h>
//#include <WiFi.h>
//#include <ESPAsyncWebServer.h>
//#include <SPI.h>
//#include "SPIFFS.h"
//#include <ArduinoJson.h>

//Botones de ESP32

//#define top  5 // 5
//#define center 21 // 18
//#define bottom 19 // 19

// Botones de arduino

#define top1  2 // 5 rojo
#define center1 3 // 21 verde 
#define bottom1 4 // 19 blanco

/*librerias del documento de prueba*/
#include <MaxMatrix.h>      //libreria display piso
#include <avr/pgmspace.h>   //libreria display piso

#include <Wire.h>           //libreria Comunicacion I2C

#include "LedControlMS.h"   //libreria display direccion

//Matrix de direcciones flechas subida y bajada
byte Subir[] = {
B00011000,
B00111100,
B01111110,
B11011011,
B10011001,
B00011000,
B00011000,
B00011000};
 
byte Bajar[] = {
B00011000,
B00011000,
B00011000,
B10011001,
B11011011,
B01111110,
B00111100,
B00011000};

//Matrix de caracteres
PROGMEM unsigned char const CH[] = {
5, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
4, 8, B00100110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

//Declaracion de variables matrix de piso
int data = 10;    // DIN pin del modulo MAX7219
int load = 11;    // CS pin del modulo MAX7219
int clock = 12;  // CLK pin del modulo MAX7219 
int maxInUse = 1; //Cambie este valor dependiendo del numero de matrices que use
MaxMatrix m(data, load, clock, maxInUse); // Define el modulo
byte buffer[10];

//Declaracion de variables matrix de direccion
LedControl lc=LedControl(7,9,8,1); // Los numeros se refieren a que pin de ARDUINO tienes en cada uno de los terminales


bool bandera_top = false;
bool bandera_center = false;
bool bandera_bottom = false;
int piso = 1;
bool ON;
bool OA;
bool OB;
bool UP = false;
bool DN = false;
int direccion = ""; 
int estadoAnterior;
int estadoAnterior1;
  int top = 0;
int center = 0;
int bottom = 0;

bool ledState = 0;
//const int ledPin = 2;
//int piso;
float temperatura;
int contador = 0;
int max_count = 5;
int piso_anterior;
int diferencia;


void setup(){
 // Serial port for debugging purposes
//  Serial.begin(115200);
  Serial.println("Magsafe");
  pinMode(top1,INPUT);
  pinMode(center1,INPUT);
  pinMode(bottom1,INPUT);
/*  digitalWrite(top,LOW);
  digitalWrite(center,LOW);
  digitalWrite(bottom,LOW);*/



 // SPI.begin();
//  pinMode(ledPin, OUTPUT);
 // digitalWrite(ledPin, LOW);

  //Declaracion de variables matrix de piso
  /*pinMode(8,OUTPUT);       //Conexion a DIN
  pinMode(9,OUTPUT);       //Conexion a CS
  pinMode(10,OUTPUT);      //Conexion a CLK*/
  m.init();               // inicializa el modulo
  m.setIntensity(4);      // intencidad de los puntos de la matriz, entre 1-5

//Declaracion de variables Comunicacion I2C
 // Wire.begin(8);                // join i2c bus with address #8
  //Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output

//Declaracion de variables matrix de direccion
  lc.shutdown(0,false);
  lc.setIntensity(0,8);// La valores estan entre 1 y 15 
  lc.clearDisplay(0);
  
}


// Funcion para imprimir numero de piso de 1 digito
void printString(char* s) // Imprime cadena
{
  int col = 1;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}

// Funcion para imprimir numero de piso de 2 digitos
void printString2(char* s) // Imprime cadena
{
  int col = 1;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}


// Funcion para imprimir direccion de la flecha
void Representar(byte *Datos) 
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setColumn(0,i,Datos[7-i]);
  }
 // delay(retardo);
}


//Funcion para saber que numero y direccion se debe imprimir
void caso(int x,char c){
  Serial.print("Los valores son, piso: ");
  Serial.println(x,c);
  switch (x){
      case -1:
      if (x==0){
        printString2("   ");
        printString("5");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
     break;
    case 0:
      if (x==0){
        printString2("   ");
        printString("S1");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
     break;
    case 1:
      if (x==1){
        Serial.print("Ascensor en piso 1");
        printString2("   ");
        printString("1");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
    case 2:
      if (x==2){
        printString2("   ");
        printString("2");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
    case 3:
      if (x==3){
        printString2("   ");
        printString("3");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
    case 4:
      if (x==4){
        printString2("   ");
        printString("4");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
    case 5:
      if (x==5){
        printString2("   ");
        printString("5");
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
    case 6:
      if (x==6){
        printString2("   ");
        printString("5");
        piso=5;
        if (c=='U')Representar(Subir);
          else if (c=='D')Representar(Bajar);
          else if (c=='N')lc.clearDisplay(0);
      }
    break;
  }
}

void loop() {

top = digitalRead(top1);
center = digitalRead(center1);
bottom = digitalRead(bottom1);

/*
if (top == 1){
  piso++;
  direccion ='U';
  caso(piso,direccion);
}
*/


//SENSOR TOP  ----------------------------------------------------
//Sensor de arriba cuando el iman se sale del area de los sensores
 if(bandera_center == false){
//    Serial.println(digitalRead(center));
    if(top == 0 && ON == true && OA == false){
        ON = false;
        DN = true;     
        direccion = 'D';//"U","N"
        bandera_center = true;
        Serial.println("------------------------->");
        Serial.println("Bajando"); 
        piso--;  
        if(piso < 0){
          piso=0;
        }
       // caso(int(piso),char(direccion));      
       caso(piso,direccion);
       while (bandera_center == true){
        top = digitalRead(top1);
         if (top == 1){
          //  Serial.println(digitalRead(top));
           bandera_center = false;
         }
         }
  }
 }
 
// Funcion de bajada mientras entra al area del iman
     if(bandera_top == false){
    if (top == 0 && UP == true){  
    bandera_top = true;
    direccion = 'U';
    Serial.println("Subiendo y entrando al area del iman");
    caso(piso,direccion);
//    Serial.println(piso);
    Serial.println();
   while (bandera_top == true){
    top = digitalRead(top1);
     if (top == 1){
       UP = false;
       OA = true;
       OB = false;
       bandera_top = false;
       ON = true;
     }
     }
   }
  }

  
//SENSOR CENTER ----------------------------------------------------
if(bandera_bottom == false){
//  ws.textAll(piso);
  if (center == 0){
    bandera_bottom = true;
    OA = false;
    OB = true;
    direccion = 'N';
    Serial.println("------------------------->");
    Serial.println("Ascensor nivelado");
    Serial.print("PISO: ");
    Serial.println(piso);
    Serial.println(); 
  //  printString("2");
  //  Representar(Subir,1000);
    caso(piso,direccion);
   while (bandera_bottom == true){
   center = digitalRead(center1);
     if (center == 1){
      // Serial.println("Saliendo de center");
       bandera_bottom = false;
        ON = true;
      }
    }
  }
}

//SENSOR BOTTOM ----------------------------------------------------
   if(bandera_top == false){
 //   Serial.println(digitalRead(top));
    if (bottom == 0 && ON == true && OB == true){
    bandera_top = true;
    ON = false;
    UP = true;
    direccion = 'U';
    Serial.println("------------------------->");
    Serial.println("Subiendo");  
    piso++; 
   caso(piso,direccion);
   while (bandera_top == true){
    bottom = digitalRead(bottom1);
     if (bottom == 1){
     //   Serial.println(digitalRead(bottom));
       bandera_top = false;
     }
     }
   }
  }
  

//Sensor de arriba cuando el sensor entra al area del iman
  if(bandera_center == false){
//    Serial.println(digitalRead(center));
    if(bottom == 0 && DN == true){
        direccion = 'D';
        bandera_center = true;
        Serial.println("Bajando y entrando al area del iman"); 
        if(piso < 0){
          piso=0;
        }
        caso(piso,direccion);
//        Serial.println(piso); 
        Serial.println();
       while (bandera_center == true){
        bottom = digitalRead(bottom1);
         if (bottom == 1){
           bandera_center = false;
           OA = true;
           OB = false;
           DN = false;
           ON = true;
         }
         }
  }
 }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*  
//SENSOR TOP  ----------------------------------------------------
//Sensor de arriba cuando el sensor se sale del area del iman
 if(bandera_center == false){
//    Serial.println(digitalRead(center));
    if(digitalRead(top) == 0 && ON == true && OA == false){
        ON = false;
        DN = true;     
        direccion = "D";//"U","N"
        bandera_center = true;
        Serial.println("------------------------->");
        Serial.println("Bajando"); 
        piso--;  
        caso(piso,direccion);
        
       while (bandera_center == true){
         if (digitalRead(top) ==  1){
          //  Serial.println(digitalRead(top));
           bandera_center = false;
         }
         }
  }
 }
 
// Funcion de bajada mientras entra al area del iman
     if(bandera_top == false){
    if (digitalRead(top) == 0 && UP == true){  
    bandera_top = true;
    direccion = "U";
    Serial.println("Subiendo y entrando al area del iman");
    caso(piso,direccion);
//    Serial.println(piso);
    Serial.println();
   while (bandera_top == true){
     if (digitalRead(top) ==  1){
       UP = false;
       OA = true;
       OB = false;
       bandera_top = false;
       ON = true;
     }
     }
   }
  }
//SENSOR CENTER ----------------------------------------------------
if(bandera_bottom == false){
//  ws.textAll(piso);
  if (digitalRead(center) == 0){
    bandera_bottom = true;
    OA = false;
    OB = true;
    direccion = "N";
    Serial.println("------------------------->");
    Serial.println("Ascensor nivelado");
    Serial.print("PISO: ");
    Serial.println(piso);
    Serial.println();  
    caso(piso,direccion);
   while (bandera_bottom == true){
     if (digitalRead(center) == 1){
   //     Serial.println(digitalRead(center));
       bandera_bottom = false;
        ON = true;
      }
    }
  }
}

//SENSOR BOTTOM ----------------------------------------------------
   if(bandera_top == false){
 //   Serial.println(digitalRead(top));
    if (digitalRead(bottom) == 0 && ON == true && OB == true){
    bandera_top = true;
    ON = false;
    UP = true;
    direccion = "U";
    Serial.println("------------------------->");
    Serial.println("Subiendo");  
    piso++; 
   caso(piso,direccion);
   while (bandera_top == true){
     if (digitalRead(bottom) == 1){
     //   Serial.println(digitalRead(bottom));
       bandera_top = false;
     }
     }
   }
  }
  

//Sensor de arriba cuando el sensor entra al area del iman
  if(bandera_center == false){
//    Serial.println(digitalRead(center));
    if(digitalRead(bottom) == 0 && DN == true){
        direccion = "D";
        bandera_center = true;
        Serial.println("Bajando y entrando al area del iman"); 
        caso(piso,direccion);
//        Serial.println(piso); 
        Serial.println();
       while (bandera_center == true){
         if (digitalRead(bottom) ==  1){
           bandera_center = false;
           OA = true;
           OB = false;
           DN = false;
           ON = true;
         }
         }
  }
 }
*/
 
  
}



  
