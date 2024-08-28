
// //Handle the form submission and save the input
// void handleSubmit() {
//   if (server.hasArg("textInput")) {
//     inputText = server.arg("textInput");
//     stringToIP(inputText, ipArray);
//     // Write data to EEPROM
//     EEPROM.begin(512); // Initialize EEPROM
//     for (int i = 0; i < 4; i++) {
//         EEPROM.put(address + i * sizeof(int), ipArray[i]); // Save data to EEPROM
//     }
//     EEPROM.commit(); // Commit the saved data
//     EEPROM.end(); // Free the EEPROM resources
//     Serial.println("Data saved to EEPROM.");

//     server.send(200, "text/html", index_html);
//     Serial.println("data terkirim");
//   } else {
//     server.send(400, "text/html", "No text received");
//     Serial.println("data tidak terkirim");
//   }
// }

// void espReset(){
//   server.send(200, "text/html",index_html);
//   ESP.restart();
// }

void handleHTML(){
  server.send(200, "text/html",index_html);
  ESP.restart();
}

String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
  //   buttons += "<h4>Output - GPIO 32</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"32\" " + outputState(DO[0]) + "><span class=\"slider\"></span></label>";

  //   buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(DO[1]) + "><span class=\"slider\"></span></label>";

  //   buttons += "<h4>Output - GPIO 25</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"25\" " + outputState(DO[2]) + "><span class=\"slider\"></span></label>";

  //  buttons += "<h4>Output - GPIO 26</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"26\" " + outputState(DO[3]) + "><span class=\"slider\"></span></label>";
    buttons += "<h2>Output - GPIO 32 - " + outputState(DO[0])+"</h2>";
    return buttons;
  }
  return String();
}

String outputState(int output){
  if(digitalRead(output)){
    return "OFF";
  }
  else {
    return "ON";
  }
}