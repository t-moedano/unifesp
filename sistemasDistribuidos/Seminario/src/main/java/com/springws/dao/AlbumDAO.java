package com.springws.dao;

import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import com.springws.model.Album;

public class AlbumDAO extends HibernateDaoSupport
{
    public void create(Album pAlbum)
    {
        getHibernateTemplate().save(pAlbum);
    }
}
