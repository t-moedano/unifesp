
public class InstituicaoImpl implements InstituicaoObserver
{
	String nome;
	public InstituicaoImpl(String nome)
	{
		this.nome = nome;
	}
	@Override
	public void update(PCDObservado pcd, String alt)
	{
		PCDData pcdData = (PCDData) pcd;
		System.out.println(nome + " recebendo notificação " +
						alt + " alterado");
		
		System.out.println(pcdData.getPh() + " " +
				pcdData.getPressaoAtmosferica() + " " +
				pcdData.getTemperatura());
	
	}
	
}
