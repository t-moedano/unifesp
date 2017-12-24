
public interface Mediator 
{

  public void send(String message, Colleague colleague);
  public void addColleague(Colleague colleague);

}
