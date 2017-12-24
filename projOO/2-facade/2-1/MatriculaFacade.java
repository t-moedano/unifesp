
public class MatriculaFacade 
{
	public String nomeAluno;
	public String nomeCurso;
	public AplicacaoUtils aplicacao; 
	
	
	public AplicacaoUtils getStatus() {
		return aplicacao;
	}


	public void setStatus(AplicacaoUtils status) {
		this.aplicacao = status;
	}


	public void matricular(String nomeAluno, String nomeCurso, String nomeTurma)
	{
		/*Pegaria dados do Aluno do banco*/
		Aluno aluno = new Aluno();
		aluno.setNome(nomeAluno);
		aluno.setMatricula(1);
		
		/*Pegaria dados do Curso do banco*/
		Curso curso = new Curso();
		curso.setNome(nomeCurso);
		
		/*Pegaria dados da Turma do banco*/
		int statusTurma = aplicacao.exibirStatus();
		
		if(statusTurma == 1)
		{
			Turma turma = new Turma();
			turma.setAluno(aluno);
			turma.setCurso(curso);
			
		}
	}
	
}
