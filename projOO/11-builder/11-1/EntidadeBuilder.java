
public abstract class EntidadeBuilder 
{
	protected EntidadeProduct entidade;
	
	public EntidadeBuilder()
	{
		entidade = new EntidadeProduct();
	}
	
	public abstract void buildAttributes();
	
	public EntidadeProduct getEntidade()
	{
		return entidade;
	}
}
