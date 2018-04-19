# 데이터베이스 엔진비교
---
## Maria DB의 데이터베이스 엔진(스토리지 엔진)
MariaDB는 원칙적으로 MySQL과 거의 동일한 데이터베이스 엔진을 제공한다.

### Aria - MyISAM 파생 엔진 대체용 (이전 명칭은 Maria)
아리아(Aria)는 MySQL과 MariaDB를 위한 새로운 스토리지 엔진이다. 
- MyISAM보다는 효율적이고 안정적으로 작동
- MariaDB의 경우 내부 임시테이블을 생성할때 Aria Storage Engine사용

### XtraDB - 오라클 InnoDB를 대체하기 위해 만든 InnoDB 파생 포크
- windows 미지원
- 트랜젝션 지원

### FederatedX - MySQL Federated 파생 엔진, 트랜잭션 제공
MySQL 관계형 데이터베이스 관리 시스템용 MySQL Federated 저장 엔진은 유저가 외부(또는 원격) 테이블을 로컬로 보여주는 테이블을 생성할 수 있게 해주는 저장 엔진이다. 이것은 MySQL 클라이언트 라이브러리 API를 데이터 통로로 이용하여, 원격의 데이터 소스를 동일하게 다른 저장 엔진으로 취급하여 로컬 데이터 자료를 MYD 파일(MyISAM), 메모리(클러스터, 힙) 또는 테이블스페이스(InnoDB)에 상관없이 취급한다. 그곳에 규정된 각 Federated 테이블은 하나의 .frm (데이터 소스 URL과 같은 정보를 포함한 데이터 정의 파일)이다. 실제 데이터는 로컬 또는 원격의 MySQL 인스턴스에 존재한다.

### OQGRAPH - 버전 5.2 이상에서 지원
### SphinxSE - 버전 5.2 이상에서 지원, Full-Text Searching이 필요할 때 사용할 수 있는 스토리지 엔진
### Cassandra - 
실제 Cassandra Cluster가 MariaDB서버 내부에 구현된것이 아니라 MariaDB가 원격 서버에 있는 카산드라 서버로 접속하여 필요한 데이터를 SQL문법으로 조회할수 있도록 해주는 스토로지엔진
10.0에서 포함. 기타 비 sql 저장 엔진을 끌어들이려는 시도
- MariaDB-10.0부터 NoSQL에 관련된 기능 추가

### TokuDB - Fractal Tree Indexes로 운영되는 DBMS
MariaDB에서 Load해서 사용,  장점은 다른 엔진보다 압축률이 높음
Fractal Tree는 "Big I/O"에 촛점을 맞춘 자료 구조로, 잦은 Disk I/O를 줄이고, 한번에 다량의 데이터를 하단 노드로 전달함에 따라 데이터가 많은 상황에서도 효과적으로 처리할수 있는 방안.
- 트랜젝션 지원

### Connect 
ConnectStorage Engine은 XML이나 Excel파일 그리고 Oracle이나 MSSQL과 같은 DBMS들의 테이블을 MariaDB에 직접 쿼리할수 있도록 연결 기능을 제공해주는 스토리지 엔진이다.

---
## MySQL의 데이터베이스 엔진
### MyISAM
- 상대적으로 높은 성능
- 읽기 위주의 요청에 유리
- 테이블 단위 락킹 
### InnoDB
이노DB(InnoDB)는 MySQL을 위한 데이터베이스 엔진이다

- 트랜젝션 지원
- 빈번한 쓰기, 수정, 삭제시 처리 능력
- 디스크, 전원 등의 장애 발생시 복구 성능
- 동시처리가 많은 환경에 적합
- Row 단위 락킹 

### Cluster(NDB)
트랜잭션을 지원하고 모든 데이터와 인덱스가 메모리에 존재하여 매우 빠른 데이터 로드 속도를 자랑하며 PK 사용시 최상의 속도를 나타낸다.

### Archive
MySQL 5.0부터 새롭게 도입된 엔진으로 자동적으로 데이터 압축을 지원하며 다른 엔진에 비해 80% 저장공간 절약 효과를 자랑한다. 그리고 가장 빠른 데이터 로드 속도 또한 자랑하지만, INSERT와 SELECT만이 가능하다.
### Federated
MySQL 5.0부터 새롭게 도입된 엔진으로 물리적 데이터베이스에 대한 논리적 데이터베이스를 생성하여 원격 데이터를 컨트롤 할 수 있다. 실행속도는 네트워크 요소에 따라 좌우되면 테이블 정의를 통한 SSL 보안 처리를 한다. 분산 데이터베이스 환경에 사용한다
