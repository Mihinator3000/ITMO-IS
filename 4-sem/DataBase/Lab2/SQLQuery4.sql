select ProductID, count(*) Count
from Sales.SalesOrderDetail
group by ProductID