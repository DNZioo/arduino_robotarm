#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(3, 4); // RX, TX

Servo servo1;  // BASE
Servo servo2;  // SHOULDER1
Servo servo3;  // SHOULDER2 (not used in this project)
Servo servo4;  // ELBOW1
Servo servo5;  // ELBOW2
Servo servo6;  // WRIST
Servo servo7;  // GRIPPER

// Speed settings (smaller is faster)
int s1Vel = 15;  // BASE
int s2Vel = 25;  // SHOULDER1
int s4Vel = 20;  // ELBOW1
int s5Vel = 20;  // ELBOW2
int s6Vel = 15;  // WRIST
int s7Vel = 15; // GRIPPER

int index = 0;
int velG = 25;

int s1Act, s2Act, s3Act, s4Act, s5Act, s6Act, s7Act;  // Current positions of servos
int s1Ant, s2Ant, s3Ant, s4Ant, s5Ant, s6Ant, s7Ant;  // Previous positions of servos
int s1[50], s2[50], s3[50], s4[50], s5[50], s6[50], s7[50]; // Arrays to store positions of each servo

String bt, btS;

void setup() {
  Serial.begin(115200);
  Bluetooth.begin(9600);
  Bluetooth.setTimeout(10);

  // Attach servos with specific PWM width for each servo model
  servo1.attach(5, 500, 2400);   // MG996R base
  servo2.attach(11, 500, 2400);  // MG946R shoulder1
  servo3.attach(6, 500, 2400);   // MG946R shoulder2
  servo4.attach(7, 500, 2400);   // MG946R elbow1
  servo5.attach(8, 500, 2400);   // MG995 elbow2
  servo6.attach(9, 500, 2400);   // MG995 wrist
  servo7.attach(10, 500, 2400);  // MG995 gripper

  // Initialize servo positions
  s1Ant = 90;  // BASE
  servo1.write(s1Ant);

  // It's important to start shoulder servos in complementary positions so that s2 + s3 = 180;
  s2Ant = 100; // SHOULDER1 
  s3Ant = 80;  // SHOULDER2
  servo2.write(s2Ant); 
  servo3.write(s3Ant);

  s4Ant = 115; // ELBOW1
  servo4.write(s4Ant);

  s5Ant = 60;  // ELBOW2
  servo5.write(s5Ant);

  s6Ant = 90;  // WRIST
  servo6.write(s6Ant);

  s7Ant = 0;  // GRIPPER
  servo7.write(s7Ant);

  delay(10);
}

