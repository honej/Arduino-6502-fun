// reads data from RAM and puts on the data bus
void RAM_read(int address) {
    digitalWrite(data_bus_pins[0], m_RAM[address] & B00000001);
    digitalWrite(data_bus_pins[1], m_RAM[address] & B00000010);
    digitalWrite(data_bus_pins[2], m_RAM[address] & B00000100);
    digitalWrite(data_bus_pins[3], m_RAM[address] & B00001000);
    digitalWrite(data_bus_pins[4], m_RAM[address] & B00010000);
    digitalWrite(data_bus_pins[5], m_RAM[address] & B00100000);
    digitalWrite(data_bus_pins[6], m_RAM[address] & B01000000);
    digitalWrite(data_bus_pins[7], m_RAM[address] & B10000000);
} // of RAM_read


// reads data from data bus and puts them in RAM
void RAM_write(int address) {
byte temp;
int i, j=7;
for (i=0; i<8; i++) {
  temp += digitalRead(data_bus_pins[j]*pow(2,i)); 
  j--;
}
m_RAM[address] = temp;
} // of RAM_write


// sends RESET signal to processor - should be done soon after turning on the device
void processor_reset() {
  digitalWrite(resetPin,LOW);
  delay(1000);
  digitalWrite(resetPin,HIGH);
}


// NOP on data bus - 11101010b - temp function
void send_NOP() {
  digitalWrite(42,HIGH);
  digitalWrite(43,HIGH);
  digitalWrite(44,HIGH);
  digitalWrite(46,HIGH);
  digitalWrite(48,HIGH);
}

void clock_tick() {
  digitalWrite(clockPin, LOW); 
  delay(1);
  digitalWrite(clockPin, HIGH);
}

