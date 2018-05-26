package com.springws.bo.impl;

import com.springws.bo.AlbumBo;
import com.springws.dao.AlbumDAO;
import com.springws.model.Album;

public class AlbumBoImpl implements AlbumBo
{

    AlbumDAO albumDao;
    
    public void setAlbumDao(AlbumDAO pAlbumDAO) {
        this.albumDao = pAlbumDAO;
    }
    
    @Override
    public void create(Album pAlbum)
    {
        albumDao.create(pAlbum);
    }

}
