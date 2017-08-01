#ifndef IRESOURCEITEM_H
#define IRESOURCEITEM_H

class IResourceItem
{
public:
    virtual int resourceInitialize() = 0;
    virtual int resourceUnInitialize() = 0;
};

#endif // IRESOURCEITEM_H
