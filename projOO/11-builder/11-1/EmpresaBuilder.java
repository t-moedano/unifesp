
public class EmpresaBuilder extends EntidadeBuilder 
{
	PessoaBuilder pessoa;
	
	@Override
	public void buildAttributes() 
	{
		System.out.println("Pegando do banco");
		entidade.id = 987;
		entidade.nome = "teste2";
		System.out.println("Empresa: " + entidade.nome + " Id: " + entidade.id);
		pessoa = new PessoaBuilder();
		pessoa.buildAttributes();
		System.out.println("Pessoa: " + pessoa.entidade.nome + " Id: " + pessoa.entidade.id);
		
	}
}
