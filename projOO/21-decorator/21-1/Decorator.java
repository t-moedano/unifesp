
public abstract class Decorator implements Componente
{
    public Componente componente;
    
    public Decorator(Componente componente)
    {
        this.componente = componente;
    }
    
    public String getTexto()
    {
        return componente.getTexto();
    }
    
    public void operacao()
    {
        componente.operacao();
    }
}
