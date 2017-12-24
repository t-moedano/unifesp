import java.util.List;

public class ListQueue implements Implementador 
{

	List lista;
	
	
	@Override
	public void enqueue(Object n) 
	{
		lista.add(n);
		
	}

	@Override
	public void dequeue() 
	{
		lista.remove(0);
		
	}

	@Override
	public boolean isEmpty() {
		return lista.isEmpty();
	}

	@Override
	public int size() {
		return lista.size();
	}

}
