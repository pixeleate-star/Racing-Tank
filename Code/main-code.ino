#define CH1 18
#define CH2 19

#define L_RPWM 25
#define L_LPWM 26

#define R_RPWM 27
#define R_LPWM 14

int readCh(int pin) {
  int v = pulseIn(pin, HIGH, 25000);
  if (v < 900 || v > 2100) return 1500;
  return v;
}

void motor(int rpwm, int lpwm, int speed) {
  speed = constrain(speed, -255, 255);

  if (speed > 0) {
    analogWrite(rpwm, speed);
    analogWrite(lpwm, 0);
  } 
  else if (speed < 0) {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, -speed);
  } 
  else {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }
}

void setup() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  motor(L_RPWM, L_LPWM, 0);
  motor(R_RPWM, R_LPWM, 0);
}

void loop() {
  int steering = readCh(CH1);
  int throttle = readCh(CH2);

  int s = map(steering, 1000, 2000, -255, 255);
  int t = map(throttle, 1000, 2000, -255, 255);

  if (abs(s) < 15) s = 0;
  if (abs(t) < 15) t = 0;

  int left = t + s;
  int right = t - s;

  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);

  motor(L_RPWM, L_LPWM, left);
  motor(R_RPWM, R_LPWM, right);

  delay(10);
}
