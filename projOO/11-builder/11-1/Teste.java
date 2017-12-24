
public class Teste 
{
	public static void main(String[] args) 
	{
		ClienteDirector _cliente = new ClienteDirector(new EmpresaBuilder());
		_cliente.buildEntidade();
		EntidadeProduct entidade = _cliente.getEntidade();
		System.out.println("Entidade: " + entidade.nome);
	}
}
