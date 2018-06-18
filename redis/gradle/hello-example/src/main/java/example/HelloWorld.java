package example;


import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPool;
import redis.clients.jedis.JedisPoolConfig;

public class HelloWorld {

  public static void basic() {
    System.out.println("*** basic ***");
    Jedis jedis = new Jedis("127.0.0.1", 6379);
    jedis.set("key", "value");
    String value = jedis.get("key");
    System.out.println("key = " + value);
  }

  public static void testRedisConnect() {
    System.out.println("*** testRedisConnect ***");
    JedisPoolConfig jedisPoolConfig = new JedisPoolConfig();
    JedisPool pool = new JedisPool(jedisPoolConfig, "127.0.0.1", 6379);

    Jedis jedis = pool.getResource();

    jedis.set("foo", "bar");
    String value = jedis.get("foo");
    value = jedis.get("foo");
    System.out.println("jedis.get = " + value);
    jedis.del("foo");
    value = jedis.get("foo");

    if (jedis != null) {
      jedis.close();
    }
  }

  public static void main(String[] args) {
    System.out.println("*** Main start.. ***");
    basic();
    testRedisConnect();
  }
}