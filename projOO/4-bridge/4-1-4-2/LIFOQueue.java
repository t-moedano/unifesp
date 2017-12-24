
public class LIFOQueue extends Queue
{
	
	public void enqueue(Object n)
	{
		impl.enqueue(n);
	}
	
	public void dequeue()
	{
		impl.dequeue();	
	}
	
	public boolean isEmpty()
	{
		return impl.isEmpty();
	}
	
	public int size()
	{
		return impl.size();
	}
	
}
