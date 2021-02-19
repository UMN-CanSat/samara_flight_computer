// Functions for the 2.4 Ghz xBee radios

void initXbee() {
  XBEE_SERIAL.begin(XBEE_BAUD);

  // set local xBee parameters
  xBee.enterATmode();
  xBee.atCommand("ATID" + networkID);
  xBee.atCommand(myCmdID);
  xBee.atCommand(destinationCmdID);
  xBee.exitATmode();
}
