import java.util.ArrayList;
import java.util.List;

public class Artigo extends Publicacao
{
    String nome;
    List<String> autores;
    
    public Artigo(String nome)
    {
        this.nome = nome;
        autores = new ArrayList<>();
    }
    
    @Override
    public void addAutor(String autor)
    {
       autores.add(autor);
    }
    
    @Override
    public String toString()
    {
        String artigoNome = nome;
        for(String a : autores)
            nome += " " + autores;
        
        return nome;
    }

}
