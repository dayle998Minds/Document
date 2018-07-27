# Elasticsearch
## Elasticsearch 설치
### install
```
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-6.3.1.tar.gz
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-6.3.1.tar.gz.sha512
shasum -a 512 -c elasticsearch-6.3.1.tar.gz.sha512 
tar -xzf elasticsearch-6.3.1.tar.gz
cd elasticsearch-6.3.1/ 
## 실행
./bin/elasticsearch
```
### Cross Origin 정책 수정
cross origin  정책으로 인해서 초기 접속이 되지 않습니다.
elasticsearch.yml 에 아래 내용 추가해 주시고 재실행 하시면 됩니다.
처음 전송되는 리소스의 도메인과 다른 도메인으로부터 리소스가 요청될 경우 해당 리소스는 cross-origin HTTP 요청에 의해 요청됩니다. 
보안 상의 이유로, 브라우저들은 스크립트 내에서 초기화되는 cross-origin HTTP 요청을 제한합니다. 
요청을 받은 웹서버가 허락하면 크로스도메인이라도 Ajax로 통신할 수 있다"라는 정책이다. 기술적으로는 크로스도메인에 위치한 웹서버가 응답에 적절한 Access-Control-Allow-류의 헤더를 보냄으로써 크로스도메인 Ajax를 허용 수 있다.

```
$ vi config/elasticsearch.yml

http.cors.enabled: true
http.cors.allow-origin: "*"
```

### 테스트
```
$ curl localhost:9200
{
  "name" : "1OZipKd",
  "cluster_name" : "elasticsearch",
  "cluster_uuid" : "VDqU1s9ETRap451_36lQPw",
  "version" : {
    "number" : "6.3.1",
    "build_flavor" : "default",
    "build_type" : "zip",
    "build_hash" : "eb782d0",
    "build_date" : "2018-06-29T21:59:26.107521Z",
    "build_snapshot" : false,
    "lucene_version" : "7.3.1",
    "minimum_wire_compatibility_version" : "5.6.0",
    "minimum_index_compatibility_version" : "5.0.0"
  },
  "tagline" : "You Know, for Search"
}

```
### Running as a daemon
$ ./bin/elasticsearch -d -p pid
$ kill `cat pid`

### JVM 메모리 설정
elasticsearch v5.0부터 메모리 설정이 /etc/init.d/elasticsearch에서 /etc/elasticsaerch/jvm.options로 옮겨졌다.

## 주요 설정
config/elasticsearch.yml
``` 
# 클러스터를 식별하기 위한 이름이므로 유일성과 의미를 가진 이름을 사용하자
cluster.name: es-cluster

# 노드 이름은 자동으로 생성되지만 호스트명과 같이 클러스터 내에서 식별 가능한 이름을 활용하는 것이 좋다.
node.name: "es-node1"

# 기본값은 아래 두 값이 모두 true다. node.master는 노드가 마스터가 될 수 있지에 대한 설정이고, node.data는 데이터를 저장하는 노드인지에 대한 설정이다. 보통은 두 값을 true로 설정하면 되고, 클러스터의 규모가 큰 경우에는 3가지 종류의 노드를 구성하기 위해 이 값을 노드별로 조정해 설정한다. 자세한 사항은 토폴로지(topology) 설정에서 다시 설명하겠다.
node.master: true  
node.data: true

# 샤드와 리플리카 수를 변경하는 설정이다. 아래 값은 기본값이다. 
index.number_of_shards: 5  
index.number_of_replicas: 1



#JVM의 스왑을 방지하려면 아래 설정 값을 true로 한다.
bootstrap.mlockall: true

# 클러스터 내의 각 노드의 상태 체크를 위한 타임아웃 값으로, 너무 작게 하면 노드가 클러스터에서 자주 이탈하는 문제가 발생할 수 있어 적절한 값을 설정한다. 기본값은 3초다.
discovery.zen.ping.timeout: 10s

# 기본값은 멀티캐스트를 사용하지만, 실환경에서는 다른 클러스터와 노드가 섞이는 위험이 발생할 수 있으므로 유니캐스트를 사용하고 두 번째 설정 값에 마스터가 될 수 있는 서버들의 목록을 나열하는 것이 좋다.
discovery.zen.ping.multicast.enabled: false  
discovery.zen.ping.unicast.hosts: ["host1", "host2:port", "host3[portX-portY]"]  
```

## plugin elasticsearch-head 설치
Elasticsearch의 모니터링을 위해서 가장 많이 사용하는 플러그인인 HEAD

```
$ git clone git://github.com/mobz/elasticsearch-head.git
$ cd elasticsearch-head
$ npm install
$ npm run start
open http://localhost:9100/
```
## 기본 개념
### Near Realtime(NRT)
Elasticsearch는 준 실시간 검색 플랫폼 입니다. 문서가 검색가능하기까지 색인하는데 1초 이하의 아주 작은 시간이 걸린다는 것을 의미합니다.

### 인덱스 Index
인덱스는 비슷한 형질을 가지는 문서 간의 집합이라고 보시면 됩니다. 예로들면 고객정보, 제품카탈로그, 주문정보 같은 것 입니다. 소문자로 구성된 이름으로 구분이 되며 인덱스 이름은 문서에 대한 인덱싱/검색/갱신/삭제 등을 수행할 때 참조값으로 사용됩니다.
단일 클러스터에서 원하는 대로 다수의 인덱스를 정의할 수 있습니다.

### 타입 Type
인덱스안에 1개 이상의 타입을 정의할 수 있습니다. 타입은 당신이 정의한 의미기준으로 인덱스를 논리적 분류/파티션입니다.

### 문서 Document
문서는 인덱싱된 정보의 기본 단위입니다. 예로 하나의 고객 정보, 제품 정보, 주문 정보 입니다. 문서는 어디든 호환이 가능한 JSON(JavaScript Object Notation)으로 구성됩니다.


## 사용법
### 클러스터 상태확인
```
curl -XGET 'localhost:9200/_cat/health?v&pretty'

epoch      timestamp cluster       status node.total node.data shards pri relo init unassign pending_tasks max_task_wait_time active_shards_percent
1475247709 17:01:49  elasticsearch green           1         1      0   0    0    0        0             0                  -                100.0%

```
상태확인 메시지를 통해서 status 항목에 green, yellow, red라는 정보를 볼 수 있습니다. +
- green은 모든 기능이 정상적으로 동작하고 있다는 것입니다.
- yellow는 전체적인 기능은 수행하고 있으나 일부 복제본이 아직 할당되지 않은 상태입니다.
- red는 어떤 이유로 인하여 데이터를 사용할 수 없는 상태입니다.

### 인텍스 생성
```
$ curl -XGET 'localhost:9200/_cat/indices?v&pretty'
health status index uuid pri rep docs.count docs.deleted store.size pri.store.size
$ curl -XPUT 'localhost:9200/customer?pretty&pretty'
{
  "acknowledged" : true,
  "shards_acknowledged" : true,
  "index" : "customer"
}
$ curl -XGET 'localhost:9200/_cat/indices?v&pretty'
health status index    uuid                   pri rep docs.count docs.deleted store.size pri.store.size
yellow open   customer czTQwPheTiKvbEbGd4BLtw   5   1          0            0      1.1kb          1.1kb
 ```


## references
https://www.elastic.co/downloads/elasticsearch
https://www.elastic.co/guide/en/elasticsearch/reference/current/zip-targz.html
https://d2.naver.com/helloworld/273788
https://iju707.gitbooks.io/elasticsearch/content/_cluster_health.html