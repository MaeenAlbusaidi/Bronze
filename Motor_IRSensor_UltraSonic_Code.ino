if (US_distance <= 10) {

  //Sends message if its the first time the obstacle has been detected
  if (!OBSTACLE_DETECTED) {
    sendMessage("Obstacle Seen");
    
    //When obstacle is detected first, it will set to true.
    OBSTACLE_DETECTED = true;
  }
  stopmove();

  } else {

    //If an obstacle was detected before and has now been cleared, it will send "obstacle cleared"
    if (OBSTACLE_DETECTED){
      sendMessage("Obstacle Cleared");

      //When the obstacle is cleared, the variable resets to false.
      OBSTACLE_DETECTED = false;
    }

    if (value_SL >= 100 && value_SR >= 100) {
      moveforward(80);
    } else if (value_SL < 100 && value_SR >= 100) {
      forwardLeft(70);
    } else if (value_SL >= 100 && value_SR < 100) {
      forwardRight(70);
    } else if (value_SL < 100 && value_SR < 100) {
      stopmove();
    }
  }

  delay(100);

//This is the end of the loop
}

