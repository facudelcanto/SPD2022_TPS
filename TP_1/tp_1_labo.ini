// C++ code
//

#define TAM 10
#define NARANJA 4
#define BLANCO 13

//VARIABLES MILLIS.
unsigned long tiempoAhora1;
unsigned long tiempoAhora2;
unsigned long tiempo2 = 0;
unsigned long tiempo1 = 0;

void setup()
{
  Serial.begin(9600);

  for (int i = NARANJA; i < BLANCO + 1; i++)
  {
    pinMode(i, OUTPUT);
  }
  tiempoAhora1 = millis();
  tiempoAhora2 = millis();

  pinMode(3, INPUT);
  pinMode(2, INPUT);
}

// FUNCIONES
//-----------------------------------------------------------------
// ESTA FUNCION CONVIERTE UN NUMERO DECIMAL EN NUMERO BINARIO.
void decimalAbinario(int decimal, int array[], int tamanio)
{
  int numeroBinario;
  int ultimoIndice = tamanio - 1;

  while (decimal > 0)
  {
    numeroBinario = decimal % 2;
    decimal /= 2;
    array[ultimoIndice] = numeroBinario;
    ultimoIndice--;
  }
}
// FUNCION PARA MOSTRAR LOS NUMEROS DECIMALES Y BINARIOS.
void mostrarDecimalBinario(int decimal, int binario[], int tamanio)
{
  Serial.print("Decimal = ");
  Serial.print(decimal);

  Serial.print(" // Binario = ");

  for (int i = 0; i < tamanio; i++)
  {
    Serial.print(binario[i]);
  }
  Serial.println(" ");
}
// ESTA FUNCION APAGA TODOS LOS LEDS DEL CIRCUITO.
void apagarLeds()
{
  for (int i = NARANJA; i < BLANCO + 1; i++)
  {
    digitalWrite(i, LOW);
  }
}
// FUNCION PARA CARGAR ARRAY DE LEDS.
void cargarArrays(int array[], int tam)
{
  int j = 4;
  int flag = 0;
  if (flag == 0)
  {
    for (int i = tam - 1; i > -1; i--)
    {
      array[i] = j;
      j++;
    }
    flag = 1;
  }
}
// FUNCION PARA LLENAR LOS ESPACIOS DEL ARRAY CON 0.
void rellenarArrays(int binario[], int tam)
{
  for (int i = 0; tam > i; i++)
  {
    if (binario[i] != 1)
    {
      binario[i] = 0;
    }
  }
}
// ESTA FUNCION PRENDE EL LED CORRESPONDIENTE.
void prenderLed(int bin[], int array[], int tam)
{
  for (int i = tam; i > -1; i--)
  {
    if (bin[i] == 1)
    {
      digitalWrite(array[i], HIGH);
    }
  }
}

// ESTA FUNCION PONE EN 0 EL ARRAY DE BINARIOS Y DEVUELVE CERO PARA UTILIZAR CON EL CONTADOR.
  int reset (int array[], int tam)
  {
    int contador = 0;
    
    for (int i = 0; i < tam; i++)
    {
      array[i] = 0;
    }
    
    return contador;
    
  }

//-----------------------------------------------------------------
//  VARIABLES GENERALES.
int contador = 0;
int binario[TAM];
int arrayLeds[TAM];
int periodo = 1023;
int periodo2 = 1000;
int valorStart = 0;
int estadoAntes = 0;
int valorReset = 0;
int estadoResetAntes = 0;
//-----------------------------------------------------------------
void loop()
{
  int valorResetAhora = digitalRead(3);
  int botonAhora = digitalRead(2);
  
  cargarArrays(arrayLeds, TAM);
  
  //LOGICA BOTON RESET.
  if (valorResetAhora == 1 && estadoResetAntes == 0)
  {
    valorReset = !valorReset;
  }
  estadoResetAntes = valorResetAhora;
  
  //SI SE PRESIONA EL BOTON RESET.
  if (valorReset == 1)
  {
    contador =  reset(binario,TAM);
    valorReset = 0;
  }

  //LOGICA BOTON START.
  if (botonAhora == 1 && estadoAntes == 0)
  {
    valorStart = !valorStart;
  }
  estadoAntes = botonAhora;
  
  //SI SE PRESIONA EL BOTON START.
  if (valorStart == 1)
  {
    tiempo1 = millis();
    if (tiempo1 > (tiempoAhora1 + periodo))
    {
      contador++;
      tiempoAhora1 = millis();
      decimalAbinario(contador, binario, TAM);
      mostrarDecimalBinario(contador, binario, TAM);
      rellenarArrays(binario, TAM);
      prenderLed(binario, arrayLeds, TAM);
    }
    tiempo2 = millis();

    
    if (tiempo2 > (tiempoAhora2 + periodo2))
    {
      tiempoAhora2 = millis();
      apagarLeds();
    }
    
  } 
  
  
  
}



