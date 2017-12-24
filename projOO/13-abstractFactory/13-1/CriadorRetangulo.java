
public class CriadorRetangulo 
{

	CriadorPonto p;
	
	public Retangulo getRetangulo(int x1, int y1, int x2, int y2)
	{
		Ponto p1 = p.getPonto(x1, y1);
		Ponto p2 = p.getPonto(x2, y2);
		
		Retangulo r = new Retangulo(p1, p2);
		
		return r;
	}
}
