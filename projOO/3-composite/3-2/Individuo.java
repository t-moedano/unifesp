
public class Individuo extends InstituicaoComponent
{
    private String nome, assento;
    
    public Individuo(String nome, String assento)
    {
        this.nome = nome;
        this.assento = assento; 
    }

    public String getNome()
    {
        return nome;
    }

    public void setNome(String nome)
    {
        this.nome = nome;
    }

    @Override
    public String getAssento()
    {
        return assento;
    }

    public void setAssento(String assento)
    {
        this.assento = assento;
    }
    
    
}
