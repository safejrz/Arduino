/*
 * Control de Motor DC con Control Remoto IR
 * Librería: IRremote 3.0+ (versión actualizada)
 */

#include <IRremote.hpp>  // Nota: ahora usa .hpp en vez de .h

// Configuración de pines
const int IR_PIN = 11;        // Pin del receptor IR
const int MOTOR_PIN1 = 5;     // Pin 1 del motor (o relay)
const int MOTOR_PIN2 = 6;     // Pin 2 del motor (opcional para control de dirección)
const int ENABLE_PIN = 9;     // Pin PWM para velocidad (opcional)

// Estado del motor
bool motorEncendido = false;

void setup() {
  Serial.begin(9600);
  
  // Inicializar receptor IR (sintaxis nueva)
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  
  // Configurar pines del motor
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  
  // Motor apagado inicialmente
  apagarMotor();
  
  Serial.println("Sistema listo. Presiona un botón en el control remoto.");
  Serial.println("Esperando señales IR...");
}

void loop() {
  // Verificar si se recibió una señal IR
  if (IrReceiver.decode()) {
    
    // Imprimir toda la información recibida
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    
    // Obtener el código del comando
    uint16_t comando = IrReceiver.decodedIRData.command;
    
    Serial.print("Comando: 0x");
    Serial.println(comando, HEX);
    
    // Procesar el comando
    procesarComando(comando);
    
    // Preparar para la siguiente señal
    IrReceiver.resume();
  }
}

void procesarComando(uint16_t comando) {
  // IMPORTANTE: Reemplaza estos valores con los comandos de tu control remoto
  // Para obtenerlos, abre el Monitor Serial y presiona los botones
  // Verás algo como "Comando: 0x45" o "Comando: 0x16"
  
  switch(comando) {
    case 0x45:  // Ejemplo: Botón 1 - Encender
      encenderMotor();
      break;
      
    case 0x46:  // Ejemplo: Botón 2 - Apagar
      apagarMotor();
      break;
      
    case 0x47:  // Ejemplo: Botón 3 - Toggle (alternar)
      toggleMotor();
      break;
      
    case 0x44:  // Ejemplo: Botón 4 - También encender
      encenderMotor();
      break;
      
    case 0x40:  // Ejemplo: Botón 5 - También apagar
      apagarMotor();
      break;
      
    default:
      Serial.println("Botón no configurado");
      break;
  }
}

void encenderMotor() {
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  analogWrite(ENABLE_PIN, 255);  // Velocidad máxima
  motorEncendido = true;
  Serial.println(">>> Motor ENCENDIDO <<<");
}

void apagarMotor() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  analogWrite(ENABLE_PIN, 0);
  motorEncendido = false;
  Serial.println(">>> Motor APAGADO <<<");
}

void toggleMotor() {
  if (motorEncendido) {
    apagarMotor();
  } else {
    encenderMotor();
  }
}
