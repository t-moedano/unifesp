
public class Trecho extends TrechoComponent
{
    private String origem;
    private String destino;
    private float preco;
    
    public Trecho(String origem, String destino, float preco)
    {
        this.origem = origem;
        this.destino = destino;
        this.preco = preco;
    }
	@Override
    public String getOrigem()
    {
        return origem;
    }

    @Override
    public String getDestino()
    {
       return destino;
    }
	
	 @Override
    public void getPreco()
    {
        return preco;
    }

    @Override
    public void setPreco(float preco)
    {
        this.preco = preco;
    }
    @Override
    public void setOrigem(String origem)
    {
        this.origem = origem;
    }

    @Override
    public void setDestino(String destino)
    {
       this.destino = destino;
    }
    
}
