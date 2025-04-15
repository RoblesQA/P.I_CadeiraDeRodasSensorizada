#define trigPin 6  // Pino Trigger do sensor ultrassônico
#define echoPin 5  // Pino Echo do sensor ultrassônico
#define vibraPin 9  // Pino do módulo de vibração
#define buzzerPin 10 // Pino do buzzer (opcional)

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(vibraPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    long duration;
    int distance;
    
    // Envia pulso de ultrassom
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Mede o tempo de retorno
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; // Converte tempo em distância (cm)
    
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance > 0 && distance <= 30) {  // Alerta se obstáculo estiver a 50 cm ou menos
        analogWrite(vibraPin, map(distance, 30, 0, 30, 255)); // Vibração proporcional à proximidade
        tone(buzzerPin, 1000, 200); // Som curto para alertar
    } else {
        analogWrite(vibraPin, 0);
        noTone(buzzerPin);
    }
    
    delay(200); // Pequeno delay para estabilização
}
