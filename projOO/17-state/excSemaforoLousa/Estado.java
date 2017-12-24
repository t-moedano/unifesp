
public abstract class Estado
{
    String verde, vermelho, amarelo;
    
    public Estado()
    {
        verde = new String();
        amarelo = new String();
        vermelho = new String();
    }
    public void execute()
    {
        
    }
    
    public void printSemaforo()
    {
        System.out.println("vermelho: " + vermelho);
        System.out.println("amarelo: " + amarelo);
        System.out.println("verde: " + verde);
    }
}
