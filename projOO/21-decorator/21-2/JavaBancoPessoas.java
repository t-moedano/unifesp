import java.util.HashMap;

public class JavaBancoPessoas 
{
	HashMap<String, Comando> comandoList;
	HashMap<Long, String> pessoasList;
	
	public JavaBancoPessoas()
	{
		comandoList = new HashMap();
		Comando get = new ComandoGet();
		Comando all = new ComandoAll();
		Comando delete = new ComandoDelete();
		Comando novo = new ComandoNovo();
		comandoList.put("get", get);
		comandoList.put("all", all);
		comandoList.put("delete", delete);
		comandoList.put("novo", novo);
	}
	
	public void getComando(String comandoNome, Long id, String nome)
	{
		Comando c = comandoList.get(comandoNome);
		c.execute(pessoasList, id, nome);
	}
	
}
