# QUERY
- - -
실행 순서
1. from 테이블에서 (join)
2. where 이런 튜플들을 (select)
3. group by 묶고
4. having 이거 가지고 있는걸
5. select 찾는대 (project)
6. order by 순서대로

```mysql
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명], }⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ]
[ GROUP BY 컬럼명 [HAVING 그룹_조건식] ]
[ ORDER BY {컬럼명|컬럼_별명|컬럼_위치 [ASC|DESC],}⁺ ];
# 조건식 := 컬럼명 비교연산자|SQL연산자 {숫자|문자|표현식}|컬럼명
```
## select
```mysql
# example
SELECT PLAYER_ID, PLAYER_NAME, BACK_NO
FROM PLAYER
WHERE TEAM_ID = 'K07'


SELECT DISTINCT POSITION # DISTINCT : 중복 제거
FROM PLAYER;


SELECT *
FROM PLAYER;


SELECT PLAYER_NAME AS 선수명, POSITION AS 위치, HEIGHT AS 키,
WEIGHT AS 몸무게
FROM PLAYER;
# 표준 SQL에서 컬럼 별명(alias)은 출력 용도로만 사용


SELECT PLAYER_NAME 이름,
ROUND(WEIGHT / ((HEIGHT/100)*(HEIGHT/100)), 2) 'BMI 비만지수'
FROM PLAYER;


SELECT CONCAT(PLAYER_NAME, '선수,', HEIGHT, 'cm,', WEIGHT, 'kg') AS 체격정보
FROM PLAYER;
```
## where
```mysql
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명],}⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ];
# 투플_조건식 := 컬럼명 비교연산자|SQL연산자 {숫자|문자|표현식}|컬럼명

# example
SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE (TEAM_ID = ‘K02’ OR TEAM_ID = ‘K07’) AND
POSITION = ‘MF’ AND
HEIGHT >= 170 AND HEIGHT <= 180; 


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE (TEAM_ID = ‘K02’ OR TEAM_ID = ‘K07’) AND
POSITION <> ‘MF’ AND
NOT (HEIGHT >= 170 AND HEIGHT <= 180);


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE TEAM_ID IN ('K02','K07'); # TEAM_ID = 'K02‘ OR TEAM_ID = 'K07';


SELECT PLAYER_NAME, TEAM_ID, POSITION, NATION
FROM PLAYER
WHERE (POSITION, NATION) IN (('MF','브라질'), ('FW', '러시아'));


SELECT PLAYER_NAME, TEAM_ID, POSITION, NATION
FROM PLAYER
WHERE POSITION IN ('MF', 'FW') AND NATION IN ('브라질', '러시아');


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE POSITION LIKE 'MF'; 


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE PLAYER_NAME LIKE '장%';


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE HEIGHT BETWEEN 170 AND 180;


SELECT PLAYER_NAME 선수이름, POSITION 포지션, TEAM_ID
FROM PLAYER
WHERE POSITION IS NULL;


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE TEAM_ID IN (‘K02’,‘K07’) AND POSITION = ‘MF’ AND HEIGHT BETWEEN 170 AND 180;
```
## Builtin Function
### string function
```
ASCII, CHAR
LOWER, UPPER
LENGTH
LOCATE
CONCAT
SUBSTRING
TRIM, LTRIM, RTRIM
```
```mysql
SELECT PLAYER_ID, CONCAT(PLAYER_NAME, ' 축구선수') AS 선수명
FROM PLAYER;

SELECT LENGTH('SQL Expert') AS ColumnLength;
```
### numeric function
```
SIGN(x), ABS(x)
FLOOR(x), ROUND(x, d) TRUNCATE(x, d), MOD(x, y)
POWER(x, y), LOG(b, x), EXP(x), SQRT(x)
SIN(x), COS(x), TAN(x), ASIN(x), ACOS(x), ATAN(x)
```
```mysql
SELECT ROUND(SUM(HEIGHT)/COUNT(HEIGHT),1)
AS '평균키(소수 둘째자리 올림)',
TRUNCATE(SUM(HEIGHT)/COUNT(HEIGHT),1)
AS '평균키(소수 둘째자리 버림)'
FROM PLAYER;
```
### date function
```
SYSDATE(), NOW()
TIMESTAMP(), DATE(), TIME()
EXTRACT(unit FROM date)
DATEDIF(), TIMEDIFF(), TIMESTAMPDIFF()
DATE_ADD(), DATE_SUB()
TIME_ADD(), TIME_SUB()
DATE_FORMAT(), GET_FORMAT(), STR_TO_DATE()
# unit = MICROSECOND | SECOND | MINUTE | HOUR |DAY | WEEK | MONTH |QUARTER | YEAR
```
```mysql
SELECT NOW(); # ‘2020-05-15 14:41:46’
SELECT NOW() + 0; # 20200515144146 


SELECT SYSDATE(), SLEEP(5), SYSDATE();
SELECT NOW(), SLEEP(5), NOW();


CREATE TABLE tmp (
id INT PRIMARY KEY AUTO_INCREMENT,
title VARCHAR(255) NOT NULL,
created_on DATETIME NOT NULL DEFAULT NOW()
# or CURRENT_TIMESTAMP
); 


SELECT TIMESTAMP(NOW()) AS CurrentTimestamp,
DATE(NOW()) AS CurrentDate,
YEAR(NOW()) AS Year,
MONTH(NOW()) AS Month,
DAY(NOW()) AS Day,
MONTHNAME(NOW()) AS MonthName,
DAYNAME(NOW()) AS DayName,
WEEKDAY(NOW()) AS WeekIndex, # Monday 0, Tuesday 1, … Sunday 6
TIME(NOW()) AS CurrentTime,
HOUR(NOW()) AS Hour,
MINUTE(NOW()) AS Minute,
SECOND(NOW()) AS Second;

EXTRACT(unit FROM date);
# unit
# QUARTER | YEAR | YEAR_MONTH | MONTH | WEEK |
# DAY | DAY_HOUR | DAY_MINUTE | DAY_SECOND | DAY_MICROSECOND |
# HOUR | HOUR_MINUTE | HOUR_SECOND | HOUR_MICROSECOND |
# MINUTE | MINUTE_SECOND | MINUTE_MICROSECOND |
# SECOND | SECOND_MICROSECOND 
 

SELECT PLAYER_NAME,
YEAR(BIRTH_DATE) 출생년도,
MONTH(BIRTH_DATE) 출생월,
DAY(BIRTH_DATE) 출생일
FROM PLAYER;

SELECT PLAYER_NAME,
EXTRACT(YEAR FROM BIRTH_DATE) 출생년도,
EXTRACT(MONTH FROM BIRTH_DATE) 출생월,
EXTRACT(DAY FROM BIRTH_DATE) 출생일
FROM PLAYER;

SELECT DATEDIFF('2009-03-01', '2009-01-01') diff; 
SELECT TIMEDIFF('2009-02-01 00:00:00', '2009-01-01 00:00:00') diff;
SELECT TIMEDIFF('2009-03-01 00:00:00', '2009-01-01 00:00:00') diff;
SELECT TIMESTAMPDIFF(HOUR, '2009-01-01 00:00:00', '2009-03-01 00:00:00') diff;


SELECT DATE_ADD('1999-12-31 00:00:01', INTERVAL 1 DAY) result;
SELECT DATE_ADD('1999-12-31 23:59:59', INTERVAL '1:1' MINUTE_SECOND) result;
SELECT DATE_ADD('2000-01-01 00:00:00', INTERVAL '-1 5' DAY_HOUR) result;
SELECT DATE_ADD('1999-12-31 23:59:59.000002', INTERVAL '1.999999' SECOND_MICROSECOND) result;


SELECT PLAYER_NAME,
DATE_FORMAT(BIRTH_DATE, '%Y-%m-%d'),
DATE_FORMAT(BIRTH_DATE, '%D %M %Y')
FROM PLAYER;


SELECT PLAYER_NAME, POSITION,
DATE_FORMAT(BIRTH_DATE, GET_FORMAT(DATE, 'ISO')) AS BIRTH_DATE
FROM PLAYER;


SELECT STR_TO_DATE('21,5,2013', '%d,%m,%Y'); /* 2013-05-21 */
SELECT STR_TO_DATE('2013', '%Y'); /* 2013-00-00 */
SELECT STR_TO_DATE('113005', '%h%i%s'); /* 11:30:05 */
SELECT STR_TO_DATE('11', '%h'); /* 11:00:00 */
SELECT STR_TO_DATE('20130101 1130', '%Y%m%d %h%i'); /* 2013-01-01 11:30:00*/
SELECT STR_TO_DATE('21,5,2013 extra characters', '%d,%m,%Y'); /* 2013-05-21 */
```
### cast function
```
CAST()
CONVERT()
```
```mysql
SELECT TEAM_ID, ZIP_CODE1, ZIP_CODE2,
CONCAT(ZIP_CODE1, '-', ZIP_CODE2) AS 우편번호,
CAST(ZIP_CODE1 AS UNSIGNED) + CAST(ZIP_CODE2 AS UNSIGNED)
AS 우편번호합
FROM TEAM;

SELECT CONVERT(‘test’ USING utf8);
```
### case function
```mysql
CASE
{ WHEN condition_expr THEN return_expr } * [ ELSE 표현식 ]
END
# condition_expr ::= expr 비교_연산자 comparison_expr
```
```mysql
SELECT PLAYER_NAME,
CASE
WHEN POSITION = 'FW' THEN 'Forward'
WHEN POSITION = 'DF' THEN 'Defense'
WHEN POSITION = 'MF' THEN 'Mid-field'
WHEN POSITION = 'GK' THEN 'Goal keeper'
ELSE 'Undefined'
END AS 포지션
FROM PLAYER;

SELECT PLAYER_NAME, HEIGHT,
	CASE
		WHEN HEIGHT >= 185 THEN 'A'
		ELSE (
			CASE
				WHEN HEIGHT >= 175 THEN 'B'
				WHEN HEIGHT < 175 THEN 'C'
				WHEN HEIGHT IS NULL THEN 'Undecided'
			END
		)
	END AS '신장 그룹'
FROM PLAYER;
```
### Handling NULL
```
COALESCE (expr1, expr2, …);
NULLIF (expr1, expr2);
```
```mysql
SELECT PLAYER_NAME,
COALESCE(POSITION, '*****') AS POSITION, # 문자형
COALESCE(HEIGHT, 0) AS HEIGHT # 숫자형
FROM PLAYER
WHERE TEAM_ID = 'K08';


SELECT MAX(HEIGHT),
FROM PLAYER
WHERE PLAYER_NAME = '손흥민'; # null

SELECT COALESCE(MAX(HEIGHT),99999) AS HEIGHT
FROM PLAYER
WHERE PLAYER_NAME = '손흥민'; # 99999

SELECT TEAM_NAME, ORIG_YYYY,
NULLIF(ORIG_YYYY, 1983) AS NULLIF_1983
FROM TEAM;
```
## Group
### Aggregate Functions
```
집단함수명 ([ALL|DISTINCT] 컬럼명|표현식);
COUNT(*)
COUNT(col)
SUM(col)
AVG(col)
STDDEV(col)
VARIAN(col)
MIN(col)
MAX(col)
```
```mysql
SELECT COUNT(PLAYER_ID), COUNT(*)
FROM PLAYER; /* 480, 480 */

SELECT COUNT(TEAM_ID), COUNT(POSITION), COUNT(BACK_NO),
COUNT(HEIGHT)
FROM PLAYER; /* 480, 477, 438, 448 */

SELECT COUNT(TEAM_ID), COUNT(DISTINCT POSITION),
COUNT(DISTINCT BACK_NO), COUNT(DISTINCT HEIGHT)
FROM PLAYER; /* 15, 4, 55, 29 */

SELECT ROUND( SUM(HEIGHT) / COUNT(*), 1) AS '잘못된 평균키',
ROUND( SUM(HEIGHT) / COUNT(HEIGHT), 1) AS '올바른 평균키',
ROUND( AVG(HEIGHT), 1) AS 'AVG 함수'
FROM PLAYER;
```
### Group By
```
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명],}⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ]
[ GROUP BY 컬럼명 ];
```
```mysql
SELECT POSITION 포지션, COUNT(*) 인원수, COUNT(HEIGHT) 키대상,
MAX(HEIGHT) 최대키, MIN(HEIGHT) 최소키,
ROUND(AVG(HEIGHT),2) 평균키
FROM PLAYER
GROUP BY POSITION;
```
### Having
```
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명],}⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ]
[ GROUP BY 컬럼명 [HAVING 그룹_조건식] ];

# Having 절에서는 GROUP BY 또는 집단함수에서 사용한 컬럼만 사용 가능하다
```
```mysql
SELECT TEAM_ID 팀아이디, COUNT(*) 인원수
FROM PLAYER
GROUP BY TEAM_ID HAVING TEAM_ID IN ('K09', 'K02');

SELECT TEAM_ID 팀아이디, COUNT(*) 인원수
FROM PLAYER
WHERE TEAM_ID IN ('K09', 'K02') # 더 효율적인 코드
GROUP BY TEAM_ID;

SELECT PLAYER_NAME AS '선수이름',
COUNT(PLAYER_NAME) AS '동명이인의 인원수'
FROM PLAYER
GROUP BY PLAYER_NAME HAVING COUNT(PLAYER_NAME) >=2;

SELECT POSITION 포지션, ROUND(AVG(HEIGHT),2) 평균키
FROM PLAYER
GROUP BY POSITION HAVING AVG(HEIGHT) >= 180;

# where 절에 집단함수 사용하면 병신이다
SELECT POSITION 포지션, ROUND(AVG(HEIGHT),2) 평균키
FROM PLAYER
WHERE AVG(HEIGHT) >= 180 /* 에러 */
GROUP BY POSITION;


# 팀 별로 각각의 생월(태어난 달)에 대한 선수의 평균 키를 구함.
SELECT TEAM_ID, COUNT(*) AS '선수 수',
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 1 THEN HEIGHT END),2) M01,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 2 THEN HEIGHT END),2) M02,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 3 THEN HEIGHT END),2) M03,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 4 THEN HEIGHT END),2) M04,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 5 THEN HEIGHT END),2) M05,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 6 THEN HEIGHT END),2) M06,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 7 THEN HEIGHT END),2) M07,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 8 THEN HEIGHT END),2) M08,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 9 THEN HEIGHT END),2) M09,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 10 THEN HEIGHT END),2) M10,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 11 THEN HEIGHT END),2) M11,
ROUND(AVG(CASE MONTH(BIRTH_DATE) WHEN 12 THEN HEIGHT END),2) M12,
ROUND(AVG(CASE WHEN MONTH(BIRTH_DATE) IS NULL THEN HEIGHT END),2) 생일모름
FROM PLAYER
GROUP BY TEAM_ID;

/* 질의 : 팀별로 각 포지션(FW,MF,DF,GK)에 대한 인원수, 그리고
팀의 전체 인원수를 구하라. 단 데이터가 없는 경우는 0으로
표시한다.
 */
SELECT TEAM_ID,
SUM(CASE POSITION WHEN 'FW' THEN 1 ELSE 0 END) FW,
SUM(CASE POSITION WHEN 'MF' THEN 1 ELSE 0 END) MF,
SUM(CASE POSITION WHEN 'DF' THEN 1 ELSE 0 END) DF,
SUM(CASE POSITION WHEN 'GK' THEN 1 ELSE 0 END) GK,
SUM(CASE WHEN POSITION IS NULL THEN 1 ELSE 0 END) UNDECIDED,
COUNT(*) SUM
FROM PLAYER
GROUP BY TEAM_ID;
```
## Order By
```mysql
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명],}⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ]
[ GROUP BY 컬럼명 [HAVING 그룹_조건식] ]
[ ORDER BY {컬럼명|컬럼_별명|컬럼_위치 [ASC|DESC],}⁺ ];

# ASC가 기본이다
```
```mysql
SELECT PLAYER_NAME 선수명, POSITION 포지션, BACK_NO 백넘버
FROM PLAYER
ORDER BY 포지션 ASC; 


SELECT PLAYER_NAME 선수이름, POSITION 포지션, BACK_NO 백넘버,
HEIGHT 키
FROM PLAYER
WHERE HEIGHT IS NOT NULL
ORDER BY HEIGHT DESC, BACK_NO;


SELECT PLAYER_NAME 선수명, POSITION 포지션, BACK_NO 백넘버,
FROM PLAYER
WHERE BACK_NO IS NOT NULL
ORDER BY 3 DESC, 2, 1; 

# ORDER BY 절에는 SELECT 목록에 나타나지 않은 컬럼이 포함될 수 있음.
SELECT PLAYER_ID, POSITION
FROM PLAYER
ORDER BY PLAYER_NAME; // No Error !!
```

