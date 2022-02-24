select SalesOrderID
from Sales.SalesOrderDetail
group by SalesOrderID
having count(*) > 3