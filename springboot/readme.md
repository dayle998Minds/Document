#Sping Boot
## 네이밍
### group id
groupid는 프로젝트마다 접근할 수 있는 고유한 이름을 만들도록 한다.보통은 패키지 네이밍룰(도메인 뒤집기)을 따르는게 정석이다. 이후에 원하는 만큼 하위 그룹을 만들 수있다. \ 
예) org.apache.maven, org.apache.commons \
groupid에 프로젝트의 구조를 밝히는 것이 좋다. 만약 현재 프로젝트가 멀티 프로젝트가 되었을 때, 새로운 식별자만 부모의 groupid 뒤에 붙이면 된다. \ 
예) org.apache.maven, org.apache.maven.plugins, org.apache.maven.reporting
### artifact id
artifactid 는 jar 파일에서 버젼 정보를 뺀 이름이다. 자유롭게 적되, 소문자를 사용하고 이상한 특수문자를 사용하지 않는다. \ 
예) maven, commons-math

 
## Java keytool 인증서 관리
### 인증서 생성 
```
$ keytool -genkey -alias my_ssl_key -keyalg RSA -keysize 2048 -validity 700 -keypass 123456 -storepass 123456 -keystore ssl-server.jks
drwxrwxr-x  2 david david 4096  7월 13 17:34 ./
drwxr-xr-x 73 david david 4096  7월 13 15:20 ../
-rw-rw-r--  1 david david 2248  7월 13 17:34 ssl-server.jks

```
옵션들
- genkey : keytool 기능중 key를 생성하는 기능을 이용한다는 뜻.
- alias : key에 부여할 이름
- keyalg : 암호화 방식 지정
- keystore : 생성되는 keystore 파일 이름
- storetype : keystore 형식
- validity : 유효기간 설정(일 단위)
- keypass : truststore 의 암호
- storepass : keystore 의 암호
### KeyStore와 TrustStore
KeyStore는 클라이언트 인증을 위해 클라이언트 측에 놓이는 것\
TrustStore는 서버를 인증하기 위한 것
- KeyStore는 비밀키, 관련된 인증서 혹은 인증서 체인을 가지고 있는 데이타베이스입니다. 인증서 체인은 클라이언트 인증서와 하나 이상의 CA 인증서(공인인증서)로 구성됩니다. 보통 서버 역할을 하는 측에서만 필요하지만, 클라이언트 인증을 요구하는 경우 클라이언트 쪽도 있어야 합니다. 
- TrustStore는 클라이언트가 신뢰할 수 있는 인증서만을 가지고 있습니다. 이들 인증서는 CA 루트 인증서 즉 자기서명 인증서입니다. 보통 웹서버가 설치되면 cacerts.jks라는 파일명으로 이 TrustStore가 저장됩니다.
KeyStore와 TrustStore의 파일 형식은 동일합니다. 이 둘다 keytool을 이용하여 만들고 조작할 수 있습니다. 


### 인증서 보기 
```
$ keytool -list -keystore ssl-server.jks
...
selfsigned_localhost_sslserver, Jul 13, 2018, PrivateKeyEntry, 
Certificate fingerprint (SHA1): B4:25:29:B8:61:B4:EE:69:6D:D2:7B:AC:54:DE:6F:5C:80:AA:27:A1
...
```
# 개발 가이드
## Web Application 예제

### Create the directory structure
```
$ mkdir dist-jar
$ cd dist-jar
$ mkdir -p src/main/java/hello/

$ gradle init

```
### Create a web controller class
```
$ mkdir -p src/main/java/hello
$ vi src/main/java/hello/HelloController.java

package hello;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class HelloController {

    @RequestMapping("/")
    public String index() {
        return "Greetings from Spring Boot!";
    }

}
```
### Create an Application class
``` 
$ vi src/main/java/hello/Application.java

package hello;

import java.util.Arrays;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    public CommandLineRunner commandLineRunner(ApplicationContext ctx) {
        return args -> {

            System.out.println("Let's inspect the beans provided by Spring Boot:");

            String[] beanNames = ctx.getBeanDefinitionNames();
            Arrays.sort(beanNames);
            for (String beanName : beanNames) {
                System.out.println(beanName);
            }
        };
    }
}
```
### Build
$ vi build.gradle
```
buildscript {
    repositories {
        mavenCentral()
    }
    dependencies {
        classpath("org.springframework.boot:spring-boot-gradle-plugin:2.0.3.RELEASE")
    }
}

apply plugin: 'java'
apply plugin: 'eclipse'
apply plugin: 'idea'
apply plugin: 'org.springframework.boot'
apply plugin: 'io.spring.dependency-management'

bootJar {
    baseName = 'projectName'
    version =  '0.1'
}

repositories {
    mavenCentral()
}

sourceCompatibility = 1.8
targetCompatibility = 1.8

dependencies {
    compile("org.springframework.boot:spring-boot-starter-web")
    // tag::actuator[]
    compile("org.springframework.boot:spring-boot-starter-actuator")
}


```
#gradle build
```
$ gradle
$ gradle bootjar 
$ java -jar build/libs/projectName-0.1.jar

```

