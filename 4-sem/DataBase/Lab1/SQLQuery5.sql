select top 3 Name, Size
from Production.Product
where Color = 'Black'
order by ListPrice desc