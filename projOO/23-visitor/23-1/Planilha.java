
public class Planilha implements Documento
{

    @Override
    public Visitante aceitar(Visitante v)
    {
        return v.visitar(this);
        
    }
    
    public void gerarHTML()
    {
        System.out.println("Gerando HTML");
    }
    
    public void gerarTexto()
    {
        System.out.println("Gerando Texto");
    }
    

}
