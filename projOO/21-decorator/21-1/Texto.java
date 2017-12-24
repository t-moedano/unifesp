
public class Texto implements Componente
{
    String texto;
    
    public Texto(String texto)
    {
        this.texto = texto;
    }

    @Override
    public String getTexto()
    {
        return texto;
    }

    @Override
    public void setTexto(String texto)
    {
        this.texto = texto;
    }

    @Override
    public void operacao()
    {
        // TODO Auto-generated method stub
        
    }
}
