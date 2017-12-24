
public class CriadorTriangulo implements Cloneable
{
	Triangulos t;
	public Triangulos getTriangulo(int x1, int y1,
								int x2, int y2, int x3, int y3)
	{
		return t.cloneTriagulo(x1, y1, x2, y2, x3, y3);
	}
}
