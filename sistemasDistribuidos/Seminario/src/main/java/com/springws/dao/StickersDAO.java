package com.springws.dao;

import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import com.springws.model.Stickers;

public class StickersDAO extends HibernateDaoSupport
{
    public void create(Stickers pSticker)
    {
        getHibernateTemplate().save(pSticker);
    }
}
