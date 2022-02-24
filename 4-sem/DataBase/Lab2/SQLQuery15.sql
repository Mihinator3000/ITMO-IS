select Color
from Production.Product
group by Color
order by count(*) desc