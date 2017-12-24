import java.util.ArrayList;
import java.util.List;

public class Tabela extends ElementoComponent{
    private  List<ElementoComponent> linhas = new ArrayList< ElementoComponent >(); 
   
    @Override
    public void imprimir()
    {
        for(ElementoComponent ec : linhas)
            ec.imprimir();
    }
    
    @Override
    public void adicionar(ElementoComponent ec)
    {
        linhas.add(ec);
        
    }
} 