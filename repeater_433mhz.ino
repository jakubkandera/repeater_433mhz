#include <RCSwitch.h> 

RCSwitch receiver = RCSwitch();
RCSwitch transmitter = RCSwitch();
int bt_scan=5; //scan button
int bt_replay=6; //replay button
//int red_led=12; //red LED - when a signal is sniffed
//int green_led=13; //green LED - when the board is scanning
unsigned long value=0; //data to replay
int length=0; //data length to replay
int protocol=0; //data protocol to replay
int pulse=0; //data pulse

void setup() {
    Serial.begin(9600);
    receiver.enableReceive(0);
//    pinMode(bt_scan, INPUT);
//    pinMode(bt_replay, INPUT);
// pinMode(green_led, OUTPUT);
// pinMode(red_led, OUTPUT);

// digitalWrite(green_led, HIGH);
// digitalWrite(red_led, LOW);
}

void loop() {

    if (receiver.available()) {
// digitalWrite(green_led, LOW);
// digitalWrite(red_led, HIGH);

    Serial.print("Value: ");
    value=receiver.getReceivedValue();
    Serial.print(receiver.getReceivedValue() );
    Serial.print(" / ");
    Serial.print(receiver.getReceivedValue(), BIN);
    
    Serial.print(" Length: ");
    length=receiver.getReceivedBitlength();
    Serial.print(receiver.getReceivedBitlength() );
    
    Serial.print(" Delay: ");
    pulse=receiver.getReceivedDelay();
    Serial.print(receiver.getReceivedDelay() );
    
    Serial.print(" Protocol: ");
    protocol=receiver.getReceivedProtocol();
    Serial.println(receiver.getReceivedProtocol());
    }

// if (digitalRead(bt_replay)) {
 if (value!=0) {
    Serial.print("Button replay pressed: ");
    Serial.print(value);
    Serial.print(" Lenght: ");
    Serial.print(length);
    Serial.print(" Pulse: ");
    Serial.print(pulse);
    Serial.print(" Protocol: ");
    Serial.print(protocol);
    Serial.println("");
    
    receiver.disableReceive();
    transmitter.enableTransmit(10);
    transmitter.setProtocol(protocol);
    transmitter.setRepeatTransmit(15); 
    transmitter.setPulseLength(pulse-15);
    
    if(value == 15147348)
      transmitter.send(4277744, length);
    else
      transmitter.send(value, length);
    
    delay(1000);
    
    value=0;
    protocol=0;
    pulse=0;
    length=0;
    
    receiver.enableReceive(0);
//    digitalWrite(green_led, HIGH);
//    digitalWrite(red_led, LOW);
 }
// }
// if (digitalRead(bt_scan)) {
// Serial.print("Button scan pressed");
//// digitalWrite(green_led, HIGH);
//// digitalWrite(red_led, LOW);
// receiver.resetAvailable();
// } 
}
