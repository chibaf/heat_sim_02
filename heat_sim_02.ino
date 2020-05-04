float dT,Ttarget,Troom,T;

float Wcool()
{
  float Troom=20;
  float Hcond=0.2;
  float W=Hcond*(dT+Ttarget-Troom);
  return W;
}

float dt = 0.05;
float Kp = 0.0;     
float Kd = 0.0;
float Ki = 0.0;
float t;  
byte incomingByte; // for incoming serial data
int dec;


void setup() {
  Serial.begin(9600);
}

void loop() {
if (Serial.available() > 0) {
   incomingByte = Serial.read();
   dec=(int)incomingByte;

for(int i=0; i<100; i++)
  {
  if (Kp < 0.0)    // #比例ゲイン
    {Kp += 0.01;}
  else if (Ki < 0.001) //:  #積分ゲイン
    {Ki += 0.001;}
  else if( Kd < 0.5) //    #微分ゲイン
    {Kd += 0.01;}
        
  float Q=2000; // #initial condition
  float H=3.36;
  T=Q/H-273;
  //print("Treal=",T)
  float Wheat=280; // #initial condition
  Ttarget=650;
  dT=T-Ttarget;
  
  for (i=0; i<int(20/dt); i++)
    {t = i*dt;    
    dT=Ttarget-T;
    T += dt*(Wheat/H);
    //print("Wcool=",f'{Wcool():.4f}')
    //print("Wheat=",f'{Wheat:.4f}')
    Wheat += Kp*(dT) +Kd*(Wheat/H) +Ki*(dT*dt);
    //print("Wheat=",f'{Wheat:.4f}')
    Q +=Wheat-Wcool();
    //#W_heat=Input_of_Control_Loop=heater_power_input
    //print("dT=",f'{dT:.4f}')
    }
  }
  Serial.println(T);
}
}
