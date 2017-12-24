
public class Circulo implements Figura 
{
	double area;
	int raio;
	String nome;
	
	public Circulo()
	{
		raio = 2;
		nome = "Circulo";
	}
	
	@Override
	public void area() 
	{
		area = 3.14 * raio * raio;
		System.out.println("Area: " + area);
	}

	@Override
	public void setName(String nome) 
	{
		this.nome = nome;
		
	}

}
