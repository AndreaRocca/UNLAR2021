#include "LedControl.h" 
//
// Cableado de led 8x8
//
// Los numeros se refieren a que pin de ARDUINO tienes en cada uno de los terminales
// TCS3200:  5 para el DIN, 0 para el CLK, 4 para el CS y el 1 se refiere a la asignacion de la matriz 
LedControl lc=LedControl(7,5,6,1); 
//
// Cableado de TCS3200 a Arduino
//
#define S0 9 // TCS3200 13
#define S1 11 // TCS3200 15
#define S2 8 // TCS3200 12
#define S3 10 // TCS3200 14
#define salidaSensor 12 // TCS3200 16

// Para guardar las frecuencias de los fotodiodos
int frecuenciaRojo = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int retardo= 500;
// matriz dibujo
//Corazón pequeño
 
byte Corazon_datos[] = {
B00000000,
B00011000,
B00111100,
B01111110,
B11111111,
B11111111,
B01100110,
B00000000};

byte Error_datos[] = {
B10000001,
B01000010,
B00100100,
B00011000,
B00011000,
B00100100,
B01000010,
B10000001};

byte fin[] = {
B10101010,
B01010101,
B10101010,
B01010101,
B10101010,
B01010101,
B10101010,
B01010101};
 
void setup() {

  lc.shutdown(0,false);
  lc.setIntensity(0,8);// La valores estan entre 1 y 15 
  lc.clearDisplay(0);
  Representar(Corazon_datos,retardo);

  // Definiendo las Salidas
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Definiendo salidaSensor como entrada
  pinMode(salidaSensor, INPUT);
  
  // Definiendo la escala de frecuencia a 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Iniciar la comunicacion serie 
  Serial.begin(9600);
}
void loop() 
{ 
int R = getRojo();
int V = getVerde();
int A = getAzul();
/*  sacar este comentario para ver rango de colores
Serial.print("Int Rojo "+ String(R));
Serial.print("  --  Int Verde "+ String(V));
Serial.print("  --  Int Azul "+ String(A));
Serial.println(" ----- ");
*/
delay(retardo);
if (R > 20 && R < 30 && V > 20 && V < 30 && A > 15 && A < 25) {
    Serial.println(9); // blanco
    Representar(Corazon_datos,retardo);
  }
else if (R > 150 && R < 210 && V > 150 && V < 210 && A > 110 && A < 170) {
    Serial.println(0); // negro
    Representar(fin,retardo);
  }
else if (R > 100 && R < 120 && V > 80 && V < 100 && A > 40 && A < 60) {
    Serial.println(7); // azul
    Representar(Corazon_datos,retardo);
  }
else if (R > 30 && R < 40 && V > 90 && V < 120 && A > 70 && A < 90) {
     Serial.println(2); // rojo
     Representar(Error_datos,retardo);
  }
else if (R > 70 && R < 110 && V > 50 && V < 80 && A > 60 && A < 110) {
     Serial.println(6); // verde
     Representar(Corazon_datos,retardo);
  }
else if (R > 20 && R < 30 && V > 30 && V < 40 && A > 50 && A < 60) {
     Serial.println(8); //amarillo
     Representar(Corazon_datos,retardo);
  }
else if (R > 70 && R < 90 && V > 40 && V < 50 && A > 30 && A < 40) {
     Serial.println(3); //celeste
     Representar(Error_datos,retardo);     
  }
else if (R > 60 && R < 90 && V > 100 && V < 150 && A > 50 && A < 90) {
     Serial.println(4); //morado
     Representar(Error_datos,retardo);     
  }
else
  {
//    Serial.println(1);
delay(retardo);
  }
}  
    
int getRojo(){
  //leer color rojo
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(100);
  int ROJO = pulseIn(salidaSensor, LOW);
  return ROJO;
}

int getAzul(){
  //leer color azul
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(100);
  int AZUL = pulseIn(salidaSensor, LOW);
  return AZUL;
}

int getVerde(){
  //leer color verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(100);
  int VERDE = pulseIn(salidaSensor, LOW);
  return VERDE;
}

int getSinFiltro(){
  //leer color verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  int SinFiltro = pulseIn(salidaSensor, LOW);
  return SinFiltro;
}

int Representar(byte *Datos,int retardo) //Funcion para la representacion de bytes de datos para una matriz de 8x8 
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setColumn(0,i,Datos[7-i]);
  }
  delay(retardo);
}