void loop() {
  if (Bluetooth.available() > 0) {
    bt = Bluetooth.readString();  // Read the Bluetooth command
    Serial.println(bt); // Print received Bluetooth data to Serial monitor

    // ////////////////////////// SERVO 1 - BASE //////////////////////////
    if (bt.startsWith("s1")) {  // Check if command is for servo1
      btS = bt.substring(2, bt.length()); // Extract the angle value from command
      s1Act = btS.toInt();  // Convert to integer
      Serial.print("Servo 1 command received: ");
      Serial.println(s1Act);
      
      // Move servo with a sweep
      if (s1Ant > s1Act) {
        for (int j = s1Ant; j >= s1Act; j--) {
          servo1.write(j);
          delay(s1Vel);
        }
      } else {
        for (int j = s1Ant; j <= s1Act; j++) {
          servo1.write(j);
          delay(s1Vel);
        }
      }
      s1Ant = s1Act;  // Update the previous position
    }

    // ////////////////////////// SERVO 2 and 3 - SHOULDER 1 and 2 //////////////////////////
    if (bt.startsWith("s2")) {
      btS = bt.substring(2, bt.length());
      s2Act = btS.toInt();
      Serial.print("Servo 2 command received: ");
      Serial.println(s2Act);
      if (s2Ant > s2Act) {
        for (int j = s2Ant; j >= s2Act; j--) {
          servo2.write(j);
          servo3.write(180 - j);
          delay(s2Vel);
        }
      } else {
        for (int j = s2Ant; j <= s2Act; j++) {
          servo2.write(j);
          servo3.write(180 - j);
          delay(s2Vel);
        }
      }
      s2Ant = s2Act;
    }

    // ////////////////////////// SERVO 4 - ELBOW1 //////////////////////////
    if (bt.startsWith("s4")) {
      btS = bt.substring(2, bt.length());
      s4Act = btS.toInt();
      Serial.print("Servo 4 command received: ");
      Serial.println(s4Act);
      if (s4Ant > s4Act) {
        for (int j = s4Ant; j >= s4Act; j--) {
          servo4.write(j);
          delay(s4Vel);
        }
      } else {
        for (int j = s4Ant; j <= s4Act; j++) {
          servo4.write(j);
          delay(s4Vel);
        }
      }
      s4Ant = s4Act;
    }

    // ////////////////////////// SERVO 5 - ELBOW2 //////////////////////////
    if (bt.startsWith("s5")) {
      btS = bt.substring(2, bt.length());
      s5Act = btS.toInt();
      Serial.print("Servo 5 command received: ");
      Serial.println(s5Act);
      if (s5Ant > s5Act) {
        for (int j = s5Ant; j >= s5Act; j--) {
          servo5.write(j);
          delay(s5Vel);
        }
      } else {
        for (int j = s5Ant; j <= s5Act; j++) {
          servo5.write(j);
          delay(s5Vel);
        }
      }
      s5Ant = s5Act;
    }

    // ////////////////////////// SERVO 6 - WRIST //////////////////////////
    if (bt.startsWith("s6")) {
      btS = bt.substring(2, bt.length());
      s6Act = btS.toInt();
      Serial.print("Servo 6 command received: ");
      Serial.println(s6Act);
      if (s6Ant > s6Act) {
        for (int j = s6Ant; j >= s6Act; j--) {
          servo6.write(j);
          delay(s6Vel);
        }
      } else {
        for (int j = s6Ant; j <= s6Act; j++) {
          servo6.write(j);
          delay(s6Vel);
        }
      }
      s6Ant = s6Act;
    }

    // ////////////////////////// SERVO 7 - GRIPPER //////////////////////////
    if (bt.startsWith("s7")) {
      btS = bt.substring(2, bt.length());
      s7Act = btS.toInt();
      Serial.print("Servo 7 command received: ");
      Serial.println(s7Act);
      if (s7Ant > s7Act) {
        for (int j = s7Ant; j >= s7Act; j--) {
          servo7.write(j);
          delay(s7Vel);
        }
      } else {
        for (int j = s7Ant; j <= s7Act; j++) {
          servo7.write(j);
          delay(s7Vel);
        }
      }
      s7Ant = s7Act;
    }

   //////////////////////////// SAVE //////////////////////////////////////////////////
        if(bt.startsWith("SAVE")){
           s1[index]= s1Ant;
           s2[index]= s2Ant;
           s4[index]= s4Ant;
           s5[index]= s5Ant;
           s6[index]= s6Ant;
           s7[index]= s7Ant;
           index++;}
        ///////////////////////// RESET ///////////////////////////////////////////////////            
        if(bt.startsWith("RESET")){
          //memset se utiliza para rellenar un bloque de memoria con un valor determinado
          //memeset("matriz","dato a rellenar","tamaño de la matriz")
           memset(s1,0,sizeof(s1)); //rellena con el valor de "0" todas las posiciones de la matriz
           memset(s2,0,sizeof(s2));
           memset(s4,0,sizeof(s4));
           memset(s5,0,sizeof(s5));
           memset(s6,0,sizeof(s6));
           memset(s7,0,sizeof(s7)); 
           index=0;}             
        //////////////////////////// RUN ////////////////////////////////////////////////////
        if(bt.startsWith("RUN")){
           //Ejecuta los pasos una y otra vez hasta que se pulse el botón "RESET" o espera hasta que se vuelva a pulsar "RESET"
           while(bt.startsWith("RESET") != true){//MIENTRAS NO SE PRESIONE 'RESET' SE MANTIENE EN EL BUCLE y SOLO FUNCIONA BOTON "PAUSE"
                 for(int i=0; i<= index-2;i++){                      
                     if(Bluetooth.available()>0){
                        bt = Bluetooth.readString(); 
                        if(bt.startsWith("PAUSE") == true){
                           //Ejecuta los pasos una y otra vez hasta que se pulse el botón "RUN" o espera hasta que se vuelva a pulsar "RUN"                     
                           while(bt.startsWith("RUN") != true){//MIENTRAS NO SE PRESIONE 'RUN' SE MANTIENE EN EL BUCLE Y SOLO FUNCIONA BOTON "RESET"
                                 if(Bluetooth.available()>0){
                                    bt = Bluetooth.readString();
                                    if(bt.startsWith("RESET") == true){
                                       break;}
                                 }
                           }                                            
                        }//end if(PAUSE)
                        if(bt.startsWith("ss")){
                           btS  = bt.substring(2,bt.length());   
                           velG = btS.toInt();}
                     }//end 1er Bluetooth.available
                     //////// SERVO 1 ////////////////////////
                     if(s1[i] == s1[i+1]){}
                     
                     if(s1[i] > s1[i+1]){
                        for(int j = s1[i]; j >= s1[i+1];j--){
                            servo1.write(j);
                            delay(velG);}}
                            
                     if(s1[i] < s1[i+1]){ 
                        for(int j = s1[i]; j <= s1[i+1];j++){
                            servo1.write(j);
                            delay(velG);}} 
                     //////// SERVO 2 y 3 /////////////////////
                     if(s2[i] == s2[i+1]){}
                     
                     if(s2[i] > s2[i+1]){
                        for(int j = s2[i]; j >= s2[i+1];j--){
                            servo2.write(j);
                            servo3.write(180-j);
                            delay(velG);}}
                            
                     if(s2[i] < s2[i+1]){ 
                        for(int j = s2[i]; j <= s2[i+1];j++){
                            servo2.write(j);
                            servo3.write(180-j);
                            delay(velG);}}
                     //////// SERVO 4 ////////////////////////
                     if(s4[i] == s4[i+1]){}
                     
                     if(s4[i] > s4[i+1]){
                        for(int j = s4[i]; j >= s4[i+1];j--){
                            servo4.write(j);
                            delay(velG);}}
                            
                     if(s4[i] < s4[i+1]){ 
                        for(int j = s4[i]; j <= s4[i+1];j++){
                            servo4.write(j);
                            delay(velG);}}  
                     //////// SERVO 5 ////////////////////////
                     if(s5[i] == s5[i+1]){}
                     
                     if(s5[i] > s5[i+1]){
                        for(int j = s5[i]; j >= s5[i+1];j--){
                            servo5.write(j);
                            delay(velG);}}
                            
                     if(s5[i] < s5[i+1]){ 
                        for(int j = s5[i]; j <= s5[i+1];j++){
                            servo5.write(j);
                            delay(velG);}}                                                         
                     //////// SERVO 6 ////////////////////////
                     if(s6[i] == s6[i+1]){}
                     
                     if(s6[i] > s6[i+1]){
                        for(int j = s6[i]; j >= s6[i+1];j--){
                            servo6.write(j);
                            delay(velG);}}
                            
                     if(s6[i] < s6[i+1]){ 
                        for(int j = s6[i]; j <= s6[i+1];j++){
                            servo6.write(j);
                            delay(velG);}} 
                     //////// SERVO 7 ////////////////////////
                     if(s7[i] == s7[i+1]){}
                     
                     if(s7[i] > s7[i+1]){
                        for(int j = s7[i]; j >= s7[i+1];j--){
                            servo7.write(j);
                            delay(velG);}}
                            
                     if(s7[i] < s7[i+1]){ 
                        for(int j = s7[i]; j <= s7[i+1];j++){
                            servo7.write(j);
                            delay(velG);}}                                                                                                         
              }// end FOR INDEX                 
           }//end 1er WHILE "RESET"
        }
                 
     }//if(Bluetooth.available()>0){         
}//end void loop

