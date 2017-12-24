
public class AplicacaoCliente 
{
	MatriculaFacade matricula;
	
	public void aplicacao(String nomeAluno, String nomeTurma, String nomeCurso, AplicacaoUtils tipoAplicacao)
	{
		matricula.setStatus(tipoAplicacao);
		matricula.matricular(nomeAluno, nomeCurso, nomeTurma);
	}
}
