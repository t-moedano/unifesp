import java.util.Random;

public class CreateNumbers 
{
	public static void main(String[] args) 
	{
		Random random = new Random();
		FlyweightFactory ff = new FlyweightFactory();
		
		for(int i = 0; i < 10; ++ i)
		{
			System.out.print(ff.getFlyWeight(random.nextInt(10)).getNum() + " ");
		}
	}
}
