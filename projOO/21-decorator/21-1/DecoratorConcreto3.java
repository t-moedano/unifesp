
public class DecoratorConcreto3 extends Decorator
{

    public DecoratorConcreto3(Componente componente)
    {
        super(componente);     
    }

    @Override
    public void operacao()
    {
        StringBuffer sb = new StringBuffer(componente.getTexto());
        componente.setTexto(sb.reverse().toString());
        
    }

    @Override
    public void setTexto(String textos)
    {
        
    }
}
