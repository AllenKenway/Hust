use DBexp;
Go
/**��ɾ��*/

--����ȷɾ��/�޸�MBLOG
insert into MBLOG(BID,TITLE,UID,PYEAR,PMONTH,PDAY,CONT) values (8,null,1,2019,4,22,'�˹������ӱ���һ������һ����ħ��������ƽ�� ��������');
delete from MBLOG where BID = 2;
update MBLOG set BID=8 where BID=1;

--�ɽ�ֹ
insert into THUMB(UID,BID) values(1,1);	
update THUMB set BID=1 where UID=1 and BID=3;

--����ȷɾ��
delete from USERS where UID = 2;

--ɾ��B_L���������΢��
delete from LABEL where LID=4;

--���жϲ������
insert into THUMB(UID,BID)values(1,9);


DROP TABLE IF EXISTS FANS_3;
select * into FANS_3 from USERS where UID in(select UID from FOLLOW where FOLLOW.UIDFLED=3);

insert into FANS_3(UID,NAME,SEX,BYEAR,CITY) values (1,'��һ','��',2001,'�人');






