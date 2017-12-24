
public class ClienteFacade 
{
	CriadorFactory criador = new CriadorFactory();
	
	public void showAreaFigura(String nome)
	{
		Figura figura = criador.getCriador("Circulo");
		
		figura.area();
	}
}
