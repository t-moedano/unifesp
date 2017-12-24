public class ProcessadorEspacos implements Processador 
{
    ProcessadorLetraA p2;
    
	@Override
	public void processarRequisicao(String s) 
	{
		p2 = new ProcessadorLetraA();
		int cont = 0;
		for(int i = 0; i < s.length(); ++i)
		{
			if(s.charAt(i) == ' ')
				++cont;
			
		}
		System.out.println("Espaços: " + cont);
		p2.processarRequisicao(s);
		
	} 
	
}
