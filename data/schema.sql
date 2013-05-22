drop table if exists temperatures;
create table temperatures (
  date INT, 
  humidity FLOAT,
  temperature FLOAT, 
  temperature_outside FLOAT,    
  location TEXT
);
