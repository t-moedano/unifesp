
public class Quadrado implements Figura {

	String nome;
	double lado;
	double area;
	
	public Quadrado()
	{
		nome = "Quadrado";
		lado = 3;
	}
	@Override
	public void area() 
	{
		area = lado * lado;
		
	}

	@Override
	public void setName(String nome) 
	{
		this.nome = nome;
		
	}

}
