
public class Teste
{
    public static void main(String[] args)
    {
        Texto texto = new Texto("abc");
        DecoratorConcreto dc = new DecoratorConcreto(texto);
        DecoratorConcreto2 dc2 = new DecoratorConcreto2(texto);
        DecoratorConcreto3 dc3 = new DecoratorConcreto3(texto);
        dc.operacao();
        System.out.println(texto.getTexto());
        dc2.operacao();
        System.out.println(texto.getTexto());
        dc3.operacao();
        System.out.println(texto.getTexto());
    }
}
