import java.util.ArrayList;
import java.util.List;

public class Carrinho 
{
	List<Produto> produtos;
	
	public Carrinho()
	{
		produtos = new ArrayList<>();
	}
	
	public void adicionar(Produto p)
	{
		produtos.add(p);
	}
	
	public double getTotal()
	{
		double total = 0;
		for(Produto p : produtos)
		{
			total += p.getPreco();
		}
		return total;
	}
}
