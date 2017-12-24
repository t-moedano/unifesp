
public class Fonte 
{
	private Memento memento;
	private String estado;
	
	public Memento criarMemento()
	{
		return new Memento();
	}
	
	public void setMemento(Memento m)
	{
		memento = m;
	}
	
}
