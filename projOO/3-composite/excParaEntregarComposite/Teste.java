
public class Teste
{
    public static void main(String[] args)
    {
        ElementoComponent elemento = new Linha();
        ElementoComponent elemento2 = new Celula("testetestestest");
        ElementoComponent elemento4 = new Celula("restetestestest");
        ElementoComponent elemento3 = new Tabela();
        ElementoComponent elemento5 = new Linha();
        ElementoComponent elemento6 = new Celula("sestetestestest");
       
        elemento3.adicionar(elemento);
        elemento.adicionar(elemento2);
        elemento.adicionar(elemento4);
        elemento5.adicionar(elemento6);
        elemento3.adicionar(elemento5);
        elemento3.imprimir();
    }
}
