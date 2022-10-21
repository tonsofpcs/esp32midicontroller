#define num_btn 9
#define num_enc 4
#define num_fader 4
//TODO: add includes, remove default comments

int i;
int tbar, fader[num_fader], enc[num_enc], shuttle, jog, btn[num_btn];
int tbar_old, fader_old[num_fader] = {0,0,0,0}, enc_old[num_enc] = {0,0,0,0}, shuttle_old, jog_old, btn_old[num_btn];
int tbar_midi = 1, fader_midi[num_fader] = {2,3,4,5}, enc_midi[num_enc] = {6,7,8,9}, shuttle_midi = 10, jog_midi = 11, btn_midi[num_btn] = {12,13,14,15,16,17,18,19,20};
//int tbar_pin = 1, fader_pin[4] = {2,3,4,5}, enc_pin[4][2] = {{6,7},{8,9},{10,11},{12,13}}, shuttle_pin = 14, jog_pin[2] = {15,16}, btn_pin = 17;
int tbar_pin = 36, //ADC1_0
fader_pin[num_fader] = {39,34,35,32}, //ADC1_3, ADC1_6, ADC1_7, ADC1_4
enc_pin[num_enc][2] = {{1,3},{17,16},{23,22},{19,18}}, //U0 TX/RX, U2 TX/RX, VSPI MOSI/SCL, VSPI MISO/SCK
shuttle_pin = 33, //ADC1_5
jog_pin[2] = {5,21}, //VSPI_CS / SDA
btn_pin[num_btn] = {25,26,27,14,12,13,15,2,4}; //"ADC2"_8,9,7,6,5,4,3,2,0 //27;  (Original design was for resistors and a single analog pin but ADC2 is unavailable with bluetooth)

int midi_send(int channel, int value) {
  //TODO: Code to send Midi control channel changes
}

int midi_on(int note, int value) {
  //TODO: code to send midi noteon
}

int midi_off(int note) {
  //TODO: code to send midi noteoff
}

int midi_button(int note, int value) {
  if (value == 1) {
    midi_on(note, 127);
  } else {
    midi_off(note);
  }
}

void setup() {
  // put your setup code here, to run once:
  //TODO: Analog read once directly to _old
}

void loop() {
  // put your main code here, to run repeatedly:
  //TODO: READ AND UPDATE ENCODER VALUES

  for(i=0; i < num_btn; i++){
    btn[i] = analogRead(btn_pin[i]);
  }
  for(i=0; i < num_fader; i++){
    fader[i] = analogRead(fader_pin[i]);
  }
  for(i=0; i < num_enc; i++){
    //enc[i] = enc[i] + (enc_pin[i][0]) - (enc_pin[i][1]) 
  }
  tbar = analogRead(tbar_pin);
  shuttle = analogRead(shuttle_pin);
  //jog = jogcount;



  //COMPARE VALUES TO _old AND SEND MIDI UPDATES
  for(i=0; i < num_btn; i++){
    if (btn[i] != btn_old[i]) {
      midi_button(btn_midi[i], btn[i]);
    }
    btn_old[i] = btn[i];
  }
  for(i=0; i < num_fader; i++){
    if (fader[i] != fader_old[i]) {
      midi_send(fader_midi[i], fader[i]/32);
    }
    fader_old[i] = fader[i];
  }
  for(i=0; i < num_enc; i++){
    if (enc[i] != enc_old[i]) {
      midi_send(enc_midi[i], (enc[i]-enc_old[i]+64));
    }
    enc_old[i] = enc[i];
  }
  if (tbar != tbar_old) {
    midi_send(tbar_midi, tbar/32);
  }
  if (shuttle != shuttle_old) {
    midi_send(shuttle_midi, shuttle);
  }
  if (jog != jog_old) {
    midi_send(jog_midi, (jog-jog_old+64));
  }
}
