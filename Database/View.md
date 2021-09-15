# *View*
하나 이상의 기본 테이블로부터 유도된 가상 테이블  
SELECT 문을 사용하여 정의한다 (window)
DBMS는 뷰의 정의만 저장하고, 데이터는 뷰에 대한 검색 요청 시 동적으로 생성한다
## Create View
- - -
```mysql
CREATE VIEW 뷰_이름[(컬럼명_리스트)] AS
SELECT 문
[WITH CHECK OPTION]; # edit에 의해 기존에 보이던 행이 보이지 않게 되는 경우를 막는 장치
```
```mysql
CREATE TABLE table
(
id INT,
name CHAR(20)
);
CREATE VIEW view AS
SELECT *
FROM table
WHERE id < 10
WITH CHECK OPTION;
/* WHERE 절 조건을 위반하는 삽입/수정을 거부 */
INSERT INTO view
VALUES (20, ‘test’); /* 에러 */

# 한 개의 bases table에서 유도된 뷰
CREATE VIEW CSTUDENT(SNO, SNAME, YEAR) AS
SELECT SNO, SNAME, YEAR
FROM STUDENT
WHERE DEPT = '컴퓨터'
WITH CHECK OPTION;

# 두개 (join view)
CREATE VIEW HONOR(SNAME, DEPT, GRADE) AS
SELECT STUDENT.SNAME, STUDENT.DEPT, ENROL.GRADE
FROM STUDENT JOIN ENROL ON STUDENT.SNO = ENROL.SNO
WHERE ENROL.FINAL > 95;

# view에서 유도된 view
CREATE VIEW COMHONOR AS
SELECT SNAME, GRADE
FROM HONOR
WHERE DEPT = '컴퓨터';

# 컬럼명의 상속
CREATE VIEW DEPTSIZE(DEPT, STNUM) AS
SELECT DEPT, COUNT(*)
FROM STUDENT
GROUP BY DEPT;

CREATE VIEW DEPTSIZE AS
SELECT DEPT, COUNT(*) AS STNUM
FROM STUDENT
GROUP BY DEPT;
```
## Drop View
- - -
```mysql
DROP VIEW 뷰_이름 {RESTRICT|CASCADE}
```
```mysql
# RESTRICT
DROP VIEW HONOR RESTRICT; /* COMHONOR로 인해 거부됨 */

# CASCASE
DROP VIEW HONOR CASCADE; /* COMHONOR도 같이 제거됨 */
```
## View에 대한 질의 재작성 (Query Rewrite)
```mysql
CREATE VIEW HONOR(SNAME, DEPT, MID, FINAL) AS
SELECT STUDENT.SNAME, STUDENT.DEPT, ENROL.MID, ENROL.FINAL
FROM STUDENT JOIN ENROL USING (SNO)
WHERE ENROL.GRADE = 'A';

CREATE VIEW COMHONOR AS
SELECT SNAME, MID, FINAL
FROM HONOR
WHERE DEPT = '컴퓨터'

# View에 대한 검색
CREATE VIEW HONOR(SNAME, DEPT, MID, FINAL) AS
SELECT STUDENT.SNAME, STUDENT.DEPT, ENROL.MID, ENROL.FINAL
FROM STUDENT JOIN ENROL USING (SNO)
WHERE ENROL.GRADE = 'A';

SELECT SNAME, DEPT, MID, FINAL
FROM HONOR
WHERE MID < 80;

# 같은 행동
SELECT STUDENT.SNAME, STUDENT.DEPT, ENROL.MID, ENROL.FINAL
FROM STUDENT JOIN ENROL USING (SNO)
WHERE ENROL.GRADE = 'A' AND ENROL.MID < 80;


# View에 대한 검색
CREATE VIEW HONOR(SNAME, DEPT, MID, FINAL) AS
SELECT STUDENT.SNAME, STUDENT.DEPT, ENROL.MID, ENROL.FINAL
FROM STUDENT JOIN ENROL USING (SNO)
WHERE ENROL.GRADE = 'A';

CREATE VIEW COMHONOR AS
SELECT SNAME, MID, FINAL
FROM HONOR
WHERE DEPT = '컴퓨터';

# 같은 행동
SELECT SNAME
FROM COMHONOR
WHERE MID < 80;
```
## View의 조작
- - -
### Column Subset View
```mysql
CREATE VIEW SVIEW1 AS
SELECT SNO, DEPT /* PK 포함 */
FROM STUDENT;

CREATE VIEW SVIEW2 AS
SELECT DISTINCT SNAME, DEPT /* PK 미포함 */
FROM STUDENT;
```
### Row Subset View
```mysql
CREATE VIEW SVIEW3 AS
SELECT * /* 항상 PK 포함 */
FROM STUDENT
WHERE YEAR = 4;
```
### Update View
```mysql
UPDATE SVIEW1
SET DEPT='English Literature'
WHERE SNO=123; /* PK에 대한 셀렉트 조건 */

UPDATE SVIEW3
SET DEPT='English Literature'
WHERE SNO=123; /* PK에 대한 셀렉트 조건 */

UPDATE SVIEW2
SET DEPT='English Literature'
WHERE SNAME='홍길동'; /* PK에 대한 조건이 아님 동명이인이 존재 가능 */
```