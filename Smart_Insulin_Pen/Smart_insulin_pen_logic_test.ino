  int vol;
  int value;
  int initial_flag=0;
  int dose=0;
  int temp=0; 
  int dose_temp=0;
  int switch_input;
  //int switch_val;
  int count=0;
  int flag=0;
  int taken=0;
  int up=0;
  int down=0;
  
  void setup()
  {
    pinMode(A0,INPUT);
    pinMode(3,INPUT); //Switch
    pinMode(4,OUTPUT); //LED +ve
    pinMode(5,OUTPUT); //LED -ve
    pinMode(6,OUTPUT); //Buzzer +ve
    pinMode(7,OUTPUT); //Buzzer -ve
    
    Serial.begin(9600);
  }
  
  void loop()
  {
    //1. Store previous dosage value to temp for comparison and get new dosage value
    
    switch_input=digitalRead(3);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    temp=dose;
    vol=analogRead(A0);
    vol=vol*5/1023;
    dose=voltage_to_dosage(vol);
    //else
    //dose=0;
    //Serial.println(dose);
    
    //2. make sure initial value of dosage starts with zero for proper up down counting
    if(initial_flag==0 and dose!=0)
    {
      reset_pen_knob();
    }
    else if(initial_flag==0 and dose==0)
    {
      initial_flag=1;
    }
    
    //3. Perform up down counting and set stable-flag to 1 if the knob stops at a particular value     
    if(dose>temp)
    {
      up++;
    }
    else if(dose<temp)
    {
      down++;
    }
  
      //delay(100);
      if(dose!=0 && dose==temp)
      {
        count++;
      }
      else
      {
        count=0;
      }
      if(count>=200)
      {
        flag=1; // stopped at some particular non-zero value (dosage) 
      }
      else
      {
        flag=0;
      }  
     
      if(flag==1)
      {
        dose_temp=dose;
        delay(200);
        while(switch_input==0)
        {
          vol=analogRead(A0);
          vol=vol*5/1023;
          dose=voltage_to_dosage(vol);
          value=dose;
          if(dose!=dose_temp)
           {
             if(dose>temp)
               {
                 up++;
               }
             else if(dose<temp)
               {
                down++;
               }
             value=0;
             taken=0;
             dose_temp=0;
             break;
           }
       /*   else if(switch_input==1)
          {
            digitalWrite(4,HIGH);
            digitalWrite(5,LOW);
       
            while(up!=down)
            {
              vol=analogRead(A0);
              vol=vol*5/1023;
              dose=voltage_to_dosage(vol);
             if(dose>temp)
               {
                 up++;
               }
             else if(dose<temp)
               {
                down++;
               }
            } 
            up=0;
            down=0;
            taken=1;
            break;
          } */
         // Serial.print(value);
         // Serial.println(taken);
        } 
      }  
   
      Serial.print(flag);
      Serial.print(up);
      Serial.println(down);
         
  }
  
  int voltage_to_dosage(int voltage)
  {
    int dosage;
    
    if (voltage>=0.00 && voltage<0.45)
    dosage=15 ;
    else if (voltage>0.46 && voltage<1.35)
    dosage=12 ;
    else if (voltage>1.36 && voltage<2.25)
    dosage=9 ;
    else if (voltage>2.26 && voltage<3.15)
    dosage=6 ;
    else if (voltage>3.16 && voltage<4.05)
    dosage=3 ;
    else if (voltage>4.06 && voltage<=5.0)
    dosage=0 ;
    
    return dosage;
  }
  
  void reset_pen_knob(void)
  {
    
    while(dose!=0)
    {
      Serial.println("Need to reset!");
     vol=analogRead(A0);
     vol=vol*5/1023;
     dose=voltage_to_dosage(vol);
    }
    
    initial_flag=1;
  }
  
