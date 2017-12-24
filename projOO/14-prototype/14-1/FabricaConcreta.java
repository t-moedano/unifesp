
public class FabricaConcreta extends FabricaAbstrata implements Cloneable
{
	CriadorPonto p;
	CriadorRetangulo r;
	CriadorTriangulo t;
	CriadorCirculo c;
	
	public FabricaConcreta()
	{
		r = new CriadorRetangulo();
		t = new CriadorTriangulo();
		c = new CriadorCirculo();
	}
	
	public Ponto createPonto(int x, int y)
	{
		p = new CriadorPonto();
		return p.getPonto(x, y);
	}
	
	public Circulo createCirculo(int x1, int y1, double r)
	{
		return c.getCirculo(x1, y1, r);
	}
	
	public Retangulo createRetangulo(int x1, int y1, int x2, int y2)
	{
		return r.getRetangulo(x1, y1, x2, y2);
	}
	
	public Triangulos createTriangulo(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		return t.getTriangulo(x1, y1, x2, y2, x3, y3);
	}
}
