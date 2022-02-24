select count(*) Count
from Production.Product
where ListPrice >= 30
group by Color