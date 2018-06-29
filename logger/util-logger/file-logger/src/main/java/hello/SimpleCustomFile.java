package hello;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.*;

public class SimpleCustomFile {

  public static void test() {
    Logger logger = Logger.getLogger("MyLog");
    FileHandler fh;

    try {

      // This block configure the logger with handler and formatter
      fh = new FileHandler("SimpleCustomFile.log");
      logger.addHandler(fh);
      MyFormatter2 formatter = new MyFormatter2();

      fh.setFormatter(formatter);

      // the following statement is used to log any messages
      logger.info("My first log");

    } catch (Exception e) {
      e.printStackTrace();
    }

    logger.log(Level.INFO, "aaa bbb ccc ddd eee fff heloasfd", new
        Object[]{"aaa", "bbb",
        "ccc"});

  }
}

class MyFormatter2 extends Formatter {

  // Create a DateFormat to format the logger timestamp.
  private static final DateFormat df = new SimpleDateFormat(
      "dd/MM/yyyy hh:mm:ss.SSS");

  public String format(LogRecord record) {
    StringBuilder builder = new StringBuilder(1000);
    builder.append(formatMessage(record));
    builder.append("\n");
    return builder.toString();
  }

  public String getHead(Handler h) {
    return super.getHead(h);
  }

  public String getTail(Handler h) {
    return super.getTail(h);
  }
}