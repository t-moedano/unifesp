import java.util.ArrayList;
import java.util.List;

public class Linha extends ElementoComponent {
    private  List<ElementoComponent> celulas = new ArrayList<ElementoComponent>(); 
 
    public void  imprimir() 
    {
        // Imprime a borda lateral. 
        System.out.println(" |"); 
        // Imprime a linha.
        int tamanho = (celulas.size() * 17) + 5;
        char[] linha = new char[tamanho];
        for (int i = 0; i < tamanho; i++) linha[i] = '-'; 
        System.out.println(" " + new String(linha)); 
        for(ElementoComponent ec : celulas)
            ec.imprimir();
  } 
   
    @Override
    public void adicionar(ElementoComponent ec)
    {
        celulas.add(ec);
        
    }    
} 