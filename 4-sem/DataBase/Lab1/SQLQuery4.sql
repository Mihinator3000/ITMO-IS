select Name, Color, Size
from Production.Product
where ListPrice < 100 and Color = 'Black'
order by ListPrice asc