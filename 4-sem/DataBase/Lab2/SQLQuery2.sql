select Color
from Production.Product
group by Color
having min(ListPrice) > 100