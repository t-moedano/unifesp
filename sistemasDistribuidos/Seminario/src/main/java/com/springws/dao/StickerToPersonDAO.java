package com.springws.dao;

import java.util.ArrayList;
import java.util.List;

import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Restrictions;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import com.springws.model.StickerToPerson;

public class StickerToPersonDAO extends HibernateDaoSupport
{
    public void create(StickerToPerson pStickerToPerson)
    {
        getHibernateTemplate().save(pStickerToPerson);
    }

    public List<StickerToPerson> getRepetidas(Long personId)
    {
       List stickerToPerson =
               getHibernateTemplate().findByCriteria(DetachedCriteria.forClass(StickerToPerson.class)
                .add(Restrictions.eq("PERSON_ID",  personId)));
       
       List<StickerToPerson> stickerToPersonList = new ArrayList<>();
       List<StickerToPerson> sList = new ArrayList<>();
       sList.addAll(stickerToPerson);
       for(StickerToPerson s : sList)
       {
           if(s.getQuantity() > 1L)
           {
               stickerToPersonList.add(s);
           }
       }
       
       return stickerToPersonList;
    }
}
