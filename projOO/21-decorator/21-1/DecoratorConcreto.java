
public class DecoratorConcreto extends Decorator
{
 
    
    public DecoratorConcreto(Componente componente)
    {
        super(componente);     
    }

    @Override
    public void operacao()
    {
        componente.setTexto("<b>" + componente.getTexto() + "</b>");        
    }

    @Override
    public void setTexto(String textos)
    {
        
    }

}
