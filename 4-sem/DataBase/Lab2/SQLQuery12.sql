select top 1 SalesOrderID
from Sales.SalesOrderDetail
group by SalesOrderID
order by count(*) desc 