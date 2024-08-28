// void saveCheckboxState() {
//   File file = SPIFFS.open("/checkbox_state.txt", FILE_WRITE);
//   if (!file) {
//     Serial.println("Failed to open file for writing");
//     return;
//   }

//   for (int i = 0; i < 32; i++) {
//     checkboxState[i] = "unchecked";
//   }

//   for (int i = 0; i < server.args(); i++) {
//     if (server.argName(i) == "checkbox[]") {
//       int index = server.arg(i).toInt() - 1;
//       checkboxState[index] = "checked";
//     }
//   }

//   for (int i = 0; i < 32; i++) {
//     file.println(checkboxState[i]);
//   }

//   file.close();
// }

// void loadCheckboxState() {
//   File file = SPIFFS.open("/checkbox_state.txt", FILE_READ);
//   if (!file) {
//     Serial.println("Failed to open file for reading");
//     return;
//   }

//   for (int i = 0; i < 32; i++) {
//     if (file.available()) {
//       checkboxState[i] = file.readStringUntil('\n');
//       checkboxState[i].trim(); // Remove any trailing newline characters
//     } else {
//       checkboxState[i] = "unchecked";
//     }
//   }

//   file.close();
// }