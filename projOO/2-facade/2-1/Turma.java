import java.util.List;

public class Turma 
{
	private List<Aluno> aluno;
	private Curso curso;
	
	
	public List<Aluno> getAluno() {
		return aluno;
	}
	public void setAluno(Aluno aluno) {
		this.aluno.add(aluno);
	}
	public Curso getCurso() {
		return curso;
	}
	public void setCurso(Curso curso) {
		this.curso = curso;
	}
	
	
}
