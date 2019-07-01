use DBexp;
Go
--1��ѯ���������û���ע�������û���ID�š��������Ա𡢳�����ݣ����ڳ��У����Ұ��ճ�����ݵĽ������У�ͬһ����ݵ������û�ID���������С�
select USERS2.UID,USERS2.NAME,USERS2.SEX,USERS2.BYEAR,USERS2.CITY
from FOLLOW,USERS USERS1,USERS USERS2
where USERS1.NAME='����' and USERS1.UID=FOLLOW.UID and FOLLOW.UIDFLED=USERS2.UID
order by USERS2.BYEAR desc,USERS2.UID asc;


--2����û�б��κ��˵��޵Ĳ���ID�������Լ�����������������������ձ����ַ�˳�����С�
select MBLOG.TITLE,MBLOG.TITLE,USERS.NAME
from MBLOG,USERS
where MBLOG.UID=USERS.UID and MBLOG.BID not in(
select MBLOG.BID
from THUMB
where THUMB.BID=MBLOG.BID
);


--3����2000���Ժ�������人���û�����Ľ����ͷ���Ĳ���ID��
select TOPDAY.BID
from TOPDAY,MBLOG,USERS
where TOPDAY.BID=MBLOG.BID and MBLOG.UID=USERS.UID and USERS.BYEAR>=2000 and USERS.CITY='�人';


--4���Ҷ��������з�����û�ID��
select USERS.UID,count(SUB.LID)
from USERS,SUB
where USERS.UID=SUB.UID
group by USERS.UID
having count(SUB.LID) = (select count(*)from LABEL); 


--5���ҳ������С��1970����ߴ���2010����û�ID��������ݡ����ڳ��У�Ҫ��where�Ӿ���ֻ����һ���������ʽ��
select USERS.UID,USERS.BYEAR,USERS.CITY
from USERS
where USERS.BYEAR not between 1970 and 2010;


--6ͳ��ÿ�����е��û�����
select USERS.CITY,count (USERS.UID)
from USERS
group by USERS.CITY;


--7ͳ��ÿ�����е�ÿ��������ݵ��û���������������ճ��е��������У�ͬһ�����а��ճ����û����Ľ�����������Ӧ����ݣ�
select USERS.CITY,USERS.BYEAR,count (USERS.UID)
from USERS
group by USERS.CITY,USERS.BYEAR
order by USERS.CITY asc,USERS.BYEAR desc;


--8���ұ�����������10�Ĳ���ID�ţ�
select THUMB.BID,count(THUMB.UID)
from THUMB
group by THUMB.BID
having count(THUMB.UID)>10;


--9���ұ�2000���������û�����������10�Ĳ���ID�ţ�
select THUMB.BID,count(THUMB.UID)
from THUMB,USERS
where THUMB.UID = USERS.UID and USERS.BYEAR >2000
group by THUMB.BID
having count(THUMB.UID)>10;


--10���ұ�2000���������û�����������10��ÿƪ���ĵĽ���ͷ���Ĵ�����
select TOPDAY.BID,count(TOPDAY.TNO)
from TOPDAY
where TOPDAY.BID IN (
	select THUMB.BID
	from THUMB,USERS
	where THUMB.UID = USERS.UID and USERS.BYEAR >2000
	group by THUMB.BID
	having count(THUMB.UID)>10)
	group by TOPDAY.BID;


--11���Ҷ�������ѧ����������ѧ������������һ�ַ�����û�ID��Ҫ����ʹ��Ƕ�ײ�ѯ����where�Ӿ������ֻ�ܰ�������������
select DISTINCT SUB.UID
from SUB,LABEL
where SUB.LID=LABEL.LID and LABEL.LNAME in ('��ѧ','����','��ѧ','����');


--12���ұ����а����ˡ�������վ���͡�_���пƼ���ѧ�������ʵĲ��Ļ�����Ϣ��
select *
from MBLOG
where MBLOG.TITLE like '%������վ%' or MBLOG.TITLE like '%���пƼ���ѧ%';


--13 ���������໥��ע���û��Ե�����ID�ţ�Ҫ����ʹ��Ƕ�ײ�ѯ��
--����1 2 ��2 1�Ƿ���ȥ��
select a.UID,b.UID
from FOLLOW a,FOLLOW b
where a.UIDFLED=b.UID and a.UID=b.UIDFLED and a.UID>b.UID;


--14���Һ���Ȧ������5���û�����Ȧ���û�ID��
select distinct f1.UID
from FRIENDS f1
where not exists (
	select * 
	from FRIENDS f2 
	where f2.UID=5 and f2.FUID not in(
		select FUID 
		from FRIENDS f3
		where f3.UID=f1.UID
	)
);     

--15����2019��4��20��ÿһƪͷ�����ĵ�ID�š������Լ��ò��ĵ�ÿһ������ID��Ҫ��ʹ�ò���û���κη���IDҲҪ�����ID�š����⣻
select TOPDAY.BID,MBLOG.TITLE,B_L.LID
from TOPDAY,MBLOG,B_L
where TOPDAY.TYEAR=2019 and TOPDAY.TMONTH=4 and TOPDAY.TDAY=20 and TOPDAY.BID=MBLOG.BID and TOPDAY.BID=B_L.BID;


--16����������3����ͬ���ѵ������û��Ե�����ID�š�
--����1 2 ��2 1�Ƿ���ȥ��
select a.UID,b.UID,count(b.FUID)
from FRIENDS a,FRIENDS b
where a.UID!=b.UID and a.FUID=b.FUID and a.UID>b.UID
group by a.UID,b.UID
having count(b.FUID)>=2;


--17������ͼ������DBMS�ڲ�����������һ����ʾ�����ȶ�����ǰʮ��΢����Ϣ����ͼ�����е����԰���������ID�����ı��⡢������ID������������������������
DROP VIEW  if exists MBLOG_VIEW;
go
create view MBLOG_VIEW(BID,TITLE,UID,NAME,CountNUM) as(
select MBLOG.BID,MBLOG.TITLE,MBLOG.UID,USERS.NAME,count(THUMB.UID)
from THUMB,MBLOG,USERS,TOPDAY
where TOPDAY.BID = MBLOG.BID and MBLOG.BID=THUMB.BID and MBLOG.UID=USERS.UID and TOPDAY.TNO<10 and TOPDAY.TYEAR = (select YEAR(GETDATE())) and TOPDAY.TMONTH = (select MONTH(GETDATE())) and TOPDAY.TDAY = (select DAY(GETDATE()))
group by MBLOG.BID,MBLOG.TITLE,MBLOG.UID,USERS.NAME
);
Go
select * from MBLOG_VIEW;
