import java.util.List;

public class Instituicao extends InstituicaoComponent
{
    List<Individuo> alunos;
    
    public Instituicao(List<Individuo> alunos)
    {
        for(Individuo i : alunos)
            this.alunos.add(i);
    }

    @Override
    public List<Individuo> getMembros()
    {
        return alunos;
    }
    
    
}
