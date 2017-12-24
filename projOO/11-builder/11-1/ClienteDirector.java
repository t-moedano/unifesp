
public class ClienteDirector 
{
	protected EntidadeBuilder entidade;
	
	public ClienteDirector(EntidadeBuilder entidade)
	{
		this.entidade = entidade;
	}
	
	public void buildEntidade()
	{
		entidade.buildAttributes();
	}
	
	public EntidadeProduct getEntidade()
	{
		return entidade.getEntidade();
	}
}
