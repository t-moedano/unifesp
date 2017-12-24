
public class DecoratorConcreto2 extends Decorator
{
    public DecoratorConcreto2(Componente componente)
    {
        super(componente);     
    }

    @Override
    public void operacao()
    {
        componente.setTexto(componente.getTexto().toUpperCase());        
    }

    @Override
    public void setTexto(String textos)
    {
        
    }
}
