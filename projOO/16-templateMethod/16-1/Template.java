import java.util.Comparator;

public class Template implements Comparator
{

	@Override
	public int compare(Object o1, Object o2) 
	{
		String s1 = (String) o1;
		String s2 = (String) o2;
		
		if(s1.indexOf(s1.length()-1) > s2.indexOf(s2.length()-1))
			return 1;
		if(s1.indexOf(s1.length()-1) < s2.indexOf(s2.length()-1))
			return -1;
		
		return 0;
	}
	
}
