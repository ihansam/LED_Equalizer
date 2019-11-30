// Program Design: Kidan Jin, EEE, SKKU

int frequency[7] = {A1,A2,A3,A4,A5,A6,A7};
int amplitude[8] = {9,8,7,6,5,4,3,2};
int freqnum = 7;      // 가로 진동수 개수
int ampnum = 8;       // 세로 세기 개수
int delaytime = 100;  // 패턴 유지 시간

unsigned int numberPattern[9] = {  // 해당 freq에서 킬 led 개수(index) 패턴
  0B0000000000000000,
  0B0000000000000001,
  0B0000000000000011,
  0B0000000000000111,
  0B0000000000001111,
  0B0000000000011111,
  0B0000000000111111,
  0B0000000001111111,
  0B0000000011111111,
  };

void LEDSetting(int level, unsigned int state){       // 한 freq level에 특정 개수 led on
  digitalWrite(level, LOW); //해당 열 open
  for(int i=0;i<ampnum;i++){    
    digitalWrite(amplitude[i],(bitRead(state, i)));   // led on     
    }
  delay(1);
  for(int i=0;i<ampnum;i++){     
    digitalWrite(amplitude[i], LOW);                  // led off
    }
  digitalWrite(level, HIGH); //해당 열 close   
}

void setup()
{  
  for(int i=0;i<freqnum;i++){
    pinMode(frequency[i], OUTPUT);      // 층 선언
    digitalWrite(frequency[i], HIGH);    // 각 층 비활성화
  }  
  for(int i=0;i<ampnum;i++){
    pinMode(amplitude[i], OUTPUT);       // 칸 선언
  }
}

void loop()
{
  int randNum[8];
  for (int i = 0; i<ampnum; i++){
    randNum[i] = random(8)+1;     // 1~8개 중 랜덤
  }
  for(int j=0;j<delaytime;j++){  // delaytime 시간만큼 해당 패턴을 유지
    for(int f=0; f<freqnum; f++){
      LEDSetting(frequency[f], numberPattern[randNum[f]]);  // f층: randNum[f]개의 LED ON        
    }
  }
}
