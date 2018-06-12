# boost::asio
<https://www.boost.org/>\
· C++의 거의 모든 것을 STL과 Boost로 충분하다.\
네트워크 만을 위해서 boost를 사용하기에는 좀.... 이라는 사람에게는 비추\
· 바이너리가 아주 크다. \
닭 잡는데 소 잡는 칼 사용하는 듯\
C++ 슈퍼천재(괴짜)들이 만든거라 워낙 웰메이드. 사용도 쉽고.\
언뜻만 보기에도 탑 솔루션인데, C++ 17 표준에 포함된다는게 거의 확정이라 (개인적으로 80%확률일거라 봄) 가장 핫하다고 볼 수 있지 않을까요.

# cpp-netlib
<https://cpp-netlib.org/>\
· boost.asio를 한번 더 래핑 한 것 같다\
· SSL 대응\
· 실용적인지는 잘 모름

# ZeroMQ
<http://zeromq.org/>\
·기존 BSD 소켓과 다르다! 같은 느낌.\
무엇을 할 수 있는지 알기 어려움.\
·zmq 끼리만 통신.\
독자적 프레임워크의 앱 내의 통신에 사용되고 있는 것을 본 적이 있다

# ACE
<http://www.cs.wustl.edu/~schmidt/ACE.html>\
·일단 클라이언트 용도 있지만 기본적으로 서버 사이드 라이브러리.\
닭 잡는데 소 잡는 칼 사용하는 듯.\
언젠가는 써 보고 싶은 라이브러리 중 하나. 이러한 프레임워크를 사용하여 거대한 시스템을 구축 하고 싶음. Corba라는 단어에서 낡은 티가 나고 있음

# Qt
<https://www.qt.io/download>\
·Qt로 애플리케이션을 사용하고 있다면 Qt의 극진한 네트워크 지원이 있을 것

# wxCurl
<http://wxcode.sourceforge.net/components/wxcurl/>\
· curl에 의존하기 좀 싫을지도... Makefile. am이 비정상적으로 복잡\
· 라지만 이건 Curl.\
· Proxy에 대응하지 않음.\
SSL도 대응하지 않음.

# POCO 
<https://pocoproject.org/>\
네트워크 한정이 아닌 종합적인 C++ 라이브러리. 어느 쪽인가 하면 서버 사이드에 가까운 듯

# libcurl
<https://curl.haxx.se/>\
· C 언어 사용자라면 이것을 추천.\
curl은 libwww의 대체였던 것 같다. 사실 libwww의 개발은 중단된 상태.\
libcurl을 사용하자.\
· 이것도 큰 라이브러리이다

# curlpp
<http://www.curlpp.org/>
저의 추천\
· Curl의 C++ 바인딩.\
SSL 대응, Proxy 대응, GET, POST, DELETE등 여러 가지에 대응.\
·boost를 섞어 쓰는 듯.


### 출처
http://nantonaku-shiawase.hatenablog.com/entry/2013/05/20/231051
