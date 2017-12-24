
public class CriadorRetangulo implements Cloneable
{

	Retangulo r;
	public Retangulo getRetangulo(int x1, int y1, int x2, int y2)
	{
		return r.cloneRetangulo(x1, x2, y1, y2);
	}
}
