import java.util.Calendar;
import java.util.GregorianCalendar;

public class ClassePrincipal 
{

	
	
	public static void main(String[] args) 
	{
		GregorianCalendar gc = new GregorianCalendar();
		EstrategiaI e = null;
		long day = gc.get(Calendar.DAY_OF_WEEK);
		if(day == 4)
			e = new EstrategiaUm();
		
		else if(day == 1)
			e = new EstrategiaDois();
		else
			e = new EstrategiaTres();
		e.msg();
	}
}
