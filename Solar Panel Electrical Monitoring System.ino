// Mesure de la puissance d’un panneau solaire
// Par exemple avec un capteur de courant ACS712 et un diviseur de tension

#include <LiquidCrystal.h>

// Initialisation de l'écran LCD (broches RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// ==== Paramètres capteur ACS712 ====
int sensitivity = 66;      // mV/A → pour module 30A (100 pour 20A, 185 pour 5A)
int offsetVoltage = 2500;  // décalage du capteur (2.5V à zéro courant)
int adcValue = 0;          // lecture analogique brute

// ==== Variables ====
double Voltage = 0.0;  // Tension mesurée du panneau (V)
double Current = 0.0;  // Courant mesuré (A)
double Power = 0.0;    // Puissance réelle (W)

// Broches analogiques
const int pinVoltage = A1;  // capteur tension
const int pinCurrent = A0;  // capteur courant (ACS712)

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("  Mesure Panneau  ");
  lcd.setCursor(0, 1);
  lcd.print("   Solaire (W)   ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // === Mesure de la tension ===
  int sensorVoltage = analogRead(pinVoltage);
  float v = (sensorVoltage * 5.0) / 1023.0;  // tension en volts
  // Si tu utilises un diviseur de tension, multiplie par le rapport (ex: *11 pour 0-55V)
  Voltage = v * 5;  // <-- ajuste selon ton diviseur de tension

  // === Mesure du courant ===
  adcValue = analogRead(pinCurrent);
  double Vout = (adcValue * 5000.0) / 1023.0;      // en mV
  Current = (Vout - offsetVoltage) / sensitivity;  // A

  // === Calcul de la puissance ===
  Power = Voltage * Current;

  // === Affichage sur LCD ===
  lcd.setCursor(0, 0);
  lcd.print("U=");
  lcd.print(Voltage, 2);
  lcd.print("V   ");

  lcd.setCursor(0, 1);
  lcd.print("I=");
  lcd.print(Current, 2);
  lcd.print("A   ");

  lcd.setCursor(0, 2);
  lcd.print("P=");
  lcd.print(Power, 2);
  lcd.print("W   ");

  delay(1000);
}