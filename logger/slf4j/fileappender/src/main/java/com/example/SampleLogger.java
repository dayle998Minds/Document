
package com.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class SampleLogger {

  public static void main ( String [] args )
  {
    final Logger log = LoggerFactory.getLogger("FILE");

    log.error("uuid=asdfsafd|Health Check.");

  }
}
 