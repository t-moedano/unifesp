
public class CriadorTriangulo 
{
	CriadorPonto p;
	
	public Triangulos getTriangulo(int x1, int y1,
								int x2, int y2, int x3, int y3)
	{
		Ponto p1 = p.getPonto(x1, y1);
		Ponto p2 = p.getPonto(x2, y2);
		Ponto p3 = p.getPonto(x3, y3);
		Triangulos t = new Triangulos(p1, p2, p3);
		
		return t;
	}
}
