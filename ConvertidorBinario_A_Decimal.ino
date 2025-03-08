const int A = 25;
const int B = 26;
const int C = 14;
const int D = 12;
const int E = 13;
const int F = 33;
const int G = 32;

const int DISPLAY_PINS[3] = {19, 18, 5}; // DISPLAY_C, DISPLAY_D, DISPLAY_U
const int SW_PINS[4] = {22, 15, 4, 2};   // SW0, SW1, SW2, SW3

int unidades, decenas, centenas;
int valor_decimal;

const int digits[10][7] = {
  // A, B, C, D, E, F, G
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},  // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},     // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},  // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},  // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},   // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},  // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}, // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},    // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},// 8
  {HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH}  // 9
};

const int segments[7] = {A, B, C, D, E, F, G};

void mostrar_contador() {
  int digitos[3] = {centenas, decenas, unidades};

  for (int i = 0; i < 3; i++) {
    for (int s = 0; s < 7; s++) {
      digitalWrite(segments[s], digits[digitos[i]][s]);
    }
    digitalWrite(DISPLAY_PINS[i], LOW); // Encender display
    delay(5);
    digitalWrite(DISPLAY_PINS[i], HIGH); // Apagar display
  }
}

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(DISPLAY_PINS[i], OUTPUT);
    digitalWrite(DISPLAY_PINS[i], HIGH); // Apagar todos los displays
  }

  for (int i = 0; i < 4; i++) {
    pinMode(SW_PINS[i], INPUT_PULLDOWN);
  }

  unidades = 0;
  decenas = 0;
  centenas = 0;
}

void actualiza_salida() {
  valor_decimal = 0;
  for (int i = 0; i < 4; i++) {
    valor_decimal += digitalRead(SW_PINS[i]) * (1 << i);
  }

  unidades = valor_decimal % 10;
  decenas = (valor_decimal / 10) % 10;
  centenas = valor_decimal / 100;
}

void loop() {
  mostrar_contador();
  actualiza_salida();
}
