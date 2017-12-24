
public class Tick extends Estado
{
    
    public Tick()
    {
        super();
    }
    @Override
    public void execute()
    {
        if(vermelho.equals("on"))
        {
            vermelho = "off";
            verde = "on";
        }
        else if(verde.equals("on"))
        {
            verde = "off";
            amarelo = "on";
        }
        else
        {
            amarelo = "off";
            vermelho = "on";
        }
        printSemaforo();
    }
    
}