# 개발팁
## Gradle + SpringBoot 실행 가능한 JAR 만들기
build.gradle 에 io.spring.dependency-management 와 bootJar를 추가합니다.
```
apply plugin: 'io.spring.dependency-management'

bootJar {
    baseName = 'projectName'
    version =  '0.1'
}
```
아래와 같이 컴파일을 하면 모든 의존성 라이브러리가 포함된 jar파일을 생성됩니다.
```
$ gradle bootjar 
$ java -jar build/libs/projectName-0.1.jar
```
## Gradle WAR 만들기
tomcat설치는 아래를 참조하세요.
### build.gradle 수정

```
apply plugin: 'war'

war {
    baseName = 'project-war'    
}

dependencies {
    
    providedRuntime('org.springframework.boot:spring-boot-starter-tomcat')
}

```
### main class에 SpringBootServletInitializer 추가
SpringBootServletInitializer를 추가하지 않으면 tomcat에서 실행이 되지 않습니다.

### war파일 만들기
```
14:44 $ gradle build

BUILD SUCCESSFUL in 0s
2 actionable tasks: 1 executed, 1 up-to-date
$ ll build/libs/
total 15772
drwxrwxr-x 2 david david     4096  7월 23 14:39 ./
drwxrwxr-x 5 david david     4096  7월 23 12:14 ../
-rw-rw-r-- 1 david david 16142096  7월 23 14:48 dist-war.war
$ 
```

### tomcat에 복사 및 재시작
``` 
$ sudo cp build/libs/dist-war.war /var/lib/tomcat8/webapps/
systemctl restart tomcat8

```
아래와 같이 파일명과 동일한 디렉토리가 생성되면 성공한것입니다.
```
$ ll
total 15780
drwxrwxr-x 4 tomcat8 tomcat8     4096  7월 23 14:40 ./
drwxr-xr-x 4 root    root        4096  7월 23 11:58 ../
drwxr-xr-x 5 tomcat8 tomcat8     4096  7월 23 14:40 dist-war/
-rw-r--r-- 1 root    root    16141953  7월 23 14:40 dist-war.war
drwxr-xr-x 3 root    root        4096  7월 23 11:58 ROOT/

```
http://127.0.0.1:8080/dist-war 에 접속 하면 정상적으로 나오는것을 확인할수 있습니다.

## tomcat 설치
```
# tomcat 설치
$ sudo apt-get install tomcat8
# 서비스 실행
$ systemctl restart tomcat8
# 서비스 상태보기
$ systemctl status tomcat8
● tomcat8.service - LSB: Start Tomcat.
   Loaded: loaded (/etc/init.d/tomcat8; bad; vendor preset: enabled)
   Active: active (running) since 월 2018-07-23 11:59:43 KST; 10s ago
     Docs: man:systemd-sysv-generator(8)
  Process: 19358 ExecStop=/etc/init.d/tomcat8 stop (code=exited, status=0/SUCCESS)
  Process: 19374 ExecStart=/etc/init.d/tomcat8 start (code=exited, status=0/SUCCESS)
    Tasks: 45
   Memory: 111.4M
      CPU: 3.591s
   CGroup: /system.slice/tomcat8.service
           └─19402 /usr/lib/jvm/default-java/bin/java -Djava.util.logging.config.file=/var/lib/tomcat8/conf/lo
```
http://127.0.0.1:8080으로 접속을 하면 됩니다.
### tomcat 설치경로
- HOME : /usr/share/tomcat8 
- CONF :  /etc/tomcat8
- LOG :  /var/log/tomcat8 
- ROOT : /var/lib/tomcat8  
#### Port 변경
```
$sudo vi /etc/tomcat8/server.xml

    <Connector port="8080" protocol="HTTP/1.1"
               connectionTimeout="20000"
               URIEncoding="UTF-8"
               redirectPort="8443" />

```

## Reference
<http://btsweet.blogspot.com/2014/06/tls-ssl.html>

