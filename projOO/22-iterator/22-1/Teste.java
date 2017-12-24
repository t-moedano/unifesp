import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Teste
{
    public static void main(String[] args)
    {
        Quadrado q = new Quadrado();
        Circulo c = new Circulo();
        TrEquilatero tr = new TrEquilatero();
        
        ListaDeFiguras f = new ListaDeFiguras();
        f.add(q);
        f.add(c);
        f.add(tr);
        f.itera();
        
    }
}
