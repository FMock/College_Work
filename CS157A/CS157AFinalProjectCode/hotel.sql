########################### CS157A PROJECT ########################################
DROP DATABASE IF EXISTS Hotel;
CREATE DATABASE Hotel;
USE Hotel; 
DROP TABLE IF EXISTS Room;
CREATE TABLE Room
(
 rID INT PRIMARY Key AUTO_INCREMENT,
 room_type ENUM('Basic', 'Suite')DEFAULT 'Basic' NOT NULL,
 description VARCHAR(60),
 price DOUBLE NOT NULL
);

ALTER TABLE Room AUTO_INCREMENT = 101;

DROP TABLE IF EXISTS Customer;
CREATE TABLE Customer
(cID INT PRIMARY Key AUTO_INCREMENT,
 cNAME VARCHAR(40),
 email VARCHAR(50),
 phone VARCHAR(14),
 num_rooms INT DEFAULT 0,
 updatedOn TIMESTAMP NOT NULL ON UPDATE CURRENT_TIMESTAMP,
 has_spent double DEFAULT 0.00 NOT NULL
);

DROP TABLE IF EXISTS Occupied;
CREATE TABLE Occupied
(cID INT,
 rID INT,
 occupiedDate TIMESTAMP NOT NULL DEFAULT NOW(),
 overStay BOOLEAN DEFAULT FALSE,
 PRIMARY KEY(cID,rID,occupiedDate),
 FOREIGN KEY (cID) references Customer (cID)
 ON DELETE CASCADE
 ON UPDATE CASCADE,
 FOREIGN KEY (rID) references Room(rID) 
 ON DELETE CASCADE
 ON UPDATE CASCADE
);

DROP TABLE IF EXISTS VIP;
CREATE TABLE VIP
(cID INT,
 notes VARCHAR(60),
 PRIMARY KEY(cID,notes),
 FOREIGN KEY (cID) references Customer(cID)
);

DROP TABLE IF EXISTS Ammenities;
CREATE TABLE Ammenities
(aID INT AUTO_INCREMENT NOT NULL,
 description VARCHAR(60),
 price DOUBLE,
 PRIMARY KEY(aID)
);

DROP TABLE IF EXISTS Ammenity_orders;
CREATE TABLE Ammenity_orders
(aID INT,
 cID INT,
 amount INT,
 orderDate TIMESTAMP NOT NULL DEFAULT NOW(),
 PRIMARY KEY(aID, cID, orderDate),
 FOREIGN KEY (cID) references Customer(cID)
 ON DELETE CASCADE
 ON UPDATE CASCADE
);

DROP TABLE IF EXISTS Archive;
CREATE TABLE Archive
(archiveID INT PRIMARY KEY AUTO_INCREMENT,
 cID INT,
 cNAME VARCHAR(40),
 email VARCHAR(50),
 phone VARCHAR(14),
 num_rooms INT DEFAULT 0,
 updatedOn TIMESTAMP NOT NULL,
 has_spent double DEFAULT 0.00 NOT NULL
);

############### TRIGGERS ############################################

DROP TRIGGER IF EXISTS deleteCascadeTrigger;
delimiter //
CREATE TRIGGER deleteCascadeTrigger
AFTER DELETE ON Customer
FOR EACH ROW
BEGIN
    delete from Occupied where cID = OLD.cID;
	delete from VIP WHERE cID = OLD.cID;
END;//
delimiter ;

DROP TRIGGER IF EXISTS insertVIPTrigger;
delimiter //
CREATE TRIGGER insertVIPTrigger
AFTER INSERT ON Customer
FOR EACH ROW
BEGIN
	IF NEW.has_spent > 3000.0 THEN
		INSERT INTO VIP (cID, notes) VALUES (NEW.cID, "");
		INSERT INTO Ammenity_orders(aID, cID, amount) values(1, NEW.cID, 1);
	END IF;
END;//
delimiter ;

DROP TRIGGER IF EXISTS updateVIPTrigger;
delimiter //
CREATE TRIGGER updateVIPTrigger
AFTER UPDATE ON Customer
FOR EACH ROW
BEGIN
	IF NEW.has_spent > 3000.0 THEN
		INSERT INTO VIP (cID, notes) VALUES (NEW.cID, "");
	END IF;
END;//
delimiter ;

LOAD DATA LOCAL INFILE 'c:\\SQL\\rooms.txt' INTO TABLE Room;
LOAD DATA LOCAL INFILE 'c:\\SQL\\customers.txt' INTO TABLE Customer;
LOAD DATA LOCAL INFILE 'c:\\SQL\\occupied.txt' INTO TABLE Occupied;
LOAD DATA LOCAL INFILE 'c:\\SQL\\ammenities.txt' INTO TABLE Ammenities;
