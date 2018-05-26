package com.springws.model;

import java.io.Serializable;
import java.util.List;

public class StickerToPerson implements Serializable
{

    Person person;
    Album album;
    Stickers stickers;
    Long quantity;
    
    private static final long serialVersionUID = 1L;

    public Person getPerson()
    {
        return person;
    }

    public void setPerson(Person person)
    {
        this.person = person;
    }

    public Album getAlbum()
    {
        return album;
    }

    public void setAlbum(Album album)
    {
        this.album = album;
    }

    public Stickers getStickers()
    {
        return stickers;
    }

    public void setStickers(Stickers stickers)
    {
        this.stickers = stickers;
    }

    public Long getQuantity()
    {
        return quantity;
    }

    public void setQuantity(Long quantity)
    {
        this.quantity = quantity;
    }
}
