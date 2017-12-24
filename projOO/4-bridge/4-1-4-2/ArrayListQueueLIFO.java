import java.util.ArrayList;
import java.util.List;

public class ArrayListQueueLIFO implements Implementador
{

	List arrayQueue;
	
	public ArrayListQueueLIFO()
	{
		arrayQueue = new ArrayList<>();
	}
	
	@Override
	public void enqueue(Object n) 
	{
		arrayQueue.add(n);
		
	}

	@Override
	public void dequeue() 
	{
		arrayQueue.remove( arrayQueue.size()-1  );
		
	}

	@Override
	public boolean isEmpty() 
	{
		return arrayQueue.isEmpty();
		
	}

	@Override
	public int size() 
	{
		return arrayQueue.size();
	}
	
}
