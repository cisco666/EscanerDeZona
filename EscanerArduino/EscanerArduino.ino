#include<Ultrasonido.h>

int estado=0;
int estadoAnterior=0;
int estado2=0;
int estadoAnterior2=0;
int salida=0;
int salida2=0;

int carril=0;

int dist;
int distancia;
int distancia2;
int distancia3;
int distancia4;

int izquierda=13;
int derecha=12;
int regresar=11;
int alto=10;
String val;

void setup() 
{
  pinMode(regresar,INPUT);
  pinMode(alto,INPUT);
  pinMode(izquierda,OUTPUT);
  pinMode(derecha,OUTPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  estado=digitalRead(regresar);
  estado2=digitalRead(alto);
  dist=30;
  
  if((estado2==HIGH)&&(estadoAnterior2==LOW))
  {
    salida2=1-salida2;
  }
  estadoAnterior2=estado2;
  
  if(Serial.available()>0)
  {
    carril=Serial.read();
  }
  
  if ((salida2==1)&&(carril=='A'))
  {
    if((estado==HIGH)&&(estadoAnterior==LOW))
    {
      salida=1-salida;
    }
    estadoAnterior=estado;
  
    if (salida == 1)
    {
      digitalWrite (izquierda, HIGH);
      digitalWrite(derecha,LOW);
      
      val=":";
      //Sensor 1
      Ultrasonido ultrasonido(9,8,dist);
      distancia=ultrasonido.Distancia();
      val.concat(distancia);
      val.concat(":");
      delay(10);
      //Sensor 2
      Ultrasonido ultrasonido2(7,6,dist);
      distancia2=ultrasonido2.Distancia();
      val.concat(distancia);
      val.concat(":");
      delay(10);
      //Sensor 3
      Ultrasonido ultrasonido3(5,4,dist);
      distancia3=ultrasonido3.Distancia();
      val.concat(distancia3);
      val.concat(":");
      delay(10);
      //Sensor 4
      Ultrasonido ultrasonido4(3,2,dist);
      distancia4=ultrasonido4.Distancia();
      val.concat(distancia4);
      val.concat("\n");
      delay(10);
      
      Serial.print(val);
      delay(600);
    }
    else if(salida==0)
    {
      digitalWrite(derecha,HIGH);
      digitalWrite(izquierda,LOW);
    }
  }
  else if(salida2==0)
  {
    digitalWrite(derecha,LOW);
    digitalWrite(izquierda,LOW);
  }
}
