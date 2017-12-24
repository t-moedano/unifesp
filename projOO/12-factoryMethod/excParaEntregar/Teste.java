
public class Teste
{
    
    public static void main(String[] args)
    {
       NomeFactory fabricaNome = new NomeFactory();
       fabricaNome.getNome("modo1", "Scott", "McNealy").getNomeCompleto();
       fabricaNome.getNome("modo2", "Scott", "McNealy").getNomeCompleto();
    }
    
    
}
