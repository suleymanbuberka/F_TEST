// C++ code
//

const int pin13 = 13; 
const int pin12 = 12;
const int pin11 = 11;
const int pin10 = 10;
const int pin9 = 9;
const int pin8 = 8;
int  Line =0;
int Notr=0;
int PE=0;
String L_L;
String L_N;
String L_PE;
String N_N;
String PE_PE;
void setup()
{
 
 pinMode(pin13, INPUT);
  pinMode(pin12, INPUT);
  pinMode(pin11, INPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin8, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  //Teste Hazır hale gelmesi için
   digitalWrite(8, LOW);
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
  //Line kontrolü
    digitalWrite(8, HIGH);
    Line = digitalRead(pin13);
  if(Line == 1) {
    //LINE DOGRU
    L_L="KISA DEVRE";
      //Serial.println("Uygun");
    digitalWrite(8,LOW);
    digitalWrite(9, HIGH);
    Notr = digitalRead(pin12);
    Line = digitalRead(pin13);
    if(Notr == 1){
    N_N="KISA DEVRE";
    }else {
       N_N="HATALI";
    }
    if(Line == 0){
      L_N="KISA DEVRE DEGİL";
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
     PE = digitalRead(pin11); 
      if(PE == 1){ 
      PE_PE="KISA DEVRE";
      } else {
        PE_PE="HATALI";
      }
      if(Line== 0){
      L_PE="KISA DEVRE DEGİL";
      digitalWrite(10,LOW);
      }
      else{
      L_PE="HATALI";
      }
    } else {
     L_N="HATALI";
    }
  } else {
    //line bağlantısı hatalı 
    L_L="HATALI";
    //sebebi belirtilecek.
  }
    
delay(3000);
    Serial.print("L_L= ");
    Serial.println(L_L);
     Serial.print("N_N= "); 
     Serial.println(N_N);
     Serial.print("PE_PE= ");
     Serial.println(PE_PE);
}