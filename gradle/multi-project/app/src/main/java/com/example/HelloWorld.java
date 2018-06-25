package com.example;

import com.example.core.CoreApi;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * @author Petri Kainulainen
 */
public class HelloWorld {
  private static final Logger logger = LoggerFactory.getLogger(HelloWorld.class);

  public static void main(String[] args) {
    logger.info("**** main : start ****");
    CoreApi coreApi = new CoreApi();

    String message = coreApi.getApi();

    logger.info("Received message: " + message);
    logger.info("**** main : end ****");
  }
}