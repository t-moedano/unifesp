
public class Triangulos 
{
	Ponto p1, p2, p3;

	public Triangulos(Ponto p1, Ponto p2, Ponto p3)
	{
		this.p1 = p1;
		this.p2 = p2;
		this.p3 = p3;
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

	public Ponto getP3() {
		return p3;
	}

	public void setP3(Ponto p3) {
		this.p3 = p3;
	}
	
	public Triangulos cloneTriagulo(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		CriadorPonto p = new CriadorPonto();
		Ponto p1 = p.getPonto(x1, y1);
		Ponto p2 = p.getPonto(x2, y2);
		Ponto p3 = p.getPonto(x3, y3);
		
		try
		{
			return (Triangulos) super.clone();
		} catch (CloneNotSupportedException e)
		{
			return new Triangulos(p1, p2, p3);
		}
		
	}
	
}
