package com.springws.model;

import java.io.Serializable;

public class Album implements Serializable
{
    private Long albumId;
    private String albumName;
    private static final long serialVersionUID = 1L;

    public Long getAlbumId()
    {
        return albumId;
    }
    public void setAlbumId(Long albumId)
    {
        this.albumId = albumId;
    }
    public String getAlbumName()
    {
        return albumName;
    }
    public void setAlbumName(String albumName)
    {
        this.albumName = albumName;
    }
   
}
