package com.example;

import ch.qos.logback.core.rolling.RollingFileAppender;
import java.time.LocalDateTime;

public class FileAppender<E> extends RollingFileAppender<E>{

  private int fileRollingInterval = 0;

  public FileAppender() {
//    super.rollover();
  }

  @Override
  public void rollover() {
    this.fileRollingInterval = LocalDateTime.now().getMinute() % 5;
    if (this.fileRollingInterval == 1) {
      super.rollover();
    }
  }

  }