//void feed() {
//  if (!pellet) {
//    displayFeed();
//    for (int i = 0; i < 20 + random(0, 10); i++) {
//      if (!pellet) {
//        //myMotor->step(25, FORWARD, DOUBLE);
//        //myMotor->step(50, BACKWARD, DOUBLE);
//	myMotor->step(7, BACKWARD, DOUBLE);
//        myMotor->step(14, FORWARD, DOUBLE);
//        delay(50);
//        queryPI();
//	delay(200);
//      }
//    }
//    myMotor->release();
//  }
//  motorTurns++;
//  if (motorTurns > turnsBeforeClear){
//    pelletJam = true;
//  }
//  else{
//    pelletJam = false;
//  }
//
//delay(500);
//
//// avoid pellet jam
//  if (!pellet){
//	myMotor->step(50, BACKWARD, DOUBLE);
//  }
//
//}
//

void spinTest(){
	long int tic = millis();
	myMotor->step(100, FORWARD, DOUBLE);
	myMotor->release();
	long int toc = millis();
	motorTime = toc - tic;
	}

void spin(){
  if (!pellet){
    for (int i = 0; i < 41 + random(0, 50); i++){
      myMotor->step(i, FORWARD, DOUBLE);
      queryPI();
      if (pellet){
        break; // if pellet was delivered after clearJam exit loop
      }
    }
  }
  myMotor->release();
  numClears++;
  delay(500);
}


void feed() {
  if (!pellet && !pelletJam) {
    displayFeed();
    for (int i = 0; i < 10; i++) {
        queryPI();
      if (!pellet) {
        myMotor->step(10, FORWARD, DOUBLE);
        myMotor->step(0, BACKWARD, DOUBLE);
      }
    }
    myMotor->release();
  }
  motorTurns++;

  if (motorTurns > turnsBeforeClear){
    pelletJam = true;
    motorTurns = 0;
  }
  else{
  	pelletJam = false;
	}

  if (motorTurns > 10){
    doSpin = true;
  }
  else{
    doSpin = false;
  }
}

void clearJam(){
// clear jam is now spinning in the reverse direction
// to avoid jams
// if fails 5 attempts to deliver pellet it makes a spin
  if (!pellet){
    displayFeedCounter();
    for (int i = 0; i < 10; i++) {
        queryPI();
      if (!pellet) {
        myMotor->step(10, BACKWARD, DOUBLE);
        myMotor->step(0, FORWARD, DOUBLE);
      }
    }
  }
  myMotor->release();
  numClears++;
  pelletJam = false;
  delay(500);
}
