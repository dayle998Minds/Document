
package com.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class SampleLogger {
  private static final Logger log = LoggerFactory.getLogger(SampleLogger.class);

  public static  void test() {
    log.info("info message");
    log.debug("debugging");
  }

  public static void main ( String [] args ) {
    test();
  }
}
 