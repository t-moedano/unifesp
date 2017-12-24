
public class TrEquilatero implements Figura {

	String nome;
	double lado;
	double area;
	
	public TrEquilatero()
	{
		lado = 4;
		nome = "Triangulo";
	}
	
	@Override
	public void area() 
	{
		area = (lado * lado * Math.sqrt(3)) / 4;
		
	}
	
	@Override
	public void setName(String nome) 
	{
		this.nome = nome;		
	}

}
