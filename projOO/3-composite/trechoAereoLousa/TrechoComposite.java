
public class TrechoComposite extends TrechoComponent
{

  
    private TrechoComponent destino;
	private TrechoComponent origem;
    
    public TrechoComposite(TrechoComponent origem, TrechoComponent destino)
    {
        this.origem = origem;
        this.destino = destino;
 
    }
    @Override
    public String getOrigem()
    {
       return origem.getOrigem();
    }
	
	 @Override
    public void setOrigem(String origem)
    {
        throw new Exception(UnsupportedOperationException);
    }

    @Override
    public String getDestino()
    {
        return destino.getDestino();
    }

	 @Override
    public void setDestino(String destino)
    {
       throw new Exception(UnsupportedOperationException);
    }
	
    @Override
    public double getPreco()
    {
        return origem.getPreco() + destino.getPreco();
    }
	
	@Override
    public void setPreco(float preco)
    {
        throw new Exception(UnsupportedOperationException);
    }
   

   

}
