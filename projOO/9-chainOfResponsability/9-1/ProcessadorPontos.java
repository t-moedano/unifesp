
public class ProcessadorPontos implements Processador
{
	@Override
	public void processarRequisicao(String s)
	{
		int cont = 0;
		for(int i = 0; i < s.length(); ++i)
		{
			if(s.charAt(i) == '.')
				++cont;
			
		}
		System.out.println("Pontos: " + cont);
	}
 
}
