
public class Circulo implements Cloneable
{
	Ponto p;
	double r;
	
	public Circulo(Ponto p, double r)
	{
		this.p = p;
		this.r = r;
	}
	
	public Ponto getP() {
		return p;
	}
	public void setP(Ponto p) {
		this.p = p;
	}
	public double getR() {
		return r;
	}
	public void setR(double r) {
		this.r = r;
	}
	
	public Circulo cloneCirculo(int x, int y, double r)
	{
		CriadorPonto p = new CriadorPonto();
		Ponto p1 = p.getPonto(x, y);
		try 
		{
			return (Circulo) super.clone();
			
		} catch (CloneNotSupportedException e)
		{
			return new Circulo(p1, r);
		}
	}
}
