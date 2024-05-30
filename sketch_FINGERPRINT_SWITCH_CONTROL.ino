#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define FINGERPRINT_RX_PIN 2
#define FINGERPRINT_TX_PIN 3
#define switch01 12        // RELAY SWITCH
#define switch02 8         // LED SWITCH
#define switch03 10        // EXTRA SWITCH

SoftwareSerial mySerial(FINGERPRINT_RX_PIN, FINGERPRINT_TX_PIN);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  pinMode(switch01, OUTPUT);
  pinMode(switch02, OUTPUT);
  pinMode(switch03, OUTPUT);

  digitalWrite(switch01, LOW); // relay switch off initially
  digitalWrite(switch02, LOW); // LED switch ff initially
  digitalWrite(switch03, LOW); // extra switch to off initially

  Serial.begin(9600);
  while (!Serial)
    delay(100); // For Leonardo/Micro/Zero

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    while True:
      Serial.println("Did not find fingerprint sensor :(");
      digitalWrite(switch02, HIGH); 
      delay(3000);
      digitalWrite(switch02, LOW); 
      
  }
}

void loop() {
  getFingerprintID();
  delay(1000); 
}

void getFingerprintID() {
  uint8_t id = finger.getImage();

  switch (id) {
    case FINGERPRINT_OK:
      Serial.println("Image captured");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  id = finger.image2Tz();

  switch (id) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  id = finger.fingerFastSearch();

  if (id == FINGERPRINT_OK) {
    Serial.println("Fingerprint found!");
    uint8_t confidence = finger.confidence;

    if (confidence > 50) {
      if (finger.fingerID == 1) {
        Serial.println("Fingerprint ID no 1 valid");
        digitalWrite(switch01, HIGH);   
        delay(3500);                  
        digitalWrite(switch01, LOW);  
      } else if (finger.fingerID == 2) {
        Serial.println("Fingerprint ID no 2 valid");
        digitalWrite(switch01, HIGH);   
        delay(3500);                   
        digitalWrite(switch01, LOW);  
      } else if (finger.fingerID == 3) {
        Serial.println("Fingerprint ID no 3 valid");
        digitalWrite(switch01, HIGH);   
        delay(3500);                
        digitalWrite(switch01, LOW);  
      } else if (finger.fingerID == 4) {
        Serial.println("Fingerprint ID no 4 valid");
        digitalWrite(switch01, HIGH);   
        delay(3500);                  
        digitalWrite(switch01, LOW);  
      } else {
        Serial.println("Unknown fingerprint ID");
      }
    } else {
      Serial.println("Fingerprint does not match any stored ID");
    }
  } else if (id == FINGERPRINT_NOTFOUND) {
    Serial.println("Fingerprint not found");
  } else {
    Serial.println("Unknown error");
  }
}
