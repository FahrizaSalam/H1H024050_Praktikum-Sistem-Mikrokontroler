const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

const int btnNext = 3;
int currentDigit = 0;
bool lastBtnState = HIGH;

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,0,1,1,0},
  {1,1,1,0,1,1,1,0},
  {0,0,1,1,1,1,1,0},
  {1,0,0,1,1,1,0,0},
  {0,1,1,1,1,0,1,0},
  {1,0,0,1,1,1,1,0},
  {1,0,0,0,1,1,1,0}
};

void displayDigit(int num)
{
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup()
{
  for(int i = 0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnNext, INPUT_PULLUP);

  displayDigit(currentDigit);
}

void loop()
{
  bool btnState = digitalRead(btnNext);

  if(lastBtnState == HIGH && btnState == LOW)
  {
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0;

    displayDigit(currentDigit);
    delay(200);
  }

  lastBtnState = btnState;
}
