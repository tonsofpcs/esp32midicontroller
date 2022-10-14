//TODO: add includes, remove default comments

int tbar, fader[4], enc[4], shuttle, jog, btn[9];
int tbar_old, fader_old[4], enc_old[4], shuttle_old, jog_old, btn_old[9];
int tbar_midi = 1, fader_midi[4] = {2,3,4,5}, enc_midi[4] = {6,7,8,9}, shuttle_midi = 10, jog_midi = 11, btn_midi[9] = {12,13,14,15,16,17,18,19,20};
int tbar_pin = 1, fader_pin[4] = {2,3,4,5}, enc_pin[4][2] = {{6,7},{8,9},{10,11},{12,13}}, shuttle_pin = 14, jog_pin[2] = {15,16}, btn_pin = 17;

int midi_send(channel as int, value as int) {
  //TODO: Code to send Midi control channel changes
}

int midi_on(note as int, value as int) {
  //TODO: code to send midi noteon
}

int midi_off(note as int) {
  //TODO: code to send midi noteoff
}

int midi_button(note as int, value as int) {
  if (value == 1) {
    midi_on(note, 127);
  } else {
    midi_off(note);
  }
}

void setup() {
  // put your setup code here, to run once:
  //TODO: Analog read once directly to _old
  fader_old = {0,0,0,0};
  enc_old = {0,0,0,0};
}

void loop() {
  // put your main code here, to run repeatedly:
  //TODO: READ AND UPDATE VALUES

  //COMPARE VALUES TO _old AND SEND MIDI UPDATES
  for(i=0; i < 9, i++){
    if btn[i] != btn_old[i] {
      midibutton(btn_midi[i], btn[i]);
    }
    btn_old[i] = btn[i];
  }
  for(i=0; i < 4, i++){
    if fader[i] != fader_old[i] {
      midi_send(fader_midi[i], fader[i]/32);
    }
    if enc[i] != enc_old[i] {
      midi_send(enc_midi[i], (enc[i]-enc_old[i]+64));
    }
    fader_old[i] = fader[i];
    enc_old[i] = enc[i];
  }
  if tbar[i] != tbar_old[i] {
    midi_send(tbar_midi[i], tbar[i]/32);
  }
  if shuttle[i] != shuttle_old[i] {
    midi_send(shuttle_midi[i], shuttle[i]);
  }
  if jog[i] != jog_old[i] {
    midi_send(jog_midi[i], (jog[i]-jog_old[i]+64));
  }
}
