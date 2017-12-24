public class Celula extends ElementoComponent { 

    private String conteudo; 

    public Celula(String conteudo) { 
        this.conteudo = conteudo; 
    } 
    
   

    public void imprimir() {
        // Limita o conteúdo a exatamente 15 caracteres. 
        conteudo = conteudo + " ";
        conteudo = conteudo.substring(0, 15); 
        // Imprime na mesma linha e com borda lateral. 
        System.out.print(" | " + conteudo); 
   }

    @Override
    public void adicionar(ElementoComponent ec)
    {
        throw new UnsupportedOperationException("Invalid operation");
        
    } 
} 