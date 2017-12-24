
public class TesteSingleton 
{
	public static void main(String[] args) 
	{
		FacadeSingleton f1, f2, f3;
		f1 = FacadeSingleton.getFacade();
		f2 = FacadeSingleton.getFacade();
		f3 = FacadeSingleton.getFacade();
		
		if(f1 == f2 && f2 == f3 && f1 == f3)
			System.out.println("É Singleton!");
	}
}
