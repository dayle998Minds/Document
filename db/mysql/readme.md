# 환경 명령어
### MySQL 기본 스토리지 엔진 확인
SELECT engine, support FROM information_schema.engines WHERE support='DEFAULT';
```
mysql> SELECT engine, support FROM information_schema.engines WHERE support='DEFAULT';
+--------+---------+
| engine | support |
+--------+---------+
| InnoDB | DEFAULT |
+--------+---------+
1 row in set (0.00 sec)
```
### mysql 버전 확인
``` 
# mysql --version
mysql  Ver 14.12 Distrib 5.0.77, for redhat-linux-gnu (x86_64) using readline 5.1

mysql> select version();
+-----------+
| version() |
+-----------+
| 5.0.77    | 
+-----------+
1 row in set (0.00 sec)
```
# Beginner 
### SHOW DATABASES
``` 
mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| test               |
........
```
### Creating and Deleting a Database - CREATE DATABASE and DROP DATABASE
```
mysql> CREATE DATABASE southwind;
Query OK, 1 row affected (0.03 sec)
   
mysql> DROP DATABASE southwind;
Query OK, 0 rows affected (0.11 sec)
   
mysql> CREATE DATABASE IF NOT EXISTS southwind;
Query OK, 1 row affected (0.01 sec)
   
mysql> DROP DATABASE IF EXISTS southwind;
Query OK, 0 rows affected (0.00 sec)
```
### Creating and Deleting a Table - CREATE TABLE and DROP TABLE
``` 
-- Remove the database "southwind", if it exists.
-- Beware that DROP (and DELETE) actions are irreversible and not recoverable!
mysql> DROP DATABASE IF EXISTS southwind;
Query OK, 1 rows affected (0.31 sec)
 
-- Create the database "southwind"
mysql> CREATE DATABASE southwind;
Query OK, 1 row affected (0.01 sec)
 
-- Show all the databases in the server
--   to confirm that "southwind" database has been created.
mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| southwind          |
| ......             |
 
-- Set "southwind" as the default database so as to reference its table directly.
mysql> USE southwind;
Database changed
 
-- Show the current (default) database
mysql> SELECT DATABASE();
+------------+
| DATABASE() |
+------------+
| southwind  |
+------------+
 
-- Show all the tables in the current database.
-- "southwind" has no table (empty set).
mysql> SHOW TABLES;
Empty set (0.00 sec)
 
-- Create the table "products". Read "explanations" below for the column defintions
mysql> CREATE TABLE IF NOT EXISTS products (
         productID    INT UNSIGNED  NOT NULL AUTO_INCREMENT,
         productCode  CHAR(3)       NOT NULL DEFAULT '',
         name         VARCHAR(30)   NOT NULL DEFAULT '',
         quantity     INT UNSIGNED  NOT NULL DEFAULT 0,
         price        DECIMAL(7,2)  NOT NULL DEFAULT 99999.99,
         PRIMARY KEY  (productID)
       );
Query OK, 0 rows affected (0.08 sec)
 
-- Show all the tables to confirm that the "products" table has been created
mysql> SHOW TABLES;
+---------------------+
| Tables_in_southwind |
+---------------------+
| products            |
+---------------------+
 
-- Describe the fields (columns) of the "products" table
mysql> DESCRIBE products;
+-------------+------------------+------+-----+------------+----------------+
| Field       | Type             | Null | Key | Default    | Extra          |
+-------------+------------------+------+-----+------------+----------------+
| productID   | int(10) unsigned | NO   | PRI | NULL       | auto_increment |
| productCode | char(3)          | NO   |     |            |                |
| name        | varchar(30)      | NO   |     |            |                |
| quantity    | int(10) unsigned | NO   |     | 0          |                |
| price       | decimal(7,2)     | NO   |     | 99999.99   |                |
+-------------+------------------+------+-----+------------+----------------+
 
-- Show the complete CREATE TABLE statement used by MySQL to create this table
mysql> SHOW CREATE TABLE products \G
*************************** 1. row ***************************
       Table: products
Create Table: 
CREATE TABLE `products` (
  `productID`    int(10) unsigned  NOT NULL AUTO_INCREMENT,
  `productCode`  char(3)           NOT NULL DEFAULT '',
  `name`         varchar(30)       NOT NULL DEFAULT '',
  `quantity`     int(10) unsigned  NOT NULL DEFAULT '0',
  `price`        decimal(7,2)      NOT NULL DEFAULT '99999.99',
  PRIMARY KEY (`productID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1
