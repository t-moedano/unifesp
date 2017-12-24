
public class Off extends Estado
{
    
    public Off()
    {
        super();
    }
    @Override
    public void execute()
    {
        verde = "off";
        vermelho = "off";
       for(int i = 0; i < 30; ++i)
       {
            amarelo = "on";
            printSemaforo();
            amarelo = "off";
            printSemaforo();
       }
        
    }
}
