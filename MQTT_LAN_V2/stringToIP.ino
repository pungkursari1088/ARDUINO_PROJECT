// Function to convert a string IP address to an integer array
void stringToIP(String ipString, int ipArray[4]) {
  int index = 0;
  int start = 0;
  int dotIndex;

  for (int i = 0; i < 4; i++) {
    dotIndex = ipString.indexOf('.', start);  // Find the next dot
    if (dotIndex == -1) {
      dotIndex = ipString.length();  // Handle the last part after the last dot
    }

    // Extract the substring and convert it to an integer
    ipArray[i] = ipString.substring(start, dotIndex).toInt();

    // Update the starting index for the next part
    start = dotIndex + 1;
  }
}