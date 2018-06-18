#Gradle로 Java 프로젝트 시작하기
## 커맨드로 gradle 컴파일 방법
```
#프로젝트 생성
$ mkdir gradle-init
$ cd gradle-init

#gradle의 프로젝트 초기화
$ gradle init

#java파일 생성
$ mkdir -p src/main/java/hello

#프로젝트에 필요한 설정 추가
$ vi build.gradle

#gradle build
$ gradle build

#gradle로 테스트
$ ./gradlew run
```
### HelloWorld.java
```
package hello;

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("hello world");
    }
}
```

### build.gradle 파일
```
apply plugin: 'java'
apply plugin: 'eclipse'
apply plugin: 'application'

mainClassName = 'hello.HelloWorld'

// tag::repositories[]
// 서드파티 라이브러리의 소스 출처를 추가한다
repositories {
    mavenCentral()
}
// end::repositories[]

// tag::jar[]
// 빌드에서 jar를 생성할 때 메타를 추가한다
jar {
    baseName = 'gs-gradle'
    version =  '0.1.0'
}
// end::jar[]

// tag::dependencies[]
// 버전 의존성을 추가한다
sourceCompatibility = 1.8
targetCompatibility = 1.8

// 의존 라이브러리를 추가한다
dependencies {
    compile "joda-time:joda-time:2.2"
}
// end::dependencies[]

// tag::wrapper[]
// wrapper로 설치할 gradle version을 정한다
task wrapper(type: Wrapper) {
    gradleVersion = '2.3'
}
// end::wrapper[]
```

# Gradle Dependencies
## 의존성 설정 기본
group, name, version 순서
``` 
dependencies {
    compile group: 'org.hibernate', name: 'hibernate-core', version: '3.6.7.Final'
}
// 짧게 쓰면 "group:name:version"
dependencies {
    compile 'org.hibernate:hibernate-core:3.6.7.Final'
}
```
## 리포지토리의 기본
### 가장 기본 Maven 리포지토리
```
repositories {
    mavenCentral()
}
```
### 기타 Maven 리포지토리 URL 지정
```
repositories {
    maven {
        url "http://repo.mycompany.com/maven2"
    }
}
```
### 사용자 정의 리포지토리에 접속 계정정보 추가
```
repositories {
    maven {
        credentials {
            username 'user'
            password 'password'
        }
        url "http://repo.mycompany.com/maven2"
    }
}
```
### jCenter() Bintray jCenter를 리포지토리로 추가(1.7)
```
repositories {
    jcenter()
}
```

## 의존성 구성(dependency configurations)
### configuration 종류
- compile : 프로젝트를 컴파일할 때 필요한 의존 라이브러리들
- runtime : 프로젝트를 실행할 때 필요한 의존 라이브러리들. 기본적으로 compile을 모두 포함한다.
- testCompile : 프로젝트의 테스트를 컴파일할 때 필요한 라이브러리들. 기본적으로 프로젝트의 컴파일된 클래스들과 compile 의존성을 포함한다.
- testRuntime : 프로젝트의 테스트를 실행할 때 필요한 라이브러리들. 기본적으로 compile, runtime, testCompile 의존성을 포함한다.
### configuration 선언
```
configurations {
    compile
}
```
### configuration 접근
```
println configurations.compile.name
println configurations['compile'].name
```
### 구성예
```
configurations {
    compile {
        description = 'compile classpath'
        transitive = true
    }
    runtime {
        extendsFrom compile
    }
}
configurations.compile {
    description = 'compile classpath'
}
```
## 리포지토리(Repositories) 자세히
### Maven 중앙 리포지토리
Maven 중앙(central) 리포지토리를 탐색하도록 지정돼 있다.
```
repositories {
    mavenCentral()
}
```
### 로컬 Maven 리포지토리
로컬 Maven 캐시를 리포지토리로 사용한다.\
개발시 SNAPSHOT 버전 등을 Local에서 바로 받아오거나 할 때 편리하다.
```
repositories {
    mavenLocal()
}
```
settings.xml이 존재하면 이에 따라 로컬 리포지토리를 판단한다.
- $USER_HOME/.m2/repository 기본값
- $USER_HOME/.m2/settings.xml 우선
- $M2_HOME/conf/settings.xml 차선
### Maven 사용자 정의 리포지토리
``` 
repositories {
    maven {
        // POM과 jar등의 artifact 탐색
        url "http://repo2.mycompany.com/maven2"
 
        // 위에서 artifact가 없으면 다음에서 검색
        artifactUrls "http://repo.mycompany.com/jars"
        artifactUrls "http://repo.mycompany.com/jars2"
    }
}
```
### 인증 필요한 Maven 리포지토리 접근
``` 
repositories {
    maven {
        credentials {
            username 'user'
            password 'password'
        }
        url "http://repo.mycompany.com/maven2"
    }
}
```
### 단일 디렉토리 리포지토리
```
repositories {
    mavenCentral()
    flatDir {
        dirs 'libs'
    }
}
 
/* libs 디렉토리에 imap.jar, smtp.jar, hibernate-jpa-2.0-api-1.0.0.Final.jar 가 있을 때 */
 
dependencies {
    compile name: 'imap' // 혹은 compile ':imap'
    compile name: 'smtp' // 혹은 compile ':smtp'
 
    // 혹은 compile ':hibernate-jpa-2.0-api:1.0.0.Final'
    compile name: 'hibernate-jpa-2.0-api', version: '1.0.0.Final' 
}
 
task listJars << {
    configurations.compile.each { File file -> println file.name}
}
```
gradle -q listJars 실행 결과
```
imap.jar
smtp.jar
hibernate-jpa-2.0-api-1.0.0.Final.jar
```

### 의존하고 있는 라이브러리를 모두 모으기
```
task copyToLib(type: Copy) {
    into "$buildDir/output/lib"
    from configurations.runtime
}

```
##참조
http://kwonnam.pe.kr/wiki/gradle/dependencies#dokuwiki__top
