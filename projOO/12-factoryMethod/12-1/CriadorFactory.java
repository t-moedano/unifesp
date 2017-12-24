import java.util.HashMap;

public class CriadorFactory 
{
	static HashMap<String, Figura> criadores;
	
	public CriadorFactory()
	{
		criadores = new HashMap<String, Figura>();
		criadores.put("Circulo", new Circulo());
		criadores.put("Quadrado", new Quadrado());
		criadores.put("TrEquilatero", new TrEquilatero());
	}
	
	public static Figura getCriador(String key)
	{
		return (Figura) criadores.get(key);
	}
}