## Limit
```mysql
SELECT [ALL|DISTINCT] { {컬럼명 [[AS] 컬럼_별명],}⁺ | * }
FROM 테이블_리스트
[ WHERE 투플_조건식 ]
[ GROUP BY 컬럼명 [HAVING 그룹_조건식] ]
[ ORDER BY {컬럼명|컬럼_별명|컬럼_위치 [ASC|DESC],}⁺ ]
[ LIMIT [offset, ] row_count ];
```
```mysql
# 가장 규모가 큰 3개 경기장
SELECT STADIUM_ID, STADIUM_NAME, SEAT_COUNT
FROM STADIUM
ORDER BY SEAT_COUNT DESC, STADIUM_NAME
LIMIT 3; # LIMIT 0, 3

# 11, 12, 13, 14, 15
SELECT STADIUM_ID, STADIUM_NAME, SEAT_COUNT
FROM STADIUM
ORDER BY SEAT_COUNT DESC, STADIUM_NAME
LIMIT 10, 5


SELECT ROW_NUMBER( ) OVER (ORDER BY SEAT_COUNT DESC) AS ROW_NUM,
	STADIUM_ID, STADIUM_NAME, SEAT_COUNT,
	RANK( ) OVER (ORDER BY SEAT_COUNT DESC) AS SEAT_RANK
FROM STADIUM;
```
