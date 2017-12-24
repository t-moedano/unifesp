
public class Retangulo 
{
	Ponto p1;
	Ponto p2;
	
	public Retangulo(Ponto p1, Ponto p2)
	{
		this.p1 = p1;
		this.p2 = p2;
	}
	
	public Ponto getP1() {
		return p1;
	}
	public void setP1(Ponto p1) {
		this.p1 = p1;
	}
	public Ponto getP2() {
		return p2;
	}
	public void setP2(Ponto p2) {
		this.p2 = p2;
	}
	
	public Retangulo cloneRetangulo(int x1, int x2, int y1, int y2)
	{
		CriadorPonto p = new CriadorPonto();
		Ponto p1 = p.getPonto(x1, y1);
		Ponto p2 = p.getPonto(x2, y2);
		
		try
		{
			return (Retangulo) super.clone();
		} catch (CloneNotSupportedException e)
		{
			return  new Retangulo(p1, p2);
		}

	}
}
