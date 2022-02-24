select CustomerID
from Sales.SalesOrderHeader
group by CustomerID, OrderDate
having count(SalesOrderID) > 1