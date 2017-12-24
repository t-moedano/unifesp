
public class Texto implements Documento
{

    @Override
    public Visitante aceitar(Visitante v)
    {
        return v.visitar(this);
        
    }
    
    public String  gerarHTML()
    {
       return "HTML";
    }
    
    public String gerarTexto()
    {
        return "TEXTO";
    }
    
    public String gerarXML()
    {
        return "XML";
    }
    
    
}
