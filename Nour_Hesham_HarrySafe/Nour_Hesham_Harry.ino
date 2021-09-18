const int ir_right= 4; 
const int ir_left = 5;
const int ir_forward = 6;

void setup() {
pinMode(4,INPUT);
pinMode(5, INPUT);
pinMode(6, INPUT);
pinMode(13,OUTPUT);//LED
}

void loop() {
  //left-hand wall algorithm
  if(existLeft())
    rotate90left();
  else if(existForward())
    moveForward();
  else if(existRight())
    rotate90right();
  else
  {
    rotate90right();
    rotate90right();    
  }
}

int existRight()
{
  if(digitalRead(ir_right) == HIGH)
    return 1;
  return 0;  
}
int existLeft()
{
  if(digitalRead(ir_left) == HIGH)
    return 1;
  return 0;  
}
int existForward()
{
  if(digitalRead(ir_forward) == HIGH)
    return 1;
  return 0;  
}

void rotate90left(){};
void rotate90right(){};
void moveForward(){};
void moveBackward(){};
