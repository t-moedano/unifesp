import java.util.List;

public abstract class Publicacao
{
    public List<Publicacao> getPublicacao()
    {
        throw new UnsupportedOperationException();
    }
    public void addPublicacao(Publicacao publicacao)
    {
        throw new UnsupportedOperationException();
    }
    
    public void addAutor(String autor)
    {
        throw new UnsupportedOperationException();
    }
    public abstract String toString();
}
