select count(*) Count
from Production.Product
where ProductSubcategoryID is not null and Color is not null
group by ProductSubcategoryID
