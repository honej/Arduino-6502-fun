
const int clockPin = 53; // clock (37) pin of the processor
const int rwPin = 34; // R/W (34) pin of the processor
const int resetPin = 52; // reset (40) pin of 6052. Low to activate.

const int address_bus_pins[] = {22,23,24,25,26,27,28,29,37,36,35,34,33,32,31,30};
const int rev_address_bus_pins[] = {30,31,32,33,34,35,36,37,29,28,27,26,25,24,23,22}; // just to be more comfortable in some situations

const int data_bus_pins[] = {49,48,47,46,45,44,43,42};

const byte WozMon[256] = {216,88,160,127,140,18,208,169,167,141,17,208,141,19,208,201,223,240,19,201,155,240,3,200,16,15,169,220,32,239,255,169,141,32,239,255,160,1,136,48,246,173,17,208,16,251,173,16,208,153,0,2,32,239,255,201,141,208,212,160,255,169,0,170,10,133,43,200,185,0,2,201,141,240,212,201,174,144,244,240,240,201,186,240,235,201,210,240,59,134,40,134,41,132,42,185,0,2,73,176,201,10,144,6,105,136,201,250,144,17,10,10,10,10,162,4,10,38,40,38,41,202,208,248,200,208,224,196,42,240,151,36,43,80,16,165,40,129,38,230,38,208,181,230,39,76,68,255,108,36,0,48,43,162,2,181,39,149,37,149,35,202,208,247,208,20,169,141,32,239,255,165,37,32,220,255,165,36,32,220,255,169,186,32,239,255,169,160,32,239,255,161,36,32,220,255,134,43,165,36,197,40,165,37,229,41,176,193,230,36,208,2,230,37,165,36,41,7,16,200,72,74,74,74,74,32,229,255,104,41,15,9,176,201,186,144,2,105,6,44,18,208,48,251,141,18,208,96,0,0,0,15,0,255,0,0};
byte m_RAM[65536]; // RAM of our computer

      
void setup() {
  delay(1000); // for 6205 to stabilize after power-on
  int i; 
  Serial.begin(115200);
  pinMode(clockPin, OUTPUT); 
  pinMode(resetPin, OUTPUT);
  pinMode(rwPin, INPUT);
  memset(m_RAM,234,sizeof(m_RAM)); // reset RAM with NOPs (EA)
  // m_RAM[65532] = 0;
  // m_RAM[65533] = 255;

  Serial.println("Honey's device launch");
 // copy WozMon to RAM 
 for(i = 65280 ; i < 65536 ; i++ ){
    m_RAM[i] = WozMon[i-65280];
}
 

// set address bus to INPUT
for (int i = 0; i < 16; ++i)
     pinMode (address_bus_pins[i], INPUT);

// set data bus to OUTPUT (we want 5v here)
for (int i = 0; i < 8; ++i) {
     pinMode (data_bus_pins[i], OUTPUT);
     digitalWrite(data_bus_pins[i], LOW);
}


processor_reset();

} // of setup



void loop() {
  int i, j;
  int address_dec = 0;  // address on address bus in decimal
  char address_bin[8];  // the same address in binary
  digitalWrite(clockPin, LOW); 
  delay(1);
  digitalWrite(clockPin, HIGH);

// Serial.println(digitalRead(rwPin));

for (i=0; i<16; i++) {
  address_bin[i] = (digitalRead(rev_address_bus_pins[i]));
  Serial.print(digitalRead(rev_address_bus_pins[i]));
}


address_dec=0;
j=15;
for (i=0; i<16; i++) {
  address_dec += address_bin[j]*pow(2,i); 
  j--;
}

Serial.print(" - "); Serial.print(address_dec);
Serial.print(" - "); Serial.print(address_dec, HEX);

if (digitalRead(rwPin) == HIGH) {
  RAM_read(address_dec);
  Serial.print(" - R - ");
}
else {
  RAM_write(address_dec);
  Serial.print(" - W - ");
}

Serial.println(m_RAM[address_dec], HEX);

} // of main loop
