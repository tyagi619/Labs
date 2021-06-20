drop database IF EXISTS lab6;
create database lab6;
use lab6;

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
drop procedure if exists q4_1;
drop procedure if exists q4_2;
drop procedure if exists q4_3;
drop procedure if exists q5_1;
drop procedure if exists q5_2;
drop procedure if exists q5_3;
drop procedure if exists q6;

delimiter $$
create procedure q1(in gender int)
begin
case gender
  when 0 then
    select * from Professor where sex = 'F';
  when 1 then
    select * from Professor where sex = 'M';
end case;
end;$$
delimiter ;
call q1(1);

delimiter $$
create procedure q2(in x int)
begin
  declare ans int;
  declare counter int;
  set ans=1;
  set counter=1;
  while counter <= x do
    set ans = ans * counter;
    set counter = counter + 1;
  end while;

  select ans;
end;$$
delimiter ;
call q2(1);

delimiter $$
create procedure q3(in professor_id int)
begin
declare num_dependents int;
select count(*) into num_dependents from Dependents where prof_id = professor_id;
if num_dependents > 5 then
select '7000' as 'gift amount';
else
select (num_dependents+1)*1000 as 'gift amount';
end if;
end;$$
delimiter ;
call q3(1207);

delimiter $$
create procedure q4_1(in step int, in temp int)
begin
set temp = temp + step;
end;$$
delimiter ;

delimiter $$
create procedure q4_2(in step int, out temp int)
begin
set temp = temp + step;
end;$$
delimiter ;

delimiter $$
create procedure q4_3(in step int, inout temp int)
begin
set temp = temp + step;
end;$$
delimiter ;

set @temp = 7;
set @step = 1;
call q4_1(@step,@temp);
select @temp;

set @temp = 7;
set @step = 1;
call q4_2(@step,@temp);
select @temp;

set @temp = 7;
set @step = 1;
call q4_3(@step,@temp);
select @temp;

delimiter $$
create procedure q5_1(in step int, in temp int)
begin
select grade,count(*) from Attends group by grade;
update Attends set grade = temp+step where grade = temp;
select grade,count(*) from Attends group by grade;
end;$$
delimiter ;

delimiter $$
create procedure q5_2(in step int, out temp int)
begin
select grade,count(*) from Attends group by grade;
update Attends set grade = temp+step where grade = temp;
select grade,count(*) from Attends group by grade;
end;$$
delimiter ;

delimiter $$
create procedure q5_3(in step int, inout temp int)
begin
select grade,count(*) from Attends group by grade;
update Attends set grade = temp+step where grade = temp;
select grade,count(*) from Attends group by grade;
end;$$
delimiter ;

set @temp = 4;
set @step = 1;
select @temp;
call q5_1(@step,@temp);
select @temp;

set @temp = 7;
set @step = 1;
select @temp;
call q5_2(@step,@temp);
select @temp;

set @temp = 9;
set @step = 1;
select @temp;
call q5_3(@step,@temp);
select @temp;

delimiter $$
create procedure q6(in area varchar(50),out num int)
begin
select count(*) into num from Professor where research = area;
end;$$
delimiter ;

set @count = 0;
call q6('DS',@count);
select @count as 'Number of Professors';
set @count = 0;
call q6('SPEECH',@count);
select @count as 'Number of Professors';
