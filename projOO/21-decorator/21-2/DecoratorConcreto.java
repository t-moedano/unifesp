
public class DecoratorConcreto
{
    Comando c;
    
    DecoratorConcreto(Comando c)
    {
        this.c = c;
    }
    
    public void decorator()
    {
        System.out.println(c.toString());
    }
}
