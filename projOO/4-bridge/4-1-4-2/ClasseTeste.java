
public class ClasseTeste 
{

	public static void main(String[] args) 
	{
		FIFOQueue fq = new FIFOQueue();
		fq.impl = new VectorQueue();
		
		Object n = new Object();
		fq.enqueue(n);
		System.out.println("FIFO - Tamanho da fila: " + fq.size() + " Esta vazia: " +  fq.isEmpty());
		
		
		LIFOQueue lf = new LIFOQueue();
		lf.impl = new VectorQueueLIFO();
		
		Object n2 = new Object();
		lf.enqueue(n);
		lf.enqueue(n2);
		System.out.println("LIFO - Tamanho da fila: " + lf.size() + " Esta vazia: " +  lf.isEmpty());
	}
}
