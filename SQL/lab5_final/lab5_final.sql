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


create view q11 as select course_id,max(grade) as grade from Attends group by course_id;
create view q12 as select Attends.stud_id, q11.course_id from Attends natural join q11;
select q12.course_id, Student.name from Student natural join q12; 

create view q21 as select stud_id from Attends group by stud_id having sum(grade)>=20 and sum(grade)<=30;
select Student.name from Student natural join q21; 

create view q31 as select Dependents.dependent_name, Professor.prof_name, Professor.prof_id, Professor.dept_id, Professor.research from Dependents natural join Professor;
create view q32 as select * from q31 natural join Department; 
select * from q32 where dept_name = 'CSE' or dept_name = 'MATHS';

create view q41 as select prof_id, prof_name, sex, research from Professor;
select * from q41 where research = 'ML';
select research,count(prof_id) AS 'No of Professor' from q41 group by research;
update q41 set research = 'DS' where research = 'ML';
select prof_name, research from Professor where research = 'ML';

create view q51 as select Professor.prof_name,Professor.prof_id,Professor.dept_id,Department.dept_name from Professor natural join Department with CHECK OPTION; 
create view q52 as select Professor.prof_name,Professor.prof_id,Professor.dept_id,Department.dept_name from Professor natural join Department;

update q51 set dept_name = 'CSE' where prof_name = 'SAMBIT PATRA'; 
update q52 set dept_name = 'CSE' where prof_name = 'SAMBIT PATRA'; 
