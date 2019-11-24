int frequency[7] = {A0,A1,A2,A3,A4,A5,A6};
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
///////////////////////// 여기부터 ///////////////////////////
void LEDSetting(int frequency, unsigned int state){   // 확인해보고 고치자
  digitalWrite(frequency, HIGH); //층 개방
  for(int i=0;i<9;i++){    
    digitalWrite(amplitude[i],not(bitRead(state, i))); // 패턴 코드에 따라 칸 개방     
    }
  delay(1);
  for(int i=0;i<9;i++){     
    digitalWrite(amplitude[i], LOW);   // 모든 칸 닫힘      
    }
  digitalWrite(frequency, LOW); //층 닫힘    
}
/*
void LEDSetting(int frequency, unsigned int state){   // 좀 더 짧은 이 코드는 동작할까?
  digitalWrite(frequency, HIGH); //층 개방
  for(int i=0;i<9;i++){    
    digitalWrite(amplitude[i],not(bitRead(state, i))); // 패턴 코드에 따라 칸 개방     
    delay(1);
    }
  digitalWrite(frequency, LOW); //층 닫힘    
}
*/
void setup()
{  
  for(int i=0;i<freqnum;i++){
    pinMode(frequency[i], OUTPUT);      // 층 선언
    digitalWrite(frequency[i], LOW);    // 각 층 비활성화
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