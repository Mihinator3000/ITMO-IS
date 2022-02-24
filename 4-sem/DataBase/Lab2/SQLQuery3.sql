select ProductSubcategoryID, count(*)
from Production.Product
group by ProductSubcategoryID