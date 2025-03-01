const int SEGMENT_PINS[7] = {25, 26, 14, 12, 13, 33, 32};
const int DISPLAY_PINS[3] = {19, 18, 5};

const int DIGITS[10][7] = {
  // A, B, C, D, E, F, G
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, // Digito 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW}, // Digito 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}, // Digito 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH}, // Digito 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH}, // Digito 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}, // Digito 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}, // Digito 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW}, // Digito 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // Digito 8
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH} // Digito 9
};

int unidades = 0;
int decenas = 0;
int centenas = 0;

unsigned long tiempo_anterior = 0;
const unsigned long INTERVALO = 250;

void incrementarContador() {
  unidades++;
  if (unidades > 9) {
    unidades = 0;
    decenas++;
    
    if (decenas > 9) {
      decenas = 0;
      centenas++;
      
      if (centenas > 9) {
        centenas = 0;
      }
    }
  }
}

void mostrarDigito(int digito, int displayPin) {
  for (int s = 0; s < 7; s++) {
    digitalWrite(SEGMENT_PINS[s], DIGITS[digito][s]);
  }
  digitalWrite(displayPin, LOW); // LOW-> Encendido para cátodo común
  delay(5);
  digitalWrite(displayPin, HIGH);
}

void mostrarContador() {
  mostrarDigito(centenas, DISPLAY_PINS[0]); // Mostrar centenas
  mostrarDigito(decenas, DISPLAY_PINS[1]);  // Mostrar decenas
  mostrarDigito(unidades, DISPLAY_PINS[2]); // Mostrar unidades
}

void setup() {
  for (int pin : SEGMENT_PINS) {
    pinMode(pin, OUTPUT);
  }
  
  for (int pin : DISPLAY_PINS) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // Apagar todos los displays
  }
}

void loop() {
  mostrarContador();
  
  unsigned long tiempo_actual = millis();
  
  if (tiempo_actual - tiempo_anterior > INTERVALO) {
    tiempo_anterior = tiempo_actual;
    incrementarContador();
  }
}
