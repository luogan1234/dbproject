CREATE DATABASE orderDB;

USE orderDB;

CREATE TABLE publisher (
  id int(10) NOT NULL,
  name varchar(100) NOT NULL,
  state varchar(2),
  PRIMARY KEY  (id)
);


CREATE TABLE book (
  id int(10) NOT NULL,
  title varchar(100) NOT NULL,
  authors varchar(200),
  FOREIGN KEY publisher_id(publisher.id),
  copies int(10),
  PRIMARY KEY  (id)
);

CREATE TABLE customer (
  id int(10) NOT NULL,
  name varchar(25) NOT NULL,
  gender varchar(1),
  PRIMARY KEY  (id)
);
DROP INDEX customer(id);
CREATE INDEX customer(id);
CREATE TABLE orders (
  FOREIGN KEY customer_id(customer.id),
  FOREIGN KEY book_id(book.id),
  quantity int(10) NOT NULL
);