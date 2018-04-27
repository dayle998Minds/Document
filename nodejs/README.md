### node.js + loopback 사용시 로그 확인방법
> DEBUG 로그 켜기
```
$ DEBUG="GRPC" node server.js
```
> loopback inspect 사용방법
```
$ node --inspect server.js 
Debugger listening on port 13221.
Warning: This is an experimental feature and could change at any time.
To start debugging, open the following URL in Chrome:
    chrome-devtools://devtools/remote/serve_file/@60cd6e859b9f557d2312f5bf532f6aec5f284980/inspector.html?experiments=true&v8only=true&ws=127.0.0.1:9229/d025201b-82a2-4652-babe-de62ace2b942
```
웹브라우저에서 url입력
`chrome-devtools://devtools/remote/serve_file/@60cd6e859b9f557d2312f5bf532f6aec5f284980/inspector.html?experiments=true&v8only=true&ws=127.0.0.1:9229/d025201b-82a2-4652-babe-de62ace2b942`
