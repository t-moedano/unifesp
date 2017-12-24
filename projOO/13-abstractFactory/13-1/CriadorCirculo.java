
public class CriadorCirculo 
{
	CriadorPonto p;
	
	public Circulo getCirculo(int x, int y, double r)
	{
		p = new CriadorPonto();
		Ponto p1 = p.getPonto(x, y);
		Circulo c = new Circulo(p1, r);
		
		return c;
	}
}
