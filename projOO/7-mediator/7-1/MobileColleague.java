public class MobileColleague extends Colleague {

  public MobileColleague(Mediator m) 
  {
		super(m);
		m.addColleague(this);
   }

public void receive(String message) {

    System.out.println("Mobile Received: " + message);

  }

}
