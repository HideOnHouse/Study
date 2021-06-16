# *Insert*
## Data Update
- - - 
### Insert
```mysql
INSERT INTO 테이블명 [(컬럼명_리스트)]
VALUES (컬럼값_리스트);

INSERT INTO 테이블명 [(컬럼명_리스트)]
SELECT 문;

#example
INSERT INTO PLAYER (PLAYER_ID, PLAYER_NAME, TEAM_ID, POSITION,HEIGHT, WEIGHT, BACK_NO)
VALUES ('2002007', '박지성', 'K07', 'MF', 178, 73, 7); 

CREATE TABLE BLUE_DRAGON_TEAM1 (
PLAYER_ID CHAR(7) NOT NULL,
PLAYER_NAME VARCHAR(20) NOT NULL,
BACK_NO TINYINT
);

INSERT INTO BLUE_DRAGON_TEAM1
SELECT PLAYER_ID, PLAYER_NAME, BACK_NO
FROM PLAYER
WHERE TEAM_ID = ‘K07';

CREATE TABLE BLUE_DRAGON_TEAM2 [AS]
SELECT PLAYER_ID, PLAYER_NAME, BACK_NO
FROM PLAYER
WHERE TEAM_ID = ‘K07';
```
### Delete
```mysql
DELETE FROM 테이블명
[WHERE 조건식]; # -> where이 없으면 테이블의 전체 데이터가 삭제됩니다. TRUNCATE TABLE이 바람직함

# example
DELETE FROM PLAYER
WHERE PLAYER_ID = '2002007'; # PLAYER_ID는 PK

DELETE FROM PLAYER
WHERE POSITION = 'GK'; # safe_update mode에서 거부됨.

DELETE FROM PLAYER; # safe_update mode에서 거부됨.

# safe update mode: 2개 이상의 투플이 삭제되는 경우 실행되지 않음
```

### Update
```mysql
UPDATE 테이블명
SET {컬럼명 = 산술식, }⁺
[WHERE 조건식];

UPDATE PLAYER
SET BACK_NO = 99
WHERE PLAYER_ID = '2000001';

UPDATE PLAYER
SET BACK_NO = 99
```
## QUERY
- - -
### Select
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

# example
SELECT PLAYER_ID, PLAYER_NAME, BACK_NO
FROM PLAYER
WHERE TEAM_ID = ‘K07';


SELECT DISTINCT POSITION # DISTINCT : 중복 제거
FROM PLAYER;

SELECT *
FROM PLAYER; 


```