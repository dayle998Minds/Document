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

## Reference
<http://btsweet.blogspot.com/2014/06/tls-ssl.html>

