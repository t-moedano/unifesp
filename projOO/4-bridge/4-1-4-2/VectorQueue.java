import java.util.Vector;

public class VectorQueue implements Implementador
{

	Vector<Object> vectorQueue;
	
	public VectorQueue()
	{
		vectorQueue = new Vector<Object>();
	}
	@Override
	public void enqueue(Object n) 
	{
		vectorQueue.add(n);
		
	}

	@Override
	public void dequeue() 
	{
		vectorQueue.remove(0);
		
	}

	@Override
	public boolean isEmpty() {
		return vectorQueue.isEmpty();
	}

	@Override
	public int size() 
	{
		return vectorQueue.size();
	}

	
}
