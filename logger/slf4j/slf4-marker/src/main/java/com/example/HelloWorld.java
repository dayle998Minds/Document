
package com.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.slf4j.Marker;
import org.slf4j.MarkerFactory;
public class HelloWorld {
  private static final Logger logger = LoggerFactory.getLogger(HelloWorld.class);

  public static void main( String[] args )
  {
    String confidentialMarkerText = "CONFIDENTIAL";
    Marker confidentialMarker = MarkerFactory.getMarker(confidentialMarkerText);
    logger.debug("111");
    logger.debug("222");
    logger.debug(confidentialMarker,"333..confidential message");
    logger.debug(confidentialMarker, "444");
  }
}
