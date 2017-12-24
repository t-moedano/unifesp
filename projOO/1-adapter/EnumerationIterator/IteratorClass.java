

import java.util.Iterator;

/**
 * @author Thauany Moedano
 * Classe que exibe os elementos a partir de um iterador
 */
public class IteratorClass 
{
	public void showVectorElements(Iterator i)
	{
		System.out.println("Elements: ");
		while(i.hasNext())
		{
			System.out.println(i.next());
		}
	}
}
