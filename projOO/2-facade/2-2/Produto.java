
public class Produto 
{
	String nome;
	long id;
	double preco;
	
	public Produto(String nome, long id, float preco)
	{
		this.id = id;
		this.nome = nome;
		this.preco = preco;
	}

	public double getPreco() 
	{
		return preco;
	}
}
