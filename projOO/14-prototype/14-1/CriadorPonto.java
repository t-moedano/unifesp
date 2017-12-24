
public class CriadorPonto implements Cloneable
{
	Ponto p;
	
	public CriadorPonto()
	{
		p = new Ponto(1,1);
	}
	public Ponto getPonto(int x, int y) 
	{
		return p.clonePonto(x, y);
		
	}
}
