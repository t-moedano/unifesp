import java.util.ArrayList;
import java.util.List;

public class Colecao extends Publicacao
{

    List<Publicacao> publicacoes;
    
    public Colecao()
    {
        publicacoes = new ArrayList<>();
    }
    @Override
    public String toString()
    {
        String nome = null;
        for(Publicacao artigo : publicacoes)
            nome += " " + artigo.toString();
        
        return nome;
    }
    
    @Override
    public List<Publicacao> getPublicacao()
    {
        return publicacoes;
    }

    @Override
    public void addPublicacao(Publicacao publicacao)
    {
        publicacoes.add(publicacao);
    }
}
