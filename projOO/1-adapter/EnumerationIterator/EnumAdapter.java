
import java.util.Enumeration;
import java.util.Iterator;

/**
 * @author Thauany Moedano
 * Adaptador que trnasforma um enum em iterador
 */
public class EnumAdapter extends EnumGenericClass implements Iterator
{
	Enumeration enumList;
	
	public EnumAdapter()
	{
		enumList = getElements();
	}
	
	@Override
	public boolean hasNext()
	{
		return enumList.hasMoreElements();
	}

	@Override
	public Object next() 
	{
		
		return enumList.nextElement();
	}
	
}
