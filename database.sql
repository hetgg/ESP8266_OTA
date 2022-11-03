
-- Table creationg named "sensor_data" and "sensor_register"
CREATE TABLE sensor_data(
	  node_name VARCHAR(10) NOT NULL, 
    FOREIGN KEY(node_name), 
    time_received datetime,
    temperature float(6), 
    humidity float(6)
    );
   
CREATE TABLE sensor_register(
	  node_name VARCHAR(10) NOT NULL PRIMARY KEY, 
    manufacturer VARCHAR(10), 
    longitude int(15), 
    latitude float(15)
    );
  
-- Assigning FOREIGN KEY
ALTER TABLE sensor_data
ADD FOREIGN KEY (node_name) REFERENCES sensor_register(node_name);

-- Data inserion in the sensor_register table
INSERT INTO sensor_register (node_name, manufacturer, longitude, latitude)
VALUES ('node_1', 'microchip', 32.532921, 122.389045),
       ('node_2', 'digikey', 42.271768 , 106.897333),
       ('node_3', 'newark', 62.585754, -247.290087),
       ('node_4', 'sensorx', -77.658869, 76.550921),
       ('node_5', 'sensit', -86.591075, -174.345270);
       
 -- Testing the data entry outside of the sensor_register table WHICH got failed. 
 INSERT INRO sensor_data(node_name, time_received, temperature, humidity) VALUES ('node_9', '2022-10-16 13:39:22' , 32.53, 122.38);
 
 -- VIEW combined table
 
 CREATE VIEW sensor_combined AS SELECT
    sensor_register.node_name,
    sensor_data.temperature,
    sensor_data.humidity
FROM
    sensor_data,
    sensor_register
WHERE
    sensor_data.node_name = sensor_register.node_name; 



 
 
