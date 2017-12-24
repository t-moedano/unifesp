
public class FabricaConcreta extends FabricaAbstrata
{
	CriadorPonto p;
	CriadorRetangulo r;
	CriadorTriangulo t;
	CriadorCirculo c;
	
	public Ponto createPonto(int x, int y)
	{
		return p.getPonto(x, y);
	}
	
	public Circulo createCirculo(int x1, int y1, double r)
	{
		return c.getCirculo(x1, y1, r);
	}
	
	public Retangulo createRetangulo(Ponto p1, Ponto p2)
	{
		return null;
	}
	
	public Triangulos createTriangulo(Ponto p1, Ponto p2, Ponto p3)
	{
		return null;
	}
}
