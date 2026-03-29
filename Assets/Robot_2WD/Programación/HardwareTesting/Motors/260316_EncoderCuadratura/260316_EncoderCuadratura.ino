
#include "PinChangeInterrupt.h"

/* programa que calcula el valor de conteo de cada encoder
 * 
 * En este programa se puede seleccionar cualquier motor por medio de la 
 * variable motorControlado.*/

// VARIABLES Y CONSTANTES

int PWM0 = 7;
int PWM1 = 8;
int PWM2 = 9;
int DIR0 = 10;
int DIR1 = 11;
int DIR2 = 12;

int EN0A = A10;  
int EN0B = A11;
int EN1A = A12;  
int EN1B = A13;  
int EN2A = A14;  
int EN2B = A15;

// Tiempo de muestreo

unsigned long lastTime, sampleTime = 100;

int motores[3][5] = {{PWM0, DIR0, EN0A, EN0B, 12},
					 {PWM1, DIR1, EN1A, EN1B, 48},
					 {PWM2, DIR2, EN2A, EN2B, 192}};

int motorControlado = 0;

const int C1 = motores[motorControlado][3];
const int C2 = motores[motorControlado][2];

volatile int n = 0;
volatile int ant = 0;
volatile int act = 0;


void setup(){
	Serial.begin(9600);
	Serial.print(C1); Serial.print("\t"); Serial.println(C2);
	pinMode(C1, INPUT); pinMode(C2, INPUT);
	attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(C1), encoder, CHANGE);
	attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(C2), encoder, CHANGE);
	
	lastTime = millis();

}

void loop(){
	if(millis()-lastTime >= sampleTime){
		lastTime = millis();
		Serial.print("cuentas: ");
		Serial.println(n);
	}
}

void encoder(){
	ant = act;
	act = PINK & motores[motorControlado][4];
	
	if(ant == motores[motorControlado][4]*0 && act == motores[motorControlado][4]/3) n++;
	else if(ant == motores[motorControlado][4]/3 && act == motores[motorControlado][4]/1) n++;
	else if(ant == motores[motorControlado][4]/1.5 && act == motores[motorControlado][4]*0) n++;
	else if(ant == motores[motorControlado][4]/1 && act == motores[motorControlado][4]/1.5) n++;
	
	if(ant == motores[motorControlado][4]*0 && act == motores[motorControlado][4]/1.5) n--;
	else if(ant == motores[motorControlado][4]/3 && act == motores[motorControlado][4]*0) n--;
	else if(ant == motores[motorControlado][4]/1.5 && act == motores[motorControlado][4]/1) n--;
	else if(ant == motores[motorControlado][4]/1 && act == motores[motorControlado][4]/3) n--;
	
}
