import java.util.ArrayList;
import java.util.List;

public class ArrayListQueue implements Implementador
{
	ArrayList<Object> arrayQueue;
	
	public ArrayListQueue()
	{
		arrayQueue = new ArrayList<>();
	}
	

	@Override
	public void dequeue() 
	{
		arrayQueue.remove(0);
		
	}



	@Override
	public void enqueue(Object n) 
	{
		arrayQueue.add(n);	
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
