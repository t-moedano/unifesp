import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ListaDeFiguras
{

    List<Figura> list;
    
    public ListaDeFiguras()
    {
        list = new ArrayList<>();
    }
    
    public void itera()
    {
        Iterator it = list.iterator();
        while(it.hasNext())
        {
            Figura fig = (Figura) it.next();
            System.out.println(fig.toString());
        }
    }
    
    public void add(Figura f)
    {
        list.add(f);
    }
}
