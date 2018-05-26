package com.springws;

import java.io.BufferedReader;
import java.io.FileReader;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import com.springws.bo.AlbumBo;
import com.springws.bo.PersonBo;
import com.springws.bo.StickerToPersonBo;
import com.springws.bo.StickersBo;
import com.springws.model.Album;
import com.springws.model.Person;
import com.springws.model.StickerToPerson;
import com.springws.model.Stickers;

/**
 * Hello world!
 *
 */
public class DatabasenInformation 
{
    public static void main( String[] args )
    {
        ApplicationContext appContext =  new ClassPathXmlApplicationContext("file:src/main/resources/spring/config/BeanLocations.xml");

        AlbumBo albumBo = (AlbumBo)appContext.getBean("albumBo");
        Album album = new Album();
        album.setAlbumName("2018 Panini FIFA World Cup");
        albumBo.create(album);
        StickersBo stickersBo = (StickersBo)appContext.getBean("stickersBo");

        try
        {
            FileReader arq = new FileReader("C:/Users/moeda/Documents/unifesp/unifesp/sistemasDistribuidos/Seminario/src/main/resources/stickers.txt");
            BufferedReader lerArq = new BufferedReader(arq);
            String linha = lerArq.readLine(); // lê a primeira linha
            while (linha != null) 
            {
                String[] inf = linha.split("#");
                Stickers stickers = new Stickers();
                stickers.setIsBright(Boolean.valueOf(inf[2]));
                stickers.setStickerName(inf[1]);
                stickers.setStickerNumber(Long.valueOf(inf[0]));
                stickers.setAlbum(album);
                stickersBo.create(stickers);
                linha = lerArq.readLine(); // lê da segunda até a última linha
            }
            arq.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        PersonBo personBo = (PersonBo)appContext.getBean("personBo");
        Person ronaldo = new Person();
        ronaldo.setNickname("Roohm");
        ronaldo.setPersonName("Ronaldo Henrique Mizael dos Santos");

        Person rafael = new Person();
        rafael.setNickname("FormigaPagodeira");
        rafael.setPersonName("Rafael Ventura");
        personBo.create(ronaldo);
        personBo.create(rafael);
    }
}
