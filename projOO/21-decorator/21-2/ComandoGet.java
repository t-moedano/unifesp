import java.util.HashMap;

public class ComandoGet implements Comando
{
	public String get(Long id, HashMap<Long,String> map)
	{
		return map.get(id);
	}

	@Override
	public void execute(HashMap<Long, String> map, Long id, String nome) {
		String s = get(id, map);
		System.out.println(s);
	}
}
