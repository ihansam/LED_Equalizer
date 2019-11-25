int layer[3] = {A0,A1,A2};
int room[9] = {10,9,8,7,6,5,4,3,2};
int m_layer = 3;    // 층 수
int m_room = 9;     // 칸 수

void setup()
{  
  for(int i=0;i<m_layer;i++){
    pinMode(layer[i], OUTPUT);      // 층 선언
    digitalWrite(layer[i], LOW);    // 각 층 비활성화
  }  
  for(int i=0;i<m_room;i++){
    pinMode(room[i], OUTPUT);       // 칸 선언
  }
}

void loop()     // 정육면체의 대각선 세 LED (0,0), (4,4), (8,8)을 동시에(빠르게 번갈아) 키는 프로그램
{
  for (int i=0; i<m_layer; i++){
    digitalWrite(layer[i],HIGH);    // i층 활성화
    for (int j=0; j<m_room; j++){
      if (j==4*i)                       // 해당 층에서 킬 한 LED만 on
        digitalWrite(room[j],LOW);
      else
        digitalWrite(room[j],HIGH);
      }
    delay(5);                       
    digitalWrite(layer[i],LOW);     // i층 비활성화
    }
}