public class ConcreteColleague extends Colleague {

  public ConcreteColleague(Mediator m) 
  {
		super(m);
		m.addColleague(this);
	}

public void receive(String message) {

    System.out.println("Colleague Received: " + message);

  }

}