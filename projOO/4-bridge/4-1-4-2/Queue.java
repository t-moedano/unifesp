
public abstract class Queue 
{
	Implementador impl;
	
	public abstract void enqueue(Object n);
	public abstract void dequeue();
	public abstract boolean isEmpty();
	public abstract int size();
}
