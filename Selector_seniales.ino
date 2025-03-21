#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

// Configuración
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define SW_1 26
#define SW_2 25
#define SW_3 32
#define SW_4 33

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int x, y, x_offset, y_offset, A, T;
int sw_1_value, sw_2_value, sw_3_value, sw_4_value;
int dec_value;
bool muestra_menu = true; 

float sign(float value) {
  if (value >= 0.0) {
    return 1.0;
  }
  return -1.0;
}

void setup() {
  // Configura comunicación serial USB
  Serial.begin(115200);
  // Configura comunicación serial I2C
  Wire.begin(21, 22);
  // Configura OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error al inicializar la pantalla OLED SSD1306"));
    for (;;);
  }
  // Configura entradas digitales
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_3, INPUT_PULLUP);
  pinMode(SW_4, INPUT_PULLUP);
  // Parámetros de las señales
  y_offset = 36;
  x_offset = 0;
  A = 20;
  T = 40;

  // Muestra el menú inicial
  mostrarMenu();
}

void loop() {
  // Lee entradas digitales
  sw_1_value = HIGH - digitalRead(SW_1);
  sw_2_value = HIGH - digitalRead(SW_2);
  sw_3_value = HIGH - digitalRead(SW_3);
  sw_4_value = HIGH - digitalRead(SW_4);

  // Determina el valor decimal
  dec_value = sw_1_value * 8 + sw_2_value * 4 + sw_3_value * 2 + sw_4_value;

  // Oculta el menú si algún interruptor está activado
  if ( dec_value != 0 ) {  
    muestra_menu = false; 
    display.clearDisplay(); 
  }

  // Si el menú no está visible, graficar la señal correspondiente
  if (!muestra_menu) {
    // Borra OLED y escribe nombre
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Erendira Garcia");

    // Decide qué señal graficar
    switch (dec_value) {
      case 1: // Sinusoidal
            senialSinusoidal();
        break;
      case 2: // Cuadrada
            senialCuadrada();
        break;
      case 4: // Triangular
            senialTriangular();
        break;
      case 8: // Diente de sierra
            senialDienteSierra();
        break;
      default:
        display.setCursor(0, y_offset);
        display.println("Error!!!");
    }
    display.display();
  }

  // Muestra el menú cuando los interruptores están abajo
  if (dec_value == 0 ) { 
    muestra_menu = true;
    mostrarMenu();
  }

  delay(10);
  x_offset = (x_offset + 1) % 128;
}


void mostrarMenu() {
  // Función que muestra el menú inicial
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Elija una senial:");
  display.setCursor(0, 20);
  display.println("1. Diente de sierra");
  display.println("2. Triangular");
  display.println("3. Cuadrada");
  display.println("4. Sinusoidal");
  display.display();
}

void senialSinusoidal(){
  // Imprime la señal sinusoidal
  for (int x = 0; x < 128; x++) {
    y = y_offset - A * sin(2.0 * 3.1416 * (x + x_offset) / T);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void senialCuadrada(){
  // Imprime la señal cuadrada
  for (int x = 0; x < 128; x++) {
    y = y_offset - A * sign(sin(2.0 * 3.1416 * (x + x_offset) / T));
    display.drawPixel(x, y, SSD1306_WHITE);

    if ((x + x_offset) % (T / 2) == 0) {
      display.drawLine(x, y_offset - A, x, y_offset + A, SSD1306_WHITE);
    }
  }  
}

void senialTriangular(){
  // Imprime la señal triangular
  for (int x = 0; x < 128; x++) {
   y = y_offset - (4 * A / T) * abs((x + x_offset) % T - T / 2)+ A;
   display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void senialDienteSierra(){
  // Imprime la señal diente de sierra
  for (int x = 0; x < 128; x++) {
    y = y_offset - (2 * A / T) * (x + x_offset) % T + A;
    display.drawPixel(x, y, SSD1306_WHITE);

    if ((x + x_offset) % T == 0) {
      display.drawLine(x, y_offset - A, x, y_offset + A, SSD1306_WHITE);
    }
  }
 }
