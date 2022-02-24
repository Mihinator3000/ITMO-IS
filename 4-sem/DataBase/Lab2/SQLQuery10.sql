select ProductSubcategoryID
from Production.Product
group by ProductSubcategoryID
having count(*) > 10