import java.util.List;

public class PublicacaoTeste
{
    public static void main(String[] args)
    {
        Publicacao colecao = new Colecao();
        
        Publicacao artigo1 = new Artigo("artigo1");
        
        Publicacao artigo2 = new Artigo("artigo2");
        
        artigo1.addAutor("autor1");
        
        artigo2.addAutor("autor2");
        
        colecao.addPublicacao(artigo1);
        colecao.addPublicacao(artigo2);
        
        String nome = colecao.toString();
        System.out.println(nome);
    }
   
    
    
}
