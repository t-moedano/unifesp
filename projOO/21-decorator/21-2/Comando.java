import java.util.HashMap;

public interface Comando 
{
	public void execute(HashMap<Long,String> map, Long id, String nome);
}
