/****************************************************/
/*                    PIN MAP                       */
/****************************************************/

#define ENCA 2 // YELLOW
#define SWITCH 3 //INPUT_SWITCH
#define ENCB 10 // WHITE
#define PWM 5
#define IN1 7 
#define IN2 8
#define FREE_RUNNING 0
#define LEARNING     1
/**********************************************************/
/*                   DOOR STATES                          */
/**********************************************************/
#define OPENING 1
#define CLOSING 2
#define OPENED  3
#define CLOSED  4
#define MOVE    6
#define STOP    5
/**********************************************************/
/*                   GLOBALS                              */
/**********************************************************/
volatile static signed int posi=0 ,Door_State = CLOSED,Motor_state = STOP,target=0,dir=0,pwr=0;
void Intialization(void);
int Motor_Mode(unsigned int Mode); 
int Motor_speed(int target);
void setup()
{

   Serial.begin(9600);
   Intialization();
  
}

void loop(){
  
  Serial.print(target);
  Serial.print(" ");
  Serial.print(posi);
  Serial.println();
  
int Mode = Motor_Mode(FREE_RUNNING); 
  }

void Start_Motion()
{
if (Door_State == CLOSED)
{Door_State = OPENING ;

dir = 1 ;
target = 20;
Motor_state = MOVE;
}
if (Door_State == OPENED)
{Door_State = CLOSING;
dir = 0;
 target = 0;
Motor_state = MOVE; 
}
  
}


void setMotor(int dir, int pwmVal)
{
  analogWrite(PWM,pwmVal);
  if(dir == 1){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    
  }
  else if(dir == 0){
    digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);

  }

}
void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
  if(posi == target)
  {Motor_state = STOP;}
}



void Intialization(void){
  
    pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(SWITCH,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(SWITCH),Start_Motion,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  
  
  
  }  

  int Motor_speed(int target){
  int speedy = 0;
    
    return speedy; 
    }
  

  int Motor_Mode(unsigned int Mode)
  {
  switch (Mode){
    case FREE_RUNNING:{
      
  if(Motor_state == STOP) //&& ((Door_State == OPENING)||(Door_State == CLOSING)))
    {  
  
  setMotor(dir, 0);
 
  if(Door_State == OPENING) 
  Door_State = OPENED;
  if(Door_State == CLOSING) 
  Door_State = CLOSED;
   }
  else
   {
  setMotor(dir, 60);

   }
      
      
      break;
      }
    case LEARNING:{
     



      
      
      break;
      }
    
    
    
    
    }  
    
    
    
    
  return Mode;  
  }
