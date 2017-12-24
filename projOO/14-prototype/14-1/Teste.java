
public class Teste 
{
	public static void main(String[] args) 
	{
		FabricaConcreta f = new FabricaConcreta();
		Ponto p1 = f.createPonto(3, 2);
		System.out.println("p1: " + p1.getX() + " " + p1.getY());
		Ponto p2 = f.createPonto(5, 3);
		System.out.println("p1: " + p1.getX() + " " + p1.getY());
		System.out.println("p1: " + p2.getX() + " " + p2.getY());
	}
}
