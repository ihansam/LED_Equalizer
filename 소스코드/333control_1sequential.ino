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

void loop()
{
  for (int floor=0; floor<m_layer; floor++){    // 0 ~ 2층 반복
    digitalWrite(layer[floor],HIGH);          // floor층 활성화
    for (int i=0; i<m_room; i++){     // 모든 칸에 대해 반복
      for (int j=0; j<m_room; j++){
        if (i==j)
          digitalWrite(room[j],LOW);  // i칸은 on하고
        else
          digitalWrite(room[j],HIGH); // 다른 칸은 off     
        }
        delay(250);      
      }
    digitalWrite(layer[floor], LOW);        // floor층 비활성화
    }        
}