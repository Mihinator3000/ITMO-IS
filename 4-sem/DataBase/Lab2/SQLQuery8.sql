select ProductID
from Sales.SalesOrderDetail
group by ProductID
having count(*) > 3