import java.util.HashMap;
import java.util.Set;

public class ComandoAll implements Comando
{
	public void all(HashMap<Long,String> map)
	{
		Set<Long> idList = map.keySet();
		for(Long id : idList)
		{
			System.out.println(map.get(id));
		}
	}

	@Override
	public void execute(HashMap<Long, String> map, Long id, String nome) {
		all(map);
	}

	
}
