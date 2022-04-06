//PRACTICA 2 - LABORATORIO SISTEMAS DE CONTROL
//PABLO SEBASTIÁN JAUREZ MONTUFAR 201902657
//JULIO ESTEBAN DE LEON SARAVIA   201807036

#include <LiquidCrystal.h>
#define botonSumaPin  5    
#define botonRestaPin  6 
#define OPCION 2
#define POT A0

const int MOTOR = 3;
int valor_pot;
int ciclo;
int botonSumaValue;           //Variable para el boton de suma
int botonRestaValue;          //Variable para el boton de resta
int cicloTrabajo;             //Variable para el ciclo de trabajo del led
int contador = 64;
int porcentaje = 25;

const int rs = 43, en = 41, d4 = 37, d5 = 35, d6 = 33, d7 = 31;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin (9600);
  pinMode(MOTOR, OUTPUT);
  digitalWrite( MOTOR, LOW );
  pinMode(botonSumaPin, INPUT);
  pinMode(botonRestaPin, INPUT);
  pinMode(OPCION, INPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop () {
  int push;
  push = digitalRead(OPCION);

  if (push == 1) {
    funcion1();
  }
  else if (push == 0) {
    funcion2();
  }
}


void funcion1() {
  botonSumaValue = digitalRead(botonSumaPin);
  botonRestaValue = digitalRead(botonRestaPin);
  Serial.println(botonRestaValue, DEC);

  if (botonSumaValue == HIGH && contador <= 191) {
    contador = contador + 64;
    porcentaje = porcentaje + 25;
  }
  else if (botonRestaValue == HIGH && contador >= 65) {
    contador = contador - 64;
    porcentaje = porcentaje - 25;
  }
  else {
    contador = contador;
    delay(150);
  }


  Serial.print("Ciclo de trabajo: ");
  Serial.print(porcentaje);
  Serial.print("%");
  Serial.println();
  analogWrite(MOTOR, contador);
  delay(300);

}


void funcion2 () {
  valor_pot = analogRead(POT);
  if ( valor_pot > 0 and  valor_pot < 300) {
    analogWrite(MOTOR, 64);
    Serial.print("Porcentaje de trabajo: 25%");
  }
  else if ( valor_pot > 300 and  valor_pot < 700) {
    analogWrite(MOTOR, 128);
    Serial.print("Porcentaje de trabajo: 50%");
  }
  else if ( valor_pot > 700 and  valor_pot < 1024) {
    analogWrite(MOTOR, 191);
    Serial.print("Porcentaje de trabajo: 75%");
  }
  //ciclo = map(valor_pot, 0, 1023, 0, 255);
  //analogWrite( MOTOR,  ciclo );
  Serial.print("Potenciometro: ");
  Serial.println(valor_pot);
  Serial.println();
  delay(300);
}
