select top 1 SalesOrderID
from Sales.SalesOrderDetail
group by SalesOrderID
order by sum(UnitPrice * OrderQty) desc