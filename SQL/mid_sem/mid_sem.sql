drop database IF EXISTS mid_sem;
create database mid_sem;
use mid_sem;

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

load data local infile 'stud_Course.csv' replace into table attends frields terminated by ',' lines terminated by '\n';
load data local infile '' into table attends fields terminated by ',' lines terminated by '\n';
load data local infile '' into table  attends fields terminated by ',' lines terminated by '\n';
load data local infile '' into table attends fields terminated by ',' lines terminated by '\n';

delimiter $$

create procedure p1 (in x int,out ans int)
begin
declare i int default 0;
set i = 1;
set ans = 1;
while i<=x do
set ans = ans * i;
set i = i+1; 
end while;
end $$

delimiter ;

call p1(7,@ans);
select @ans as factorial;


delimiter $$

create procedure p2(in x int,out ans int)
begin
declare i int;
set i=1;
set ans=1;
fact: loop
if i>=x then
leave fact;
end if;

set ans = ans * i;
set i=i+1;
end loop;
end $$

delimiter ;


delimiter $$

create procedure p3(in x int, out ans int)
begin
declare i int;
set i=1;
set ans=1;
repeat 
set ans = ans * i;
set i = i+1;
until i<=x
end repeat;
end $$

delimiter ;

create view v1 as
select prof_name from Professor with check option;

select s.name, a.grade from Student s natural join Attends a;

select s.name, a.grade from Student s left join Attends a;

select s.name, a.grade from Student s cross join Attends a;

select stud_id from Student
UNION
select grade from Attends where grade <= 9;

create table t1(
    name varchar(50) not null,
    age int not null,
    primary key (name),
    foreign key (name) REFERENCES student(stud_id) on delete cascade
)

insert into t1(name,age) values
('ram',23),
('raju',54);