use DBexp;
Go

--���µ��ޱ�
go
drop trigger if exists insert_THUMB;
go
create trigger insert_THUMB on THUMB
AFTER insert,update
as
begin
	DECLARE @newUID INT
	DECLARE @newBID INT
	SELECT @newUID=UID FROM inserted
	SELECT @newBID=BID FROM inserted
		IF @newUID=(SELECT UID FROM MBLOG WHERE BID=@newBID)
			BEGIN
				RAISERROR('��ֹ�������߸��Լ����ޣ���������ֹ',1,1)
				rollback transaction
			END
END


--�����û���
go
drop trigger if exists delete_USER;
go
create trigger delete_USER on USERS
INSTEAD OF delete
as
begin
	DECLARE @id INT
	select @id=UID from deleted
	delete from MBLOG where UID=@id
	delete from FOLLOW where UID=@id or UIDFLED=@id
	delete from FRIENDS where UID=@id or FUID=@id
	delete from USERS where UID=@id
END



