
public class Ponto implements Cloneable 
{
	int x, y;
	
	public Ponto(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	
	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}
	
	public Ponto clonePonto(int x, int y)
	{
		try
		{
			Ponto ponto = (Ponto) super.clone();
			ponto.setX(x);
			ponto.setY(y);
			return ponto;
		} catch (CloneNotSupportedException e)
		{
			return new Ponto(x, y);
		}
	}
}
