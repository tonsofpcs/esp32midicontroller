int tbar, fader[4], enc[4], shuttle, jog, btn[9];
int tbar_o, fader_o[4], enc_o[4], shuttle_o, jog_o, btn_o[9];
int tbar_m = 1, fader_m[4] = {2,3,4,5}, enc_m[4] = {6,7,8,9}, shuttle_m = 10, jog_m = 11, btn_m[9] = {12,13,14,15,16,17,18,19,20};
int tbar_p = 1, fader_p[4] = {2,3,4,5}, enc_p[4][2] = {{6,7},{8,9},{10,11},{12,13}}, shuttle_p = 14, jog_p[2] = {15,16}, btn_p = 17;

void midisend(channel, value){

}

void midion(channel){

}

void midioff(channel, value){

}

void midibtn(channel, value){
  if value == 1 {
    midion(channel, 127)
  } else {
    midioff(channel)
  }
}

void setup() {
  // put your setup code here, to run once:
  //TODO: Analog read once directly to _o
  fader_o = {0,0,0,0};
  enc_o = {0,0,0,0};
}

void loop() {
  // put your main code here, to run repeatedly:
  //READ AND UPDATE VALUES

  //COMPARE VALUES TO _O AND SEND MIDI UPDATES
  for(i=0; i < 9, i++){
    if btn[i] != btn_o[i] {
      midibutton(btn_m[i], btn[i])
    }
    btn_o[i] = btn[i];
  }
  for(i=0; i < 4, i++){
    if fader[i] != fader_o[i] {
      midisend(fader_m[i], fader[i]/32);
    }
    if enc[i] != enc_o[i] {
      midisend(enc_m[i], (enc[i]-enc_o[i]+64));
    }
    fader_o[i] = fader[i];
    enc_o[i] = enc[i];
  }
  if tbar[i] != tbar_o[i] {
    midisend(tbar_m[i], tbar[i]/32);
  }
  if shuttle[i] != shuttle_o[i] {
    midisend(shuttle_m[i], shuttle[i]);
  }
  if jog[i] != jog_o[i] {
    midisend(jog_m[i], (jog[i]-jog_o[i]+64));
  }
}

