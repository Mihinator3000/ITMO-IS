select ProductID
from Sales.SalesOrderDetail
group by ProductID
having count(*) in (3,5)