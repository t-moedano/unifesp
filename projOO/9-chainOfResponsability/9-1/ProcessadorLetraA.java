
public class ProcessadorLetraA implements Processador 
{
	ProcessadorPontos p3;
	@Override
	public void processarRequisicao(String s) 
	{
		p3 = new ProcessadorPontos(); 
		int cont = 0;
		for(int i = 0; i < s.length(); ++i)
		{
			if(s.charAt(i) == 'a')
				++cont;
			
		}
		System.out.println("Letras A: " + cont);
		p3.processarRequisicao(s);
	}

}
