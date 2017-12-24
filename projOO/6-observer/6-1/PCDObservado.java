import java.util.ArrayList;
import java.util.List;

public class PCDObservado 
{
	List<InstituicaoObserver> observers;
	
	public PCDObservado()
	{
		observers = new ArrayList<>();
	}
	
	public void add (InstituicaoObserver pInstObserver)
	{
		observers.add(pInstObserver);
	}
	
	public void notifyObserver(String alt)
	{
		for(InstituicaoObserver o : observers)
		{
			o.update(this, alt);
		}
	}
	
}
