package com.springws.model;

public class Stickers
{

    private Long stickerId;
    private String stickerName;
    private Album album;
    private Boolean isBright;
    private Long stickerNumber;

    private static final long serialVersionUID = 1L;

    public Long getStickerId()
    {
        return stickerId;
    }

    public void setStickerId(Long stickerId)
    {
        this.stickerId = stickerId;
    }

    public String getStickerName()
    {
        return stickerName;
    }

    public void setStickerName(String stickerName)
    {
        this.stickerName = stickerName;
    }

    public Album getAlbum()
    {
        return album;
    }

    public void setAlbum(Album album)
    {
        this.album = album;
    }

    public Boolean getIsBright()
    {
        return isBright;
    }

    public void setIsBright(Boolean isBright)
    {
        this.isBright = isBright;
    }

    public Long getStickerNumber()
    {
        return stickerNumber;
    }

    public void setStickerNumber(Long stickerNumber)
    {
        this.stickerNumber = stickerNumber;
    }

}
