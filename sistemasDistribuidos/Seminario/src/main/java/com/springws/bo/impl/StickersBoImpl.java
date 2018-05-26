package com.springws.bo.impl;

import com.springws.bo.StickersBo;
import com.springws.dao.StickersDAO;
import com.springws.model.Stickers;

public class StickersBoImpl implements StickersBo
{

    StickersDAO stickersDao;
    
    public void setStickersDao(StickersDAO pStickersDao) 
    {
        this.stickersDao = pStickersDao;
    }
    
    @Override
    public void create(Stickers pStickers)
    {
        stickersDao.create(pStickers);
    }

}
