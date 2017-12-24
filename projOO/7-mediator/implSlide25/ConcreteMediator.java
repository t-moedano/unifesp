
public class ConcreteMediator implements Mediator
{
	Dog dog = new Dog();
	Hare hare = new Hare();
	
	public ConcreteMediator()
	{
		dog.setMediator(this);
		hare.setMediator(this);
	}
	
	public void chaseOperation()
	{
		hare.escapeDog();
	}
	
	public void escapeOperation()
	{
		dog.chaseHare();
	}
}
