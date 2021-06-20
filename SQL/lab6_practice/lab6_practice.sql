drop database IF EXISTS lab5;
create database lab5;
use lab5;

create table Department(
    dept_id INT,
    dept_name VARCHAR(50) NOT NULL,
    PRIMARY KEY (dept_id)
);

LOAD DATA LOCAL INFILE './department.csv' REPLACE INTO TABLE Department FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Student(
    stud_id INT,
    name VARCHAR(50) NOT NULL,
    dept_id INT NOT NULL,
    FOREIGN KEY(dept_id) REFERENCES Department(dept_id),
    PRIMARY KEY (stud_id)
);

LOAD DATA LOCAL INFILE './Student_Record.csv' REPLACE INTO TABLE Student FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Course(
    course_id INT,
    intake INT UNSIGNED NOT NULL,
    course_name VARCHAR(50) NOT NULL,
    course_type  VARCHAR(20) NOT NULL,
    room VARCHAR(10) NOT NULL,
    dept_id INT NOT NULL,
    since INT UNSIGNED NOT NULL,
    PRIMARY KEY (course_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

LOAD DATA LOCAL INFILE './Course_Offered.csv' REPLACE INTO TABLE Course FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Professor(
    prof_id INT,
    prof_name VARCHAR(50) NOT NULL,
    sex ENUM('M','F') NOT NULL,
    dept_id INT NOT NULL,
    research VARCHAR(50) NOT NULL,
    course_id INT NOT NULL,
    PRIMARY KEY (prof_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

LOAD DATA LOCAL INFILE './Prof_Dept_Course.csv' REPLACE INTO TABLE Professor FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Dependents(
    prof_id INT,
    dependent_name VARCHAR(50),
    age INT UNSIGNED NOT NULL,
    PRIMARY KEY (dependent_name,prof_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

LOAD DATA LOCAL INFILE './dependent.csv' REPLACE INTO TABLE Dependents FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Scheduled_on(
    day VARCHAR(10),
    st_time INT,
    end_time INT,
    course_id INT,
    PRIMARY KEY (day,end_time,st_time,course_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

LOAD DATA LOCAL INFILE './Scheduled_On.csv' REPLACE INTO TABLE Scheduled_on FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

create table Attends(
    stud_id INT NOT NULL,
    course_id INT NOT NULL,
    grade INT UNSIGNED NOT NULL,
    FOREIGN KEY (course_id) REFERENCES Course(course_id),
    FOREIGN KEY (stud_id) REFERENCES Student(stud_id),
    PRIMARY KEY (stud_id,course_id)
);

LOAD DATA LOCAL INFILE './Stud_Course.csv' REPLACE INTO TABLE Attends FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

drop procedure if exists q1;
drop procedure if exists q2;
drop procedure if exists q3;
drop procedure if exists q4;

delimiter $$
create procedure q1(IN department_name VARCHAR(50)) 
begin 
SELECT prof_name FROM Professor natural join Department where dept_name = department_name ;
end;$$
delimiter ;
call q1('CSE');

delimiter $$
create procedure q2(in student_id int)
begin
select avg(grade) as cpi from Attends where stud_id = student_id;
end;$$
delimiter ;
call q2(1);

delimiter $$
create procedure q3(in student_name varchar(50),in course_iid int)
begin
declare score int;
declare result varchar(10);
select
Attends.grade into score
from
Attends
natural join Student 
where
Student.name = student_name and Attends.course_id = course_iid;

if score = 1 or score = 2 or score = 3 or score = 4 then
set result = 'FAIL';
end if;
if score = 5 then
set result = 'CD';
end if;
if score = 6 then
set result = 'CC';
end if;
if score = 7 then
set result = 'BC';
end if;
if score = 8 then
set result = 'BB';
end if;
if score = 9 then
set result = 'AB';
end if;
if score = 10 then
set result = 'AA';
end if;
select result;
end;$$
delimiter ;
call q3('Andy',101);

delimiter $$
create procedure q4(in course_iid int, out number_count int)
begin
select count(*) into number_count from Attends where course_id = course_iid;
end;$$
delimiter ;
set @count_number = 0;
call q4(101,@count_number);
