
public class Facade 
{
	BancoDeDados banco;
	
	public void registrar(String nome, int id)
	{
		Cliente c = new Cliente(nome, id);
		Carrinho carrinho = new Carrinho();
		c.setCarrinhoCliente(carrinho);
	}
	
	public void comprar(Produto p, long codCliente)
	{
		banco.selectCliente(codCliente);
		/*O banco retornaria um Cliente*/
		Cliente c = new Cliente("teste", codCliente);
		c.getCarrinhoCliente().adicionar(p);
	}
	
	public void fecharCompra(long codCliente)
	{
		banco.selectCliente(codCliente);
		/*O banco retornaria um Cliente*/
		Cliente c = new Cliente("teste", codCliente);
		double total = c.getCarrinhoCliente().getTotal();
		banco.processarPagamento();
	}
}
