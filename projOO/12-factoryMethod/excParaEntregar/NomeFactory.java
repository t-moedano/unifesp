import java.util.HashMap;

public class NomeFactory
{
    static HashMap<String, Nome> factory;
    
    public NomeFactory()
    {
        factory = new HashMap<String, Nome>();
        factory.put("modo1", new NomeTipo1());
        factory.put("modo2", new NomeTipo2());
    }
    
    public static Nome getNome(String tipo, String nome, String sobrenome)
    {
        Nome tipoNome = (Nome) factory.get(tipo);
        tipoNome.setNome(nome);
        tipoNome.setSobrenome(sobrenome);
        
        return tipoNome;
    }
}
