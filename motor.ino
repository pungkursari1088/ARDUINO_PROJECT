const int MAJU = 13;
const int MUNDUR = 12;
const int LIMIT_MAJU = 14;
const int LIMIT_MUNDUR = 27;
const int RELAY_MAJU = 15;
const int RELAY_MUNDUR = 2;


void setup() {
  Serial.begin(115200);
  pinMode(MAJU, INPUT);
  pinMode(MUNDUR, INPUT);
  pinMode(LIMIT_MAJU, INPUT);
  pinMode(LIMIT_MUNDUR, INPUT);
  pinMode(RELAY_MAJU, OUTPUT);
  pinMode(RELAY_MUNDUR, OUTPUT);
  digitalWrite(RELAY_MAJU, LOW);
  digitalWrite(RELAY_MUNDUR, LOW);
}

void loop() {
  int stt_maju = digitalRead(MAJU);
  int stt_mundur = digitalRead(MUNDUR);
  int lm_stt_maju = digitalRead(LIMIT_MAJU);
  int lm_stt_mundur = digitalRead(LIMIT_MUNDUR);

  if(lm_stt_maju==1){
    digitalWrite(RELAY_MAJU, LOW);
  }
  if(lm_stt_mundur==1){
    digitalWrite(RELAY_MUNDUR, LOW);
  }
  if(stt_maju==1&&lm_stt_maju==0&&stt_mundur==0){
    digitalWrite(RELAY_MAJU, HIGH);
  }
    if(stt_mundur==1&&lm_stt_mundur==0&&stt_maju==0){
    digitalWrite(RELAY_MUNDUR, HIGH);
  }
  delay(10);

}
