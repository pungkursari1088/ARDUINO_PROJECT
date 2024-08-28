// void DigitalInputESP(){
//     unsigned long currentMillis = millis();
//   unsigned long now = millis();
//   frameCount++; 
  
//   byte Switch[chips];
  
//   digitalWrite(LATCH, LOW); 
//   digitalWrite(LATCH, HIGH); 
  
//    for (byte i = 0; i < chips; i++) { 
//     Switch[i] = SPI.transfer(0); 
//   }
    
//   if (now - lastMillis >= seconds * 1000) {
//     framesPerSecond = frameCount / seconds;
    
//     for (byte i = 0; i < chips; i++) { 
//       if (Switch[i] != 0) {
//         //INPUT 1
//         if (Switch[i] == 255) {
//           Serial.println("input 255");
//         }        
      
//         //INPUT 2
//         else if (Switch[i] == 239) {  
//           for(int i=0;i<4;i++){
//             if(checkboxState[i]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//           Serial.println("input 239");
//         }

//         //INPUT 3
//         else if (Switch[i] == 223) {
//           Serial.println("input 223");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+4]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }

//         //INPUT 4
//         else if (Switch[i] == 191) {
//           Serial.println("input 191");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+8]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }

//         //INPUT 5
//         else if (Switch[i] == 127) {
//           Serial.println("input 127");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+12]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }
        
//         //INPUT 6
//         else if (Switch[i] == 254) {
//           Serial.println("input 254");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+16]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }

//         //INPUT 7
//         else if (Switch[i] == 253) {
//           Serial.println("input 253");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+20]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }
      
//         //INPUT 8
//         else if (Switch[i] == 251) {
//           Serial.println("input 251");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+24]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }

//         //INPUT 9
//         else if (Switch[i] == 247) {
//           Serial.println("input 247");
//           for(int i=0;i<4;i++){
//             if(checkboxState[i+28]=="checked")digitalWrite(DO[i], HIGH);
//             else{
//               digitalWrite(DO[i], LOW);
//             }
//           }
//         }

//       }
//     }
//      frameCount = 0;
//      lastMillis = now;
//    }
// }