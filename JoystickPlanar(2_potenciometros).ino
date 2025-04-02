#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_ANALOGICO_X 34
#define PIN_ANALOGICO_Y 35

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void dibujar_avatar(int x, int y);
void escenario(void);

void setup() {

  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("¡Error al iniciar OLED!");
    while (true);
  } 
display.clearDisplay();
display.display();
}

void loop() {
  int valor_x = analogRead(PIN_ANALOGICO_X);
  int valor_y = analogRead(PIN_ANALOGICO_Y);

  int x = (valor_x / 4095.0) * 127;
  //int y = (valor_y / 4095.0) * 63;
  int y = (valor_y / 4095.0) * 30 + 25; // Permite 55 pixeles como máximo desplazamiento vertical

  Serial.println("x: ");
  Serial.println(x);
  Serial.println("y: ");
  Serial.println(y);
  display.clearDisplay();

  escenario();
  dibujar_avatar(x, y);

  display.display();

  delay(500);
}

// Función que dibuja el avatar
void dibujar_avatar(int x, int y) {
  // Centro del avatar (caballo y jinete)
  int x_offset = x;
  int y_offset = y;

  // 1. Cuadrado --> Cabeza persona
  display.fillRect(x_offset-6, y_offset-9, 4, 4, SSD1306_WHITE);

  // 2. Triángulo --> Cuerpo persona
  display.fillTriangle(x_offset-4, y_offset-5, x_offset+2, y_offset+1, x_offset-4, y_offset+1, SSD1306_WHITE);

  // 3. Triángulo --> Cabeza caballo
  display.fillTriangle(x_offset+7, y_offset-4, x_offset+12, y_offset+1, x_offset+3, y_offset+1, SSD1306_WHITE);

  // 4. Rombo --> Cola Caballo
  display.fillTriangle(x_offset-12, y_offset+2, x_offset-5, y_offset+1, x_offset-7, y_offset+4, SSD1306_WHITE);
  display.fillTriangle(x_offset-7, y_offset+4, x_offset-13, y_offset+5, x_offset-12, y_offset+2, SSD1306_WHITE);

  // 5. Rectangulo -- > Cuerpo caballo
  display.fillRect(x_offset-5, y_offset+1, 12, 4, SSD1306_WHITE);

  // 6. Triangulo --> Pata trasera
  display.fillTriangle(x_offset-5, y_offset+5, x_offset-2, y_offset+5, x_offset-5, y_offset+9, SSD1306_WHITE);

  // 7. Triangulo --> Pata delantera
  display.fillTriangle(x_offset+3, y_offset+5, x_offset+7, y_offset+5, x_offset+7, y_offset+9, SSD1306_WHITE);
  
  // Mostrar la figura
  display.display();
}

void escenario(void){
  // Luna
  display.fillCircle(123, 4, 4, SSD1306_WHITE);
  display.fillCircle(126, 3, 3, SSD1306_BLACK);

  // Estrellas
  display.drawPixel(9, 1, SSD1306_WHITE);
  display.drawPixel(10, 4, SSD1306_WHITE);
  display.drawPixel(23, 12, SSD1306_WHITE);
  display.drawPixel(24, 1, SSD1306_WHITE);
  display.drawPixel(32, 2, SSD1306_WHITE);
  display.drawPixel(45, 7, SSD1306_WHITE);
  display.drawPixel(53, 1, SSD1306_WHITE);
  display.drawPixel(64, 6, SSD1306_WHITE);
  display.drawPixel(65, 5, SSD1306_WHITE);
  display.drawPixel(78, 3, SSD1306_WHITE);
  display.drawPixel(84, 10, SSD1306_WHITE);
  display.drawPixel(85, 7, SSD1306_WHITE);
  display.drawPixel(97, 5, SSD1306_WHITE);
  display.drawPixel(109, 2, SSD1306_WHITE);
}
