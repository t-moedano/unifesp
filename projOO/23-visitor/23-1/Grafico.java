
public class Grafico implements Documento
{

    @Override
    public Visitante aceitar(Visitante v)
    {
        return v.visitar(this);
        
    }
    
    public void gerarPNG()
    {
        System.out.println("Gerando PNG");
    }
    
    public void gerarTexto()
    {
        System.out.println("Gerando Texto");
    }

}
