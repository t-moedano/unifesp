
public class PessoaBuilder extends EntidadeBuilder 
{

	@Override
	public void buildAttributes() 
	{
		System.out.println("Pegando do banco");
		entidade.nome = "teste";
		entidade.id = 123;
	}
	
	
}
