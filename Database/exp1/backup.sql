use DBexp;
--ɾ���߼��豸
EXEC sp_dropdevice backup_DBexp

--�½��߼��豸
EXEC sp_addumpdevice 'DISK','backup_DBexp','D:\Microsoft SQL Server\MSSQL14.MSSQLSERVER\BACKUPDEV\dbexp.bak'

--�������ݿ�
BACKUP DATABASE DBexp TO backup_DBexp

--������־�ļ�
BACKUP LOG DBexp TO backup_DBexp

--ɾ�����ݿ�
use master   
go      
declare @dbname sysname   
set @dbname = 'DBexp' --�����Ҫɾ�������ݿ����   
      
declare @s nvarchar(1000)   
declare tb cursor local  
for 
    select s = 'kill   ' + cast(spid as varchar) 
    from   master.dbo.sysprocesses 
    where  dbid = DB_ID(@dbname)   
      
open   tb     
fetch   next   from   tb   into   @s   
while @@fetch_status = 0 
begin 
    exec (@s)  
    fetch next from tb into @s 
end   
close   tb   
deallocate   tb 
DROP DATABASE DBexp;

--��ԭ���ݿ�
RESTORE DATABASE DBexp FROM backup_DBexp;


--SQL Server ��ֹ�˶������xp_cmdshell���� ���̡�sys.xp_cmdshell���ķ��ʣ���Ϊ���������Ϊ�˷�������ȫ���õ�һ���ֶ����رա�
go
sp_configure 'show advanced options',1
reconfigure
go
sp_configure 'xp_cmdshell',1
reconfigure



--������excel
--EXEC master..xp_cmdshell 'bcp "SELECT * FROM DBexp.USERS"  queryout  ��D:\Microsoft SQL Server\MSSQL14.MSSQLSERVER\BACKUPDEV\USERS.txt�� -c'