
public class Panic extends Estado
{
    public Panic()
    {
        super();
    }
    @Override
    public void execute()
    {
        vermelho = "on";
        amarelo = "off";
        verde = "off";
    }
}
