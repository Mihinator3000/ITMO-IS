select ProductID
from Sales.SalesOrderDetail
where OrderQty > 1
group by ProductID
having count(*) > 2