
public class TrechoTeste
{
    public static void main(String[] args)
    {
        TrechoComponent trecho = new Trecho("Sao Paulo", "Brasilia", 25.0);
        TrechoComponent trecho2 = new Trecho("Brasilia", "Acre", 27.0);
		trecho2.setPreco(24.0);
        TrechoComponent trechoComposite = new TrechoComposite(trecho, trecho2);
        
        double preco = trechoComposite.getPreco();
        System.out.println(preco);
    }
}
