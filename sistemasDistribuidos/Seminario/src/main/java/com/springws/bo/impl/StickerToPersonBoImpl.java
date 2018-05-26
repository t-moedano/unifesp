package com.springws.bo.impl;

import com.springws.bo.StickerToPersonBo;
import com.springws.dao.StickerToPersonDAO;
import com.springws.model.StickerToPerson;

public class StickerToPersonBoImpl implements StickerToPersonBo
{

    StickerToPersonDAO stickerToPersonDAO;

    public void setStickerToPersonDao(StickerToPersonDAO pStickerToPersonDao) 
    {
        this.stickerToPersonDAO = pStickerToPersonDao;
    }
    
    @Override
    public void create(StickerToPerson pStickerToPerson)
    {
        stickerToPersonDAO.create(pStickerToPerson);
    }

}
