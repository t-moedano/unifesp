

public class Cliente 
{
	String nome;
	long id;
	Carrinho carrinhoCliente;
	
	public Cliente(String nome, long id)
	{
		this.nome = nome;
		this.id = id;
	}

	public Carrinho getCarrinhoCliente() {
		return carrinhoCliente;
	}

	public void setCarrinhoCliente(Carrinho carrinhoCliente) {
		this.carrinhoCliente = carrinhoCliente;
	}
	
	
	
	
}
