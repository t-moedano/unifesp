import java.util.ArrayList;
import java.util.List;

public class FlyweightFactory 
{
	List<AlgarismoFlyweight> flyweightPool;
	
	public FlyweightFactory()
	{
		flyweightPool = new ArrayList<>();
	}
	public AlgarismoFlyweight getFlyWeight(int id)
	{
		for(AlgarismoFlyweight a : flyweightPool)
		{
			if(a.getNum() == id)
				return a;
		}
		
		AlgarismoFlyweight a = new AlgarismoFlyweight(id);
		flyweightPool.add(a);
		return a;
	}
	
	
}