```
### Inserting Rows - INSERT INTO
```
-- Insert a row with all the column values
mysql> INSERT INTO products VALUES (1001, 'PEN', 'Pen Red', 5000, 1.23);
Query OK, 1 row affected (0.04 sec)
 
-- Insert multiple rows in one command
-- Inserting NULL to the auto_increment column results in max_value + 1
mysql> INSERT INTO products VALUES
         (NULL, 'PEN', 'Pen Blue',  8000, 1.25),
         (NULL, 'PEN', 'Pen Black', 2000, 1.25);
Query OK, 2 rows affected (0.03 sec)
Records: 2  Duplicates: 0  Warnings: 0
 
-- Insert value to selected columns
-- Missing value for the auto_increment column also results in max_value + 1
mysql> INSERT INTO products (productCode, name, quantity, price) VALUES
         ('PEC', 'Pencil 2B', 10000, 0.48),
         ('PEC', 'Pencil 2H', 8000, 0.49);
Query OK, 2 row affected (0.03 sec)
 
-- Missing columns get their default values
mysql> INSERT INTO products (productCode, name) VALUES ('PEC', 'Pencil HB');
Query OK, 1 row affected (0.04 sec)

-- 2nd column (productCode) is defined to be NOT NULL
mysql> INSERT INTO products values (NULL, NULL, NULL, NULL, NULL);
ERROR 1048 (23000): Column 'productCode' cannot be null
 
-- Query the table
mysql> SELECT * FROM products;
+-----------+-------------+-----------+----------+------------+
| productID | productCode | name      | quantity | price      |
+-----------+-------------+-----------+----------+------------+
|      1001 | PEN         | Pen Red   |     5000 |       1.23 |
|      1002 | PEN         | Pen Blue  |     8000 |       1.25 |
|      1003 | PEN         | Pen Black |     2000 |       1.25 |
|      1004 | PEC         | Pencil 2B |    10000 |       0.48 |
|      1005 | PEC         | Pencil 2H |     8000 |       0.49 |
|      1006 | PEC         | Pencil HB |        0 | 9999999.99 |
+-----------+-------------+-----------+----------+------------+
6 rows in set (0.02 sec)
 
-- Remove the last row
mysql> DELETE FROM products WHERE productID = 1006;
```
### Querying the Database - SELECT
``` 
-- List all rows for the specified columns
mysql> SELECT name, price FROM products;
+-----------+-------+
| name      | price |
+-----------+-------+
| Pen Red   |  1.23 |
| Pen Blue  |  1.25 |
| Pen Black |  1.25 |
| Pencil 2B |  0.48 |
| Pencil 2H |  0.49 |
+-----------+-------+
5 rows in set (0.00 sec)
    
-- List all rows of ALL the columns. The wildcard * denotes ALL columns
mysql> SELECT * FROM products;
+-----------+-------------+-----------+----------+-------+
| productID | productCode | name      | quantity | price |
+-----------+-------------+-----------+----------+-------+
|      1001 | PEN         | Pen Red   |     5000 |  1.23 |
|      1002 | PEN         | Pen Blue  |     8000 |  1.25 |
|      1003 | PEN         | Pen Black |     2000 |  1.25 |
|      1004 | PEC         | Pencil 2B |    10000 |  0.48 |
|      1005 | PEC         | Pencil 2H |     8000 |  0.49 |
+-----------+-------------+-----------+----------+-------+
5 rows in set (0.00 sec)
```
