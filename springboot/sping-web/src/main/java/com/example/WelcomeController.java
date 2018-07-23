package com.example;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Map;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class WelcomeController {

  @RequestMapping("/")
  public String welcome(Map<String, Object> model) {

    String message;
    {

      Calendar cal = Calendar.getInstance();
      SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
      message = sdf.format(cal.getTime());
    }
    model.put("message", message);
    model.put("notify", "hi..");
    return "welcome";
  }

}