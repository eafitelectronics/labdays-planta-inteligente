/* Planta Inteligente (Agricultura Digital)
LabDays EAFIT
Autor: David Velásquez
Fecha: 6/11/2024
Descripción: Este programa permite configurar un sensor de humedad del suelo
para detectar si a una planta le falta agua o no. En caso de faltar agua
el ESP32 prenderá el LED azul que tiene conectado en el pin 2

Conexiones Sensor de Humedad del Suelo al ESP32:
SIG (Cable Azul) -> VP (A0)
VCC (Cable Rojo) -> 3V3
GND (Cable Negro) -> GND
*/

// Etiquetas de pines
#define SENSOR_PIN A0 // Sensor de humedad del suelo conectado al pin VP (A0)
#define LED_PIN 2 // LED del ESP32 conectado por defecto en el pin 2

// Constantes
#define TIEMPO_LECTURA 1000 // Valor del tiempo de lectura en milisegundos (1000ms)
#define VAL_SENSOR_AIRE 0 // [CAMBIAR] Valor medido aprox del sensor de humedad en el aire para calibrar
#define VAL_SENSOR_AGUA 2340 // [CAMBIAR] Valor medido aprox del sensor de humedad en el agua para calibrar
#define HUMEDAD_DESEADA 60 // [CAMBIAR] Valor deseado de humedad para la planta en porcentaje

// Variables
unsigned int humedad = 0; // Creo variable de tipo entera sin signo llamada humedad

void setup() {
  // Config de pines
  pinMode(LED_PIN, OUTPUT);

  // Limpieza de salidas
  digitalWrite(LED_PIN, LOW);

  // Iniciar comunicaciones
  Serial.begin(115200); // Inicio comms con el PC a 115200 bauds ()
}

void loop() {
  humedad = analogRead(SENSOR_PIN); // Realizo una lectura análoga del pin del sensor y la guardo en humedad
  //humedad = map(humedad, VAL_SENSOR_AIRE, VAL_SENSOR_AGUA, 0, 100); // [DESCOMENTAR AL CALIBRAR] Escalizo o mapeo la humedad leida de 0 a 100%
  if (humedad < HUMEDAD_DESEADA) { // Pregunto si la humedad medida es menor que la humedad deseada
    digitalWrite(LED_PIN, HIGH); // En caso afirmativo, prendo el LED indicando que falta agua
  } else { // En otro caso
    digitalWrite(LED_PIN, LOW); // En caso negativo, apago el LED ya que la planta tiene suficiente agua
  }
  Serial.print("Humedad: "); // Imprimo el texto "Humedad: " por el monitor Serial
  Serial.println(humedad); // Imprimo el valor de la variable humedad por el monitor serial con un enter al final
  delay(TIEMPO_LECTURA); // Realizo un retardo configurado en TIEMPO_LECTURA para la siguiente medición
}