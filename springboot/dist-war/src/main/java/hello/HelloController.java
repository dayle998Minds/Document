package hello;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class HelloController {

    @RequestMapping("/")
    public String index() {
        System.out.println("## index()");
        return "Greetings from Spring Boot in dist-war";
    }

}
