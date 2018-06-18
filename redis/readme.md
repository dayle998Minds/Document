# redis install
### download
```
$ wget http://download.redis.io/releases/redis-stable.tar.gz
$ tar xzf redis-stable.tar.gz
```
### make & install
```
$ cd redis-stable

$ make

$ make test

$ sudo make install
```
### Starting Redis
```
$ redis-server
[28550] 01 Aug 19:29:28 # Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'
[28550] 01 Aug 19:29:28 * Server started, Redis version 2.2.12
[28550] 01 Aug 19:29:28 * The server is now ready to accept connections on port 6379
... more logs ...
```
### Check if Redis is working
``` 
$ redis-cli ping
PONG
```
``` 
$ redis-cli                                                                
redis 127.0.0.1:6379> ping
PONG
redis 127.0.0.1:6379> set mykey somevalue
OK
redis 127.0.0.1:6379> get mykey
"somevalue"
```

##Reference
https://redis.io/topics/quickstart