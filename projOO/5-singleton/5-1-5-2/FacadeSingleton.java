public class FacadeSingleton 
{
	private BancoDeDados banco;
	private static FacadeSingleton facade;
	
	public static FacadeSingleton getFacade()
	{
		if (facade == null)
			facade = new FacadeSingleton();
		
		return facade;
	}
	
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
