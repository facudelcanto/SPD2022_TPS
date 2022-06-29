// C++ code
//

#include <Keypad.h>
#include<LiquidCrystal.h>
#define BOTON_M1 1
#define BOTON_M2 2
#define NO_BOTON 0

//FUNCIONES
//-------------------------------------------------------------------

//FUNCION PARA IDENTIFICAR BOTONES
int leerBoton()
{
 	int valorA0 = analogRead(A0);
  	int valorA1 = analogRead(A1);
  
  	if(valorA0 > 1000)
    {
     return BOTON_M1; 
    }
  	if(valorA1 > 1000)
    {
      return BOTON_M2;
    }
  
  	return NO_BOTON;
}

//FUNCION PARA CALCULAR LLAMANDO A LA FUNCION DE OPERACION
double calcular(long primerNumero, long segundoNumero, void(*pFunc)(long,long,double*))
{
  double auxResultado;
  pFunc(primerNumero, segundoNumero, &auxResultado);
  return auxResultado;
}

//FUNCION DE OPERACION SUMAR: SUMNA DOS NUMEROS
void sumar(long primerNumero, long segundoNumero, double* resultado)
{
  *resultado = primerNumero + segundoNumero;
}
//FUNCION DE OPERACION RESTAR: RESTA DOS NUMEROS
void restar(long primerNumero, long segundoNumero, double* resultado)
{
  *resultado = primerNumero - segundoNumero;
}
//FUNCION DE OPERACION MULTIPLICAR: MULTIPLICA DOS NUMEROS
void multiplicar(long primerNumero, long segundoNumero, double* resultado)
{
  *resultado = primerNumero * segundoNumero;
}

//FUNCION DE OPERACION DIVIDIR: DIVIDE DOS NUMEROS
void dividir(long primerNumero, long segundoNumero, double* resultado)
{
  *resultado = primerNumero / segundoNumero;
}


//Variables Generales
//--------------------------------------------------------------------
long primero = 0;
long segundo = 0;
double total = 0; 
long guardarValor;
int flagGuardarNumero = 0;
const byte ROWS = 4;
const byte COLS = 4;
char lcdLine[16];
int botonAntes = NO_BOTON;
int flagMomento = 0;


//Config. Teclado.
//--------------------------------------------------------------------
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {12, 11, 10, 9};


char keys[ROWS][COLS] = {
  {'1','2', '3', 'A'},
  {'4','5', '6', 'B'},
  {'7','8', '9', 'C'},
  {'*','0', '#', 'D'},
};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


//Config LiquidCrystal
//--------------------------------------------------------------------
LiquidCrystal lcd(13,4,3,2,A4,A5);


void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}


void loop()
{
  char key = kpd.getKey();
  int botonAhora = leerBoton();
	
  if(key)
  {
  	switch (key){
    case '0' ... '9':// Al elegir valores del 0 al 9, junta el valor hasta que se presione: '+,-,*,/'
      if(flagMomento == 0)
      {
      lcd.setCursor(5,0);
      primero = primero * 10 + (key - '0');
      lcd.print(primero);
      flagGuardarNumero = 1;
      }
      else
      {
       flagMomento = 0;
       lcd.clear();
      }

    break;
      
  	case'A':
    if(flagMomento != 1)
    {
      lcd.print('+');
      flagGuardarNumero = 2;
      if(flagMomento != 2)
      {
      segundo = ObtenerSegundoNumero();
      }
      total = calcular(primero, segundo, sumar);
      lcd.setCursor(10,1);
      lcd.print(total);
      primero = 0;
      segundo = 0;
    }
    break; 
      
    case'B':
    if(flagMomento != 1)
    {
      lcd.print('-');
      segundo = ObtenerSegundoNumero();
      total = calcular(primero, segundo, restar);
      lcd.setCursor(10,1);
      lcd.print(total);
      primero = 0;
      segundo = 0;
    }
    break;
      
    case'C':
    if(flagMomento != 1)
    {
      lcd.print('*');
      segundo = ObtenerSegundoNumero();
      total = calcular(primero, segundo, multiplicar);
      lcd.setCursor(10,1);
      lcd.print(total);
      primero = 0;
      segundo = 0;
    }
    break;
      
    case'D':
    if(flagMomento != 1)
    {
      lcd.print('/');
      segundo = ObtenerSegundoNumero();
      total = calcular(primero, segundo, dividir);
      lcd.setCursor(10,1);
      lcd.print(total);
      primero = 0;
      segundo = 0;
    }
    break;
      
    case '*':
    if(flagMomento != 1)
    {
		
    }
    break;
      
    }
  }
  
  if(botonAhora != NO_BOTON && botonAhora != botonAntes)
  {
    switch(botonAhora)
    {
      case BOTON_M1:
      switch(flagGuardarNumero)
      {
       case 1: 
        guardarValor = primero;
        break;
       case 3:
        guardarValor = total;
        break;
      }
      break;
      case BOTON_M2:
      	switch(flagMomento)
        {
        case 0:
    	primero = guardarValor;
        lcd.setCursor(5,0);
        lcd.print(primero);
        flagMomento = 1;
        break;
        case 1:

          break;
        }

      break;
    }
  }
  botonAntes = botonAhora;
  
}


long ObtenerSegundoNumero()
{
  long numeroAImprimir;
  int flag = 0;
  int botonGuardado;
  while(1)
  {
    char key = kpd.getKey();
    if(key >= '0' && key <= '9')
    {
      segundo = segundo * 10 + (key - '0');
      
      if(flag == 0)
      {
      	numeroAImprimir = segundo;
        flag = 1;
      }
      else
      {
       numeroAImprimir = (key - '0');
      }
      lcd.print(numeroAImprimir);
      
      botonGuardado = leerBoton();
      
      if(botonGuardado == 1)
      {
     	 guardarValor = segundo;
      }
      Serial.println(botonGuardado);
      
      if(botonGuardado == 2)
      {
        segundo = guardarValor;
        lcd.print(segundo);
        flagMomento = 2;      
        Serial.println("entre");
      }
        
    }
    if(key == '#' && segundo > 0)
    {
      lcd.setCursor(9,1);
      lcd.print('=');
      flagGuardarNumero = 3;
      flagMomento = 1;
      break;
    }
  }
  return segundo;
}


