package com.david.redis.client.jedis;
import redis.clients.jedis.Jedis;

public class RedisJavaClient {
  public static void main(String[] args) {
    System.out.println("main...start");
    //Connecting to Redis server on localhost
    Jedis jedis = new Jedis("localhost");
    System.out.println("Connection to server sucessfully");
    //check whether server is running or not
    System.out.println("Server is running: "+jedis.ping());
  }
}
