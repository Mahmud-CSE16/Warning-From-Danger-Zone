// connect motor controller pins to Arduino digital pins
// motor one
int enL = 5;
int L1 = 2;
int L2 = 3;
// motor two
int enR = 6;
int R1 = 4;
int R2 = 7;

//ldr sensor pin
int ldrPinF=A3;
int ldrPinL=A2;
int ldrPinR=A1;
int ldrPinB=A0;

//ldrsensor value
int ldrF;
int ldrL;
int ldrR;
int ldrB;

//motor speed;
int max=80;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  ldrSensorRead();
  if(ldrF>ldrL && ldrF>=ldrR && ldrF>=ldrB){
    set_motors(max,max); //forward
  }
  if(ldrL>ldrF && ldrL>=ldrR && ldrL>=ldrB){
    set_motors(-max,max); //left
  }
  if(ldrR>ldrF && ldrR>=ldrL && ldrR>=ldrB){
    set_motors(max,-max); //right
  }
  if(ldrB>ldrF && ldrB>=ldrL && ldrB>=ldrR){
    set_motors(-max,-max); //back
  }
}

int set_motors(int l,int r){   //motor setup
  if(l==0 && r== 0){
    analogWrite(enL,0);
    analogWrite(enR,0);
    Serial.println("Stop.");
    
    digitalWrite(L1,HIGH);
    digitalWrite(L2,HIGH);
    
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
  }
  else if(l>=0 && r>=0){
    analogWrite(enL,l);
    analogWrite(enR,r);
    Serial.println("Stright.");
    
    digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
    
    digitalWrite(R1,HIGH);
    digitalWrite(R2,LOW);
  }
  else if(l<=0 && r>=0){
    analogWrite(enL,mod(l));
    analogWrite(enR,mod(r));
    Serial.println("Left.");
    
    digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
    
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }
  else if(l>=0 && r<=0){
    analogWrite(enL,mod(l));
    analogWrite(enR,mod(r));
    Serial.println("Right.");
    
    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
    
    digitalWrite(R1,HIGH);
    digitalWrite(R2,LOW);
  }else if(l<=0 && r<=0){
    analogWrite(enL,l);
    analogWrite(enR,r);
    Serial.println("Back.");
    
    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
    
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
  }

}

void ldrSensorRead(){
  ldrF=analogRead(ldrPinF);
  Serial.print("ldrF:");
  Serial.println(ldrF);
  ldrL=analogRead(ldrPinL);
  Serial.print("ldrL:");
  Serial.println(ldrL);
  ldrR=analogRead(ldrPinR);
  Serial.print("ldrR:");
  Serial.println(ldrR);
  ldrB=analogRead(ldrPinB);
  Serial.print("ldrB:");
  Serial.println(ldrB);
  
}

int mod(int v){
  if(v<0){
    return -1*v;
  }
  else if(v>0){
    return v;
  }
  return v;
}
