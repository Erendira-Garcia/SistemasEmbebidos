#define B0 25
#define B1 26
#define B2 32
#define B3 33

#define BUTTON_PIN 27

int contador;
int mask = 0x01;

void setup(){
  pinMode(B0, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  contador = 0;
}

void loop() {
  if (contador & mask){
    digitalWrite(B0, HIGH);
  } else{
    digitalWrite(B0, LOW);
  }
  if (contador>>1 & mask){
    digitalWrite(B1, HIGH);
  } else{
    digitalWrite(B1, LOW);
  }
  if (contador>>2 & mask){
    digitalWrite(B2, HIGH);
  } else{
    digitalWrite(B2, LOW);
  }
  if (contador>>3 & mask){
    digitalWrite(B3, HIGH);
  } else{
    digitalWrite(B3, LOW);
  }

  // Incremento
  int estadoBoton = digitalRead(BUTTON_PIN); //Estado del boton
  if(estadoBoton == LOW){ //Esta presionado
    // Lo presiono
    delay(50); // Quita rebote
    while(estadoBoton == LOW){ // Espera a que deje de presionar
      estadoBoton = digitalRead(BUTTON_PIN);
  }
  // Lo dejo de presionar
  delay(50); // Quita rebote
  contador = (contador+1)%16; //Solo puede llegar a 15
  }
}
